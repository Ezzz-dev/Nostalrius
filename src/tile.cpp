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

#include <boost/range/adaptor/reversed.hpp>

#include "tile.h"

#include "creature.h"
#include "combat.h"
#include "game.h"
#include "mailbox.h"
#include "monster.h"
#include "movement.h"
#include "teleport.h"

extern Game g_game;
extern MoveEvents* g_moveEvents;

StaticTile real_nullptr_tile(0xFFFF, 0xFFFF, 0xFF);
Tile& Tile::nullptr_tile = real_nullptr_tile;

bool Tile::hasProperty(ITEMPROPERTY prop) const
{
	if (ground && ground->hasProperty(prop)) {
		return true;
	}

	if (const TileItemVector* items = getItemList()) {
		for (const Item* item : *items) {
			if (item->hasProperty(prop)) {
				return true;
			}
		}
	}
	return false;
}

bool Tile::hasProperty(const Item* exclude, ITEMPROPERTY prop) const
{
	assert(exclude);

	if (ground && exclude != ground && ground->hasProperty(prop)) {
		return true;
	}

	if (const TileItemVector* items = getItemList()) {
		for (const Item* item : *items) {
			if (item != exclude && item->hasProperty(prop)) {
				return true;
			}
		}
	}

	return false;
}

bool Tile::hasHeight(uint32_t n) const
{
	uint32_t height = 0;

	if (ground) {
		if (ground->hasProperty(CONST_PROP_HASHEIGHT)) {
			++height;
		}

		if (n == height) {
			return true;
		}
	}

	if (const TileItemVector* items = getItemList()) {
		for (const Item* item : *items) {
			if (item->hasProperty(CONST_PROP_HASHEIGHT)) {
				++height;
			}

			if (n == height) {
				return true;
			}
		}
	}
	return false;
}

size_t Tile::getCreatureCount() const
{
	if (const CreatureVector* creatures = getCreatures()) {
		return creatures->size();
	}
	return 0;
}

size_t Tile::getItemCount() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->size();
	}
	return 0;
}

uint32_t Tile::getTopItemCount() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getTopItemCount();
	}
	return 0;
}

uint32_t Tile::getDownItemCount() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getDownItemCount();
	}
	return 0;
}

std::string Tile::getDescription(int32_t) const
{
	return "You dont know why, but you cant see anything!";
}

Teleport* Tile::getTeleportItem() const
{
	if (!hasFlag(TILESTATE_TELEPORT)) {
		return nullptr;
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getTeleport()) {
				return (*it)->getTeleport();
			}
		}
	}
	return nullptr;
}

MagicField* Tile::getFieldItem() const
{
	if (!hasFlag(TILESTATE_MAGICFIELD)) {
		return nullptr;
	}

	if (ground && ground->getMagicField()) {
		return ground->getMagicField();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getMagicField()) {
				return (*it)->getMagicField();
			}
		}
	}
	return nullptr;
}

Mailbox* Tile::getMailbox() const
{
	if (!hasFlag(TILESTATE_MAILBOX)) {
		return nullptr;
	}

	if (ground && ground->getMailbox()) {
		return ground->getMailbox();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getMailbox()) {
				return (*it)->getMailbox();
			}
		}
	}
	return nullptr;
}

BedItem* Tile::getBedItem() const
{
	if (!hasFlag(TILESTATE_BED)) {
		return nullptr;
	}

	if (ground && ground->getBed()) {
		return ground->getBed();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getBed()) {
				return (*it)->getBed();
			}
		}
	}
	return nullptr;
}

Creature* Tile::getTopCreature() const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (!creatures->empty()) {
			return *creatures->begin();
		}
	}
	return nullptr;
}

const Creature* Tile::getBottomCreature() const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (!creatures->empty()) {
			return *creatures->rbegin();
		}
	}
	return nullptr;
}

Creature* Tile::getTopVisibleCreature(const Creature* creature) const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (creature) {
			const Player* player = creature->getPlayer();
			if (player && player->isAccessPlayer()) {
				return getTopCreature();
			}

			for (Creature* tileCreature : *creatures) {
				if (creature->canSeeCreature(tileCreature)) {
					return tileCreature;
				}
			}
		} else {
			for (Creature* tileCreature : *creatures) {
				if (!tileCreature->isInvisible()) {
					const Player* player = tileCreature->getPlayer();
					if (!player || !player->isInGhostMode()) {
						return tileCreature;
					}
				}
			}
		}
	}
	return nullptr;
}

