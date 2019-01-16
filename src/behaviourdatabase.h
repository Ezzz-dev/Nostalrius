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

#ifndef FS_BEHAVIOURDATABASE_H_4E785D4C545C455E1A0C2A9C84D5EFFF
#define FS_BEHAVIOURDATABASE_H_4E785D4C545C455E1A0C2A9C84D5EFFF

#include "script.h"
#include "enums.h"

enum BehaviourSituation_t
{
	SITUATION_ADDRESS = 1,
	SITUATION_BUSY,
	SITUATION_VANISH,
	SITUATION_NONE,
};

enum NpcBehaviourType_t
{
	BEHAVIOUR_TYPE_NOP = 0, // returns true on conditions
	BEHAVIOUR_TYPE_STRING, // match string, or NPC say
	BEHAVIOUR_TYPE_NUMBER, // return a number
	BEHAVIOUR_TYPE_OPERATION, // <, =, >, >=, <=, <>
	BEHAVIOUR_TYPE_MESSAGE_COUNT, // get quantity in player message
	BEHAVIOUR_TYPE_IDLE, // idle npc
	BEHAVIOUR_TYPE_QUEUE, // queue talking creature
	BEHAVIOUR_TYPE_TOPIC, // get/set topic
	BEHAVIOUR_TYPE_PRICE, // get/set price
	BEHAVIOUR_TYPE_DATA, // get/set data
	BEHAVIOUR_TYPE_ITEM, // get/set item
	BEHAVIOUR_TYPE_AMOUNT, // get/set amount
	BEHAVIOUR_TYPE_TEXT, // get/set string
	BEHAVIOUR_TYPE_HEALTH, // get/set health
	BEHAVIOUR_TYPE_COUNT, // count amount of items
	BEHAVIOUR_TYPE_CREATEMONEY, // create money
	BEHAVIOUR_TYPE_COUNTMONEY, // get player total money
	BEHAVIOUR_TYPE_DELETEMONEY, // remove money from player
	BEHAVIOUR_TYPE_CREATE, // create item
	BEHAVIOUR_TYPE_DELETE, // deletes an item
	BEHAVIOUR_TYPE_EFFECTME, // effect on NPC
	BEHAVIOUR_TYPE_EFFECTOPP, // effect on player
	BEHAVIOUR_TYPE_BURNING, // get/set burning
	BEHAVIOUR_TYPE_POISON, // get/set poison
	BEHAVIOUR_TYPE_SPELLKNOWN, // check if spell is known
	BEHAVIOUR_TYPE_SPELLLEVEL, // get spell level
	BEHAVIOUR_TYPE_TEACHSPELL, // player learn spell
	BEHAVIOUR_TYPE_LEVEL, // get player level
	BEHAVIOUR_TYPE_RANDOM, // random value
	BEHAVIOUR_TYPE_QUESTVALUE, // get/set quest value
	BEHAVIOUR_TYPE_TELEPORT, // teleport player to position
	BEHAVIOUR_TYPE_SORCERER, // get/set vocation
	BEHAVIOUR_TYPE_DRUID, // get/set vocation
	BEHAVIOUR_TYPE_KNIGHT, // get/set vocation
	BEHAVIOUR_TYPE_PALADIN, // get/set vocation
	BEHAVIOUR_TYPE_ISPREMIUM, // is account premium
	BEHAVIOUR_TYPE_PVPENFORCED, // get world type pvpenforced
	BEHAVIOUR_TYPE_MALE, // is player male
	BEHAVIOUR_TYPE_FEMALE, // is player female
	BEHAVIOUR_TYPE_PZLOCKED, // is player pz locked
	BEHAVIOUR_TYPE_PROMOTED, // check if player promoted
	BEHAVIOUR_TYPE_PROFESSION, // get/set profession
	BEHAVIOUR_TYPE_PROMOTE, // promote the player
	BEHAVIOUR_TYPE_SUMMON, // summons a monster
	BEHAVIOUR_TYPE_EXPERIENCE, // grant experience to a player
	BEHAVIOUR_TYPE_BALANCE, // return player balance
	BEHAVIOUR_TYPE_WITHDRAW, // withdraw from player bank balance
	BEHAVIOUR_TYPE_DEPOSIT, // deposit x amount of gold
	BEHAVIOUR_TYPE_TRANSFER, // transfer x amount of gold
	BEHAVIOUR_TYPE_BLESS, // add blessing to player
	BEHAVIOUR_TYPE_CREATECONTAINER, // create a container of an item in particular
	BEHAVIOUR_TYPE_TOWN, // change player town
};

enum NpcBehaviourOperator_t
{
	BEHAVIOUR_OPERATOR_LESSER_THAN = '<',
	BEHAVIOUR_OPERATOR_EQUALS = '=',
	BEHAVIOUR_OPERATOR_GREATER_THAN = '>',
	BEHAVIOUR_OPERATOR_GREATER_OR_EQUALS = 'G',
	BEHAVIOUR_OPERATOR_LESSER_OR_EQUALS = 'L',
	BEHAVIOUR_OPERATOR_NOT_EQUALS = 'N',
	BEHAVIOUR_OPERATOR_MULTIPLY = '*',
	BEHAVIOUR_OPERATOR_SUM = '+',
	BEHAVIOUR_OPERATOR_RES = '-',
};

