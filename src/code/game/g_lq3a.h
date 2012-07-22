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
#ifndef __G_LQ3A_H__
#define __G_LQ3A_H__

#define LQ3A_SVC_BROADCAST	(-1)	/**< clientNum parameter for broadcasting commands with trap_SendServerCommand(). */
#define LQ3A_INVALID_HANDLE	(-1)	/**< Invalid file handle value for files read in with LQ3A_ReadFile(). */
#define LQ3A_MAX_FILE_SIZE	8192	/**< Maximum allowed file size in bytes of files read by LQ3A. */
#define LQ3A_MAX_MAPLIST	256		/**< Maximum number of maps supported by the map rotation system. */
#define LQ3A_MAX_PM_IVALUE	9999	/**< Max integer value of shared player movement variables,
											limited to prevent overflowing the CS_LQ3A_CONFIG configuration string. */
#define LQ3A_MAX_PM_FVALUE	9999.0f	/**< Max floating point value of shared player movement variables,
											limited to prevent overflowing the CS_LQ3A_CONFIG configuration string. */

/** Argument ordering for map list files. */
enum
{
	LQ3A_MAPLIST_ARG_NAME,
	LQ3A_MAPLIST_ARG_TITLE,
	LQ3A_MAPLIST_ARG_MIN,
	LQ3A_MAPLIST_ARG_MAX,
	LQ3A_MAPLIST_ARG_CONFIG,
	LQ3A_MAPLIST_ARG_FLAGS,

	NUM_LQ3A_MAPLIST_ARGS
};

/** Map entry flags. */
#define LQ3A_MAP_VISITED	0x01	/**< The map has be used in the current cycle. */

/** This structure describes a map in the maplist. */
typedef struct
{
	char	cName[MAX_QPATH];			/**< Filename. */
	char	cTitle[MAX_TOKEN_CHARS];	/**< Mapname. */
	int		iMin;						/**< Minimum number of desired players. */
	int		iMax;						/**< Maximum number of desired players. */
	char	cConfig[MAX_QPATH];			/**< Optional configuration file to use for the map. */
	uint	uFlags;						/**< See LQ3A_MAP_* flags. */

} lq3a_maplist_entry_t, *plq3a_maplist_entry_t;

typedef struct
{
	char					cFile[MAX_QPATH];		/**< The filename used to populate the map list,
															used to ensure the saved state is valid in LQ3A_RestoreMapListState(). */
	lq3a_maplist_entry_t	Map[LQ3A_MAX_MAPLIST];	/**< Array of map entries. */
	int						iCount;					/**< Number of maps in the map list. */
	int						iCurrent;				/**< Index of the current map, set to LQ3A_MAPLIST_NOT_IN_ROTATION
															when the current map is not in the map list.*/
	qboolean				bSurpressNextCycle;		/**< Suppresses the nextmap selection within LQ3A_SelectNextMap() for one call.
															Used when the next map has been voted in. */
	qboolean				bRestartMap;			/**< Set to qtrue in LQ3A_SelectNextMap() when the 'level.nextmap' command
															will execute the 'map_restart' command. */
} lq3a_maplist_t;

/** This structure describes a list of maps suitable for the next map selection,
		Use LQ3A_GetMapListPickList() to populate this structure. */
typedef struct
{
	plq3a_maplist_entry_t	pMap[LQ3A_MAX_MAPLIST];	/**< Map entries in the pick list. */
	int						iCount;					/**< Number of maps in the pick list. */
	int						iCurrent;				/**< Index of the current map, set to LQ3A_MAPLIST_NOT_IN_ROTATION
															when the current map is not in the pick list. */
} lq3a_maplist_picklist_t, *plq3a_maplist_picklist_t;

/** Value of lq3a_maplist_t::uCurrent when the current map is not in the map list. */
#define LQ3A_MAP_NOT_IN_LIST	-1

#define LQ3A_HIGHSCORE_IDENT		('L' + ('Q' << 8) + ('3' << 16) + ('H' << 24))	/**< Magic number used to identify high score files. */
#define LQ3A_HIGHSCORE_VERSION		0x02U				/**< File format version. Increment this if changes have been made which
																make older formats incompatible with the new format. */
#define LQ3A_HIGHSCORE_DIR			"highscores"		/**< Directory to which our high score files will be saved in. */

/** Maximum size of g_highScoreTag cvar in bytes. */
#define LQ3A_MAX_HIGHSCORE_TAG_SIZE	16

/** High score file header. */
typedef struct
{
	uint	uID;								/**< Must equal LQ3A_HIGHSCORE_IDENT. */
	uint	uVersion;							/**< Must equal LQ3A_HIGHSCORE_VERSION. */
	uint	uCRC32;								/**< Not used. */
	char	cMapName[MAX_QPATH];				/**< Mapname without the bsp extension. */
	char	cTag[LQ3A_MAX_HIGHSCORE_TAG_SIZE];	/**< Value of g_highscoreTag cvar at the time the scores where set. */
	int		iTimeLimit;							/**< Value of timelimit cvar at the time the scores where set. */
	int		iFragLimit;							/**< Value of fraglimit cvar at the time the scores where set. */
	int		iCaptureLimit;						/**< Value of capturelimit cvar at the time the scores where set. */
	uint	uCount;								/**< Count of score entries in the file.*/

} lq3a_highscore_header_t;