const Creature* Tile::getBottomVisibleCreature(const Creature* creature) const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (creature) {
			const Player* player = creature->getPlayer();
			if (player && player->isAccessPlayer()) {
				return getBottomCreature();
			}

			for (auto it = creatures->rbegin(), end = creatures->rend(); it != end; ++it) {
				if (creature->canSeeCreature(*it)) {
					return *it;
				}
			}
		} else {
			for (auto it = creatures->rbegin(), end = creatures->rend(); it != end; ++it) {
				if (!(*it)->isInvisible()) {
					const Player* player = (*it)->getPlayer();
					if (!player || !player->isInGhostMode()) {
						return *it;
					}
				}
			}
		}
	}
	return nullptr;
}

Item* Tile::getTopDownItem() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getTopDownItem();
	}
	return nullptr;
}

Item* Tile::getTopTopItem() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getTopTopItem();
	}
	return nullptr;
}

Item* Tile::getItemByTopOrder(int32_t topOrder)
{
	//topOrder:
	//1: borders
	//2: ladders, signs, splashes
	//3: doors etc
	//4: creatures
	if (TileItemVector* items = getItemList()) {
		for (auto it = ItemVector::const_reverse_iterator(items->getEndTopItem()), end = ItemVector::const_reverse_iterator(items->getBeginTopItem()); it != end; ++it) {
			if (Item::items[(*it)->getID()].alwaysOnTopOrder == topOrder) {
				return (*it);
			}
		}
	}
	return nullptr;
}

Thing* Tile::getTopVisibleThing(const Creature* creature)
{
	Thing* thing = getTopVisibleCreature(creature);
	if (thing) {
		return thing;
	}

	TileItemVector* items = getItemList();
	if (items) {
		for (ItemVector::const_iterator it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
			return (*it);
		}

		for (auto it = ItemVector::const_reverse_iterator(items->getEndTopItem()), end = ItemVector::const_reverse_iterator(items->getBeginTopItem()); it != end; ++it) {
			return (*it);
		}
	}

	return ground;
}

void Tile::onAddTileItem(Item* item)
{
	setTileFlags(item);

	const Position& cylinderMapPos = getPosition();

	SpectatorVec list;
	g_game.map.getSpectators(list, cylinderMapPos, true);

	//send to client
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendAddTileItem(this, cylinderMapPos, item);
		}
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->onAddTileItem(this, cylinderMapPos);
	}
}

void Tile::onUpdateTileItem(Item* oldItem, const ItemType& oldType, Item* newItem, const ItemType& newType)
{
	const Position& cylinderMapPos = getPosition();

	SpectatorVec list;
	g_game.map.getSpectators(list, cylinderMapPos, true);

	//send to client
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendUpdateTileItem(this, cylinderMapPos, newItem);
		}
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->onUpdateTileItem(this, cylinderMapPos, oldItem, oldType, newItem, newType);
	}
}

void Tile::onRemoveTileItem(const SpectatorVec& list, const std::vector<int32_t>& oldStackPosVector, Item* item)
{
	resetTileFlags(item);

	const Position& cylinderMapPos = getPosition();
	const ItemType& iType = Item::items[item->getID()];

	//send to client
	size_t i = 0;
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendRemoveTileThing(cylinderMapPos, oldStackPosVector[i++]);
		}
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->onRemoveTileItem(this, cylinderMapPos, iType, item);
	}
}

void Tile::onUpdateTile(const SpectatorVec& list)
{
	const Position& cylinderMapPos = getPosition();

	//send to clients
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendUpdateTile(this, cylinderMapPos);
	}
}

