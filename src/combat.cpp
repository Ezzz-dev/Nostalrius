/**
 * Tibia GIMUD Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2017  Alejandro Mujica <alejandrodemujica@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "otpch.h"

#include "combat.h"

#include "game.h"
#include "configmanager.h"
#include "monster.h"

extern Game g_game;
extern ConfigManager g_config;

CombatDamage Combat::getCombatDamage(Creature* creature) const
{
	CombatDamage damage;
	damage.type = params.combatType;
	if (formulaType == COMBAT_FORMULA_DAMAGE) {
		damage.min = static_cast<int32_t>(mina);
		damage.max = static_cast<int32_t>(maxa);
	} else if (creature) {
		int32_t min, max;
		if (creature->getCombatValues(min, max)) {
			damage.min = min;
			damage.max = max;
		} else if (Player* player = creature->getPlayer()) {
			if (params.valueCallback) {
				params.valueCallback->getMinMaxValues(player, damage, params.useCharges);
			}
		}
	}
	return damage;
}

void Combat::getCombatArea(const Position& centerPos, const Position& targetPos, const AreaCombat* area, std::forward_list<Tile*>& list)
{
	if (targetPos.z >= MAP_MAX_LAYERS) {
		return;
	}

	if (area) {
		area->getList(centerPos, targetPos, list);
	} else {
		Tile* tile = g_game.map.getTile(targetPos);
		if (!tile) {
			tile = new StaticTile(targetPos.x, targetPos.y, targetPos.z);
			g_game.map.setTile(targetPos, tile);
		}
		list.push_front(tile);
	}
}

CombatType_t Combat::ConditionToDamageType(ConditionType_t type)
{
	switch (type) {
		case CONDITION_FIRE:
			return COMBAT_FIREDAMAGE;

		case CONDITION_ENERGY:
			return COMBAT_ENERGYDAMAGE;

		case CONDITION_POISON:
			return COMBAT_EARTHDAMAGE;

		default:
			break;
	}

	return COMBAT_NONE;
}

ConditionType_t Combat::DamageToConditionType(CombatType_t type)
{
	switch (type) {
		case COMBAT_FIREDAMAGE:
			return CONDITION_FIRE;

		case COMBAT_ENERGYDAMAGE:
			return CONDITION_ENERGY;

		case COMBAT_EARTHDAMAGE:
			return CONDITION_POISON;

		default:
			return CONDITION_NONE;
	}
}

bool Combat::isPlayerCombat(const Creature* target)
{
	if (target->getPlayer()) {
		return true;
	}

	if (target->isSummon() && target->getMaster()->getPlayer()) {
		return true;
	}

	return false;
}

ReturnValue Combat::canTargetCreature(Player* player, Creature* target)
{
	if (player == target) {
		return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
	}

	if (!player->hasFlag(PlayerFlag_IgnoreProtectionZone)) {
		//pz-zone
		if (player->getZone() == ZONE_PROTECTION) {
			return RETURNVALUE_YOUMAYNOTATTACKAPERSONWHILEINPROTECTIONZONE;
		}

		if (target->getZone() == ZONE_PROTECTION) {
			return RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE;
		}

		//nopvp-zone
		if (isPlayerCombat(target)) {
			if (player->getZone() == ZONE_NOPVP) {
				return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
			}

			if (target->getZone() == ZONE_NOPVP) {
				return RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE;
			}
		}
	}

	if (player->hasFlag(PlayerFlag_CannotUseCombat) || !target->isAttackable()) {
		if (target->getPlayer()) {
			return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
		} else {
			return RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE;
		}
	}

	if (target->getPlayer()) {
		if (isProtected(player, target->getPlayer())) {
			return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
		}

		if (player->hasSecureMode() && !Combat::isInPvpZone(player, target) && player->getSkullClient(target->getPlayer()) == SKULL_NONE) {
			return RETURNVALUE_TURNSECUREMODETOATTACKUNMARKEDPLAYERS;
		}
	}

	return Combat::canDoCombat(player, target);
}

ReturnValue Combat::canDoCombat(Creature* caster, Tile* tile, bool aggressive)
{
	if (tile->hasProperty(CONST_PROP_BLOCKPROJECTILE)) {
		return RETURNVALUE_NOTENOUGHROOM;
	}

	if (tile->hasProperty(CONST_PROP_BLOCKPROJECTILE) && tile->hasProperty(CONST_PROP_IMMOVABLEBLOCKSOLID)) {
		return RETURNVALUE_NOTENOUGHROOM;
	}

	if (tile->hasProperty(CONST_PROP_IMMOVABLEBLOCKSOLID) && tile->hasProperty(CONST_PROP_UNLAY)) {
		return RETURNVALUE_NOTENOUGHROOM;
	}

	if (tile->getTeleportItem()) {
		return RETURNVALUE_NOTENOUGHROOM;
	}

	if (caster) {
		const Position& casterPosition = caster->getPosition();
		const Position& tilePosition = tile->getPosition();
		if (casterPosition.z < tilePosition.z) {
			return RETURNVALUE_FIRSTGODOWNSTAIRS;
		} else if (casterPosition.z > tilePosition.z) {
			return RETURNVALUE_FIRSTGOUPSTAIRS;
		}

		if (const Player* player = caster->getPlayer()) {
			if (player->hasFlag(PlayerFlag_IgnoreProtectionZone)) {
				return RETURNVALUE_NOERROR;
			}
		}
	}

	//pz-zone
	if (aggressive && tile->hasFlag(TILESTATE_PROTECTIONZONE)) {
		return RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE;
	}

	return RETURNVALUE_NOERROR;
}

bool Combat::isInPvpZone(const Creature* attacker, const Creature* target)
{
	return attacker->getZone() == ZONE_PVP && target->getZone() == ZONE_PVP;
}

bool Combat::isProtected(const Player* attacker, const Player* target)
{
	uint32_t protectionLevel = g_config.getNumber(ConfigManager::PROTECTION_LEVEL);
	if (target->getLevel() < protectionLevel || attacker->getLevel() < protectionLevel) {
		return true;
	}

	if (attacker->getVocationId() == VOCATION_NONE || target->getVocationId() == VOCATION_NONE) {
		return true;
	}

	return false;
}

ReturnValue Combat::canDoCombat(Creature* attacker, Creature* target)
{
	if (attacker) {
		if (const Player* targetPlayer = target->getPlayer()) {
			if (targetPlayer->hasFlag(PlayerFlag_CannotBeAttacked)) {
				return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
			}

			if (const Player* attackerPlayer = attacker->getPlayer()) {
				if (attackerPlayer->hasFlag(PlayerFlag_CannotAttackPlayer)) {
					return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
				}

				if (isProtected(attackerPlayer, targetPlayer)) {
					return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
				}

				//nopvp-zone
				const Tile* targetPlayerTile = targetPlayer->getTile();
				if (targetPlayerTile->hasFlag(TILESTATE_NOPVPZONE)) {
					return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
				} else if (attackerPlayer->getTile()->hasFlag(TILESTATE_NOPVPZONE) && !targetPlayerTile->hasFlag(TILESTATE_NOPVPZONE | TILESTATE_PROTECTIONZONE)) {
					return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
				}
			}

			if (attacker->isSummon()) {
				if (const Player* masterAttackerPlayer = attacker->getMaster()->getPlayer()) {
					if (masterAttackerPlayer->hasFlag(PlayerFlag_CannotAttackPlayer)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
					}

					if (targetPlayer->getTile()->hasFlag(TILESTATE_NOPVPZONE)) {
						return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
					}

					if (isProtected(masterAttackerPlayer, targetPlayer)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
					}
				}
			}
		} else if (target->getMonster()) {
			if (const Player* attackerPlayer = attacker->getPlayer()) {
				if (attackerPlayer->hasFlag(PlayerFlag_CannotAttackMonster)) {
					return RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE;
				}

				if (target->isSummon() && target->getMaster()->getPlayer() && target->getZone() == ZONE_NOPVP) {
					return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
				}
			}
		}

		if (g_game.getWorldType() == WORLD_TYPE_NO_PVP) {
			if (attacker->getPlayer() || (attacker->isSummon() && attacker->getMaster()->getPlayer())) {
				if (target->getPlayer()) {
					if (!isInPvpZone(attacker, target)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
					}
				}

				if (target->isSummon() && target->getMaster()->getPlayer()) {
					if (!isInPvpZone(attacker, target)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE;
					}
				}
			}
		}
	}
	return RETURNVALUE_NOERROR;
}

void Combat::setPlayerCombatValues(formulaType_t formulaType, double mina, double minb, double maxa, double maxb)
{
	this->formulaType = formulaType;
	this->mina = mina;
	this->minb = minb;
	this->maxa = maxa;
	this->maxb = maxb;
}

bool Combat::setParam(CombatParam_t param, uint32_t value)
{
	switch (param) {
		case COMBAT_PARAM_TYPE: {
			params.combatType = static_cast<CombatType_t>(value);
			return true;
		}

		case COMBAT_PARAM_EFFECT: {
			params.impactEffect = static_cast<uint8_t>(value);
			return true;
		}

		case COMBAT_PARAM_DISTANCEEFFECT: {
			params.distanceEffect = static_cast<uint8_t>(value);
			return true;
		}

		case COMBAT_PARAM_BLOCKARMOR: {
			params.blockedByArmor = (value != 0);
			return true;
		}

		case COMBAT_PARAM_BLOCKSHIELD: {
			params.blockedByShield = (value != 0);
			return true;
		}

		case COMBAT_PARAM_TARGETCASTERORTOPMOST: {
			params.targetCasterOrTopMost = (value != 0);
			return true;
		}

		case COMBAT_PARAM_CREATEITEM: {
			params.itemId = value;
			return true;
		}

		case COMBAT_PARAM_AGGRESSIVE: {
			params.aggressive = (value != 0);
			return true;
		}

		case COMBAT_PARAM_DISPEL: {
			params.dispelType = static_cast<ConditionType_t>(value);
			return true;
		}

		case COMBAT_PARAM_USECHARGES: {
			params.useCharges = (value != 0);
			return true;
		}

		case COMBAT_PARAM_DECREASEDAMAGE: {
			params.decreaseDamage = static_cast<uint16_t>(value);
			return true;
		}

		case COMBAT_PARAM_MAXIMUMDECREASEDDAMAGE: {
			params.maximumDecreasedDamage = static_cast<uint16_t>(value);
			return true;
		}
	}
	return false;
}

bool Combat::setCallback(CallBackParam_t key)
{
	switch (key) {
		case CALLBACK_PARAM_LEVELMAGICVALUE: {
			params.valueCallback.reset(new ValueCallback(COMBAT_FORMULA_LEVELMAGIC));
			return true;
		}

		case CALLBACK_PARAM_SKILLVALUE: {
			params.valueCallback.reset(new ValueCallback(COMBAT_FORMULA_SKILL));
			return true;
		}

		case CALLBACK_PARAM_TARGETTILE: {
			params.tileCallback.reset(new TileCallback());
			return true;
		}

		case CALLBACK_PARAM_TARGETCREATURE: {
			params.targetCallback.reset(new TargetCallback());
			return true;
		}
	}
	return false;
}

CallBack* Combat::getCallback(CallBackParam_t key)
{
	switch (key) {
		case CALLBACK_PARAM_LEVELMAGICVALUE:
		case CALLBACK_PARAM_SKILLVALUE: {
			return params.valueCallback.get();
		}

		case CALLBACK_PARAM_TARGETTILE: {
			return params.tileCallback.get();
		}

		case CALLBACK_PARAM_TARGETCREATURE: {
			return params.targetCallback.get();
		}
	}
	return nullptr;
}

bool Combat::CombatHealthFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data)
{
	assert(data);
	CombatDamage damage = *data;

	if (damage.value == 0) {
		damage.value = normal_random(damage.min, damage.max);
	}

	if (damage.value < 0 && caster) {
		Player* targetPlayer = target->getPlayer();
		if (targetPlayer && caster->getPlayer()) {
			damage.value /= 2;
		}
	}

	if (g_game.combatBlockHit(damage, caster, target, params.blockedByShield, params.blockedByArmor, params.itemId != 0)) {
		return false;
	}

	if (g_game.combatChangeHealth(caster, target, damage)) {
		CombatConditionFunc(caster, target, params, nullptr);
		CombatDispelFunc(caster, target, params, nullptr);
	}

	return true;
}

bool Combat::CombatManaFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data)
{
	assert(data);
	CombatDamage damage = *data;

	if (damage.value == 0) {
		damage.value = normal_random(damage.min, damage.max);
	}

	if (damage.value < 0) {
		if (caster && caster->getPlayer() && target->getPlayer()) {
			damage.value /= 2;
		}
	}

	if (g_game.combatChangeMana(caster, target, damage.value)) {
		CombatConditionFunc(caster, target, params, nullptr);
		CombatDispelFunc(caster, target, params, nullptr);
	}

	return true;
}

bool Combat::CombatConditionFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage*)
{
	for (const auto& condition : params.conditionList) {
		if (caster == target || !target->isImmune(condition->getType())) {
			Condition* conditionCopy = condition->clone();
			if (caster) {
				conditionCopy->setParam(CONDITION_PARAM_OWNER, caster->getID());
			}

			//TODO: infight condition until all aggressive conditions has ended
			target->addCombatCondition(conditionCopy);
		}
	}

	return true;
}

bool Combat::CombatDispelFunc(Creature*, Creature* target, const CombatParams& params, CombatDamage*)
{
	target->removeCombatCondition(params.dispelType);
	return true;
}

bool Combat::CombatNullFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage*)
{
	CombatConditionFunc(caster, target, params, nullptr);
	CombatDispelFunc(caster, target, params, nullptr);
	return true;
}

void Combat::combatTileEffects(const SpectatorVec& list, Creature* caster, Tile* tile, const CombatParams& params)
{
	if (params.itemId != 0) {
		uint16_t itemId = params.itemId;
		switch (itemId) {
			case ITEM_FIREFIELD_PERSISTENT_FULL:
				itemId = ITEM_FIREFIELD_PVP_FULL;
				break;

			case ITEM_FIREFIELD_PERSISTENT_MEDIUM:
				itemId = ITEM_FIREFIELD_PVP_MEDIUM;
				break;

			case ITEM_FIREFIELD_PERSISTENT_SMALL:
				itemId = ITEM_FIREFIELD_PVP_SMALL;
				break;

			case ITEM_ENERGYFIELD_PERSISTENT:
				itemId = ITEM_ENERGYFIELD_PVP;
				break;

			case ITEM_POISONFIELD_PERSISTENT:
				itemId = ITEM_POISONFIELD_PVP;
				break;

			case ITEM_MAGICWALL_PERSISTENT:
				itemId = ITEM_MAGICWALL;
				break;

			case ITEM_WILDGROWTH_PERSISTENT:
				itemId = ITEM_WILDGROWTH;
				break;

			default:
				break;
		}

		if (caster) {
			Player* casterPlayer;
			if (caster->isSummon()) {
				casterPlayer = caster->getMaster()->getPlayer();
			} else {
				casterPlayer = caster->getPlayer();
			}

			if (casterPlayer) {
				if (g_game.getWorldType() == WORLD_TYPE_NO_PVP || tile->hasFlag(TILESTATE_NOPVPZONE)) {
					if (itemId == ITEM_FIREFIELD_PVP_FULL) {
						itemId = ITEM_FIREFIELD_NOPVP;
					} else if (itemId == ITEM_POISONFIELD_PVP) {
						itemId = ITEM_POISONFIELD_NOPVP;
					} else if (itemId == ITEM_ENERGYFIELD_PVP) {
						itemId = ITEM_ENERGYFIELD_NOPVP;
					}
				} else if (itemId == ITEM_FIREFIELD_PVP_FULL || itemId == ITEM_POISONFIELD_PVP || itemId == ITEM_ENERGYFIELD_PVP) {
					casterPlayer->addInFightTicks();
				}
			}
		}

		Item* item = Item::CreateItem(itemId);
		if (caster) {
			item->setOwner(caster->getID());
		}

		ReturnValue ret = g_game.internalAddItem(tile, item);
		if (ret == RETURNVALUE_NOERROR) {
			g_game.startDecay(item);
		} else {
			delete item;
		}
	}

	if (params.tileCallback) {
		params.tileCallback->onTileCombat(caster, tile);
	}

	if (params.impactEffect != CONST_ME_NONE) {
		Game::addMagicEffect(list, tile->getPosition(), params.impactEffect);
	}
}

void Combat::postCombatEffects(Creature* caster, const Position& pos, const CombatParams& params)
{
	if (caster && params.distanceEffect != CONST_ANI_NONE) {
		addDistanceEffect(caster->getPosition(), pos, params.distanceEffect);
	}
}

void Combat::addDistanceEffect(const Position& fromPos, const Position& toPos, uint8_t effect)
{
	if (effect != CONST_ANI_NONE) {
		g_game.addDistanceEffect(fromPos, toPos, effect);
	}
}

void Combat::CombatFunc(Creature* caster, const Position& pos, const AreaCombat* area, const CombatParams& params, COMBATFUNC func, CombatDamage* data)
{
	std::forward_list<Tile*> tileList;

	if (caster) {
		getCombatArea(caster->getPosition(), pos, area, tileList);
	} else {
		getCombatArea(pos, pos, area, tileList);
	}

	SpectatorVec list;
	uint32_t maxX = 0;
	uint32_t maxY = 0;

	//calculate the max viewable range
	for (Tile* tile : tileList) {
		const Position& tilePos = tile->getPosition();

		uint32_t diff = Position::getDistanceX(tilePos, pos);
		if (diff > maxX) {
			maxX = diff;
		}

		diff = Position::getDistanceY(tilePos, pos);
		if (diff > maxY) {
			maxY = diff;
		}
	}

	const int32_t rangeX = maxX + Map::maxViewportX;
	const int32_t rangeY = maxY + Map::maxViewportY;
	g_game.map.getSpectators(list, pos, true, true, rangeX, rangeX, rangeY, rangeY);

	uint16_t decreasedDamage = 0;
	const uint16_t maximumDecreasedDamage = params.maximumDecreasedDamage;

	bool firstCreature = true;

	if (params.decreaseDamage && data) {
		for (Tile* tile : tileList) {
			if (canDoCombat(caster, tile, params.aggressive) != RETURNVALUE_NOERROR) {
				continue;
			}

			if (CreatureVector* creatures = tile->getCreatures()) {
				const Creature* topCreature = tile->getTopCreature();
				for (Creature* creature : *creatures) {
					if (params.targetCasterOrTopMost) {
						if (caster && caster->getTile() == tile) {
							if (creature != caster) {
								continue;
							}
						} else if (creature != topCreature) {
							continue;
						}
					}

					if (!params.aggressive || (caster != creature && Combat::canDoCombat(caster, creature) == RETURNVALUE_NOERROR)) {
						if (firstCreature) {
							firstCreature = false;
							continue;
						}

						// only apply to players
						if (creature->getPlayer()) {
							if (maximumDecreasedDamage && decreasedDamage >= maximumDecreasedDamage) {
								break;
							}

							decreasedDamage += params.decreaseDamage;
						}
					}
				}
			}
		}

		// actually decrease total damage output
		if (data->value == 0) {
			int32_t decreasedMinDamage = std::abs(data->min) * decreasedDamage / 100;
			int32_t decreasedMaxDamage = std::abs(data->max) * decreasedDamage / 100;

			if (data->min < 0) {
				// damaging spell, get as close as zero as we can get
				// do not allow healing values
				data->min += decreasedMinDamage;
				data->max += decreasedMaxDamage;

				data->min = std::min<int32_t>(0, data->min);
				data->max = std::min<int32_t>(0, data->max);
			} else {
				// healing spell, get as close as zero as we can get
				// do not allow damaging values
				data->min -= decreasedMinDamage;
				data->max -= decreasedMaxDamage;

				data->min = std::max<int32_t>(0, data->min);
				data->max = std::max<int32_t>(0, data->max);
			}
		} else {
			int32_t decreasedValue = (std::abs(data->value) * decreasedDamage) / 100;

			if (data->value < 0) {
				// damaging spell, get as close as zero as we can get
				// do not allow healing values
				data->value += decreasedValue;

				data->value = std::min<int32_t>(0, data->value);
			} else {
				// healing spell, get as close as zero as we can get
				// do not allow damaging values
				data->value -= decreasedValue;

				data->value = std::max<int32_t>(0, data->value);
			}
		}
	}

	for (Tile* tile : tileList) {
		if (canDoCombat(caster, tile, params.aggressive) != RETURNVALUE_NOERROR) {
			continue;
		}

		if (CreatureVector* creatures = tile->getCreatures()) {
			const Creature* topCreature = tile->getTopCreature();
			for (Creature* creature : *creatures) {
				if (params.targetCasterOrTopMost) {
					if (caster && caster->getTile() == tile) {
						if (creature != caster) {
							continue;
						}
					} else if (creature != topCreature) {
						continue;
					}
				}

				if (!params.aggressive || (caster != creature && Combat::canDoCombat(caster, creature) == RETURNVALUE_NOERROR)) {
					func(caster, creature, params, data);
					if (params.targetCallback) {
						params.targetCallback->onTargetCombat(caster, creature);
					}

					if (params.targetCasterOrTopMost) {
						break;
					}
				}
			}
		}
		combatTileEffects(list, caster, tile, params);
	}
	postCombatEffects(caster, pos, params);
}

void Combat::doCombat(Creature* caster, Creature* target) const
{
	//target combat callback function
	if (params.combatType != COMBAT_NONE) {
		CombatDamage damage = getCombatDamage(caster);
		if (damage.type != COMBAT_MANADRAIN) {
			doCombatHealth(caster, target, damage, params);
		} else {
			doCombatMana(caster, target, damage, params);
		}
	} else {
		doCombatDefault(caster, target, params);
	}
}

void Combat::doCombat(Creature* caster, const Position& position) const
{
	//area combat callback function
	if (params.combatType != COMBAT_NONE) {
		CombatDamage damage = getCombatDamage(caster);
		if (damage.type != COMBAT_MANADRAIN) {
			doCombatHealth(caster, position, area.get(), damage, params);
		} else {
			doCombatMana(caster, position, area.get(), damage, params);
		}
	} else {
		CombatFunc(caster, position, area.get(), params, CombatNullFunc, nullptr);
	}
}

int32_t Combat::computeDamage(Creature* creature, int32_t strength, int32_t variation)
{
	int32_t damage = strength;
	if (variation) {
		damage = normal_random(-variation, variation) + strength;
	}

	if (creature) {
		if (Player* player = creature->getPlayer()) {
			int32_t formula = 3 * player->getMagicLevel() + 2 * player->getLevel();
			damage = formula * damage / 100;
		}
	}

	return damage;
}

int32_t Combat::getTotalDamage(int32_t attackSkill, int32_t attackValue, fightMode_t fightMode)
{
	int32_t damage = attackValue;

	switch (fightMode) {
		case FIGHTMODE_ATTACK:
			damage += 2 * damage / 10;
			break;
		case FIGHTMODE_DEFENSE:
			damage -= 4 * damage / 10;
			break;
		default: break;
	}

	int32_t formula = (5 * (attackSkill) + 50) * damage;
	int32_t randresult = rand() % 100;
	int32_t totalDamage = -(ceil(formula * ((rand() % 100 + randresult) / 2) / 10000.));
	return totalDamage;
}

bool Combat::attack(Creature* attacker, Creature* target)
{
	if (Player* player = attacker->getPlayer()) {
		Item* weapon = player->getWeapon();
		if (weapon) {
			if (weapon->getWeaponType() == WEAPON_DISTANCE || weapon->getWeaponType() == WEAPON_WAND) {
				return rangeAttack(attacker, target, player->getFightMode());
			}
		}
		
		return closeAttack(attacker, target, player->getFightMode());
	}

	return false;
}

bool Combat::closeAttack(Creature* attacker, Creature* target, fightMode_t fightMode)
{
	const Position& attackerPos = attacker->getPosition();
	const Position& targetPos = target->getPosition();
	if (attackerPos.z != targetPos.z) {
		return false;
	}

	if (std::max<uint32_t>(Position::getDistanceX(attackerPos, targetPos), Position::getDistanceY(attackerPos, targetPos)) > 1) {
		return false;
	}

	Item* weapon = nullptr;

	if (Player* player = attacker->getPlayer()) {
		weapon = player->getWeapon();
		if (weapon && !Combat::canUseWeapon(player, weapon)) {
			return false;
		}
	}

	uint32_t attackValue = 0;
	uint32_t skillValue = 0;
	uint8_t skill = SKILL_FIST;

	Combat::getAttackValue(attacker, attackValue, skillValue, skill);

	int32_t defense = target->getDefense();

	if (OTSYS_TIME() < target->earliestDefendTime) {
		defense = 0;
	}

	CombatParams combatParams;
	combatParams.blockedByArmor = true;
	combatParams.blockedByShield = true;
	combatParams.combatType = COMBAT_PHYSICALDAMAGE;
	
	CombatDamage combatDamage;
	combatDamage.type = combatParams.combatType;
	int32_t totalDamage = Combat::getTotalDamage(skillValue, attackValue, fightMode);
	combatDamage.value = totalDamage;

	bool hit = Combat::doCombatHealth(attacker, target, combatDamage, combatParams);

	if (Monster* monster = attacker->getMonster()) {
		int32_t poison = monster->mType->info.poison;
		if (poison) {
			int32_t randTest = rand();

			if (hit || -totalDamage > defense && (randTest == 5 * (randTest / 5))) {
				poison = normal_random(poison / 2, poison);
				if (poison) {
					ConditionDamage* condition = static_cast<ConditionDamage*>(Condition::createCondition(CONDITIONID_COMBAT, CONDITION_POISON, 0, 0));
					condition->setParam(CONDITION_PARAM_OWNER, attacker->getID());
					condition->setParam(CONDITION_PARAM_CYCLE, poison);
					condition->setParam(CONDITION_PARAM_COUNT, 3);
					condition->setParam(CONDITION_PARAM_MAX_COUNT, 3);
					target->addCombatCondition(condition);
				}
			}
		}
	}

	if (Player* player = attacker->getPlayer()) {
		// skills advancing
		if (!player->hasFlag(PlayerFlag_NotGainSkill)) {
			if (player->getAddAttackSkill() && player->getLastAttackBlockType() != BLOCK_IMMUNITY) {
				player->addSkillAdvance(static_cast<skills_t>(skill), 1);
			}
		}

		// weapon 
		if (weapon) {
			if (weapon->getCharges() > 0) {
				int32_t charges = weapon->getCharges() - 1;
				if (charges <= 0) {
					g_game.internalRemoveItem(weapon);
				} else {
					g_game.transformItem(weapon, weapon->getID(), charges);
				}
			}
		}
	}

	if (Player* player = attacker->getPlayer()) {
		Combat::postWeaponEffects(player, weapon);
	}

	return true;
}

bool Combat::rangeAttack(Creature* attacker, Creature* target, fightMode_t fightMode)
{
	const Position& attackerPos = attacker->getPosition();
	const Position& targetPos = target->getPosition();
	if (attackerPos.z != targetPos.z) {
		return false;
	}

	uint8_t range = 0;
	uint8_t hitChance = 0;
	uint8_t distanceEffect = 0;
	uint8_t specialEffect = 0;
	int32_t attackStrength = 0;
	int32_t attackVariation = 0;

	Item* weapon = nullptr;
	Item* ammunition = nullptr;

	bool moveWeapon = true;

	if (Player* player = attacker->getPlayer()) {
		weapon = player->getWeapon();
		if (!weapon) {
			return false;
		}

		if (!Combat::canUseWeapon(player, weapon)) {
			return false;
		}

		range = weapon->getShootRange();
		distanceEffect = weapon->getMissileType();

		if (weapon->getWeaponType() == WEAPON_DISTANCE) {
			ammunition = player->getAmmunition();
			if (weapon->getAmmoType() != AMMO_NONE) {
				if (!ammunition || weapon->getAmmoType() != ammunition->getAmmoType()) {
					// redirect to fist fighting
					return closeAttack(attacker, target, fightMode);
				}

				distanceEffect = ammunition->getMissileType();
			}
		}
	}

	if (std::max<uint32_t>(Position::getDistanceX(attackerPos, targetPos), Position::getDistanceY(attackerPos, targetPos)) > range) {
		return false;
	}

	if (weapon->getWeaponType() == WEAPON_DISTANCE) {
		uint32_t attackValue = 0;
		uint32_t skillValue = 0;
		uint8_t skill = SKILL_FIST;

		Combat::getAttackValue(attacker, attackValue, skillValue, skill);

		CombatParams combatParams;
		combatParams.blockedByArmor = true;
		combatParams.blockedByShield = false;
		combatParams.combatType = COMBAT_PHYSICALDAMAGE;

		CombatDamage combatDamage;
		combatDamage.type = combatParams.combatType;
		combatDamage.value = Combat::getTotalDamage(skillValue, attackValue, fightMode);

		if (weapon) {
			hitChance = 75; // throwables and such
			specialEffect = weapon->getWeaponSpecialEffect();
			attackStrength = weapon->getAttackStrength();
			attackVariation = weapon->getAttackVariation();
			if (weapon->getFragility()) {
				if (normal_random(0, 99) <= weapon->getFragility()) {
					uint16_t count = weapon->getItemCount();
					if (count > 1) {
						g_game.transformItem(weapon, weapon->getID(), count - 1);
					} else {
						g_game.internalRemoveItem(weapon);
					}

					moveWeapon = false;
				}
			}
		}

		if (ammunition && weapon->getAmmoType() != AMMO_NONE && weapon->getAmmoType() == ammunition->getAmmoType()) {
			hitChance = 90; // bows and crossbows
			specialEffect = ammunition->getWeaponSpecialEffect();
			attackStrength = ammunition->getAttackStrength();
			attackVariation = ammunition->getAttackVariation();
			if (normal_random(0, 100) <= ammunition->getFragility()) {
				uint16_t count = ammunition->getItemCount();
				if (count > 1) {
					g_game.transformItem(ammunition, ammunition->getID(), count - 1);
				} else {
					g_game.internalRemoveItem(ammunition);
				}
			}

			moveWeapon = false;
		}

		int32_t distance = std::max<uint32_t>(Position::getDistanceX(attackerPos, targetPos), Position::getDistanceY(attackerPos, targetPos));
		if (distance <= 1) {
			distance = 5;
		}

		distance *= 15;

		bool hit = false;

		if (rand() % distance <= skillValue) {
			hit = rand() % 100 <= hitChance;
		}

		if (Player* player = attacker->getPlayer()) {
			if (player->getAddAttackSkill()) {
				switch (player->getLastAttackBlockType()) {
					case BLOCK_NONE: {
						player->addSkillAdvance(SKILL_DISTANCE, 2);
						break;
					}

					case BLOCK_DEFENSE:
					case BLOCK_ARMOR: {
						player->addSkillAdvance(SKILL_DISTANCE, 1);
						break;
					}

					default: break;
				}
			}
		}

		if (specialEffect == 1) {
			if (hit) {
				const int32_t rounds = ammunition ? ammunition->getAttackStrength() : weapon->getAttackStrength();

				ConditionDamage* poisonDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_POISON);
				poisonDamage->setParam(CONDITION_PARAM_OWNER, attacker->getID());
				poisonDamage->setParam(CONDITION_PARAM_CYCLE, rounds);
				poisonDamage->setParam(CONDITION_PARAM_COUNT, 3);
				poisonDamage->setParam(CONDITION_PARAM_MAX_COUNT, 3);

				target->addCombatCondition(poisonDamage);
			}
		} else if (specialEffect == 2) {
			DamageImpact impact;
			impact.actor = attacker;
			impact.damage.type = COMBAT_PHYSICALDAMAGE;
			impact.damage.value = -Combat::computeDamage(attacker, attackStrength, attackVariation);
			impact.params.blockedByArmor = true;
			impact.params.blockedByShield = false;
			circleShapeSpell(attacker, target->getPosition(), 0xFF, 0, 3, &impact, 7);
		}

		if (!hit) {
			Tile* destTile = target->getTile();

			if (!Position::areInRange<1, 1, 0>(attacker->getPosition(), target->getPosition())) {
				static std::vector<std::pair<int32_t, int32_t>> destList{
					{ -1, -1 },{ 0, -1 },{ 1, -1 },
					{ -1,  0 },{ 0,  0 },{ 1,  0 },
					{ -1,  1 },{ 0,  1 },{ 1,  1 }
				};
				std::shuffle(destList.begin(), destList.end(), getRandomGenerator());

				Position destPos = target->getPosition();

				for (const auto& dir : destList) {
					// Blocking tiles or tiles without ground ain't valid targets for spears
					Tile* tmpTile = g_game.map.getTile(destPos.x + dir.first, destPos.y + dir.second, destPos.z);
					if (tmpTile && !tmpTile->hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID) && tmpTile->getGround() != nullptr) {
						destTile = tmpTile;
						break;
					}
				}
			}

			g_game.addMagicEffect(destTile->getPosition(), CONST_ME_POFF);
			g_game.addDistanceEffect(attackerPos, destTile->getPosition(), distanceEffect);

			if (moveWeapon) {
				g_game.internalMoveItem(weapon->getParent(), destTile, INDEX_WHEREEVER, weapon, 1, nullptr, FLAG_NOLIMIT);
			}

			return true;
		}

		g_game.addDistanceEffect(attackerPos, targetPos, distanceEffect);
		Combat::doCombatHealth(attacker, target, combatDamage, combatParams);

		if (moveWeapon) {
			g_game.internalMoveItem(weapon->getParent(), target->getTile(), INDEX_WHEREEVER, weapon, 1, nullptr, FLAG_NOLIMIT);
		}
	} else if (weapon->getWeaponType() == WEAPON_WAND) {
		int32_t variation = normal_random(-weapon->getAttackVariation(), weapon->getAttackVariation());

		CombatParams combatParams;
		combatParams.combatType = weapon->getDamageType();

		CombatDamage combatDamage;
		combatDamage.type = combatParams.combatType;
		combatDamage.value = -(variation + weapon->getAttackStrength());

		g_game.addDistanceEffect(attackerPos, targetPos, distanceEffect);
		Combat::doCombatHealth(attacker, target, combatDamage, combatParams);
	}

	if (Player* player = attacker->getPlayer()) {
		Combat::postWeaponEffects(player, weapon);
	}

	return true;
}

void Combat::circleShapeSpell(Creature* attacker, const Position& toPos, int32_t range, int32_t animation, int32_t radius, DamageImpact* impact, int32_t effect)
{
	const Position& fromPos = attacker->getPosition();
	if (fromPos.z != toPos.z) {
		return;
	}

	int32_t distance = std::max<int32_t>(Position::getDistanceX(fromPos, toPos), Position::getDistanceY(fromPos, toPos));
	if (distance > range) {
		return;
	}

	if (animation && fromPos != toPos) {
		g_game.addDistanceEffect(fromPos, toPos, animation);
	}

	std::forward_list<Tile*> tiles;

	AreaCombat areaCombat;
	areaCombat.setupArea(radius);

	areaCombat.getList(toPos, toPos, tiles);

	for (Tile* tile : tiles) {
		if (tile->hasFlag(TILESTATE_PROTECTIONZONE)) {
			continue;
		}

		if (CreatureVector* creatures = tile->getCreatures()) {
			for (Creature* creature : *creatures) {
				impact->handleCreature(creature);
			}
		}

		if (effect) {
			g_game.addMagicEffect(tile->getPosition(), effect);
		}
	}
}

void Combat::getAttackValue(Creature* creature, uint32_t& attackValue, uint32_t& skillValue, uint8_t& skill)
{
	skill = SKILL_FIST;

	if (Player* player = creature->getPlayer()) {
		Item* weapon = player->getWeapon();
		if (weapon) {
			switch (weapon->getWeaponType()) {
			case WEAPON_AXE: {
				skill = SKILL_AXE;
				attackValue = weapon->getAttack();
				break;
			}
			case WEAPON_SWORD: {
				skill = SKILL_SWORD;
				attackValue = weapon->getAttack();
				break;
			}
			case WEAPON_CLUB: {
				skill = SKILL_CLUB;
				attackValue = weapon->getAttack();
				break;
			}
			case WEAPON_DISTANCE: {
				skill = SKILL_DISTANCE;
				attackValue = weapon->getAttack();

				if (weapon->getAmmoType() != AMMO_NONE) {
					Item* ammunition = player->getAmmunition();
					if (ammunition && ammunition->getAmmoType() == weapon->getAmmoType()) {
						attackValue += ammunition->getAttack();
					}
				}
				break;
			}
			default:
				attackValue = 7;
				break;
			}

			skillValue = player->getSkillLevel(skill);
		} else {
			attackValue = 7;
			skillValue = player->getSkillLevel(skill);
		}
	} else if (Monster* monster = creature->getMonster()) {
		attackValue = monster->mType->info.attack;
		skillValue = monster->mType->info.skill;
	}
}

bool Combat::canUseWeapon(Player* player, Item* weapon)
{
	if (player->hasFlag(PlayerFlag_IgnoreWeaponCheck)) {
		return true;
	}

	if (player->getLevel() < weapon->getMinimumLevel()) {
		return false;
	}

	if (!player->hasFlag(PlayerFlag_HasInfiniteMana) && player->getMana() < weapon->getManaConsumption()) {
		return false;
	}

	const ItemType& itemType = Item::items[weapon->getID()];
	if (hasBitSet(WIELDINFO_VOCREQ, itemType.wieldInfo)) {
		if (!hasBitSet(player->getVocationFlagId(), itemType.vocations)) {
			return false;
		}
	}

	return true;
}

void Combat::postWeaponEffects(Player* player, Item* weapon)
{
	if (!weapon || player->hasFlag(PlayerFlag_IgnoreWeaponCheck)) {
		return;
	}

	int32_t manaConsumption = weapon->getManaConsumption();
	if (manaConsumption) {
		player->addManaSpent(manaConsumption);
		player->changeMana(-manaConsumption);
	}
}

bool Combat::doCombatHealth(Creature* caster, Creature* target, CombatDamage& damage, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		canCombat = CombatHealthFunc(caster, target, params, &damage);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}

	return canCombat;
}

void Combat::doCombatHealth(Creature* caster, const Position& position, const AreaCombat* area, CombatDamage& damage, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatHealthFunc, &damage);
}

void Combat::doCombatMana(Creature* caster, Creature* target, CombatDamage& damage, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		CombatManaFunc(caster, target, params, &damage);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

void Combat::doCombatMana(Creature* caster, const Position& position, const AreaCombat* area, CombatDamage& damage, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatManaFunc, &damage);
}

void Combat::doCombatCondition(Creature* caster, const Position& position, const AreaCombat* area, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatConditionFunc, nullptr);
}

void Combat::doCombatCondition(Creature* caster, Creature* target, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		CombatConditionFunc(caster, target, params, nullptr);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

void Combat::doCombatDispel(Creature* caster, const Position& position, const AreaCombat* area, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatDispelFunc, nullptr);
}

void Combat::doCombatDispel(Creature* caster, Creature* target, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		CombatDispelFunc(caster, target, params, nullptr);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

void Combat::doCombatDefault(Creature* caster, Creature* target, const CombatParams& params)
{
	if (!params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR)) {
		SpectatorVec list;
		g_game.map.getSpectators(list, target->getPosition(), true, true);

		CombatNullFunc(caster, target, params, nullptr);
		combatTileEffects(list, caster, target->getTile(), params);

		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		/*
		if (params.impactEffect != CONST_ME_NONE) {
			g_game.addMagicEffect(target->getPosition(), params.impactEffect);
		}
		*/

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

