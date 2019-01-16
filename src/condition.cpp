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

#include "condition.h"
#include "game.h"

extern Game g_game;

bool Condition::setParam(ConditionParam_t param, int32_t value)
{
	switch (param) {
		case CONDITION_PARAM_TICKS: {
			ticks = value;
			return true;
		}

		case CONDITION_PARAM_SUBID: {
			subId = value;
			return true;
		}

		default: {
			return false;
		}
	}
}

bool Condition::unserialize(PropStream& propStream)
{
	uint8_t attr_type;
	while (propStream.read<uint8_t>(attr_type) && attr_type != CONDITIONATTR_END) {
		if (!unserializeProp(static_cast<ConditionAttr_t>(attr_type), propStream)) {
			return false;
		}
	}
	return true;
}

bool Condition::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	switch (attr) {
		case CONDITIONATTR_TYPE: {
			int32_t value;
			if (!propStream.read<int32_t>(value)) {
				return false;
			}

			conditionType = static_cast<ConditionType_t>(value);
			return true;
		}

		case CONDITIONATTR_ID: {
			int32_t value;
			if (!propStream.read<int32_t>(value)) {
				return false;
			}

			id = static_cast<ConditionId_t>(value);
			return true;
		}

		case CONDITIONATTR_TICKS: {
			return propStream.read<int32_t>(ticks);
		}

		case CONDITIONATTR_SUBID: {
			return propStream.read<uint32_t>(subId);
		}

		case CONDITIONATTR_END:
			return true;

		default:
			return false;
	}
}

void Condition::serialize(PropWriteStream& propWriteStream)
{
	propWriteStream.write<uint8_t>(CONDITIONATTR_TYPE);
	propWriteStream.write<uint32_t>(conditionType);

	propWriteStream.write<uint8_t>(CONDITIONATTR_ID);
	propWriteStream.write<uint32_t>(id);

	propWriteStream.write<uint8_t>(CONDITIONATTR_TICKS);
	propWriteStream.write<uint32_t>(ticks);

	propWriteStream.write<uint8_t>(CONDITIONATTR_SUBID);
	propWriteStream.write<uint32_t>(subId);
}

void Condition::setTicks(int32_t newTicks)
{
	ticks = newTicks;
	endTime = ticks + OTSYS_TIME();
}

bool Condition::executeCondition(Creature*, int32_t interval)
{
	if (ticks == -1) {
		return true;
	}

	//Not using set ticks here since it would reset endTime
	ticks = std::max<int32_t>(0, ticks - interval);
	return getEndTime() >= OTSYS_TIME();
}

Condition* Condition::createCondition(ConditionId_t id, ConditionType_t type, int32_t ticks, int32_t param/* = 0*/, uint32_t subId/* = 0*/)
{
	switch (type) {
		case CONDITION_POISON:
		case CONDITION_FIRE:
		case CONDITION_ENERGY:
			return new ConditionDamage(id, type, subId);

		case CONDITION_HASTE:
		case CONDITION_PARALYZE:
			return new ConditionSpeed(id, type, ticks, subId, param);

		case CONDITION_INVISIBLE:
			return new ConditionInvisible(id, type, ticks, subId);

		case CONDITION_OUTFIT:
			return new ConditionOutfit(id, type, ticks, subId);

		case CONDITION_LIGHT:
			return new ConditionLight(id, type, ticks, subId, param & 0xFF, (param & 0xFF00) >> 8);

		case CONDITION_REGENERATION:
			return new ConditionRegeneration(id, type, ticks, subId);

		case CONDITION_SOUL:
			return new ConditionSoul(id, type, ticks, subId);

		case CONDITION_ATTRIBUTES:
			return new ConditionAttributes(id, type, ticks, subId);

		case CONDITION_INFIGHT:
		case CONDITION_DRUNK:
		case CONDITION_EXHAUST:
		case CONDITION_MUTED:
		case CONDITION_CHANNELMUTEDTICKS:
		case CONDITION_YELLTICKS:
		case CONDITION_PACIFIED:
		case CONDITION_MANASHIELD:
		case CONDITION_AGGRESSIVE:
			return new ConditionGeneric(id, type, ticks, subId);

		default:
			return nullptr;
	}
}

