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

#ifndef FS_CONST_H_0A49B5996F074465BF44B90F4F780E8B
#define FS_CONST_H_0A49B5996F074465BF44B90F4F780E8B

static constexpr int32_t NETWORKMESSAGE_MAXSIZE = 24590;

enum MagicEffectClasses : uint8_t {
	CONST_ME_NONE,

	CONST_ME_DRAWBLOOD = 1,
	CONST_ME_LOSEENERGY = 2,
	CONST_ME_POFF = 3,
	CONST_ME_BLOCKHIT = 4,
	CONST_ME_EXPLOSIONAREA = 5,
	CONST_ME_EXPLOSIONHIT = 6,
	CONST_ME_FIREAREA = 7,
	CONST_ME_YELLOW_RINGS = 8,
	CONST_ME_GREEN_RINGS = 9,
	CONST_ME_HITAREA = 10,
	CONST_ME_TELEPORT = 11,
	CONST_ME_ENERGYHIT = 12,
	CONST_ME_MAGIC_BLUE = 13,
	CONST_ME_MAGIC_RED = 14,
	CONST_ME_MAGIC_GREEN = 15,
	CONST_ME_HITBYFIRE = 16,
	CONST_ME_HITBYPOISON = 17,
	CONST_ME_MORTAREA = 18,
	CONST_ME_SOUND_GREEN = 19,
	CONST_ME_SOUND_RED = 20,
	CONST_ME_POISONAREA = 21,
	CONST_ME_SOUND_YELLOW = 22,
	CONST_ME_SOUND_PURPLE = 23,
	CONST_ME_SOUND_BLUE = 24,
	CONST_ME_SOUND_WHITE = 25,
};

enum ShootType_t : uint8_t {
	CONST_ANI_NONE,

	CONST_ANI_SPEAR = 1,
	CONST_ANI_BOLT = 2,
	CONST_ANI_ARROW = 3,
	CONST_ANI_FIRE = 4,
	CONST_ANI_ENERGY = 5,
	CONST_ANI_POISONARROW = 6,
	CONST_ANI_BURSTARROW = 7,
	CONST_ANI_THROWINGSTAR = 8,
	CONST_ANI_THROWINGKNIFE = 9,
	CONST_ANI_SMALLSTONE = 10,
	CONST_ANI_DEATH = 11,
	CONST_ANI_LARGEROCK = 12,
	CONST_ANI_SNOWBALL = 13,
	CONST_ANI_POWERBOLT = 14,
	CONST_ANI_POISON = 15,
};

enum SpeakClasses : uint8_t {
	TALKTYPE_SAY = 1,
	TALKTYPE_WHISPER = 2,
	TALKTYPE_YELL = 3,
	TALKTYPE_PRIVATE = 4,
	TALKTYPE_CHANNEL_Y = 5, // Yellow
	TALKTYPE_RVR_CHANNEL = 6,
	TALKTYPE_RVR_ANSWER = 7,
	TALKTYPE_RVR_CONTINUE = 8,
	TALKTYPE_BROADCAST = 9,
	TALKTYPE_CHANNEL_R1 = 10, // Red - #c text
	TALKTYPE_PRIVATE_RED = 11, // @name@text
	TALKTYPE_CHANNEL_O = 12, // orange
	TALKTYPE_CHANNEL_R2 = 13, // red anonymous - #d text
	TALKTYPE_MONSTER_YELL = 0x10,
	TALKTYPE_MONSTER_SAY = 0x11,
};

enum MessageClasses : uint8_t {
	MESSAGE_STATUS_CONSOLE_YELLOW = 0x01, //Yellow message in the console
	MESSAGE_STATUS_CONSOLE_LBLUE = 0x04, //Light blue message in the console
	MESSAGE_STATUS_CONSOLE_ORANGE = 0x11, //Orange message in the console
	MESSAGE_STATUS_WARNING = 0x12, //Red message in game window and in the console
	MESSAGE_EVENT_ADVANCE = 0x13, //White message in game window and in the console
	MESSAGE_EVENT_DEFAULT = 0x14, //White message at the bottom of the game window and in the console
	MESSAGE_STATUS_DEFAULT = 0x15, //White message at the bottom of the game window and in the console
	MESSAGE_INFO_DESCR = 0x16, //Green message in game window and in the console
	MESSAGE_STATUS_SMALL = 0x17, //White message at the bottom of the game window"
	MESSAGE_STATUS_CONSOLE_BLUE = 0x18, //Blue message in the console
	MESSAGE_STATUS_CONSOLE_RED = 0x19, //Red message in the console