//**********************************************************//

void ValueCallback::getMinMaxValues(Player* player, CombatDamage& damage, bool useCharges) const
{
	//onGetPlayerMinMaxValues(...)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - ValueCallback::getMinMaxValues] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	if (!env->setCallbackId(scriptId, scriptInterface)) {
		scriptInterface->resetScriptEnv();
		return;
	}

	lua_State* L = scriptInterface->getLuaState();

	scriptInterface->pushFunction(scriptId);

	LuaScriptInterface::pushUserdata<Player>(L, player);
	LuaScriptInterface::setMetatable(L, -1, "Player");

	int parameters = 1;
	switch (type) {
		case COMBAT_FORMULA_LEVELMAGIC: {
			//onGetPlayerMinMaxValues(player, level, maglevel)
			lua_pushnumber(L, player->getLevel());
			lua_pushnumber(L, player->getMagicLevel());
			parameters += 2;
			break;
		}

		case COMBAT_FORMULA_SKILL: {
			//onGetPlayerMinMaxValues(player, attackSkill, attackValue, fightMode)
			uint32_t attackValue = 7;
			uint32_t attackSkill = 0;
			uint8_t skill = 0;

			Combat::getAttackValue(player, attackValue, attackSkill, skill);

			Item* weapon = player->getWeapon();
			if (useCharges && weapon) {
				const ItemType& itemType = Item::items.getItemType(weapon->getID());
				if (itemType.charges) {
					int32_t newCount = std::max<int32_t>(0, weapon->getCharges() - 1);
					if (newCount <= 0) {
						g_game.internalRemoveItem(weapon);
					} else {
						g_game.transformItem(weapon, weapon->getID(), newCount);
					}
				}
			}

			lua_pushnumber(L, attackSkill);
			lua_pushnumber(L, attackValue);
			lua_pushnumber(L, player->getFightMode());
			parameters += 3;
			break;
		}

		default: {
			std::cout << "ValueCallback::getMinMaxValues - unknown callback type" << std::endl;
			scriptInterface->resetScriptEnv();
			return;
		}
	}

	int size0 = lua_gettop(L);
	if (lua_pcall(L, parameters, 2, 0) != 0) {
		LuaScriptInterface::reportError(nullptr, LuaScriptInterface::popString(L));
	} else {
		damage.min = LuaScriptInterface::getNumber<int32_t>(L, -2);
		damage.max = LuaScriptInterface::getNumber<int32_t>(L, -1);
		lua_pop(L, 2);
	}

	if ((lua_gettop(L) + parameters + 1) != size0) {
		LuaScriptInterface::reportError(nullptr, "Stack size changed!");
	}

	scriptInterface->resetScriptEnv();
}