ReturnValue Tile::queryAdd(int32_t, const Thing& thing, uint32_t, uint32_t flags, Creature*) const
{
	if (const Creature* creature = thing.getCreature()) {
		if (hasBitSet(FLAG_NOLIMIT, flags)) {
			return RETURNVALUE_NOERROR;
		}

		if (hasBitSet(FLAG_PATHFINDING, flags) && hasFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH)) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (ground == nullptr) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (const Monster* monster = creature->getMonster()) {
			if (hasFlag(TILESTATE_PROTECTIONZONE | TILESTATE_TELEPORT)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasFlag(TILESTATE_IMMOVABLEBLOCKPATH | TILESTATE_IMMOVABLENOFIELDBLOCKPATH)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasBitSet(FLAG_PLACECHECK, flags) && hasFlag(TILESTATE_BLOCKSOLID)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			const CreatureVector* creatures = getCreatures();
			if (monster->canPushCreatures() && !monster->isSummon()) {
				if (creatures) {
					for (Creature* tileCreature : *creatures) {
						if (tileCreature->getPlayer() && tileCreature->getPlayer()->isInGhostMode()) {
							continue;
						}

						const Monster* creatureMonster = tileCreature->getMonster();
						if (!creatureMonster || !tileCreature->isPushable() ||
							(creatureMonster->isSummon() && creatureMonster->getMaster()->getPlayer())) {
							return RETURNVALUE_NOTPOSSIBLE;
						}
					}
				}
			} else if (creatures && !creatures->empty()) {
				for (const Creature* tileCreature : *creatures) {
					if (!tileCreature->isInGhostMode()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}
				}
			}

			if (hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasBitSet(FLAG_PATHFINDING, flags) && hasFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasFlag(TILESTATE_BLOCKSOLID) || (hasBitSet(FLAG_PATHFINDING, flags) && hasFlag(TILESTATE_NOFIELDBLOCKPATH))) {
				if (!(monster->canPushItems() || hasBitSet(FLAG_IGNOREBLOCKITEM, flags))) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			if (!monster->hasCondition(CONDITION_AGGRESSIVE) &&
				!hasBitSet(FLAG_IGNOREFIELDDAMAGE, flags)) {
				if (hasFlag(TILESTATE_FIREDAMAGE) && !monster->isImmune(COMBAT_FIREDAMAGE)) {
					return RETURNVALUE_NOTPOSSIBLE;
				}

				if (hasFlag(TILESTATE_POISONDAMAGE) && !monster->isImmune(COMBAT_EARTHDAMAGE)) {
					return RETURNVALUE_NOTPOSSIBLE;
				}

				if (hasFlag(TILESTATE_ENERGYDAMAGE) && !monster->isImmune(COMBAT_ENERGYDAMAGE)) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			return RETURNVALUE_NOERROR;
		}

		const CreatureVector* creatures = getCreatures();
		if (const Player* player = creature->getPlayer()) {
			if (creatures && !creatures->empty() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, flags) && !player->isAccessPlayer()) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasBitSet(FLAG_PATHFINDING, flags) && hasFlag(TILESTATE_BLOCKPATH)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (player->getParent() == nullptr && hasFlag(TILESTATE_NOLOGOUT)) {
				//player is trying to login to a "no logout" tile
				return RETURNVALUE_NOTPOSSIBLE;
			}

			const Tile* playerTile = player->getTile();
			if (playerTile && player->isPzLocked()) {
				if (!playerTile->hasFlag(TILESTATE_PVPZONE)) {
					//player is trying to enter a pvp zone while being pz-locked
					if (hasFlag(TILESTATE_PVPZONE)) {
						return RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE;
					}
				} else if (!hasFlag(TILESTATE_PVPZONE)) {
					// player is trying to leave a pvp zone while being pz-locked
					return RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE;
				}

				if ((!playerTile->hasFlag(TILESTATE_NOPVPZONE) && hasFlag(TILESTATE_NOPVPZONE)) ||
					(!playerTile->hasFlag(TILESTATE_PROTECTIONZONE) && hasFlag(TILESTATE_PROTECTIONZONE))) {
					// player is trying to enter a non-pvp/protection zone while being pz-locked
					return RETURNVALUE_PLAYERISPZLOCKED;
				}
			}
		} else if (creatures && !creatures->empty() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, flags)) {
			for (const Creature* tileCreature : *creatures) {
				if (!tileCreature->isInGhostMode()) {
					return RETURNVALUE_NOTENOUGHROOM;
				}
			}
		}

		if (!hasBitSet(FLAG_IGNOREBLOCKITEM, flags)) {
			//If the FLAG_IGNOREBLOCKITEM bit isn't set we dont have to iterate every single item
			if (hasFlag(TILESTATE_BLOCKSOLID)) {
				return RETURNVALUE_NOTENOUGHROOM;
			}
		} else {
			//FLAG_IGNOREBLOCKITEM is set
			if (ground) {
				const ItemType& iiType = Item::items[ground->getID()];
				if (iiType.blockSolid) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			if (const auto items = getItemList()) {
				for (const Item* item : *items) {
					const ItemType& iiType = Item::items[item->getID()];
					if (iiType.blockSolid && !iiType.moveable) {
						return RETURNVALUE_NOTPOSSIBLE;
					}
				}
			}
		}
	} else if (const Item* item = thing.getItem()) {
		const TileItemVector* items = getItemList();
		if (items && items->size() >= 0xFFFF) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (hasBitSet(FLAG_NOLIMIT, flags)) {
			return RETURNVALUE_NOERROR;
		}

		bool itemIsHangable = item->isHangable();
		if (ground == nullptr && !itemIsHangable) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		const CreatureVector* creatures = getCreatures();
		if (creatures && !creatures->empty() && item->isBlocking() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, flags)) {
			for (const Creature* tileCreature : *creatures) {
				if (!tileCreature->isInGhostMode()) {
					return RETURNVALUE_NOTENOUGHROOM;
				}
			}
		}

		if (item->isMagicField() && hasProperty(CONST_PROP_IMMOVABLENOFIELDBLOCKPATH)) {
			return RETURNVALUE_NOTENOUGHROOM;
		}

		if (itemIsHangable && hasFlag(TILESTATE_SUPPORTS_HANGABLE)) {
			if (items) {
				for (const Item* tileItem : *items) {
					if (tileItem->isHangable()) {
						return RETURNVALUE_NEEDEXCHANGE;
					}
				}
			}
		} else {
			if (ground) {
				const ItemType& iiType = Item::items[ground->getID()];
				if (iiType.blockSolid) {
					if (!iiType.allowPickupable || item->isMagicField() || item->isBlocking()) {
						if (!item->isPickupable()) {
							return RETURNVALUE_NOTENOUGHROOM;
						}

						if (!iiType.hasHeight || iiType.pickupable || iiType.isBed()) {
							return RETURNVALUE_NOTENOUGHROOM;
						}
					}
				}
			}

			if (items) {
				for (const Item* tileItem : *items) {
					const ItemType& iiType = Item::items[tileItem->getID()];
					if (!iiType.blockSolid) {
						continue;
					}

					if (iiType.allowPickupable && !item->isMagicField() && !item->isBlocking()) {
						continue;
					}

					if (!item->isPickupable()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}

					if (!iiType.hasHeight || iiType.pickupable || iiType.isBed()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}
				}
			}
		}
	}
	return RETURNVALUE_NOERROR;
}