	MESSAGE_CLASS_FIRST = MESSAGE_STATUS_CONSOLE_YELLOW,
	MESSAGE_CLASS_LAST = MESSAGE_STATUS_CONSOLE_RED,
};

enum FluidTypes_t : uint8_t
{
	FLUID_NONE = 0,
	FLUID_WATER,
	FLUID_WINE,
	FLUID_BEER,
	FLUID_MUD,
	FLUID_BLOOD,
	FLUID_SLIME,
	FLUID_OIL,
	FLUID_URINE,
	FLUID_MILK,
	FLUID_MANAFLUID,
	FLUID_LIFEFLUID,
	FLUID_LEMONADE,
};

enum FluidColor_t : uint8_t
{
	FLUID_COLOR_NONE = 0,
	FLUID_COLOR_BLUE = 1,
	FLUID_COLOR_PURPLE = 2,
	FLUID_COLOR_BROWN = 3,
	FLUID_COLOR_RED = 4,
	FLUID_COLOR_GREEN = 5,
	FLUID_COLOR_YELLOW = 6,
	FLUID_COLOR_WHITE = 7,
};

enum SquareColor_t : uint8_t {
	SQ_COLOR_BLACK = 0,
};

enum TextColor_t : uint8_t {
	TEXTCOLOR_BLUE = 5,
	TEXTCOLOR_LIGHTGREEN = 30,
	TEXTCOLOR_LIGHTBLUE = 35,
	TEXTCOLOR_MAYABLUE = 95,
	TEXTCOLOR_DARKRED = 108,
	TEXTCOLOR_LIGHTGREY = 129,
	TEXTCOLOR_SKYBLUE = 143,
	TEXTCOLOR_PURPLE = 155,
	TEXTCOLOR_RED = 180,
	TEXTCOLOR_ORANGE = 198,
	TEXTCOLOR_YELLOW = 210,
	TEXTCOLOR_WHITE_EXP = 215,
	TEXTCOLOR_NONE = 255,
};

enum Icons_t {
	ICON_POISON = 1 << 0,
	ICON_BURN = 1 << 1,
	ICON_ENERGY =  1 << 2,
	ICON_DRUNK = 1 << 3,
	ICON_MANASHIELD = 1 << 4,
	ICON_PARALYZE = 1 << 5,
	ICON_HASTE = 1 << 6,
	ICON_SWORDS = 1 << 7
};

enum WeaponType_t : uint8_t {
	WEAPON_NONE,
	WEAPON_SWORD,
	WEAPON_CLUB,
	WEAPON_AXE,
	WEAPON_SHIELD,
	WEAPON_DISTANCE,
	WEAPON_WAND,
	WEAPON_AMMO,
};

enum Ammo_t : uint8_t {
	AMMO_NONE,
	AMMO_BOLT,
	AMMO_ARROW,
	AMMO_SPEAR,
	AMMO_THROWINGSTAR,
	AMMO_THROWINGKNIFE,
	AMMO_STONE,
	AMMO_SNOWBALL,
};

enum WeaponAction_t : uint8_t {
	WEAPONACTION_NONE,
	WEAPONACTION_REMOVECOUNT,
	WEAPONACTION_REMOVECHARGE,
	WEAPONACTION_MOVE,
};

enum WieldInfo_t {
	WIELDINFO_LEVEL = 1 << 0,
	WIELDINFO_MAGLV = 1 << 1,
	WIELDINFO_VOCREQ = 1 << 2,
	WIELDINFO_PREMIUM = 1 << 3,
};

enum Skulls_t : uint8_t {
	SKULL_NONE = 0,
	SKULL_YELLOW = 1,
	SKULL_GREEN = 2,
	SKULL_WHITE = 3,
	SKULL_RED = 4,
};

enum PartyShields_t : uint8_t {
	SHIELD_NONE = 0,
	SHIELD_WHITEYELLOW = 1,
	SHIELD_WHITEBLUE = 2,
	SHIELD_BLUE = 3,
	SHIELD_YELLOW = 4
};

enum item_t : uint16_t {
	ITEM_FIREFIELD_PVP_FULL = 2118,
	ITEM_FIREFIELD_PVP_MEDIUM = 2119,
	ITEM_FIREFIELD_PVP_SMALL = 2120,
	ITEM_FIREFIELD_PERSISTENT_FULL = 2123,
	ITEM_FIREFIELD_PERSISTENT_MEDIUM = 2124,
	ITEM_FIREFIELD_PERSISTENT_SMALL = 2125,
	ITEM_FIREFIELD_NOPVP = 2131,