Condition* Condition::createCondition(PropStream& propStream)
{
	uint8_t attr;
	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_TYPE) {
		return nullptr;
	}

	uint32_t type;
	if (!propStream.read<uint32_t>(type)) {
		return nullptr;
	}

	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_ID) {
		return nullptr;
	}

	uint32_t id;
	if (!propStream.read<uint32_t>(id)) {
		return nullptr;
	}

	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_TICKS) {
		return nullptr;
	}

	uint32_t ticks;
	if (!propStream.read<uint32_t>(ticks)) {
		return nullptr;
	}

	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_SUBID) {
		return nullptr;
	}

	uint32_t subId;
	if (!propStream.read<uint32_t>(subId)) {
		return nullptr;
	}

	return createCondition(static_cast<ConditionId_t>(id), static_cast<ConditionType_t>(type), ticks, 0, subId);
}

bool Condition::startCondition(Creature*)
{
	if (ticks > 0) {
		endTime = ticks + OTSYS_TIME();
	}
	return true;
}

bool Condition::isPersistent() const
{
	if (ticks == -1) {
		return false;
	}

	if (!(id == CONDITIONID_DEFAULT || id == CONDITIONID_COMBAT)) {
		return false;
	}

	return true;
}

uint32_t Condition::getIcons() const
{
	return 0;
}

bool Condition::updateCondition(const Condition* addCondition)
{
	if (conditionType != addCondition->getType()) {
		return false;
	}

	if (ticks == -1 && addCondition->getTicks() > 0) {
		return false;
	}

	if (addCondition->getTicks() >= 0 && getEndTime() > (OTSYS_TIME() + addCondition->getTicks())) {
		return false;
	}

	return true;
}

bool ConditionGeneric::startCondition(Creature* creature)
{
	return Condition::startCondition(creature);
}

bool ConditionGeneric::executeCondition(Creature* creature, int32_t interval)
{
	return Condition::executeCondition(creature, interval);
}

void ConditionGeneric::endCondition(Creature*)
{
	//
}

void ConditionGeneric::addCondition(Creature*, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());
	}
}

uint32_t ConditionGeneric::getIcons() const
{
	uint32_t icons = Condition::getIcons();

	switch (conditionType) {
		case CONDITION_MANASHIELD:
			icons |= ICON_MANASHIELD;
			break;

		case CONDITION_INFIGHT:
			icons |= ICON_SWORDS;
			break;

		case CONDITION_DRUNK:
			icons |= ICON_DRUNK;
			break;

		default:
			break;
	}

	return icons;
}

void ConditionAttributes::addCondition(Creature* creature, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

		const ConditionAttributes& conditionAttrs = static_cast<const ConditionAttributes&>(*addCondition);
		//Remove the old condition
		endCondition(creature);

		//Apply the new one
		memcpy(skills, conditionAttrs.skills, sizeof(skills));
		memcpy(skillsPercent, conditionAttrs.skillsPercent, sizeof(skillsPercent));
		memcpy(stats, conditionAttrs.stats, sizeof(stats));
		memcpy(statsPercent, conditionAttrs.statsPercent, sizeof(statsPercent));

		if (Player* player = creature->getPlayer()) {
			updatePercentSkills(player);
			updateSkills(player);
			updatePercentStats(player);
			updateStats(player);
		}
	}
}

bool ConditionAttributes::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_SKILLS) {
		return propStream.read<int32_t>(skills[currentSkill++]);
	} else if (attr == CONDITIONATTR_STATS) {
		return propStream.read<int32_t>(stats[currentStat++]);
	}
	return Condition::unserializeProp(attr, propStream);
}

void ConditionAttributes::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	for (int32_t i = SKILL_FIRST; i <= SKILL_LAST; ++i) {
		propWriteStream.write<uint8_t>(CONDITIONATTR_SKILLS);
		propWriteStream.write<int32_t>(skills[i]);
	}

	for (int32_t i = STAT_FIRST; i <= STAT_LAST; ++i) {
		propWriteStream.write<uint8_t>(CONDITIONATTR_STATS);
		propWriteStream.write<int32_t>(stats[i]);
	}
}