enum NpcBehaviourParameterSearch_t
{
	BEHAVIOUR_PARAMETER_NONE,
	BEHAVIOUR_PARAMETER_ASSIGN,
	BEHAVIOUR_PARAMETER_ONE,
	BEHAVIOUR_PARAMETER_TWO,
	BEHAVIOUR_PARAMETER_THREE,
};

class Npc;
class Player;

struct NpcBehaviourNode
{
	NpcBehaviourType_t type;
	int32_t number;
	std::string string;
	NpcBehaviourNode* left;
	NpcBehaviourNode* right;

	NpcBehaviourNode() : type(), number(0), left(nullptr), right(nullptr) { }
	~NpcBehaviourNode() {
		delete left;
		delete right;
	}

	NpcBehaviourNode* clone() {
		NpcBehaviourNode* copy = new NpcBehaviourNode();
		copy->type = type;
		copy->number = number;
		copy->string = string;
		if (left) {
			copy->left = left->clone();
		}
		if (right) {
			copy->right = right->clone();
		}
		return copy;
	}
};

struct NpcBehaviourCondition
{
	NpcBehaviourType_t type;
	BehaviourSituation_t situation;
	std::string string;
	int32_t number;
	NpcBehaviourNode* expression;

	NpcBehaviourCondition() : type(), situation(SITUATION_NONE), string(), number(0), expression(nullptr) {}
	~NpcBehaviourCondition() {
		delete expression;
	}

	//non-copyable
	NpcBehaviourCondition(const NpcBehaviourCondition&) = delete;
	NpcBehaviourCondition& operator=(const NpcBehaviourCondition&) = delete;

	bool setCondition(NpcBehaviourType_t _type, int32_t _number, const std::string& _string);
};

struct NpcBehaviourAction
{
	NpcBehaviourType_t type;
	std::string string;
	int32_t number;
	NpcBehaviourNode* expression;
	NpcBehaviourNode* expression2;
	NpcBehaviourNode* expression3;

	NpcBehaviourAction() :
		type(),
		string(),
		number(0),
		expression(nullptr),
		expression2(nullptr),
		expression3(nullptr) {}
	~NpcBehaviourAction() {
		delete expression;
		delete expression2;
		delete expression3;
	}

	NpcBehaviourAction* clone() {
		NpcBehaviourAction* copy = new NpcBehaviourAction();
		copy->type = type;
		copy->string = string;
		copy->number = number;
		if (expression) {
			copy->expression = expression->clone();
		}
		if (expression2) {
			copy->expression2 = expression2->clone();
		}
		if (expression3) {
			copy->expression3 = expression3->clone();
		}
		return copy;
	}
};

struct NpcBehaviour
{
	BehaviourSituation_t situation = SITUATION_NONE;
	uint32_t priority = 0;
	std::vector<NpcBehaviourCondition*> conditions;
	std::vector<NpcBehaviourAction*> actions;

	NpcBehaviour() = default;
	~NpcBehaviour() {
		for (auto condition : conditions) {
			delete condition;
		}

		for (auto action : actions) {
			delete action;
		}
	}

	//non-copyable
	NpcBehaviour(const NpcBehaviour&) = delete;
	NpcBehaviour& operator=(const NpcBehaviour&) = delete;
};

struct NpcQueueEntry
{
	uint32_t playerId;
	std::string text;
};

class BehaviourDatabase
{
	public:
		BehaviourDatabase(Npc* _npc);
		~BehaviourDatabase();

		// non-copyable
		BehaviourDatabase(const BehaviourDatabase&) = delete;
		BehaviourDatabase& operator=(const BehaviourDatabase&) = delete;

		bool loadDatabase(ScriptReader& script);
		bool loadBehaviour(ScriptReader& script);
		bool loadConditions(ScriptReader& script, NpcBehaviour* behaviour);
		bool loadActions(ScriptReader& script, NpcBehaviour* behaviour);
		NpcBehaviourNode* readValue(ScriptReader& script);
		NpcBehaviourNode* readFactor(ScriptReader& script, NpcBehaviourNode* nextNode);

		void react(BehaviourSituation_t situation, Player* player, const std::string& message);

		static bool compareBehaviour(const NpcBehaviour* left, const NpcBehaviour* right) {
			return left->priority >= right->priority;
		}

	private:

		bool checkCondition(const NpcBehaviourCondition* condition, Player* player, const std::string& message);
		void checkAction(const NpcBehaviourAction* action, Player* player, const std::string& message);

		int32_t evaluate(NpcBehaviourNode* node, Player* player, const std::string& message = "");

		int32_t checkOperation(Player* player, NpcBehaviourNode* node, const std::string& message);
		int32_t searchDigit(const std::string& message);
		bool searchWord(const std::string& pattern, const std::string& message);

		std::string parseResponse(Player* player, const std::string& message);
		void attendCustomer(uint32_t playerId);
		void queueCustomer(uint32_t playerId, const std::string& message);
		void idle();
		void reset();

		int32_t topic;
		int32_t data;
		int32_t type;
		int32_t price;
		int32_t amount;
		int32_t delay;

		std::string string;

		Npc* npc = nullptr;
		NpcBehaviour* previousBehaviour = nullptr;
		NpcBehaviour* priorityBehaviour = nullptr;

		std::list<NpcQueueEntry> queueList;
		std::vector<uint32_t> delayedEvents;
		std::list<NpcBehaviour*> behaviourEntries;
		std::recursive_mutex mutex;

};

#endif
