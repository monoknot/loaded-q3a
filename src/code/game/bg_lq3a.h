/**
 * @brief		Loaded Q3A
 * @author		Kevin Fell <kevin@kevin-fell.co.uk>
 * @link		http://www.kevin-fell.co.uk/
 * @copyright	(C) 1999-2012 Kevin Fell.
 * 
 * Loaded Q3A
 *
 * Copyright (C) 1999-2012 Kevin Fell
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#pragma once
#ifndef __BG_LQ3A_H__
#define __BG_LQ3A_H__

#ifndef MISSIONPACK
#define LQ3A_VERSION "2.0 RC1"
#else
#define LQ3A_VERSION "2.0 TA RC1"
#endif /* !MISSIONPACK */

/* Type definitions. */
typedef unsigned short	ushort;
typedef int							*pint;
typedef unsigned int	uint,		*puint;
typedef char			*pchar,		**ppchar;
typedef const char		*pcchar,	**ppcchar;

#define LQ3A_PARSE_IN_SIZE(s,p)		(s+sizeof(s)-p)
#define LQ3A_PARSE_IN_SIZE2(s,l,p)	(s+l-p)

/* LQ3A_Parse() flags. */
#define LQ3A_PARSE_COMMENTS				0x01
#define LQ3A_PARSE_BREAK_ON_CRLF		0x02
#define LQ3A_PARSE_BREAK_ON_EMPTY		0x04
#define LQ3A_PARSE_BREAK_ON_DELIMITER	0x08

enum
{
	LQ3A_PARSE_R_OK,
	LQ3A_PARSE_R_COMPLETE,
	LQ3A_PARSE_R_CRLF,
	LQ3A_PARSE_R_EMPTY,
	LQ3A_PARSE_R_DELIMITER
};

/** Calculates array size. */
#define LQ3A_ARRAYSIZE(a)	(sizeof(a) / sizeof(a[0]))

/** Offsets for the CS_LQ3A_CONFIG configuration string. */
enum
{
	LQ3A_CS_CONFIG_QVM,				/**< '1' when the server is running the game qvm. */
	LQ3A_CS_CONFIG_MISSIONPACK,		/**< '1' when the mission pack content is present on the server,
											this enables the mission pack 'mode' on the client. */
	LQ3A_CS_CONFIG_HIGHSCORES,		/**< '1' when the high scoring system is enabled. */
	
	/* Shared player movement config for prediction. */
	LQ3A_CS_CONFIG_HOOK_PULLSPEED,			/**< g_hookPullSpeed */
	LQ3A_CS_CONFIG_REFIRE_HOOK,				/**< g_refireHook */
	LQ3A_CS_CONFIG_REFIRE_GAUNTLET,			/**< g_refireGauntlet */
	LQ3A_CS_CONFIG_REFIRE_MACHINEGUN,		/**< g_refireMachinegun */
	LQ3A_CS_CONFIG_REFIRE_SHOTGUN,			/**< g_refireShotgun */
	LQ3A_CS_CONFIG_REFIRE_GRENADE_LAUNCHER,	/**< g_refireGrenadeLaucnher */
	LQ3A_CS_CONFIG_REFIRE_ROCKET_LAUNCHER,	/**< g_refireRocketLauncher */
	LQ3A_CS_CONFIG_REFIRE_LIGHTNINGGUN,		/**< g_refireLightninggun */
	LQ3A_CS_CONFIG_REFIRE_RAILGUN,			/**< g_refireRailgun */
	LQ3A_CS_CONFIG_REFIRE_PLASMAGUN,		/**< g_refirePlasmagun */
	LQ3A_CS_CONFIG_REFIRE_BFG,				/**< g_refireBFG */
	LQ3A_CS_CONFIG_REFIRE_NAILGUN,			/**< g_refireNailgun (Always present, even without MISSIONPACK defined) */
	LQ3A_CS_CONFIG_REFIRE_PROX_LAUNCHER,	/**< g_refireProxLauncher (Always present, even without MISSIONPACK defined) */
	LQ3A_CS_CONFIG_REFIRE_CHAINGUN,			/**< g_refireChaingun (Always present, even without MISSIONPACK defined) */
	LQ3A_CS_CONFIG_SWITCH_SPEED,			/**< g_switchSpeed */
	LQ3A_CS_CONFIG_HASTE_FACTOR,			/**< g_hasteFactor */
	LQ3A_CS_CONFIG_JUMP_VELOCITY,			/**< g_jumpVelocity */

	LQ3A_CS_CONFIG_SHELL_SPREAD,			/**< g_damageShellSpread */
	LQ3A_CS_CONFIG_NUM_ENTRIES
};

/** Follow types for spectators. */
typedef enum
{
	LQ3A_FOLLOW_AUTO,				/**< Preserves current type when SPECTATOR_FOLLOW or SPECTATOR_FOLLOW_THIRSPERSON
											is already set. Defaults to SPECTATOR_FOLLOW_THIRDPERSON. */
	LQ3A_FOLLOW_TYPE_FIRSTPERSON,
	LQ3A_FOLLOW_TYPE_THIRDPERSON

} lq3a_follow_type_t;

#define LQ3A_MAX_HIGHSCORE_ENTRIES	10
#define LQ3A_MAX_DATE				10	/**< Maximum size in bytes of a date string, format "dd/mm/yyyy". */

/* High score entry flags. */
#define LQ3A_HSEF_BOT	0x01
#define LQ3A_HSEF_DATE	0x02

/** This structure describes a high score entry. The structure is saved to the high score
	file in the order they appear in the structure in little endian format. */
typedef struct
{
	char	cGamerTag[MAX_NETNAME];
	uint	uScore;
	uint	uFlags;					/**< See LQ3A_HSEF_* definitions. */
	uint	uBotSkill;
	uint	uImpresiveCount;
	uint	uHumiliationCount;
	uint	uExcellentCount;
	uint	uCaptureCount;
	uint	uAssistCount;
	uint	uDefenceCount;
	uint	uAccuracy;
	uint	uEfficiency;
	char	cDate[LQ3A_MAX_DATE+1];	/**< Space for null terminator. */

	/* ITEMS BELOW THIS LINE ARE NOT SAVED TO FILE. */

	int		iClient;

} lq3a_highscore_entry_t, *plq3a_highscore_entry_t;

/** Real bytes offsets for the lq3a_highscore_entry_t structure minus items not saved to file. */
#define LQ3A_HIGHSCORE_ENTRY_SIZEOF	(MAX_NETNAME+44L+LQ3A_MAX_DATE)

/* Function definitions. */
extern void				LQ3A_SetParseOptions(uint uOpt);
extern void				LQ3A_SetParseDelimiter(char cChr);
extern void				LQ3A_ParsePath(pchar pFileName);
extern int				LQ3A_ParseToCrLf(pchar *ppIn, size_t uIn);
extern qboolean			LQ3A_ParseComment(pchar *ppIn, size_t uIn);
extern int				LQ3A_ParseArg(pchar *ppIn, uint uIn, pchar pOut, uint uOut, puint puOutLen);
extern int				LQ3A_Clampi(int iValue, int iMin, int iMax);
extern float			LQ3A_Clampf(float fValue, float fMin, float fMax);
extern struct gitem_s	*LQ3A_FindItemByClassname(pcchar pcClassName);
extern int				LQ3A_GetMaxAmmoValue(int iWeapon); /* g_lq3a.c and cg_lq3a.c */

#endif /* __BG_LQ3A_H__ */