bool ConditionAttributes::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	if (Player* player = creature->getPlayer()) {
		updatePercentSkills(player);
		updateSkills(player);
		updatePercentStats(player);
		updateStats(player);
	}

	return true;
}

void ConditionAttributes::updatePercentStats(Player* player)
{
	for (int32_t i = STAT_FIRST; i <= STAT_LAST; ++i) {
		if (statsPercent[i] == 0) {
			continue;
		}

		switch (i) {
			case STAT_MAXHITPOINTS:
				stats[i] = static_cast<int32_t>(player->getMaxHealth() * ((statsPercent[i] - 100) / 100.f));
				break;

			case STAT_MAXMANAPOINTS:
				stats[i] = static_cast<int32_t>(player->getMaxMana() * ((statsPercent[i] - 100) / 100.f));
				break;

			case STAT_MAGICPOINTS:
				stats[i] = static_cast<int32_t>(player->getMagicLevel() * ((statsPercent[i] - 100) / 100.f));
				break;
		}
	}
}

void ConditionAttributes::updateStats(Player* player)
{
	bool needUpdateStats = false;

	for (int32_t i = STAT_FIRST; i <= STAT_LAST; ++i) {
		if (stats[i]) {
			needUpdateStats = true;
			player->setVarStats(static_cast<stats_t>(i), stats[i]);
		}
	}

	if (needUpdateStats) {
		player->sendStats();
	}
}

void ConditionAttributes::updatePercentSkills(Player* player)
{
	for (uint8_t i = SKILL_FIRST; i <= SKILL_LAST; ++i) {
		if (skillsPercent[i] == 0) {
			continue;
		}

		int32_t unmodifiedSkill = player->getBaseSkill(i);
		skills[i] = static_cast<int32_t>(unmodifiedSkill * ((skillsPercent[i] - 100) / 100.f));
	}
}

void ConditionAttributes::updateSkills(Player* player)
{
	bool needUpdateSkills = false;

	for (int32_t i = SKILL_FIRST; i <= SKILL_LAST; ++i) {
		if (skills[i]) {
			needUpdateSkills = true;
			player->setVarSkill(static_cast<skills_t>(i), skills[i]);
		}
	}

	if (needUpdateSkills) {
		player->sendSkills();
	}
}

bool ConditionAttributes::executeCondition(Creature* creature, int32_t interval)
{
	return ConditionGeneric::executeCondition(creature, interval);
}

void ConditionAttributes::endCondition(Creature* creature)
{
	Player* player = creature->getPlayer();
	if (player) {
		bool needUpdateSkills = false;

		for (int32_t i = SKILL_FIRST; i <= SKILL_LAST; ++i) {
			if (skills[i] || skillsPercent[i]) {
				needUpdateSkills = true;
				player->setVarSkill(static_cast<skills_t>(i), -skills[i]);
			}
		}

		if (needUpdateSkills) {
			player->sendSkills();
		}

		bool needUpdateStats = false;

		for (int32_t i = STAT_FIRST; i <= STAT_LAST; ++i) {
			if (stats[i]) {
				needUpdateStats = true;
				player->setVarStats(static_cast<stats_t>(i), -stats[i]);
			}
		}

		if (needUpdateStats) {
			player->sendStats();
		}
	}
}