/** Real bytes offsets for the lq3a_highscore_header_t structure. */
#define LQ3A_HIGHSCORE_HEADER_SIZEOF	(MAX_QPATH+LQ3A_MAX_HIGHSCORE_TAG_SIZE+28L)

/** Maps short names to quake items, see s_lq3a_short_name_map[]. */
typedef struct s_lq3a_item_short_name
{
	pcchar		pShortName;								/**< LQ3A short name. */
	pcchar		pClassName;								/**< Quake class name. */
	gitem_t		*pItem;									/**< Pointer to the structure which describes the item. */
	vmCvar_t	*pSpawnCvar;							/**< Pointer to the cvar structure which describes the spawn short name for this item. */
	struct s_lq3a_item_short_name *pSpawnShortItem;		/**< Pointer to the structure which describes the parsed spawn cvar short item. */
	char		cSpawnCvarName[32];						/**< Name of the cvar pointed to by lq3a_item_ref_t::pSpawnCvar.
																We should use a constant to define the size here but 32 bytes is enough.
																This must appear at the end of the structure due to QVM compilation issues. */
} lq3a_item_short_name_t, *plq3a_item_short_name_t;

/** LQ3A_ParseItems() result. */
typedef struct
{
	plq3a_item_short_name_t	pFirstItem;
	gitem_t					*pFirstWeapon;
	int						iWeapons;
	gitem_t					*pFirstPowerup;
	int						iPowerups;
	gitem_t					*pFirstHoldable;
	int						iHoldables;

} lq3a_parse_items_t, *plq3a_parse_items_t;

/* Globals. */
extern int		g_pm_hookPullSpeed;					/**< bg_pmove.c */
extern int		g_pm_refireTime[WP_NUM_WEAPONS];	/**< bg_pmove.c */
extern int		g_pm_switchSpeed;					/**< bg_pmove.c */
extern float	g_pm_hasteFactor;					/**< bg_pmove.c */
extern int		g_pm_jumpVelocity;					/**< bg_pmove.c */

/* Function definitions. */
extern void			LQ3A_WriteCvarTableToFile(pcchar pFileName, qboolean bDefaultValues);	/**< g_main.c */
extern cvarTable_t	*LQ3A_FindCvarByName(pcchar pName);										/**< g_main.c */
extern qboolean		LQ3A_GetCvarName(vmCvar_t *pVmCvar, pchar pBuffer, int iSize);			/**< g_main.c */
extern void			LQ3A_UpdateCvarByName(pcchar pName, qboolean bSurpressTracking);		/**< g_main.c */
extern qboolean		LQ3A_GameHasLimits(void);
extern int			LQ3A_EntityToEntityNum(gentity_t *pEntity);
extern gentity_t	*LQ3A_ClientToEntity(gclient_t *pClient);
extern void			LQ3A_SendServerCommand(gentity_t *pEntity, pcchar pFormat, ...);
extern void			LQ3A_RegisterItems(void);
extern qboolean		LQ3A_CvarChanged(cvarTable_t *pCvar);
extern gitem_t		*LQ3A_GetSpawnItem(gentity_t *pEntity, gitem_t *pItem);
extern void			LQ3A_RestartMap(float fWarmUp);
extern int			LQ3A_GetSpawnSpotCount(void);
extern int			LQ3A_GetVacantPlayerSlots(void);
extern qboolean		LQ3A_CanClientSpectate(gentity_t *pEntity);
extern void			LQ3A_CompleteClientMoveToSpectatorTeam(gentity_t *pEntity);
extern void			LQ3A_GiveClientInititalInventory(gclient_t *pClient);
extern int			LQ3A_GetItemQuantityValue(gitem_t *pItem);
extern int			LQ3A_GetMaxAmmoValue(int iWeapon);
extern int			LQ3A_GetRailStyleFromUserInfo(pcchar pUserInfo);
extern void			LQ3A_ClientCampCheck(gclient_t *pClient);
extern qboolean		LQ3A_GetClientIndexInSortedScores(int iClient, pint piIndex);
extern qboolean		LQ3A_FileExists(pcchar pFileName);
extern int			LQ3A_ReadFile(pcchar pFileName, pchar pBuffer, int iSize, pint puFileSize);
extern void			LQ3A_LoadMapList(void);
extern void			LQ3A_SelectNextMap(void);
extern void			LQ3A_SaveMapListState(void);
extern void			LQ3A_LoadMotd(void);
extern void			LQ3A_LoadHighScores(void);
extern void			LQ3A_SaveHighScores(void);
extern void			LQ3A_InitGame(void);
extern void			LQ3A_SvCmdExportConfig(void);

#endif /* __G_LQ3A_H__ */