	ITEM_POISONFIELD_PVP = 2121,
	ITEM_POISONFIELD_PERSISTENT = 2127,
	ITEM_POISONFIELD_NOPVP = 2134,

	ITEM_ENERGYFIELD_PVP = 2122,
	ITEM_ENERGYFIELD_PERSISTENT = 2126,
	ITEM_ENERGYFIELD_NOPVP = 2135,

	ITEM_MAGICWALL = 2128,
	ITEM_MAGICWALL_PERSISTENT = 2128,

	ITEM_WILDGROWTH = 2130,
	ITEM_WILDGROWTH_PERSISTENT = 2130,

	ITEM_GOLD_COIN = 3031,
	ITEM_PLATINUM_COIN = 3035,
	ITEM_CRYSTAL_COIN = 3043,

	ITEM_DEPOT = 3502,
	ITEM_LOCKER1 = 3497,

	ITEM_MALE_CORPSE = 4240,
	ITEM_FEMALE_CORPSE = 4247,

	ITEM_FULLSPLASH = 2886,
	ITEM_SMALLSPLASH = 2889,

	ITEM_PARCEL = 3503,
	ITEM_PARCEL_STAMPED = 3504,
	ITEM_LETTER = 3505,
	ITEM_LETTER_STAMPED = 3506,
	ITEM_LABEL = 3507,

	ITEM_AMULETOFLOSS = 3057,

	ITEM_DOCUMENT_RO = 2819, //read-only
};

enum PlayerFlags : uint64_t {
	PlayerFlag_CannotUseCombat = 1 << 0,
	PlayerFlag_CannotAttackPlayer = 1 << 1,
	PlayerFlag_CannotAttackMonster = 1 << 2,
	PlayerFlag_CannotBeAttacked = 1 << 3,
	PlayerFlag_CanConvinceAll = 1 << 4,
	PlayerFlag_CanSummonAll = 1 << 5,
	PlayerFlag_CanIllusionAll = 1 << 6,
	PlayerFlag_CanSenseInvisibility = 1 << 7,
	PlayerFlag_IgnoredByMonsters = 1 << 8,
	PlayerFlag_NotGainInFight = 1 << 9,
	PlayerFlag_HasInfiniteMana = 1 << 10,
	PlayerFlag_HasInfiniteSoul = 1 << 11,
	PlayerFlag_HasNoExhaustion = 1 << 12,
	PlayerFlag_CannotUseSpells = 1 << 13,
	PlayerFlag_CannotPickupItem = 1 << 14,
	PlayerFlag_CanAlwaysLogin = 1 << 15,
	PlayerFlag_CanBroadcast = 1 << 16,
	PlayerFlag_CanEditHouses = 1 << 17,
	PlayerFlag_CannotBeBanned = 1 << 18,
	PlayerFlag_CannotBePushed = 1 << 19,
	PlayerFlag_HasInfiniteCapacity = 1 << 20,
	PlayerFlag_CanPushAllCreatures = 1 << 21,
	PlayerFlag_CanTalkRedPrivate = 1 << 22,
	PlayerFlag_CanTalkRedChannel = 1 << 23,
	PlayerFlag_TalkOrangeHelpChannel = 1 << 24,
	PlayerFlag_NotGainExperience = 1 << 25,
	PlayerFlag_NotGainMana = 1 << 26,
	PlayerFlag_NotGainHealth = 1 << 27,
	PlayerFlag_NotGainSkill = 1 << 28,
	PlayerFlag_SetMaxSpeed = 1 << 29,
	PlayerFlag_SpecialVIP = 1 << 30,
	PlayerFlag_NotGenerateLoot = static_cast<uint64_t>(1) << 31,
	PlayerFlag_CanTalkRedChannelAnonymous = static_cast<uint64_t>(1) << 32,
	PlayerFlag_IgnoreProtectionZone = static_cast<uint64_t>(1) << 33,
	PlayerFlag_IgnoreSpellCheck = static_cast<uint64_t>(1) << 34,
	PlayerFlag_IgnoreWeaponCheck = static_cast<uint64_t>(1) << 35,
	PlayerFlag_CannotBeMuted = static_cast<uint64_t>(1) << 36,
	PlayerFlag_IsAlwaysPremium = static_cast<uint64_t>(1) << 37,
	PlayerFlag_SpecialMoveUse = static_cast<uint64_t>(1) << 38,
};

static constexpr int32_t CHANNEL_GUILD = 0x00;
static constexpr int32_t CHANNEL_PARTY = 0x01;
static constexpr int32_t CHANNEL_RULE_REP = 0x02;
static constexpr int32_t CHANNEL_PRIVATE = 0xFFFF;

#endif