bool ConditionAttributes::setParam(ConditionParam_t param, int32_t value)
{
	bool ret = ConditionGeneric::setParam(param, value);

	switch (param) {
		case CONDITION_PARAM_SKILL_MELEE: {
			skills[SKILL_CLUB] = value;
			skills[SKILL_AXE] = value;
			skills[SKILL_SWORD] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_MELEEPERCENT: {
			skillsPercent[SKILL_CLUB] = value;
			skillsPercent[SKILL_AXE] = value;
			skillsPercent[SKILL_SWORD] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_FIST: {
			skills[SKILL_FIST] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_FISTPERCENT: {
			skillsPercent[SKILL_FIST] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_CLUB: {
			skills[SKILL_CLUB] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_CLUBPERCENT: {
			skillsPercent[SKILL_CLUB] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_SWORD: {
			skills[SKILL_SWORD] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_SWORDPERCENT: {
			skillsPercent[SKILL_SWORD] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_AXE: {
			skills[SKILL_AXE] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_AXEPERCENT: {
			skillsPercent[SKILL_AXE] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_DISTANCE: {
			skills[SKILL_DISTANCE] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_DISTANCEPERCENT: {
			skillsPercent[SKILL_DISTANCE] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_SHIELD: {
			skills[SKILL_SHIELD] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_SHIELDPERCENT: {
			skillsPercent[SKILL_SHIELD] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_FISHING: {
			skills[SKILL_FISHING] = value;
			return true;
		}

		case CONDITION_PARAM_SKILL_FISHINGPERCENT: {
			skillsPercent[SKILL_FISHING] = value;
			return true;
		}

		case CONDITION_PARAM_STAT_MAXHITPOINTS: {
			stats[STAT_MAXHITPOINTS] = value;
			return true;
		}

		case CONDITION_PARAM_STAT_MAXMANAPOINTS: {
			stats[STAT_MAXMANAPOINTS] = value;
			return true;
		}

		case CONDITION_PARAM_STAT_MAGICPOINTS: {
			stats[STAT_MAGICPOINTS] = value;
			return true;
		}

		case CONDITION_PARAM_STAT_MAXHITPOINTSPERCENT: {
			statsPercent[STAT_MAXHITPOINTS] = std::max<int32_t>(0, value);
			return true;
		}

		case CONDITION_PARAM_STAT_MAXMANAPOINTSPERCENT: {
			statsPercent[STAT_MAXMANAPOINTS] = std::max<int32_t>(0, value);
			return true;
		}

		case CONDITION_PARAM_STAT_MAGICPOINTSPERCENT: {
			statsPercent[STAT_MAGICPOINTS] = std::max<int32_t>(0, value);
			return true;
		}

		default:
			return ret;
	}
}

void ConditionRegeneration::addCondition(Creature*, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

		const ConditionRegeneration& conditionRegen = static_cast<const ConditionRegeneration&>(*addCondition);

		healthTicks = conditionRegen.healthTicks;
		manaTicks = conditionRegen.manaTicks;

		healthGain = conditionRegen.healthGain;
		manaGain = conditionRegen.manaGain;
	}
}

bool ConditionRegeneration::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_HEALTHTICKS) {
		return propStream.read<uint32_t>(healthTicks);
	} else if (attr == CONDITIONATTR_HEALTHGAIN) {
		return propStream.read<uint32_t>(healthGain);
	} else if (attr == CONDITIONATTR_MANATICKS) {
		return propStream.read<uint32_t>(manaTicks);
	} else if (attr == CONDITIONATTR_MANAGAIN) {
		return propStream.read<uint32_t>(manaGain);
	}
	return Condition::unserializeProp(attr, propStream);
}

void ConditionRegeneration::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	propWriteStream.write<uint8_t>(CONDITIONATTR_HEALTHTICKS);
	propWriteStream.write<uint32_t>(healthTicks);

	propWriteStream.write<uint8_t>(CONDITIONATTR_HEALTHGAIN);
	propWriteStream.write<uint32_t>(healthGain);

	propWriteStream.write<uint8_t>(CONDITIONATTR_MANATICKS);
	propWriteStream.write<uint32_t>(manaTicks);

	propWriteStream.write<uint8_t>(CONDITIONATTR_MANAGAIN);
	propWriteStream.write<uint32_t>(manaGain);
}

bool ConditionRegeneration::executeCondition(Creature* creature, int32_t interval)
{
	internalHealthTicks += interval;
	internalManaTicks += interval;

	if (creature->getZone() != ZONE_PROTECTION) {
		if (internalHealthTicks >= healthTicks) {
			internalHealthTicks = 0;

			creature->changeHealth(healthGain);
		}

		if (internalManaTicks >= manaTicks) {
			internalManaTicks = 0;
			creature->changeMana(manaGain);
		}
	}

	return ConditionGeneric::executeCondition(creature, interval);
}

bool ConditionRegeneration::setParam(ConditionParam_t param, int32_t value)
{
	bool ret = ConditionGeneric::setParam(param, value);

	switch (param) {
		case CONDITION_PARAM_HEALTHGAIN:
			healthGain = value;
			return true;

		case CONDITION_PARAM_HEALTHTICKS:
			healthTicks = value;
			return true;

		case CONDITION_PARAM_MANAGAIN:
			manaGain = value;
			return true;

		case CONDITION_PARAM_MANATICKS:
			manaTicks = value;
			return true;

		default:
			return ret;
	}
}

void ConditionSoul::addCondition(Creature*, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

		const ConditionSoul& conditionSoul = static_cast<const ConditionSoul&>(*addCondition);

		soulTicks = conditionSoul.soulTicks;
		soulGain = conditionSoul.soulGain;
	}
}

bool ConditionSoul::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_SOULGAIN) {
		return propStream.read<uint32_t>(soulGain);
	} else if (attr == CONDITIONATTR_SOULTICKS) {
		return propStream.read<uint32_t>(soulTicks);
	}
	return Condition::unserializeProp(attr, propStream);
}

void ConditionSoul::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	propWriteStream.write<uint8_t>(CONDITIONATTR_SOULGAIN);
	propWriteStream.write<uint32_t>(soulGain);

	propWriteStream.write<uint8_t>(CONDITIONATTR_SOULTICKS);
	propWriteStream.write<uint32_t>(soulTicks);
}

bool ConditionSoul::executeCondition(Creature* creature, int32_t interval)
{
	internalSoulTicks += interval;

	if (Player* player = creature->getPlayer()) {
		if (player->getZone() != ZONE_PROTECTION) {
			if (internalSoulTicks >= soulTicks) {
				internalSoulTicks = 0;
				player->changeSoul(soulGain);
			}
		}
	}

	return ConditionGeneric::executeCondition(creature, interval);
}

bool ConditionSoul::setParam(ConditionParam_t param, int32_t value)
{
	bool ret = ConditionGeneric::setParam(param, value);
	switch (param) {
		case CONDITION_PARAM_SOULGAIN:
			soulGain = value;
			return true;

		case CONDITION_PARAM_SOULTICKS:
			soulTicks = value;
			return true;

		default:
			return ret;
	}
}

bool ConditionDamage::setParam(ConditionParam_t param, int32_t value)
{
	bool ret = Condition::setParam(param, value);

	switch (param) {
		case CONDITION_PARAM_OWNER:
			owner = value;
			return true;

		case CONDITION_PARAM_CYCLE:
			cycle = value;
			return true;

		case CONDITION_PARAM_COUNT:
			count = value;
			return true;

		case CONDITION_PARAM_MAX_COUNT:
			max_count = value;
			return true;

		case CONDITION_PARAM_HIT_DAMAGE:
			hit_damage = value;
			return true;

		default:
			return false;
	}
}

bool ConditionDamage::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_OWNER) {
		return propStream.skip(4);
	} else if (attr == CONDITIONATTR_CYCLE) {
		if (!propStream.read<int32_t>(cycle)) {
			return false;
		}

		return true;
	} else if (attr == CONDITIONATTR_COUNT) {
		if (!propStream.read<int32_t>(count)) {
			return false;
		}

		return true;
	} else if (attr == CONDITIONATTR_MAX_COUNT) {
		if (!propStream.read<int32_t>(max_count)) {
			return false;
		}

		return true;
	} else if (attr == CONDITIONATTR_FACTOR_PERCENT) {
		if (!propStream.read<int32_t>(factor_percent)) {
			return false;
		}

		return true;
	}

	return Condition::unserializeProp(attr, propStream);
}

void ConditionDamage::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	propWriteStream.write<uint8_t>(CONDITIONATTR_CYCLE);
	propWriteStream.write<int32_t>(cycle);

	propWriteStream.write<uint8_t>(CONDITIONATTR_COUNT);
	propWriteStream.write<int32_t>(count);

	propWriteStream.write<uint8_t>(CONDITIONATTR_MAX_COUNT);
	propWriteStream.write<int32_t>(max_count);

	propWriteStream.write<uint8_t>(CONDITIONATTR_FACTOR_PERCENT);
	propWriteStream.write<int32_t>(factor_percent);
}

bool ConditionDamage::updateCondition(const Condition* addCondition)
{
	const ConditionDamage& conditionDamage = static_cast<const ConditionDamage&>(*addCondition);
	return conditionDamage.getTotalDamage() >= getTotalDamage();
}

bool ConditionDamage::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	creature->onAttacked();

	setParam(CONDITION_PARAM_TICKINTERVAL, 1000);

	if (factor_percent == -1) {
		factor_percent = 50;
	}

	if (factor_percent <= 9) {
		factor_percent = 10;
	}

	if (factor_percent >= 1001) {
		factor_percent = 1000;
	}

	if (hit_damage) {
		doDamage(creature, -hit_damage);
	}

	return true;
}

bool ConditionDamage::executeCondition(Creature* creature, int32_t)
{
	if (conditionType == CONDITION_FIRE) {
		const int32_t r_cycle = cycle;
		if (r_cycle) {
			if (count <= 0) {
				count = max_count;
				cycle = r_cycle + 2 * (r_cycle <= 0) - 1;
				doDamage(creature, -10);
			} else {
				--count;
			}
		} else {
			return false;
		}
	} else if (conditionType == CONDITION_POISON) {
		const int32_t r_cycle = cycle;
		if (r_cycle) {
			if (count <= 0) {
				count = max_count;
				int32_t f = factor_percent * r_cycle / 1000;
				if (!f) {
					f = 2 * (r_cycle > 0) - 1;
				}

				cycle = r_cycle - f;
				doDamage(creature, -f);
			} else {
				--count;
			}
		} else {
			return false;
		}
	} else if (conditionType == CONDITION_ENERGY) {
		const int32_t r_cycle = cycle;
		if (r_cycle) {
			if (count <= 0) {
				count = max_count;
				cycle = r_cycle + 2 * (r_cycle <= 0) - 1;
				doDamage(creature, -25);
			} else {
				--count;
			}
		} else {
			return false;
		}
	}

	return true;
}

bool ConditionDamage::doDamage(Creature* creature, int32_t healthChange)
{
	if (creature->isSuppress(getType())) {
		return true;
	}

	CombatDamage damage;
	damage.value = healthChange;
	damage.type = Combat::ConditionToDamageType(conditionType);

	Creature* attacker = g_game.getCreatureByID(owner);

	if (!creature->isAttackable() || Combat::canDoCombat(attacker, creature) != RETURNVALUE_NOERROR) {
		if (!creature->isInGhostMode()) {
			g_game.addMagicEffect(creature->getPosition(), CONST_ME_POFF);
		}
		return false;
	}

	if (g_game.combatBlockHit(damage, attacker, creature, false, false, true)) {
		return false;
	}
	return g_game.combatChangeHealth(attacker, creature, damage);
}

void ConditionDamage::endCondition(Creature*)
{
	//
}

void ConditionDamage::addCondition(Creature* creature, const Condition* addCondition)
{
	if (addCondition->getType() != conditionType) {
		return;
	}

	const ConditionDamage& conditionDamage = static_cast<const ConditionDamage&>(*addCondition);

	if (hit_damage) {
		doDamage(creature, -conditionDamage.hit_damage);
	}

	if (!updateCondition(addCondition)) {
		return;
	}

	owner = conditionDamage.owner;
	cycle = conditionDamage.cycle;
	count = conditionDamage.count;
	max_count = conditionDamage.max_count;
}

int32_t ConditionDamage::getTotalDamage() const
{
	return cycle;
}

uint32_t ConditionDamage::getIcons() const
{
	uint32_t icons = Condition::getIcons();
	switch (conditionType) {
		case CONDITION_FIRE:
			icons |= ICON_BURN;
			break;

		case CONDITION_ENERGY:
			icons |= ICON_ENERGY;
			break;

		case CONDITION_POISON:
			icons |= ICON_POISON;
			break;

		default:
			break;
	}
	return icons;
}

bool ConditionSpeed::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_SPEEDDELTA) {
		return propStream.read<int32_t>(speedDelta);
	} else if (attr == CONDITIONATTR_APPLIEDSPEEDDELTA) {
		return propStream.read<int32_t>(appliedSpeedDelta);
	}
	return Condition::unserializeProp(attr, propStream);
}