//**********************************************************//

void TileCallback::onTileCombat(Creature* creature, Tile* tile) const
{
	//onTileCombat(creature, pos)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - TileCallback::onTileCombat] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	if (!env->setCallbackId(scriptId, scriptInterface)) {
		scriptInterface->resetScriptEnv();
		return;
	}

	lua_State* L = scriptInterface->getLuaState();

	scriptInterface->pushFunction(scriptId);
	if (creature) {
		LuaScriptInterface::pushUserdata<Creature>(L, creature);
		LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	} else {
		lua_pushnil(L);
	}
	LuaScriptInterface::pushPosition(L, tile->getPosition());

	scriptInterface->callFunction(2);
}

//**********************************************************//

void TargetCallback::onTargetCombat(Creature* creature, Creature* target) const
{
	//onTargetCombat(creature, target)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - TargetCallback::onTargetCombat] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	if (!env->setCallbackId(scriptId, scriptInterface)) {
		scriptInterface->resetScriptEnv();
		return;
	}

	lua_State* L = scriptInterface->getLuaState();

	scriptInterface->pushFunction(scriptId);

	if (creature) {
		LuaScriptInterface::pushUserdata<Creature>(L, creature);
		LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	} else {
		lua_pushnil(L);
	}

	if (target) {
		LuaScriptInterface::pushUserdata<Creature>(L, target);
		LuaScriptInterface::setCreatureMetatable(L, -1, target);
	} else {
		lua_pushnil(L);
	}

	int size0 = lua_gettop(L);

	if (lua_pcall(L, 2, 0 /*nReturnValues*/, 0) != 0) {
		LuaScriptInterface::reportError(nullptr, LuaScriptInterface::popString(L));
	}

	if ((lua_gettop(L) + 2 /*nParams*/ + 1) != size0) {
		LuaScriptInterface::reportError(nullptr, "Stack size changed!");
	}

	scriptInterface->resetScriptEnv();
}