ReturnValue Tile::queryMaxCount(int32_t, const Thing&, uint32_t count, uint32_t& maxQueryCount, uint32_t) const
{
	maxQueryCount = std::max<uint32_t>(1, count);
	return RETURNVALUE_NOERROR;
}

ReturnValue Tile::queryRemove(const Thing& thing, uint32_t count, uint32_t flags) const
{
	int32_t index = getThingIndex(&thing);
	if (index == -1) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	const Item* item = thing.getItem();
	if (item == nullptr) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (count == 0 || (item->isStackable() && count > item->getItemCount())) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (!item->isMoveable() && !hasBitSet(FLAG_IGNORENOTMOVEABLE, flags)) {
		return RETURNVALUE_NOTMOVEABLE;
	}

	return RETURNVALUE_NOERROR;
}

Tile* Tile::queryDestination(int32_t&, const Thing&, Item** destItem, uint32_t&)
{
	Thing* destThing = getTopDownItem();
	if (destThing) {
		*destItem = destThing->getItem();
	}

	return this;
}

void Tile::addThing(Thing* thing)
{
	addThing(0, thing);
}

void Tile::addThing(int32_t, Thing* thing)
{
	Creature* creature = thing->getCreature();
	if (creature) {
		g_game.map.clearSpectatorCache();
		creature->setParent(this);
		CreatureVector* creatures = makeCreatures();
		creatures->insert(creatures->end(), creature);
	} else {
		Item* item = thing->getItem();
		if (item == nullptr) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		TileItemVector* items = getItemList();
		if (items && items->size() >= 0xFFFF) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		item->setParent(this);

		const ItemType& itemType = Item::items[item->getID()];
		if (itemType.isGroundTile()) {
			if (ground == nullptr) {
				ground = item;
				onAddTileItem(item);
			} else {
				const ItemType& oldType = Item::items[ground->getID()];

				Item* oldGround = ground;
				ground->setParent(nullptr);
				g_game.ReleaseItem(ground);
				ground = item;
				resetTileFlags(oldGround);
				setTileFlags(item);
				onUpdateTileItem(oldGround, oldType, item, itemType);
				postRemoveNotification(oldGround, nullptr, 0);
			}
		} else if (itemType.alwaysOnTop) {
			if (itemType.isSplash() && items) {
				//remove old splash if exists
				SpectatorVec spectators;
				g_game.map.getSpectators(spectators, getPosition(), true, true);
				for (ItemVector::const_iterator it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
					Item* oldSplash = *it;
					if (!Item::items[oldSplash->getID()].isSplash()) {
						continue;
					}

					removeThing(oldSplash, 1);
					oldSplash->setParent(nullptr);
					g_game.ReleaseItem(oldSplash);
					postRemoveNotification(oldSplash, nullptr, 0);
					onUpdateTile(spectators);
					break;
				}
			}

			bool isInserted = false;

			if (items) {
				for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
					//Note: this is different from internalAddThing
					if (itemType.alwaysOnTopOrder <= Item::items[(*it)->getID()].alwaysOnTopOrder) {
						items->insert(it, item);
						isInserted = true;
						break;
					}
				}
			} else {
				items = makeItemList();
			}

			if (!isInserted) {
				items->push_back(item);
			}

			onAddTileItem(item);
		} else {
			if (itemType.isMagicField()) {
				//remove old field item if exists
				if (items) {
					for (ItemVector::const_iterator it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
						MagicField* oldField = (*it)->getMagicField();
						if (oldField) {
							if (oldField->isReplaceable()) {
								removeThing(oldField, 1);

								oldField->setParent(nullptr);
								g_game.ReleaseItem(oldField);
								postRemoveNotification(oldField, nullptr, 0);
								break;
							} else {
								//This magic field cannot be replaced.
								item->setParent(nullptr);
								g_game.ReleaseItem(item);
								return;
							}
						}
					}
				}
			}

			items = makeItemList();
			items->insert(items->getBeginDownItem(), item);
			items->addDownItemCount(1);
			onAddTileItem(item);
		}
	}
}