void ConditionSpeed::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	propWriteStream.write<uint8_t>(CONDITIONATTR_SPEEDDELTA);
	propWriteStream.write<int32_t>(speedDelta);

	propWriteStream.write<uint8_t>(CONDITIONATTR_APPLIEDSPEEDDELTA);
	propWriteStream.write<int32_t>(appliedSpeedDelta);
}

bool ConditionSpeed::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	if (appliedSpeedDelta == 0) {
		speedDelta = normal_random(-variation, variation) + speedDelta;

		if (speedDelta >= -100) {
			speedDelta = static_cast<int32_t>(creature->getBaseSpeed()) * speedDelta / 100;
		} else {
			speedDelta = -20 - creature->getBaseSpeed();
		}

		appliedSpeedDelta = speedDelta;
	} else {
		speedDelta = appliedSpeedDelta;
	}

	g_game.changeSpeed(creature, speedDelta);
	return true;
}

bool ConditionSpeed::executeCondition(Creature* creature, int32_t interval)
{
	return Condition::executeCondition(creature, interval);
}

void ConditionSpeed::endCondition(Creature* creature)
{
	g_game.changeSpeed(creature, -appliedSpeedDelta);
}

void ConditionSpeed::addCondition(Creature* creature, const Condition* addCondition)
{
	if (conditionType != addCondition->getType()) {
		return;
	}

	if (ticks == -1 && addCondition->getTicks() > 0) {
		return;
	}

	const ConditionSpeed& conditionSpeed = static_cast<const ConditionSpeed&>(*addCondition);

	int32_t newVariation = conditionSpeed.variation;
	int32_t newSpeedDelta = conditionSpeed.speedDelta;

	newSpeedDelta = normal_random(-newVariation, newVariation) + newSpeedDelta;

	// update ticks
	setTicks(addCondition->getTicks());

	if (newSpeedDelta >= -100) {
		newSpeedDelta = static_cast<int32_t>(creature->getBaseSpeed()) * newSpeedDelta / 100;
	} else {
		newSpeedDelta = -20 - creature->getBaseSpeed();
	}

	creature->setSpeed(-appliedSpeedDelta);

	appliedSpeedDelta = newSpeedDelta;
	speedDelta = newSpeedDelta;

	g_game.changeSpeed(creature, newSpeedDelta);
}