//**********************************************************//

void AreaCombat::clear()
{
	for (const auto& it : areas) {
		delete it.second;
	}
	areas.clear();
}

AreaCombat::AreaCombat(const AreaCombat& rhs)
{
	hasExtArea = rhs.hasExtArea;
	for (const auto& it : rhs.areas) {
		areas[it.first] = new MatrixArea(*it.second);
	}
}

void AreaCombat::getList(const Position& centerPos, const Position& targetPos, std::forward_list<Tile*>& list) const
{
	const MatrixArea* area = getArea(centerPos, targetPos);
	if (!area) {
		return;
	}

	uint32_t centerY, centerX;
	area->getCenter(centerY, centerX);

	Position tmpPos(targetPos.x - centerX, targetPos.y - centerY, targetPos.z);
	uint32_t cols = area->getCols();
	for (uint32_t y = 0, rows = area->getRows(); y < rows; ++y) {
		for (uint32_t x = 0; x < cols; ++x) {
			if (area->getValue(y, x) != 0) {
				if (g_game.isSightClear(targetPos, tmpPos, true)) {
					Tile* tile = g_game.map.getTile(tmpPos);
					if (!tile) {
						tile = new StaticTile(tmpPos.x, tmpPos.y, tmpPos.z);
						g_game.map.setTile(tmpPos, tile);
					}
					list.push_front(tile);
				}
			}
			tmpPos.x++;
		}
		tmpPos.x -= cols;
		tmpPos.y++;
	}
}