void Tile::updateThing(Thing* thing, uint16_t itemId, uint32_t count)
{
	int32_t index = getThingIndex(thing);
	if (index == -1) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	Item* item = thing->getItem();
	if (item == nullptr) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	const ItemType& oldType = Item::items[item->getID()];
	const ItemType& newType = Item::items[itemId];
	resetTileFlags(item);
	item->setID(itemId);
	item->setSubType(count);
	setTileFlags(item);
	onUpdateTileItem(item, oldType, item, newType);
}

void Tile::replaceThing(uint32_t index, Thing* thing)
{
	int32_t pos = index;

	Item* item = thing->getItem();
	if (item == nullptr) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	Item* oldItem = nullptr;
	bool isInserted = false;

	if (ground) {
		if (pos == 0) {
			oldItem = ground;
			ground = item;
			isInserted = true;
		}

		--pos;
	}

	TileItemVector* items = getItemList();
	if (items && !isInserted) {
		int32_t topItemSize = getTopItemCount();
		if (pos < topItemSize) {
			auto it = items->getBeginTopItem();
			it += pos;

			oldItem = (*it);
			it = items->erase(it);
			items->insert(it, item);
			isInserted = true;
		}

		pos -= topItemSize;
	}

	CreatureVector* creatures = getCreatures();
	if (creatures) {
		if (!isInserted && pos < static_cast<int32_t>(creatures->size())) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		pos -= static_cast<uint32_t>(creatures->size());
	}

	if (items && !isInserted) {
		int32_t downItemSize = getDownItemCount();
		if (pos < downItemSize) {
			auto it = items->getBeginDownItem() + pos;
			oldItem = *it;
			it = items->erase(it);
			items->insert(it, item);
			isInserted = true;
		}
	}

	if (isInserted) {
		item->setParent(this);

		resetTileFlags(oldItem);
		setTileFlags(item);
		const ItemType& oldType = Item::items[oldItem->getID()];
		const ItemType& newType = Item::items[item->getID()];
		onUpdateTileItem(oldItem, oldType, item, newType);

		oldItem->setParent(nullptr);
		return /*RETURNVALUE_NOERROR*/;
	}
}