uint32_t ConditionSpeed::getIcons() const
{
	uint32_t icons = Condition::getIcons();
	switch (conditionType) {
		case CONDITION_HASTE:
			icons |= ICON_HASTE;
			break;

		case CONDITION_PARALYZE:
			icons |= ICON_PARALYZE;
			break;

		default:
			break;
	}
	return icons;
}

bool ConditionInvisible::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	g_game.internalCreatureChangeVisible(creature, false);
	return true;
}

void ConditionInvisible::endCondition(Creature* creature)
{
	if (!creature->isInvisible()) {
		g_game.internalCreatureChangeVisible(creature, true);
	}
}

void ConditionOutfit::setOutfit(const Outfit_t& outfit)
{
	this->outfit = outfit;
}

bool ConditionOutfit::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_OUTFIT) {
		return propStream.read<Outfit_t>(outfit);
	}
	return Condition::unserializeProp(attr, propStream);
}

void ConditionOutfit::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	propWriteStream.write<uint8_t>(CONDITIONATTR_OUTFIT);
	propWriteStream.write<Outfit_t>(outfit);
}

bool ConditionOutfit::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	g_game.internalCreatureChangeOutfit(creature, outfit);
	return true;
}

bool ConditionOutfit::executeCondition(Creature* creature, int32_t interval)
{
	return Condition::executeCondition(creature, interval);
}