void AreaCombat::copyArea(const MatrixArea* input, MatrixArea* output, MatrixOperation_t op) const
{
	uint32_t centerY, centerX;
	input->getCenter(centerY, centerX);

	if (op == MATRIXOPERATION_COPY) {
		for (uint32_t y = 0; y < input->getRows(); ++y) {
			for (uint32_t x = 0; x < input->getCols(); ++x) {
				(*output)[y][x] = (*input)[y][x];
			}
		}

		output->setCenter(centerY, centerX);
	} else if (op == MATRIXOPERATION_MIRROR) {
		for (uint32_t y = 0; y < input->getRows(); ++y) {
			uint32_t rx = 0;
			for (int32_t x = input->getCols(); --x >= 0;) {
				(*output)[y][rx++] = (*input)[y][x];
			}
		}

		output->setCenter(centerY, (input->getRows() - 1) - centerX);
	} else if (op == MATRIXOPERATION_FLIP) {
		for (uint32_t x = 0; x < input->getCols(); ++x) {
			uint32_t ry = 0;
			for (int32_t y = input->getRows(); --y >= 0;) {
				(*output)[ry++][x] = (*input)[y][x];
			}
		}

		output->setCenter((input->getCols() - 1) - centerY, centerX);
	} else {
		// rotation
		int32_t rotateCenterX = (output->getCols() / 2) - 1;
		int32_t rotateCenterY = (output->getRows() / 2) - 1;
		int32_t angle;

		switch (op) {
			case MATRIXOPERATION_ROTATE90:
				angle = 90;
				break;

			case MATRIXOPERATION_ROTATE180:
				angle = 180;
				break;

			case MATRIXOPERATION_ROTATE270:
				angle = 270;
				break;

			default:
				angle = 0;
				break;
		}

		double angleRad = M_PI * angle / 180.0;

		double a = std::cos(angleRad);
		double b = -std::sin(angleRad);
		double c = std::sin(angleRad);
		double d = std::cos(angleRad);

		const uint32_t rows = input->getRows();
		for (uint32_t x = 0, cols = input->getCols(); x < cols; ++x) {
			for (uint32_t y = 0; y < rows; ++y) {
				//calculate new coordinates using rotation center
				int32_t newX = x - centerX;
				int32_t newY = y - centerY;

				//perform rotation
				int32_t rotatedX = static_cast<int32_t>(round(newX * a + newY * b));
				int32_t rotatedY = static_cast<int32_t>(round(newX * c + newY * d));

				//write in the output matrix using rotated coordinates
				(*output)[rotatedY + rotateCenterY][rotatedX + rotateCenterX] = (*input)[y][x];
			}
		}

		output->setCenter(rotateCenterY, rotateCenterX);
	}
}