void Tile::removeThing(Thing* thing, uint32_t count)
{
	Creature* creature = thing->getCreature();
	if (creature) {
		CreatureVector* creatures = getCreatures();
		if (creatures) {
			auto it = std::find(creatures->begin(), creatures->end(), thing);
			if (it != creatures->end()) {
				g_game.map.clearSpectatorCache();
				creatures->erase(it);
			}
		}
		return;
	}

	Item* item = thing->getItem();
	if (!item) {
		return;
	}

	int32_t index = getThingIndex(item);
	if (index == -1) {
		return;
	}

	if (item == ground) {
		ground->setParent(nullptr);
		ground = nullptr;

		SpectatorVec list;
		g_game.map.getSpectators(list, getPosition(), true);
		onRemoveTileItem(list, std::vector<int32_t>(list.size(), 0), item);
		return;
	}

	TileItemVector* items = getItemList();
	if (!items) {
		return;
	}

	const ItemType& itemType = Item::items[item->getID()];
	if (itemType.alwaysOnTop) {
		auto it = std::find(items->getBeginTopItem(), items->getEndTopItem(), item);
		if (it == items->getEndTopItem()) {
			return;
		}

		std::vector<int32_t> oldStackPosVector;

		SpectatorVec list;
		g_game.map.getSpectators(list, getPosition(), true);
		for (Creature* spectator : list) {
			if (Player* tmpPlayer = spectator->getPlayer()) {
				oldStackPosVector.push_back(getStackposOfItem(tmpPlayer, item));
			}
		}

		item->setParent(nullptr);
		items->erase(it);
		onRemoveTileItem(list, oldStackPosVector, item);
	} else {
		auto it = std::find(items->getBeginDownItem(), items->getEndDownItem(), item);
		if (it == items->getEndDownItem()) {
			return;
		}

		if (itemType.stackable && count != item->getItemCount()) {
			uint8_t newCount = static_cast<uint8_t>(std::max<int32_t>(0, static_cast<int32_t>(item->getItemCount() - count)));
			item->setItemCount(newCount);
			onUpdateTileItem(item, itemType, item, itemType);
		} else {
			std::vector<int32_t> oldStackPosVector;

			SpectatorVec list;
			g_game.map.getSpectators(list, getPosition(), true);
			for (Creature* spectator : list) {
				if (Player* tmpPlayer = spectator->getPlayer()) {
					oldStackPosVector.push_back(getStackposOfItem(tmpPlayer, item));
				}
			}

			item->setParent(nullptr);
			items->erase(it);
			items->addDownItemCount(-1);
			onRemoveTileItem(list, oldStackPosVector, item);
		}
	}
}

void Tile::removeCreature(Creature* creature)
{
	g_game.map.getQTNode(tilePos.x, tilePos.y)->removeCreature(creature);
	removeThing(creature, 0);
}

int32_t Tile::getThingIndex(const Thing* thing) const
{
	int32_t n = -1;
	if (ground) {
		if (ground == thing) {
			return 0;
		}
		++n;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		const Item* item = thing->getItem();
		if (item && item->isAlwaysOnTop()) {
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				++n;
				if (*it == item) {
					return n;
				}
			}
		} else {
			n += items->getTopItemCount();
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		if (thing->getCreature()) {
			for (Creature* creature : *creatures) {
				++n;
				if (creature == thing) {
					return n;
				}
			}
		} else {
			n += creatures->size();
		}
	}

	if (items) {
		const Item* item = thing->getItem();
		if (item && !item->isAlwaysOnTop()) {
			for (auto it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
				++n;
				if (*it == item) {
					return n;
				}
			}
		}
	}
	return -1;
}

int32_t Tile::getClientIndexOfCreature(const Player* player, const Creature* creature) const
{
	int32_t n;
	if (ground) {
		n = 1;
	} else {
		n = 0;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		n += items->getTopItemCount();
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (const Creature* c : boost::adaptors::reverse(*creatures)) {
			if (c == creature) {
				return n;
			} else if (player->canSeeCreature(c)) {
				++n;
			}
		}
	}
	return -1;
}