void ConditionOutfit::endCondition(Creature* creature)
{
	g_game.internalCreatureChangeOutfit(creature, creature->getDefaultOutfit());
}

void ConditionOutfit::addCondition(Creature* creature, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

		const ConditionOutfit& conditionOutfit = static_cast<const ConditionOutfit&>(*addCondition);
		outfit = conditionOutfit.outfit;

		g_game.internalCreatureChangeOutfit(creature, outfit);
	}
}

bool ConditionLight::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	internalLightTicks = 0;
	lightChangeInterval = ticks / lightInfo.level;
	creature->setCreatureLight(lightInfo);
	g_game.changeLight(creature);
	return true;
}

bool ConditionLight::executeCondition(Creature* creature, int32_t interval)
{
	internalLightTicks += interval;

	if (internalLightTicks >= lightChangeInterval) {
		internalLightTicks = 0;
		LightInfo creatureLight;
		creature->getCreatureLight(creatureLight);

		if (creatureLight.level > 0) {
			--creatureLight.level;
			creature->setCreatureLight(creatureLight);
			g_game.changeLight(creature);
		}
	}

	return Condition::executeCondition(creature, interval);
}

void ConditionLight::endCondition(Creature* creature)
{
	creature->setNormalCreatureLight();
	g_game.changeLight(creature);
}