MatrixArea* AreaCombat::createArea(const std::list<uint32_t>& list, uint32_t rows)
{
	uint32_t cols;
	if (rows == 0) {
		cols = 0;
	} else {
		cols = list.size() / rows;
	}

	MatrixArea* area = new MatrixArea(rows, cols);

	uint32_t x = 0;
	uint32_t y = 0;

	for (uint32_t value : list) {
		if (value == 1 || value == 3) {
			area->setValue(y, x, true);
		}

		if (value == 2 || value == 3) {
			area->setCenter(y, x);
		}

		++x;

		if (cols == x) {
			x = 0;
			++y;
		}
	}
	return area;
}

void AreaCombat::setupArea(const std::list<uint32_t>& list, uint32_t rows)
{
	MatrixArea* area = createArea(list, rows);

	//NORTH
	areas[DIRECTION_NORTH] = area;

	uint32_t maxOutput = std::max<uint32_t>(area->getCols(), area->getRows()) * 2;

	//SOUTH
	MatrixArea* southArea = new MatrixArea(maxOutput, maxOutput);
	copyArea(area, southArea, MATRIXOPERATION_ROTATE180);
	areas[DIRECTION_SOUTH] = southArea;

	//EAST
	MatrixArea* eastArea = new MatrixArea(maxOutput, maxOutput);
	copyArea(area, eastArea, MATRIXOPERATION_ROTATE90);
	areas[DIRECTION_EAST] = eastArea;

	//WEST
	MatrixArea* westArea = new MatrixArea(maxOutput, maxOutput);
	copyArea(area, westArea, MATRIXOPERATION_ROTATE270);
	areas[DIRECTION_WEST] = westArea;
}