int32_t Tile::getStackposOfCreature(const Player* player, const Creature* creature) const
{
	int32_t n;
	if (ground) {
		n = 1;
	} else {
		n = 0;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		n += items->getTopItemCount();
		if (n >= 10) {
			return -1;
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (const Creature* c : boost::adaptors::reverse(*creatures)) {
			if (c == creature) {
				return n;
			} else if (player->canSeeCreature(c)) {
				if (++n >= 10) {
					return -1;
				}
			}
		}
	}
	return -1;
}

int32_t Tile::getStackposOfItem(const Player* player, const Item* item) const
{
	int32_t n = 0;
	if (ground) {
		if (ground == item) {
			return n;
		}
		++n;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		if (item->isAlwaysOnTop()) {
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				if (*it == item) {
					return n;
				} else if (++n == 10) {
					return -1;
				}
			}
		} else {
			n += items->getTopItemCount();
			if (n >= 10) {
				return -1;
			}
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (const Creature* creature : *creatures) {
			if (player->canSeeCreature(creature)) {
				if (++n >= 10) {
					return -1;
				}
			}
		}
	}

	if (items && !item->isAlwaysOnTop()) {
		for (auto it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
			if (*it == item) {
				return n;
			} else if (++n >= 10) {
				return -1;
			}
		}
	}
	return -1;
}

size_t Tile::getFirstIndex() const
{
	return 0;
}

size_t Tile::getLastIndex() const
{
	return getThingCount();
}

uint32_t Tile::getItemTypeCount(uint16_t itemId, int32_t subType /*= -1*/) const
{
	uint32_t count = 0;
	if (ground && ground->getID() == itemId) {
		count += Item::countByType(ground, subType);
	}

	const TileItemVector* items = getItemList();
	if (items) {
		for (const Item* item : *items) {
			if (item->getID() == itemId) {
				count += Item::countByType(item, subType);
			}
		}
	}
	return count;
}

Thing* Tile::getThing(size_t index) const
{
	if (ground) {
		if (index == 0) {
			return ground;
		}

		--index;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		uint32_t topItemSize = items->getTopItemCount();
		if (index < topItemSize) {
			return items->at(items->getDownItemCount() + index);
		}
		index -= topItemSize;
	}

	if (const CreatureVector* creatures = getCreatures()) {
		if (index < creatures->size()) {
			return (*creatures)[index];
		}
		index -= creatures->size();
	}

	if (items && index < items->getDownItemCount()) {
		return items->at(index);
	}
	return nullptr;
}

void Tile::postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link /*= LINK_OWNER*/)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->postAddNotification(thing, oldParent, index, LINK_NEAR);
	}

	//add a reference to this item, it may be deleted after being added (mailbox for example)
	Creature* creature = thing->getCreature();
	Item* item;
	if (creature) {
		creature->incrementReferenceCounter();
		item = nullptr;
	} else {
		item = thing->getItem();
		if (item) {
			item->incrementReferenceCounter();
		}
	}

	if (link == LINK_OWNER) {
		if (hasFlag(TILESTATE_TELEPORT)) {
			Teleport* teleport = getTeleportItem();
			if (teleport) {
				teleport->addThing(thing);
			}
		} else if (hasFlag(TILESTATE_MAILBOX)) {
			Mailbox* mailbox = getMailbox();
			if (mailbox) {
				mailbox->addThing(thing);
			}
		}

		//calling movement scripts
		if (creature) {
			g_moveEvents->onCreatureMove(creature, this, MOVE_EVENT_STEP_IN);
		} else if (item) {
			g_moveEvents->onItemMove(item, this, true);
		}
	}

	//release the reference to this item onces we are finished
	if (creature) {
		g_game.ReleaseCreature(creature);
	} else if (item) {
		g_game.ReleaseItem(item);
	}
}

void Tile::postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), true, true);

	if (getThingCount() > 8) {
		onUpdateTile(list);
	}

	for (Creature* spectator : list) {
		spectator->getPlayer()->postRemoveNotification(thing, newParent, index, LINK_NEAR);
	}

	//calling movement scripts
	Creature* creature = thing->getCreature();
	if (creature) {
		g_moveEvents->onCreatureMove(creature, this, MOVE_EVENT_STEP_OUT);
	} else {
		Item* item = thing->getItem();
		if (item) {
			g_moveEvents->onItemMove(item, this, false);
		}
	}
}

void Tile::internalAddThing(Thing* thing)
{
	internalAddThing(0, thing);
}

void Tile::internalAddThing(uint32_t, Thing* thing)
{
	thing->setParent(this);

	Creature* creature = thing->getCreature();
	if (creature) {
		g_game.map.clearSpectatorCache();
		CreatureVector* creatures = makeCreatures();
		creatures->insert(creatures->end(), creature);
	} else {
		Item* item = thing->getItem();
		if (item == nullptr) {
			return;
		}

		const ItemType& itemType = Item::items[item->getID()];
		if (itemType.isGroundTile()) {
			if (ground == nullptr) {
				ground = item;
				setTileFlags(item);
			}
			return;
		}

		TileItemVector* items = makeItemList();
		if (items->size() >= 0xFFFF) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		if (itemType.alwaysOnTop) {
			bool isInserted = false;
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				if (Item::items[(*it)->getID()].alwaysOnTopOrder > itemType.alwaysOnTopOrder) {
					items->insert(it, item);
					isInserted = true;
					break;
				}
			}

			if (!isInserted) {
				items->push_back(item);
			}
		} else {
			items->insert(items->getBeginDownItem(), item);
			items->addDownItemCount(1);
		}

		setTileFlags(item);
	}
}

