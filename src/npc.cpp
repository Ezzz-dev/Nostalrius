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

#include "npc.h"
#include "game.h"
#include "tools.h"
#include "position.h"
#include "player.h"
#include "spawn.h"
#include "script.h"
#include "behaviourdatabase.h"

extern Game g_game;

uint32_t Npc::npcAutoID = 0x80000000;

void Npcs::loadNpcs()
{
	std::cout << ">> Loading npcs..." << std::endl;

	std::vector<boost::filesystem::path> files;
	getFilesInDirectory("data/npc/", ".npc", files);
	for (auto file : files)
	{
		std::string npcName = file.filename().string();
		int32_t end = npcName.find_first_of('/');
		npcName = npcName.substr(end + 1, npcName.length() - end);
		end = npcName.find_first_of('.');
		npcName = npcName.substr(0, end);

		Npc* npc = Npc::createNpc(npcName);
		if (!npc) {
			return;
		}

		g_game.placeCreature(npc, npc->getMasterPos(), false, true);
	}
}

void Npcs::reload()
{
	const std::map<uint32_t, Npc*>& npcs = g_game.getNpcs();

	for (const auto& it : npcs) {
		it.second->reload();
	}
}

Npc* Npc::createNpc(const std::string& name)
{
	std::unique_ptr<Npc> npc(new Npc(name));
	npc->filename = "data/npc/" + name + ".npc";
	if (!npc->load()) {
		return nullptr;
	}

	return npc.release();
}

Npc::Npc(const std::string& name) :
	Creature(),
	filename("data/npc/" + name + ".npc"),
	masterRadius(0),
	staticMovementTime(0),
	loaded(false),
	behaviourDatabase(nullptr)
{
	baseSpeed = 5;
	reset();
}

Npc::~Npc()
{
	reset();
}

void Npc::addList()
{
	g_game.addNpc(this);
}

void Npc::removeList()
{
	g_game.removeNpc(this);
}

bool Npc::load()
{
	if (loaded) {
		return true;
	}

	reset();

	ScriptReader script;
	if (!script.open(filename)) {
		return false;
	}

	while (true) {
		script.nextToken();

		if (script.Token == ENDOFFILE) {
			break;
		}

		if (script.Token != IDENTIFIER) {
			script.error("identifier expected");
			return false;
		}

		std::string ident = script.getIdentifier();
		script.readSymbol('=');

		if (ident == "name") {
			name = script.readString();
		} else if (ident == "outfit") {
			script.readSymbol('(');
			uint8_t* c;
			currentOutfit.lookType = script.readNumber();
			script.readSymbol(',');
			if (currentOutfit.lookType > 0) {
				c = script.readBytesequence();
				currentOutfit.lookHead = c[0];
				currentOutfit.lookBody = c[1];
				currentOutfit.lookLegs = c[2];
				currentOutfit.lookFeet = c[3];
			} else {
				currentOutfit.lookTypeEx = script.readNumber();
			}
			script.readSymbol(')');
		} else if (ident == "home") {
			script.readCoordinate(masterPos.x, masterPos.y, masterPos.z);
		} else if (ident == "radius") {
			masterRadius = script.readNumber();
		} else if (ident == "behaviour") {
			if (behaviourDatabase) {
				script.error("behaviour database already defined");
				return false;
			}

			behaviourDatabase = new BehaviourDatabase(this);
			if (!behaviourDatabase->loadDatabase(script)) {
				return false;
			}
		}
	}

	script.close();
	return true;
}

void Npc::reset()
{
	loaded = false;
	focusCreature = 0;
	conversationEndTime = 0;

	if (behaviourDatabase) {
		delete behaviourDatabase;
		behaviourDatabase = nullptr;
	}
}

void Npc::reload()
{
	loaded = false;

	reset();
	load();

	if (baseSpeed > 0) {
		addEventWalk();
	}
}

bool Npc::canSee(const Position& pos) const
{
	if (pos.z != getPosition().z) {
		return false;
	}
	return Creature::canSee(getPosition(), pos, 3, 3);
}

std::string Npc::getDescription(int32_t) const
{
	std::string descr;
	descr.reserve(name.length() + 1);
	descr.assign(name);
	descr.push_back('.');
	return descr;
}

void Npc::onCreatureAppear(Creature* creature, bool isLogin)
{
	Creature::onCreatureAppear(creature, isLogin);

	if (creature == this) {
		if (baseSpeed > 0) {
			addEventWalk();
		}
	} else if (Player* player = creature->getPlayer()) {
		spectators.insert(player);
		updateIdleStatus();
	}
}

void Npc::onRemoveCreature(Creature* creature, bool isLogout)
{
	Creature::onRemoveCreature(creature, isLogout);

	if (!behaviourDatabase) {
		return;
	}

	Player* player = creature->getPlayer();
	if (player) {
		if (player->getID() == focusCreature) {
			behaviourDatabase->react(SITUATION_VANISH, player, "");
		}

		spectators.erase(player);
		updateIdleStatus();
	}
}

void Npc::onCreatureMove(Creature* creature, const Tile* newTile, const Position& newPos,
                         const Tile* oldTile, const Position& oldPos, bool teleport)
{
	Creature::onCreatureMove(creature, newTile, newPos, oldTile, oldPos, teleport);

	if (!behaviourDatabase) {
		return;
	}

	Player* player = creature->getPlayer();
	if (player && player->getID() == focusCreature) {
		if (!Position::areInRange<3, 3, 0>(creature->getPosition(), getPosition())) {
			behaviourDatabase->react(SITUATION_VANISH, player, "");
		}
	}

	if (creature != this) {
		if (player) {
			if (player->canSee(position)) {
				spectators.insert(player);
			} else {
				spectators.erase(player);
			}

			updateIdleStatus();
		}
	}
}