void AreaCombat::setupArea(int32_t length, int32_t spread)
{
	std::list<uint32_t> list;

	uint32_t rows = length;
	int32_t cols = 1;

	if (spread != 0) {
		cols = ((length - (length % spread)) / spread) * 2 + 1;
	}

	int32_t colSpread = cols;

	for (uint32_t y = 1; y <= rows; ++y) {
		int32_t mincol = cols - colSpread + 1;
		int32_t maxcol = cols - (cols - colSpread);

		for (int32_t x = 1; x <= cols; ++x) {
			if (y == rows && x == ((cols - (cols % 2)) / 2) + 1) {
				list.push_back(3);
			} else if (x >= mincol && x <= maxcol) {
				list.push_back(1);
			} else {
				list.push_back(0);
			}
		}

		if (spread > 0 && y % spread == 0) {
			--colSpread;
		}
	}

	setupArea(list, rows);
}

void AreaCombat::setupArea(int32_t radius)
{
	int32_t area[13][13] = {
		{0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 8, 8, 7, 8, 8, 0, 0, 0, 0},
		{0, 0, 0, 8, 7, 6, 6, 6, 7, 8, 0, 0, 0},
		{0, 0, 8, 7, 6, 5, 5, 5, 6, 7, 8, 0, 0},
		{0, 8, 7, 6, 5, 4, 4, 4, 5, 6, 7, 8, 0},
		{0, 8, 6, 5, 4, 3, 2, 3, 4, 5, 6, 8, 0},
		{8, 7, 6, 5, 4, 2, 1, 2, 4, 5, 6, 7, 8},
		{0, 8, 6, 5, 4, 3, 2, 3, 4, 5, 6, 8, 0},
		{0, 8, 7, 6, 5, 4, 4, 4, 5, 6, 7, 8, 0},
		{0, 0, 8, 7, 6, 5, 5, 5, 6, 7, 8, 0, 0},
		{0, 0, 0, 8, 7, 6, 6, 6, 7, 8, 0, 0, 0},
		{0, 0, 0, 0, 8, 8, 7, 8, 8, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0}
	};

	std::list<uint32_t> list;

	for (auto& row : area) {
		for (int cell : row) {
			if (cell == 1) {
				list.push_back(3);
			} else if (cell > 0 && cell <= radius) {
				list.push_back(1);
			} else {
				list.push_back(0);
			}
		}
	}

	setupArea(list, 13);
}