void ConditionLight::addCondition(Creature* creature, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

		const ConditionLight& conditionLight = static_cast<const ConditionLight&>(*addCondition);
		lightInfo.level = conditionLight.lightInfo.level;
		lightInfo.color = conditionLight.lightInfo.color;
		lightChangeInterval = ticks / lightInfo.level;
		internalLightTicks = 0;
		creature->setCreatureLight(lightInfo);
		g_game.changeLight(creature);
	}
}

bool ConditionLight::setParam(ConditionParam_t param, int32_t value)
{
	bool ret = Condition::setParam(param, value);
	if (ret) {
		return false;
	}

	switch (param) {
		case CONDITION_PARAM_LIGHT_LEVEL:
			lightInfo.level = value;
			return true;

		case CONDITION_PARAM_LIGHT_COLOR:
			lightInfo.color = value;
			return true;

		default:
			return false;
	}
}

bool ConditionLight::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_LIGHTCOLOR) {
		uint32_t value;
		if (!propStream.read<uint32_t>(value)) {
			return false;
		}

		lightInfo.color = value;
		return true;
	} else if (attr == CONDITIONATTR_LIGHTLEVEL) {
		uint32_t value;
		if (!propStream.read<uint32_t>(value)) {
			return false;
		}

		lightInfo.level = value;
		return true;
	} else if (attr == CONDITIONATTR_LIGHTTICKS) {
		return propStream.read<uint32_t>(internalLightTicks);
	} else if (attr == CONDITIONATTR_LIGHTINTERVAL) {
		return propStream.read<uint32_t>(lightChangeInterval);
	}
	return Condition::unserializeProp(attr, propStream);
}

void ConditionLight::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	// TODO: color and level could be serialized as 8-bit if we can retain backwards
	// compatibility, but perhaps we should keep it like this in case they increase
	// in the future...
	propWriteStream.write<uint8_t>(CONDITIONATTR_LIGHTCOLOR);
	propWriteStream.write<uint32_t>(lightInfo.color);

	propWriteStream.write<uint8_t>(CONDITIONATTR_LIGHTLEVEL);
	propWriteStream.write<uint32_t>(lightInfo.level);

	propWriteStream.write<uint8_t>(CONDITIONATTR_LIGHTTICKS);
	propWriteStream.write<uint32_t>(internalLightTicks);

	propWriteStream.write<uint8_t>(CONDITIONATTR_LIGHTINTERVAL);
	propWriteStream.write<uint32_t>(lightChangeInterval);
}