void Tile::setTileFlags(const Item* item)
{
	if (item->hasProperty(CONST_PROP_IMMOVABLEBLOCKSOLID)) {
		setFlag(TILESTATE_IMMOVABLEBLOCKSOLID);
	}

	if (item->hasProperty(CONST_PROP_BLOCKPATH)) {
		setFlag(TILESTATE_BLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_NOFIELDBLOCKPATH)) {
		setFlag(TILESTATE_NOFIELDBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLENOFIELDBLOCKPATH)) {
		setFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH);
	}

	if (item->getTeleport()) {
		setFlag(TILESTATE_TELEPORT);
	}

	if (item->getMagicField()) {
		setFlag(TILESTATE_MAGICFIELD);
	}

	if (item->getMailbox()) {
		setFlag(TILESTATE_MAILBOX);
	}

	if (item->hasProperty(CONST_PROP_BLOCKSOLID)) {
		setFlag(TILESTATE_BLOCKSOLID);
	}

	if (item->getBed()) {
		setFlag(TILESTATE_BED);
	}

	if (item->getCombatType() == COMBAT_FIREDAMAGE) {
		setFlag(TILESTATE_FIREDAMAGE);
	}

	if (item->getCombatType() == COMBAT_ENERGYDAMAGE) {
		setFlag(TILESTATE_ENERGYDAMAGE);
	}

	if (item->getCombatType() == COMBAT_EARTHDAMAGE) {
		setFlag(TILESTATE_POISONDAMAGE);
	}

	const Container* container = item->getContainer();
	if (container && container->getDepotLocker()) {
		setFlag(TILESTATE_DEPOT);
	}

	if (item->hasProperty(CONST_PROP_SUPPORTHANGABLE)) {
		setFlag(TILESTATE_SUPPORTS_HANGABLE);
	}
}

void Tile::resetTileFlags(const Item* item)
{
	if (item->hasProperty(CONST_PROP_BLOCKSOLID) && !hasProperty(item, CONST_PROP_BLOCKSOLID)) {
		resetFlag(TILESTATE_BLOCKSOLID);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLEBLOCKSOLID) && !hasProperty(item, CONST_PROP_IMMOVABLEBLOCKSOLID)) {
		resetFlag(TILESTATE_IMMOVABLEBLOCKSOLID);
	}

	if (item->hasProperty(CONST_PROP_BLOCKPATH) && !hasProperty(item, CONST_PROP_BLOCKPATH)) {
		resetFlag(TILESTATE_BLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_NOFIELDBLOCKPATH) && !hasProperty(item, CONST_PROP_NOFIELDBLOCKPATH)) {
		resetFlag(TILESTATE_NOFIELDBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLEBLOCKPATH) && !hasProperty(item, CONST_PROP_IMMOVABLEBLOCKPATH)) {
		resetFlag(TILESTATE_IMMOVABLEBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLENOFIELDBLOCKPATH) && !hasProperty(item, CONST_PROP_IMMOVABLENOFIELDBLOCKPATH)) {
		resetFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH);
	}

	if (item->getTeleport()) {
		resetFlag(TILESTATE_TELEPORT);
	}

	if (item->getMagicField()) {
		resetFlag(TILESTATE_MAGICFIELD);
	}

	if (item->getMailbox()) {
		resetFlag(TILESTATE_MAILBOX);
	}

	if (item->getBed()) {
		resetFlag(TILESTATE_BED);
	}

	if (item->getCombatType() == COMBAT_FIREDAMAGE) {
		resetFlag(TILESTATE_FIREDAMAGE);
	}

	if (item->getCombatType() == COMBAT_ENERGYDAMAGE) {
		resetFlag(TILESTATE_ENERGYDAMAGE);
	}

	if (item->getCombatType() == COMBAT_EARTHDAMAGE) {
		resetFlag(TILESTATE_POISONDAMAGE);
	}

	const Container* container = item->getContainer();
	if (container && container->getDepotLocker()) {
		resetFlag(TILESTATE_DEPOT);
	}

	if (item->hasProperty(CONST_PROP_SUPPORTHANGABLE)) {
		resetFlag(TILESTATE_SUPPORTS_HANGABLE);
	}
}

bool Tile::isMoveableBlocking() const
{
	return !ground || hasFlag(TILESTATE_BLOCKSOLID);
}

Item* Tile::getUseItem() const
{
	const TileItemVector* items = getItemList();
	if (!items || items->size() == 0) {
		return ground;
	}

	for (Item* item : boost::adaptors::reverse(*items)) {
		if (Item::items[item->getID()].forceUse) {
			return item;
		}
	}

	Item* item = items->getTopDownItem();
	if (!item) {
		item = items->getTopTopItem();
	}
	return item;
}