void AreaCombat::setupExtArea(const std::list<uint32_t>& list, uint32_t rows)
{
	if (list.empty()) {
		return;
	}

	hasExtArea = true;
	MatrixArea* area = createArea(list, rows);

	//NORTH-WEST
	areas[DIRECTION_NORTHWEST] = area;

	uint32_t maxOutput = std::max<uint32_t>(area->getCols(), area->getRows()) * 2;

	//NORTH-EAST
	MatrixArea* neArea = new MatrixArea(maxOutput, maxOutput);
	copyArea(area, neArea, MATRIXOPERATION_MIRROR);
	areas[DIRECTION_NORTHEAST] = neArea;

	//SOUTH-WEST
	MatrixArea* swArea = new MatrixArea(maxOutput, maxOutput);
	copyArea(area, swArea, MATRIXOPERATION_FLIP);
	areas[DIRECTION_SOUTHWEST] = swArea;

	//SOUTH-EAST
	MatrixArea* seArea = new MatrixArea(maxOutput, maxOutput);
	copyArea(swArea, seArea, MATRIXOPERATION_MIRROR);
	areas[DIRECTION_SOUTHEAST] = seArea;
}

//**********************************************************//

void MagicField::onStepInField(Creature* creature)
{
	//remove magic walls/wild growth
	if (id == ITEM_MAGICWALL || id == ITEM_WILDGROWTH || isBlocking()) {
		if (!creature->isInGhostMode()) {
			g_game.internalRemoveItem(this, 1);
		}

		return;
	}

	const ItemType& it = items[getID()];
	if (it.conditionDamage) {
		Condition* conditionCopy = it.conditionDamage->clone();
		uint32_t ownerId = getOwner();
		if (ownerId) {
			bool harmfulField = true;

			if (g_game.getWorldType() == WORLD_TYPE_NO_PVP || getTile()->hasFlag(TILESTATE_NOPVPZONE)) {
				Creature* owner = g_game.getCreatureByID(ownerId);
				if (owner) {
					if (owner->getPlayer() || (owner->isSummon() && owner->getMaster()->getPlayer())) {
						harmfulField = false;
					}
				}
			}

			Player* targetPlayer = creature->getPlayer();
			if (targetPlayer) {
				Player* attackerPlayer = g_game.getPlayerByID(ownerId);
				if (attackerPlayer) {
					if (Combat::isProtected(attackerPlayer, targetPlayer)) {
						harmfulField = false;
					}
				}
			}

			if (!harmfulField || (OTSYS_TIME() - createTime <= 5000) || creature->hasBeenAttacked(ownerId)) {
				conditionCopy->setParam(CONDITION_PARAM_OWNER, ownerId);
			}
		}

		creature->addCondition(conditionCopy);
	}
}

void DamageImpact::handleCreature(Creature* target)
{
	Combat::doCombatHealth(actor, target, damage, params);
}

void SpeedImpact::handleCreature(Creature* target)
{
	ConditionType_t conditionType = CONDITION_PARALYZE;
	if (percent > 0) {
		conditionType = CONDITION_HASTE;
	}

	ConditionSpeed* condition = static_cast<ConditionSpeed*>(Condition::createCondition(CONDITIONID_COMBAT, conditionType, duration));
	condition->setSpeedDelta(percent);
	target->addCondition(condition);
}

void DunkenImpact::handleCreature(Creature* target)
{
	Condition* condition = Condition::createCondition(CONDITIONID_COMBAT, CONDITION_DRUNK, duration);
	target->addCondition(condition);
}