void Npc::onCreatureSay(Creature* creature, SpeakClasses type, const std::string& text)
{
	if (creature->getID() == id || type != TALKTYPE_SAY || !behaviourDatabase) {
		return;
	}

	Player* player = creature->getPlayer();
	if (player) {
		if (!Position::areInRange<3, 3>(creature->getPosition(), getPosition())) {
			return;
		}

		lastTalkCreature = creature->getID();

		if (focusCreature == 0) {
			behaviourDatabase->react(SITUATION_ADDRESS, player, text);
		} else if (focusCreature != player->getID()) {
			behaviourDatabase->react(SITUATION_BUSY, player, text);
		} else if (focusCreature == player->getID()) {
			behaviourDatabase->react(SITUATION_NONE, player, text);
		}
	}
}

void Npc::onThink(uint32_t interval)
{
	Creature::onThink(interval);

	if (!isIdle && focusCreature == 0 && baseSpeed > 0 && getTimeSinceLastMove() >= 100 + getStepDuration()) {
		addEventWalk();
	}

	if (!behaviourDatabase) {
		return;
	}

	if (focusCreature) {
		Player* player = g_game.getPlayerByID(focusCreature);
		if (player) {
			turnToCreature(player);

			if (conversationEndTime != 0 && OTSYS_TIME() > conversationEndTime) {
				if (player) {
					behaviourDatabase->react(SITUATION_VANISH, player, "");
				}
			}
		}
	}
}

void Npc::doSay(const std::string& text)
{
	if (lastTalkCreature == focusCreature) {
		conversationEndTime = OTSYS_TIME() + 60000;
	}

	g_game.internalCreatureSay(this, TALKTYPE_SAY, text, false);
}

bool Npc::getNextStep(Direction& dir, uint32_t& flags)
{
	if (Creature::getNextStep(dir, flags)) {
		return true;
	}

	if (baseSpeed <= 0) {
		return false;
	}

	if (focusCreature != 0) {
		return false;
	}

	if (OTSYS_TIME() < staticMovementTime) {
		return false;
	}

	if (getTimeSinceLastMove() < 100 + getStepDuration() + getStepSpeed()) {
		return false;
	}

	return getRandomStep(dir);
}

void Npc::setIdle(bool idle)
{
	if (isRemoved() || getHealth() <= 0) {
		return;
	}

	isIdle = idle;

	if (isIdle) {
		onIdleStatus();
	}
}

void Npc::updateIdleStatus()
{
	bool status = spectators.empty();
	if (status != isIdle) {
		setIdle(status);
	}
}

bool Npc::canWalkTo(const Position& fromPos, Direction dir) const
{
	if (masterRadius == 0) {
		return false;
	}

	Position toPos = getNextPosition(dir, fromPos);
	if (!Spawns::isInZone(masterPos, masterRadius, toPos)) {
		return false;
	}

	Tile* tile = g_game.map.getTile(toPos);
	if (!tile || tile->queryAdd(0, *this, 1, 0) != RETURNVALUE_NOERROR) {
		return false;
	}

	if (tile->hasFlag(TILESTATE_BLOCKPATH)) {
		return false;
	}

	if (tile->hasHeight(1)) {
		return false;
	}

	return true;
}

bool Npc::getRandomStep(Direction& dir) const
{
	std::vector<Direction> dirList;
	const Position& creaturePos = getPosition();

	if (canWalkTo(creaturePos, DIRECTION_NORTH)) {
		dirList.push_back(DIRECTION_NORTH);
	}

	if (canWalkTo(creaturePos, DIRECTION_SOUTH)) {
		dirList.push_back(DIRECTION_SOUTH);
	}

	if (canWalkTo(creaturePos, DIRECTION_EAST)) {
		dirList.push_back(DIRECTION_EAST);
	}

	if (canWalkTo(creaturePos, DIRECTION_WEST)) {
		dirList.push_back(DIRECTION_WEST);
	}

	if (dirList.empty()) {
		return false;
	}

	dir = dirList[uniform_random(0, dirList.size() - 1)];
	return true;
}

void Npc::doMoveTo(const Position& target)
{
	std::forward_list<Direction> listDir;
	if (getPathTo(target, listDir, 1, 1, true, true)) {
		startAutoWalk(listDir);
	}
}

void Npc::turnToCreature(Creature* creature)
{
	const Position& creaturePos = creature->getPosition();
	const Position& myPos = getPosition();
	const auto dx = Position::getOffsetX(myPos, creaturePos);
	const auto dy = Position::getOffsetY(myPos, creaturePos);

	float tan;
	if (dx != 0) {
		tan = static_cast<float>(dy) / dx;
	} else {
		tan = 10;
	}

	Direction dir;
	if (std::abs(tan) < 1) {
		if (dx > 0) {
			dir = DIRECTION_WEST;
		} else {
			dir = DIRECTION_EAST;
		}
	} else {
		if (dy > 0) {
			dir = DIRECTION_NORTH;
		} else {
			dir = DIRECTION_SOUTH;
		}
	}
	g_game.internalCreatureTurn(this, dir);
}

void Npc::setCreatureFocus(Creature* creature)
{
	if (creature) {
		focusCreature = creature->getID();
		turnToCreature(creature);
	} else {
		focusCreature = 0;
	}
}