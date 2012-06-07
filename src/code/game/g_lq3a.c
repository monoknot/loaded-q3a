/**
 * @brief		Loaded Q3A
 * @author		Kevin Fell
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
 *
 * @todo	Powerup 'time' for mission pack items.
 * @todo	Default g_jumpVelocity to JUMP_VELOCITY in the gameCvarTable.
 */

#include "g_local.h"

/********
 * CORE *
 ********/

/** Item short name map, initialised in Q3A_InitShortNameMap(). */
static lq3a_item_short_name_t s_lq3a_short_name_map[] =
{
	{"shard",			"item_armor_shard",			NULL,	&g_spawnShard,				NULL},
	{"combatArmor",		"item_armor_combat",		NULL,	&g_spawnCombatArmor,		NULL},
	{"bodyArmor",		"item_armor_body",			NULL,	&g_spawnBodyArmor,			NULL},
	{"smallHealth",		"item_health_small",		NULL,	&g_spawnSmallHealth,		NULL},
	{"mediumHealth",	"item_health",				NULL,	&g_spawnMediumHealth,		NULL},
	{"largeHealth",		"item_health_large",		NULL,	&g_spawnLargeHealth,		NULL},
	{"megaHealth",		"item_health_mega",			NULL,	&g_spawnMegaHealth,			NULL},
	{"hook",			"weapon_grapplinghook",		NULL,	&g_spawnHook,				NULL},
	{"gauntlet",		"weapon_gauntlet",			NULL,	&g_spawnGauntlet,			NULL},
	{"machinegun",		"weapon_machinegun",		NULL,	&g_spawnMachinegun,			NULL},
	{"shotgun",			"weapon_shotgun",			NULL,	&g_spawnShotgun,			NULL},
	{"glauncher",		"weapon_grenadelauncher",	NULL,	&g_spawnGrenadeLauncher,	NULL},
	{"rlauncher",		"weapon_rocketlauncher",	NULL,	&g_spawnRocketLauncher,		NULL},
	{"lightninggun",	"weapon_lightning",			NULL,	&g_spawnLightninggun,		NULL},
	{"railgun",			"weapon_railgun",			NULL,	&g_spawnRailgun,			NULL},
	{"plasmagun",		"weapon_plasmagun",			NULL,	&g_spawnPlasmagun,			NULL},
	{"bfg",				"weapon_bfg",				NULL,	&g_spawnBFG,				NULL},
	{"shells",			"ammo_shells",				NULL,	&g_spawnShells,				NULL},
	{"bullets",			"ammo_bullets",				NULL,	&g_spawnBullets,			NULL},
	{"grenades",		"ammo_grenades",			NULL,	&g_spawnGrenades,			NULL},
	{"cells",			"ammo_cells",				NULL,	&g_spawnCells,				NULL},
	{"lightning",		"ammo_lightning",			NULL,	&g_spawnLightning,			NULL},
	{"rockets",			"ammo_rockets",				NULL,	&g_spawnRockets,			NULL},
	{"slugs",			"ammo_slugs",				NULL,	&g_spawnSlugs,				NULL},
	{"bfgammo",			"ammo_bfg",					NULL,	&g_spawnBFGAmmo,			NULL},
	{"teleporter",		"holdable_teleporter",		NULL,	&g_spawnTeleporter,			NULL},
	{"medkit",			"holdable_medkit",			NULL,	&g_spawnMedkit,				NULL},
	{"quad",			"item_quad",				NULL,	&g_spawnQuad,				NULL},
	{"enviro",			"item_enviro",				NULL,	&g_spawnEnviro,				NULL},
	{"haste",			"item_haste",				NULL,	&g_spawnHaste,				NULL},
	{"invis",			"item_invis",				NULL,	&g_spawnInvis,				NULL},
	{"regen",			"item_regen",				NULL,	&g_spawnRegen,				NULL},
	{"flight",			"item_flight",				NULL,	&g_spawnFlight,				NULL},
#ifdef MISSIONPACK
	{"kamikaze",		"holdable_kamikaze",		NULL,	&g_spawnKamikaze,			NULL},
	{"portal",			"holdable_portal",			NULL,	&g_spawnPortal,				NULL},
	{"invuln",			"holdable_invulnerability",	NULL,	&g_spawnInvuln,				NULL},
	{"nails",			"ammo_nails",				NULL,	&g_spawnNails,				NULL},
	{"mines",			"ammo_mines",				NULL,	&g_spawnMines,				NULL},
	{"belt",			"ammo_belt",				NULL,	&g_spawnBelt,				NULL},
	{"scout",			"item_scout",				NULL,	&g_spawnScout,				NULL},
	{"guard",			"item_guard",				NULL,	&g_spawnGuard,				NULL},
	{"doubler",			"item_doubler",				NULL,	&g_spawnDoubler,			NULL},
	{"ammoRegen",		"item_ammoregen",			NULL,	&g_spawnAmmoRegen,			NULL},
	{"nailgun",			"weapon_nailgun",			NULL,	&g_spawnNailgun,			NULL},
	{"plauncher",		"weapon_prox_launcher",		NULL,	&g_spawnProxLauncher,		NULL},
	{"chaingun",		"weapon_chaingun",			NULL,	&g_spawnChaingun,			NULL},
#endif /* MISSIONPACK */
	{NULL}
};

/** Returns qtrue when the mission pack content is present. */
static qboolean LQ3A_IsMissionPack(void)
{
	fileHandle_t	hFile;
	int				iSize;

	/* Detect the mission pack by checking for the
		"mpintro.roq" file and ensuring its the correct size. */
	iSize = trap_FS_FOpenFile(va("video%cmpintro.roq", PATH_SEP), &hFile, FS_READ);

	if (hFile == LQ3A_INVALID_HANDLE)
	{
		return qfalse;
	}

	trap_FS_FCloseFile(hFile);

	return (iSize == 15590130) ? qtrue : qfalse;
}

/** Returns qtrue if the current game has a valid limit which will finish the game when met. */
qboolean LQ3A_GameHasLimits(void)
{
	if ((g_timelimit.integer > 0) || (g_fraglimit.integer > 0))
	{
		return qtrue;
	}

	if (((g_gametype.integer == GT_CTF) || (g_gametype.integer == GT_1FCTF)) && (g_capturelimit.integer > 0))
	{
		return qtrue;
	}

	return qfalse;
}

/** Updates the shared player movement variables from cvars for prediction. */
ID_INLINE void LQ3A_UpdateSharedPlayerMovementConfig(void)
{
	g_pm_hookPullSpeed						= LQ3A_Clampi(g_hookPullSpeed.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_GRAPPLING_HOOK]		= LQ3A_Clampi(g_refireHook.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_GAUNTLET]			= LQ3A_Clampi(g_refireGauntlet.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_MACHINEGUN]			= LQ3A_Clampi(g_refireMachinegun.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_SHOTGUN]				= LQ3A_Clampi(g_refireShotgun.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_GRENADE_LAUNCHER]	= LQ3A_Clampi(g_refireGrenadeLauncher.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_ROCKET_LAUNCHER]		= LQ3A_Clampi(g_refireRocketLauncher.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_LIGHTNING]			= LQ3A_Clampi(g_refireLightninggun.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_RAILGUN]				= LQ3A_Clampi(g_refireRailgun.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_PLASMAGUN]			= LQ3A_Clampi(g_refirePlasmagun.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_BFG]					= LQ3A_Clampi(g_refireBFG.integer, 0, LQ3A_MAX_PM_IVALUE);
#ifdef MISSIONPACK
	g_pm_refireTime[WP_NAILGUN]				= LQ3A_Clampi(g_refireNailgun.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_PROX_LAUNCHER]		= LQ3A_Clampi(g_refireProxLauncher.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_refireTime[WP_CHAINGUN]			= LQ3A_Clampi(g_refireChaingun.integer, 0, LQ3A_MAX_PM_IVALUE);
#endif /* MISSIONPACK */
	g_pm_switchSpeed						= LQ3A_Clampi(g_switchSpeed.integer, 0, LQ3A_MAX_PM_IVALUE);
	g_pm_hasteFactor						= LQ3A_Clampf(g_hasteFactor.value, 0.0f, LQ3A_MAX_PM_FVALUE);
	g_pm_jumpVelocity						= LQ3A_Clampi(g_jumpVelocity.integer, 0, LQ3A_MAX_PM_IVALUE);
}

/** Sets the CS_LQ3A_CONFIG configuration string. This is used to communicate a selection of core settings. */
ID_INLINE static void LQ3A_SetLoadedConfigString(void)
{
	char cString[MAX_STRING_CHARS];

	LQ3A_UpdateSharedPlayerMovementConfig();

	Com_sprintf(cString, sizeof(cString), "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %f %i %i",
		level.bQVM ? 1 : 0,
		level.bMissionPack ? 1 : 0,
		g_highScores.integer ? 1 : 0,
		g_pm_hookPullSpeed,
		g_pm_refireTime[WP_GRAPPLING_HOOK],
		g_pm_refireTime[WP_GAUNTLET],
		g_pm_refireTime[WP_MACHINEGUN],
		g_pm_refireTime[WP_SHOTGUN],
		g_pm_refireTime[WP_GRENADE_LAUNCHER],
		g_pm_refireTime[WP_ROCKET_LAUNCHER],
		g_pm_refireTime[WP_LIGHTNING],
		g_pm_refireTime[WP_RAILGUN],
		g_pm_refireTime[WP_PLASMAGUN],
		g_pm_refireTime[WP_BFG],
#ifdef MISSIONPACK
		g_pm_refireTime[WP_NAILGUN],
		g_pm_refireTime[WP_PROX_LAUNCHER],
		g_pm_refireTime[WP_CHAINGUN],
#else
		0,
		0,
		0,
#endif /* MISSIONPACK */
		g_pm_switchSpeed,
		g_pm_hasteFactor,
		g_pm_jumpVelocity,
		LQ3A_Clampi(g_damageShellSpread.integer, 0, LQ3A_MAX_PM_IVALUE));

	trap_SetConfigstring(CS_LQ3A_CONFIG, cString);
}

/** Sets the CS_LQ3A_LIMITS configuration string. This is used to communicate the maximum
		item values so the client module can display everything correctly. */
static void LQ3A_SetLimitsConfigString(void)
{
	char	cString[MAX_CONFIGSTRINGS];
	int		iLen;

	iLen = Com_sprintf(cString, sizeof(cString), "%i %i %i %i %i %i %i %i",
				g_maxBullets.integer,
				g_maxShells.integer,
				g_maxGrenades.integer,
				g_maxRockets.integer,
				g_maxLightning.integer,
				g_maxSlugs.integer,
				g_maxCells.integer,
				g_maxBFGAmmo.integer);

#ifdef MISSIONPACK
	Com_sprintf(cString+iLen, sizeof(cString)-iLen, " %i %i %i",
		g_maxNails.integer,
		g_maxMines.integer,
		g_maxBelt.integer);
#endif /* MISSIONPACK */

	trap_SetConfigstring(CS_LQ3A_LIMITS, cString);
}

/** Safely returns the entity number for the given gentity_t structure. */
ID_INLINE int LQ3A_EntityToEntityNum(gentity_t *pEntity)
{
	assert(pEntity);

	if (!pEntity)
	{
		G_Error("LQ3A_EntityToEntityNum: bad entity.\n");
		return 0;
	}

	return pEntity - g_entities;
}

/** Safely converts the gentity_t from the given gclient_t structure. */
ID_INLINE gentity_t *LQ3A_ClientToEntity(gclient_t *pClient)
{
	assert(pClient);

	if (!pClient)
	{
		G_Error("LQ3A_ClientToEntity: bad client.\n");
		return NULL;
	}

	return g_entities + (pClient - level.clients);
}

/** Sends a formatted string to the given client. Set pEntity to NULL to broadcast. */
void LQ3A_SendServerCommand(gentity_t *pEntity, pcchar pFormat, ...)
{
	va_list	argptr;
	char	cBuffer[MAX_STRING_TOKENS];

	assert(pFormat);

	/* Do not send commands to bots. */
	if (pEntity && (pEntity->r.svFlags & SVF_BOT))
	{
		return;
	}

	va_start(argptr, pFormat);
	vsprintf(cBuffer, pFormat, argptr);
	va_end(argptr);

	if (pEntity)
	{
		trap_SendServerCommand(LQ3A_EntityToEntityNum(pEntity), cBuffer);
	}
	else
	{
		trap_SendServerCommand(LQ3A_SVC_BROADCAST, cBuffer);
	}
}

/** Returns a valid item from the given short name. */
static plq3a_item_short_name_t LQ3A_ItemShortNameToShortItem(pcchar pShortName)
{
	uint				i;
	plq3a_item_short_name_t	pShortItem;

	for (i=0;i<LQ3A_ARRAYSIZE(s_lq3a_short_name_map)-1; i++)
	{
		pShortItem = &s_lq3a_short_name_map[i];

		if (Q_stricmp(pShortItem->pShortName, pShortName) == 0)
		{
			return pShortItem;
		}
	}

	return NULL;
}

/** Parses the given string for items and writes the results to the given lq3a_parse_items_t structure. */
static uint LQ3A_ParseItems(pchar pBuffer, uint uSize, plq3a_parse_items_t pResult, itemType_t eType, size_t uLimit)
{
	int						iRtn;
	char					cArg[MAX_TOKEN_CHARS];
	plq3a_item_short_name_t	pShortItem;
	uint					uLen, uCount;

	assert(pBuffer && uSize && pResult);

	memset(pResult, 0, sizeof(lq3a_parse_items_t));

	/* Set the parser up for csv. */
	LQ3A_SetParseOptions(LQ3A_PARSE_BREAK_ON_DELIMITER);
	LQ3A_SetParseDelimiter(',');

	for (uCount=0;;)
	{
		iRtn = LQ3A_ParseArg(&pBuffer, uSize, cArg, sizeof(cArg), &uLen);

		if (uLen)
		{
			pShortItem = LQ3A_ItemShortNameToShortItem(cArg);

			if (pShortItem)
			{
				/* Ignore the entry if its not of the desired type. */
				if (eType && (pShortItem->pItem->giType != eType))
				{
					continue;
				}

				/* Save the first parsed item. */
				if (!pResult->pFirstItem)
				{
					pResult->pFirstItem = pShortItem;
				}

				switch (pShortItem->pItem->giType)
				{
				case IT_HEALTH:
				case IT_ARMOR:
				case IT_AMMO:

					/* Counted but not referenced the in the result structure. */
					uCount++;
					break;

				case IT_WEAPON:

					if (!pResult->pFirstWeapon)
					{
						pResult->pFirstWeapon = pShortItem->pItem;
					}

					pResult->iWeapons |= (1 << pShortItem->pItem->giTag);
					uCount++;
					break;

				case IT_POWERUP:

					if (!pResult->pFirstPowerup)
					{
						pResult->pFirstPowerup = pShortItem->pItem;
					}

					pResult->iPowerups |= (1 << pShortItem->pItem->giTag);
					uCount++;
					break;

				case IT_HOLDABLE:

					if (!pResult->pFirstHoldable)
					{
						pResult->pFirstHoldable = pShortItem->pItem;
					}

					pResult->iHoldables |= (1 << pShortItem->pItem->giTag);
					uCount++;
					break;

				case IT_BAD:
				default:
					G_Error("Unknown item: %s\n", cArg);
					break;
				}

				/* Break on item limit. */
				if (uCount == uLimit)
				{
					break;
				}
			}
		}

		if (iRtn == LQ3A_PARSE_R_COMPLETE)
		{
			break;
		}
	}

	return uCount;
}

/** Validates the g_startItem cvar. */
static void LQ3A_ValidateStartItemCacheResult(void)
{
	plq3a_parse_items_t pStartItems = &level.StartItems;

	/* Ensure we always have a weapon. */
	if (pStartItems->iWeapons == 0)
	{
		pStartItems->pFirstWeapon = BG_FindItem("Gauntlet");
		assert(pStartItems->pFirstWeapon);

		pStartItems->iWeapons |= (1 << pStartItems->pFirstWeapon->giTag);
	}
}

/** Parses the g_initialWeapons cvar into the level.StartItems data structure
		and returns qtrue when a valid weapon was parsed.

		Pass bUpdateRegisteredItems as qtrue to update the CS_ITEMS configuration string
		to reflect any changes. If you choose not to update the registered items list
		you'll need to call SameRegisteredItems() yourself when you are ready to do so. */
static qboolean LQ3A_ParseInitialWeaponCvar(qboolean bUpdateRegisteredItems)
{
	lq3a_parse_items_t items;

	LQ3A_ParseItems(g_initialWeapon.string, sizeof(g_initialWeapon.string), &items, IT_WEAPON, 1);

	/* If we parsed something merge it into the level.StartItems structure.
		When nothing is parsed here we'll leave it to the g_startItems cvar to decide the initial weapon. */
	if (items.iWeapons)
	{
		level.StartItems.iWeapons |= items.iWeapons;
		level.StartItems.pFirstWeapon = items.pFirstWeapon;

		if (bUpdateRegisteredItems)
		{
			/* Ensure clients cache the changes. */
			SaveRegisteredItems();
		}

		return qtrue;
	}

	return qfalse;
}

/** Parses the g_startItems cvar into the level.StartItems data structure. */
static void LQ3A_ParseStartItemsCvar(qboolean bUpdateRegisteredItems)
{
	LQ3A_ParseItems(g_startItems.string, sizeof(g_startItems.string), &level.StartItems, 0, 0);

	/* Bring in the g_initialWeapon cvar. If we don't parse anything in from it we just use the
		first weapon in g_startItems reverting back to the machine gun when it goes horribly wrong. */
	LQ3A_ParseInitialWeaponCvar(qfalse);

	LQ3A_ValidateStartItemCacheResult();

	if (bUpdateRegisteredItems)
	{
		/* Ensure clients cache the changes. */
		SaveRegisteredItems();
	}
}

/** Registers items which are part of the lq3a configuration. Follow up with a call to SaveRegisteredItems()
		to ensure the CS_ITEMS configuration string is updated to reflect these changes. */
void LQ3A_RegisterItems(void)
{
	uint i;

	/* Weapons. */
	for (i=0; i<WP_NUM_WEAPONS; i++)
	{
		if (level.StartItems.iWeapons & (1 << i))
		{
			RegisterItem(BG_FindItemForWeapon((weapon_t)i));
		}
	}

	/* Register the hook shaders when the offhand hook is active. */
	if (g_hookOffhand.integer)
	{
		RegisterItem(BG_FindItemForWeapon(WP_GRAPPLING_HOOK));
	}

	/* Powerups. */
	for (i=0; i<PW_NUM_POWERUPS; i++)
	{
		if (level.StartItems.iPowerups & (1 << i))
		{
			RegisterItem(BG_FindItemForPowerup((powerup_t)i));
		}
	}

	/* Holdables. */
	for (i=0; i<HI_NUM_HOLDABLE; i++)
	{
		if (level.StartItems.iHoldables & (1 << i))
		{
			RegisterItem(BG_FindItemForHoldable((holdable_t)i));
		}
	}
}

/** Searches through the arena items and updates items linked to the given short code to.
		Returns qtrue when changes were applied to the arena. */
static qboolean LQ3A_UpdateSpawnItemsFromShortItem(plq3a_item_short_name_t pShortItem)
{
	uint		i;
	gentity_t	*pEntity;

	assert(pShortItem);

	/* Search through the entity list, find all items relating to this spawn item and update it. */
	for (i=0; i<level.num_entities; i++)
	{
		pEntity = &g_entities[i];

		/* Ensure this entity is a valid item. */
		if (!pEntity->inuse || !pEntity->item)
		{
			continue;
		}

		/* Do not modify dropped items. */
		if (pEntity->flags & FL_DROPPED_ITEM)
		{
			continue;
		}

		if (Q_stricmp(pEntity->cOriginalClassName, pShortItem->pClassName) != 0)
		{
			continue;
		}

		/* Start to execute the swap.
			Send the teleport effect if the item is visible. */
		if (!(pEntity->s.eFlags & EF_NODRAW))
		{		
			G_TempEntity(pEntity->s.origin, EV_PLAYER_TELEPORT_OUT);
		}

		/* Remove the current item from the arena. */
		pEntity->r.svFlags	|= SVF_NOCLIENT;
		pEntity->s.eFlags	|= EF_NODRAW;
		pEntity->r.contents	= 0;
		pEntity->nextthink	= 0;
		pEntity->think		= 0;

		/* Spawn in the new item if we have one lined up. */
		if (pShortItem->pSpawnShortItem)
		{
			G_SpawnItem(pEntity, pShortItem->pSpawnShortItem->pItem);
			FinishSpawningItem(pEntity);

			/* Delay the respawn for a second,
				this also overwrites the default delay time when spawning powerups. */
			pEntity->nextthink = level.time + (1 * 1000);
			pEntity->think = RespawnItem;
		}
	}

	/* Send the updated CS_ITEMS configuration string to clients. */
	SaveRegisteredItems();

	return qtrue;
}

/** Parses the value of the given cvar and ensures its an exact match of the short name it represents.
		This allows us to use the cvar value in functions like LQ3A_ItemShortNameToItem() without a need
		to reparse the value each time we need to reference it. */
static qboolean LQ3A_UpdateShortNameCvar(plq3a_item_short_name_t pShortItem, cvarTable_t *pCvar, qboolean bUpdateRegisteredItems)
{
	uint				uCount;
	lq3a_parse_items_t	Result;

	assert(pShortItem && pCvar);

	uCount = LQ3A_ParseItems(pCvar->vmCvar->string, MAX_TOKEN_CHARS, &Result, (itemType_t)0, 1);

	if (uCount == 0)
	{
		trap_Cvar_Set(pCvar->cvarName, "");
		trap_Cvar_Update(pCvar->vmCvar);

		/* Suppress change in G_UpdateCvars(). */
		pCvar->modificationCount = pCvar->vmCvar->modificationCount;
	}
	else if (Q_stricmp(pCvar->vmCvar->string, Result.pFirstItem->pShortName) != 0)
	{
		trap_Cvar_Set(pCvar->cvarName, Result.pFirstItem->pShortName);
		trap_Cvar_Update(pCvar->vmCvar);

		/* Suppress change in G_UpdateCvars(). */
		pCvar->modificationCount = pCvar->vmCvar->modificationCount;
	}

	pShortItem->pSpawnShortItem = Result.pFirstItem;

	if (bUpdateRegisteredItems)
	{
		/* Update items in the arena to reflect the changes. */
		LQ3A_UpdateSpawnItemsFromShortItem(pShortItem);
	}

	return qtrue;
}

/** Initialise the item pointers in the s_lq3a_item_map[] short name map. */
static void LQ3A_InitShortNameMap(void)
{
	uint					i;
	cvarTable_t				*pCvar;
	plq3a_item_short_name_t	pShortItem;

	/* Set pItem and cSpawnCvarName. */
	for (i=0; i<LQ3A_ARRAYSIZE(s_lq3a_short_name_map)-1; i++)
	{
		pShortItem = &s_lq3a_short_name_map[i];

		pShortItem->pItem = LQ3A_FindItemByClassname(pShortItem->pClassName);

		if (!pShortItem->pItem)
		{
			/* We should never get here providing the short name item map is correct. */
			G_Error("Unable to find item for short code \"%s\".\n", pShortItem->pShortName);
			continue;
		}

		LQ3A_GetCvarName(pShortItem->pSpawnCvar, pShortItem->cSpawnCvarName,
			sizeof(s_lq3a_short_name_map[0].cSpawnCvarName));
	}

	/* Parse the spawn cvars values to create a quick reference to the item. */
	for (i=0; i<LQ3A_ARRAYSIZE(s_lq3a_short_name_map)-1; i++)
	{
		pShortItem = &s_lq3a_short_name_map[i];

		pCvar = LQ3A_FindCvarByName(pShortItem->cSpawnCvarName);

		if (pCvar)
		{
			LQ3A_UpdateShortNameCvar(pShortItem, pCvar, qfalse);
		}
	}
}

/** Forces an update of all clients userinfo strings. */
static void LQ3A_UpdateUserInfo(void)
{
	uint		i;

	for (i=0; i<level.numConnectedClients; i++)
	{
		ClientUserinfoChanged(level.sortedClients[i]);
	}
}

/** Executes any actions which should follow specific changes. This allows us to create some
		variables without the need for the CVAR_LATCH flag since we can manage the change at runtime.
		Return qtrue to broadcast the change. */
qboolean LQ3A_CvarChanged(cvarTable_t *pCvar)
{
	plq3a_item_short_name_t pShortItem;

	assert(pCvar);

	if (!level.intermissiontime)
	{
		if (Q_stricmp(pCvar->cvarName, "g_mapList") == 0)
		{
			LQ3A_LoadMapList();
			return qfalse;
		}

		if (Q_stricmp(pCvar->cvarName, "g_motd") == 0)
		{
			LQ3A_LoadMotd();
			return qfalse;
		}

		if (Q_stricmp(pCvar->cvarName, "g_highScores") == 0)
		{
			LQ3A_LoadHighScores();
			LQ3A_SetLoadedConfigString();
			return qfalse;
		}

		if (Q_stricmp(pCvar->cvarName, "g_highScoresTag") == 0)
		{
			if (*pCvar->vmCvar->string == 0)
			{
				trap_Cvar_Set(pCvar->cvarName, pCvar->defaultString);
				trap_Cvar_Update(pCvar->vmCvar);

				G_Printf("%s must have a value, defaulting to \"%s\".", pCvar->cvarName, pCvar->defaultString);
			}

			LQ3A_LoadHighScores();
			LQ3A_SetLoadedConfigString();
			return qfalse;
		}

		/* Same as g_highScores etc only we return qtrue to broadcast the change. */
		if ((Q_stricmp(pCvar->cvarName, "timelimit") == 0) ||
				(Q_stricmp(pCvar->cvarName, "fraglimit") == 0) ||
				(Q_stricmp(pCvar->cvarName, "capturelimit") == 0))
		{
			LQ3A_LoadHighScores();
			LQ3A_SetLoadedConfigString();
			return qtrue;
		}
	}
	else
	{
		/* Surpress the notification, changes will be applied on reload. */
		return qfalse;
	}

	if (Q_stricmp(pCvar->cvarName, "g_forceRailStyle") == 0)
	{
		LQ3A_UpdateUserInfo();
		return qfalse;
	}

	if (Q_stricmp(pCvar->cvarName, "g_hookOffhand") == 0)
	{
		if (g_hookOffhand.integer)
		{
			RegisterItem(BG_FindItemForWeapon(WP_GRAPPLING_HOOK));
		}

		return qfalse;
	}

	if (Q_stricmp(pCvar->cvarName, "g_initialWeapon") == 0)
	{
		LQ3A_ParseInitialWeaponCvar(qtrue);
		return qfalse;
	}

	if (Q_stricmp(pCvar->cvarName, "g_startItems") == 0)
	{
		LQ3A_ParseStartItemsCvar(qtrue);
		return qfalse;
	}

	if ((Q_stricmp(pCvar->cvarName, "g_maxBullets") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_maxShells") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_maxGrenades") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_maxRockets") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_maxLightning") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_maxSlugs") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_maxCells") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_maxBFGAmmo") == 0)
#ifdef MISSIONPACK
			|| (Q_stricmp(pCvar->cvarName, "g_maxNails") == 0)
			|| (Q_stricmp(pCvar->cvarName, "g_maxMines") == 0)
			|| (Q_stricmp(pCvar->cvarName, "g_maxBelt") == 0)
#endif /* MISSIONPACK */
			)
	{
		LQ3A_SetLimitsConfigString();
		return qtrue;
	}

	if ((Q_stricmp(pCvar->cvarName, "g_hookPullSpeed") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireHook") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireGauntlet") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireMachinegun") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireShotgun") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireGrenadeLauncher") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireRocketLauncher") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireLightninggun") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireRailgun") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refirePlasmagun") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireBFG") == 0) ||
#ifdef MISSIONPACK
			(Q_stricmp(pCvar->cvarName, "g_refireNailgun") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireProxLauncher") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_refireChaingun") == 0) ||
#endif /* MISSIONPACK */
			(Q_stricmp(pCvar->cvarName, "g_switchSpeed") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_hasteFactor") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_jumpVelocity") == 0) ||
			(Q_stricmp(pCvar->cvarName, "g_damageShellSpread") == 0)
		)
	{
		LQ3A_SetLoadedConfigString();
		return qfalse;
	}

	/* Items. */
	for (pShortItem=&s_lq3a_short_name_map[0]; pShortItem->pShortName != NULL; pShortItem++)
	{
		if (Q_stricmp(pCvar->cvarName, pShortItem->cSpawnCvarName) == 0)
		{
			LQ3A_UpdateShortNameCvar(pShortItem, pCvar, qtrue);
			return qtrue;
		}
	}

	/* Broadcast change. */
	return qtrue;
}

/** Returns a pointer to the spawn item which should spawn in place of the given item. */
gitem_t *LQ3A_GetSpawnItem(gentity_t *pEntity, gitem_t *pItem)
{
	uint					i;
	plq3a_item_short_name_t	pShortItem;

	assert(pEntity && pItem);

	/* When the entities original classname has a value this entity has
		already been substituted and the value of pItem is correct. */
	if (*pEntity->cOriginalClassName)
	{
		return pItem;
	}

	/* Set the original item classname so we can always identify
		the item as described in the entity lump. */
	Q_strncpyz(pEntity->cOriginalClassName, pEntity->classname, MAX_TOKEN_CHARS);

	for (i=0; i<LQ3A_ARRAYSIZE(s_lq3a_short_name_map); i++)
	{
		if (pItem == s_lq3a_short_name_map[i].pItem)
		{
			pShortItem = LQ3A_ItemShortNameToShortItem(s_lq3a_short_name_map[i].pSpawnCvar->string);

			return (pShortItem) ? pShortItem->pItem : NULL;
		}
	}

	/* Spawn the original item if there is no short name map for this item. */
	return pItem;
}

/** Returns the number of vacant playing slots. */
int LQ3A_GetVacantPlayerSlots(void)
{
	switch (g_gametype.integer)
	{
	case GT_TOURNAMENT:

		/* Tournaments a limited to 2 players only, everyone else spectates. */
		return 2 - level.numNonSpectatorClients;

	default:

		/* When the max game client limit is set ensure it's not already full. */
		if (g_maxGameClients.integer > 0)
		{
			return g_maxGameClients.integer - level.numNonSpectatorClients;
		}

		/* No max game client limit set. */
		return g_maxclients.integer - level.numNonSpectatorClients;
	}
}

/** Returns qtrue if the given client's spectator password matches the server's spectator password. */
static qboolean LQ3A_CheckClientSpectatorPassword(gentity_t *pEntity)
{
	char		cPassword[MAX_TOKEN_CHARS];
	qboolean	bConsoleCommand = qfalse;

	assert(pEntity && pEntity->client);

	if (*g_spectatorPassword.string == 0)
	{
		/* No password set. */
		return qtrue;
	}

	/* Check the password from the console when present. */
	if (trap_Argc() > 1)
	{
		bConsoleCommand = qtrue;

		trap_Argv(2, cPassword, sizeof(cPassword));

		if (Q_strncmp(g_spectatorPassword.string, cPassword, sizeof(cPassword)) == 0)
		{
			return qtrue;
		}
	}

	/* Check the password in the userinfo string. */
	if (Q_strncmp(g_spectatorPassword.string, pEntity->client->pers.cSpectatorPassword, sizeof(cPassword)) == 0)
	{
		return qtrue;
	}

	if (pEntity->client->pers.connected != CON_CONNECTING)
	{
		if (bConsoleCommand)
		{
			LQ3A_SendServerCommand(pEntity, "print \"Invalid spectator password.\nUsage: team <password>.\n\"");
		}
		else
		{
			if (*pEntity->client->pers.cSpectatorPassword == 0)
			{
				LQ3A_SendServerCommand(pEntity, "print \"Password required for spectator mode.\nUsage: cg_spectatorPass <password>.\n\"");
			}
			else
			{
				LQ3A_SendServerCommand(pEntity, "print \"Invalid spectator password.\nUsage: cg_spectatorPass <password>.\n\"");
			}
		}
	}

	return qfalse;
}

/** Returns qtrue if the given client entity should be allowed to spectate. */
qboolean LQ3A_CanClientSpectate(gentity_t *pEntity)
{
	assert(pEntity);

	/* Don't allow bots to spectate when there are vacant player slots. */
	if ((pEntity->r.svFlags & SVF_BOT) && (LQ3A_GetVacantPlayerSlots() > 0))
	{
		return qfalse;
	}

	return LQ3A_CheckClientSpectatorPassword(pEntity);
}

/** Used to complement a move to spectator mode, use on initial client spawn and by SetTeam(). */
void LQ3A_CompleteClientMoveToSpectatorTeam(gentity_t *pEntity)
{
	gclient_t	*pClient;
	gentity_t	*pTmpEntity;

	assert(pEntity);

	pClient = pEntity->client;

	if ((pClient->sess.spectatorState == SPECTATOR_FOLLOW) ||
			(pClient->sess.spectatorState == SPECTATOR_FOLLOW_THIRDPERSON))
	{
		StopFollowing(pEntity);
	}
	else
	{
		pClient->ps.persistant[PERS_TEAM] = TEAM_SPECTATOR;
	}

	pClient->sess.spectatorTime = level.time;

	pEntity->r.svFlags |= SVF_NOCLIENT;
	pClient->ps.pm_type = PM_NOCLIP;

	if (g_gametype.integer != GT_TOURNAMENT)
	{
		/* Save the clients score in case they decide to rejoin the game. */
		pClient->pers.iScore = pClient->ps.persistant[PERS_SCORE];
	}

	/* Dead people cannot move, spectators can. */
	pEntity->health = pClient->ps.stats[STAT_HEALTH] = 100;

	pEntity->takedamage = qfalse;

	pEntity->r.contents = CONTENTS_BODY;

	pClient->ps.weapon = WP_NONE;

	if ((pEntity->health <= 0) || (pClient->ps.stats[STAT_HEALTH] <= 0))
	{
		/* Correct the view angles. */
		pEntity->s.angles[ROLL] = 0;
		pEntity->s.angles[YAW] = pEntity->client->ps.stats[STAT_DEAD_YAW];
		SetClientViewAngle(pEntity, pEntity->s.angles);
	}
	else
	{
		/* Release the grapple hook if active. */
		if (pClient->hook)
		{
			Weapon_HookFree(pClient->hook);
		}

		/* Remove active powerups */
		pEntity->s.powerups = 0;
		memset(pClient->ps.powerups, 0, sizeof(int) * MAX_POWERUPS);

		/* Teleport out the game. */
		pTmpEntity = G_TempEntity(pClient->ps.origin, EV_PLAYER_TELEPORT_OUT);
		pTmpEntity->s.clientNum = pEntity->s.clientNum;
		pClient->ps.eFlags ^= EF_TELEPORT_BIT;
	}

	trap_LinkEntity(pEntity);
}

static void LQ3A_GiveClientInitialAmmo(gclient_t *pClient)
{
	int i, iMax;

	assert(pClient);

	pClient->ps.ammo[WP_MACHINEGUN] += g_startBullets.integer;
	pClient->ps.ammo[WP_SHOTGUN] += g_startShells.integer;
	pClient->ps.ammo[WP_GRENADE_LAUNCHER] += g_startGrenades.integer;
	pClient->ps.ammo[WP_ROCKET_LAUNCHER] += g_startRockets.integer;
	pClient->ps.ammo[WP_LIGHTNING] += g_startLightning.integer;
	pClient->ps.ammo[WP_RAILGUN] += g_startSlugs.integer;
	pClient->ps.ammo[WP_PLASMAGUN] += g_startCells.integer;
	pClient->ps.ammo[WP_BFG] += g_startBFGAmmo.integer;
#ifdef MISSIONPACK
	pClient->ps.ammo[WP_NAILGUN] += g_startNails.integer;
	pClient->ps.ammo[WP_PROX_LAUNCHER] += g_startMines.integer;
	pClient->ps.ammo[WP_CHAINGUN] += g_startBelt.integer;
#endif /* MISSIONPACK */

	/* Ensure we stick to the limits. */
	for (i=WP_GAUNTLET; i<WP_NUM_WEAPONS;i++)
	{
		iMax = LQ3A_GetMaxAmmoValue(i);

		if (pClient->ps.ammo[i] > iMax)
		{
			pClient->ps.ammo[i] = iMax;
		}
	}
}

static void LQ3A_GiveClientInitialPowerups(gclient_t *pClient)
{
	int i, time;

	assert(pClient);

	/* Ensure powerups count in sync. */
	time = level.time - (level.time % 1000);

	if ((g_startProtection.value > 0) && !level.StartItems.iPowerups)
	{
		pClient->ps.powerups[PW_PROTECTION] = time + (g_startProtection.value * 1000);
		return;
	}

	if (level.StartItems.iPowerups)
	{
		for (i=PW_NONE+1; i<PW_NUM_POWERUPS-1; i++)
		{
			if (level.StartItems.iPowerups & (1 << i))
			{
				pClient->ps.powerups[i] = time + (LQ3A_GetItemQuantityValue(BG_FindItemForPowerup((powerup_t)i)) * 1000);
			}
		}
	}
}

static void LQ3A_GiveClientInitialHoldables(gclient_t *pClient)
{
	uint i;

	assert(pClient);

	for (i=HI_NONE+1; i<HI_NUM_HOLDABLE-1; i++)
	{
		if (level.StartItems.iHoldables & (1 << i))
		{
			pClient->ps.stats[STAT_HOLDABLE_ITEM] = ITEM_INDEX(BG_FindItemForHoldable((holdable_t)i));
#ifdef MISSIONPACK
			if (i == HI_KAMIKAZE)
			{
				pClient->ps.eFlags |= EF_KAMIKAZE;
			}
#endif /* MISSIONPACK */
		}
	}
}

void LQ3A_GiveClientInititalInventory(gclient_t *pClient)
{
	assert(pClient);

	if (pClient->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR)
	{
		/* Spectators get nothing. */
		return;
	}

	/* Weapons. */
	pClient->ps.stats[STAT_WEAPONS] = level.StartItems.iWeapons;
	pClient->ps.weapon = level.StartItems.pFirstWeapon->giTag;

	/* Armor. */
	pClient->ps.stats[STAT_ARMOR] = g_startArmor.integer;

	if (pClient->ps.stats[STAT_ARMOR] < 0)
	{
		pClient->ps.stats[STAT_ARMOR] = 0;
	}

	LQ3A_GiveClientInitialAmmo(pClient);
	LQ3A_GiveClientInitialPowerups(pClient);
	LQ3A_GiveClientInitialHoldables(pClient);
}

/** Returns the quantity of the given item. */
int LQ3A_GetItemQuantityValue(gitem_t *pItem)
{
	assert(pItem);

	switch (pItem->giType)
	{
	case IT_ARMOR:

		if (Q_stricmp(pItem->classname, "item_armor_shard") == 0)
		{
			return g_packShard.integer;
		}

		if (Q_stricmp(pItem->classname, "item_armor_combat") == 0)
		{
			return g_packCombatArmor.integer;
		}

		if (Q_stricmp(pItem->classname, "item_armor_body") == 0)
		{
			return g_packHeavyArmor.integer;
		}

		break;

	case IT_HEALTH:

		if (Q_stricmp(pItem->classname, "item_health_small") == 0)
		{
			return g_packSmallHealth.integer;
		}

		if (Q_stricmp(pItem->classname, "item_health") == 0)
		{
			return g_packMediumHealth.integer;
		}

		if (Q_stricmp(pItem->classname, "item_health_large") == 0)
		{
			return g_packLargeHealth.integer;
		}

		if (Q_stricmp(pItem->classname, "item_health_mega") == 0)
		{
			return g_packMegaHealth.integer;
		}

		break;

	case IT_WEAPON:

		switch (pItem->giTag)
		{
		case WP_GRAPPLING_HOOK:
			return -1;
		case WP_MACHINEGUN:
			return g_packMachinegun.integer;
		case WP_SHOTGUN:
			return g_packShotgun.integer;
		case WP_GRENADE_LAUNCHER:
			return g_packGrenadeLauncher.integer;
		case WP_ROCKET_LAUNCHER:
			return g_packRocketLauncher.integer;
		case WP_LIGHTNING:
			return g_packLightninggun.integer;
		case WP_RAILGUN:
			return g_packRailgun.integer;
		case WP_PLASMAGUN:
			return g_packPlasmagun.integer;
		case WP_BFG:
			return g_packBFG.integer;
#ifdef MISSIONPACK
		case WP_NAILGUN:
			return g_packNailgun.integer;
		case WP_PROX_LAUNCHER:
			return g_packProxLauncher.integer;
		case WP_CHAINGUN:
			return g_packChaingun.integer;
#endif /* MISSIONPACK */
		}

		break;

	case IT_AMMO:

		switch (pItem->giTag)
		{
		case WP_MACHINEGUN:
			return g_packBullets.integer;
		case WP_SHOTGUN:
			return g_packShells.integer;
		case WP_GRENADE_LAUNCHER:
			return g_packGrenadeLauncher.integer;
		case WP_ROCKET_LAUNCHER:
			return g_packRocketLauncher.integer;
		case WP_LIGHTNING:
			return g_packLightning.integer;
		case WP_RAILGUN:
			return g_packSlugs.integer;
		case WP_PLASMAGUN:
			return g_packPlasmagun.integer;
		case WP_BFG:
			return g_packBFGAmmo.integer;
#ifdef MISSIONPACK
		case WP_NAILGUN:
			return g_packNails.integer;
		case WP_PROX_LAUNCHER:
			return g_packProxLauncher.integer;
		case WP_CHAINGUN:
			return g_packBelt.integer;
#endif /* MISSIONPACK */
		}

		break;

	case IT_POWERUP:

		switch (pItem->giTag)
		{
		case PW_QUAD:
			return g_quadTime.integer;
		case PW_BATTLESUIT:
			return g_battleSuiteTime.integer;
		case PW_HASTE:
			return g_hasteTime.integer;
		case PW_INVIS:
			return g_invisTime.integer;
		case PW_REGEN:
			return g_regenTime.integer;
		case PW_FLIGHT:
			return g_flightTime.integer;
		}

		break;
	}

	/* We should never get here. */
	return 0.0f;
}

/** Returns the ammo capacity for the given weapon.
		A variation of this function exists in both server and client modules. */
int LQ3A_GetMaxAmmoValue(int iWeapon)
{
	int iValue;

	switch (iWeapon)
	{
	case WP_GAUNTLET:
	case WP_GRAPPLING_HOOK:
		return -1;
	case WP_MACHINEGUN:
		iValue = g_maxBullets.integer;
		break;
	case WP_SHOTGUN:
		iValue = g_maxShells.integer;
		break;
	case WP_GRENADE_LAUNCHER:
		iValue = g_maxGrenades.integer;
		break;
	case WP_ROCKET_LAUNCHER:
		iValue = g_maxRockets.integer;
		break;
	case WP_LIGHTNING:
		iValue = g_maxLightning.integer;
		break;
	case WP_RAILGUN:
		iValue = g_maxSlugs.integer;
		break;
	case WP_PLASMAGUN:
		iValue = g_maxCells.integer;
		break;
	case WP_BFG:
		iValue = g_maxBFGAmmo.integer;
		break;
#ifdef MISSIONPACK
	case WP_NAILGUN:
		iValue = g_maxNails.integer;
		break;
	case WP_PROX_LAUNCHER:
		iValue = g_maxMines.integer;
		break;
	case WP_CHAINGUN:
		iValue = g_maxBelt.integer;
		break;
#endif /* MISSIONPACK */
	default:
		G_Error("LQ3A_GetMaxAmmo: Bad weapon index %i\n", iWeapon);
		return 0;
	}

	/* Max negative values to -1. */
	return (iValue >= 0) ? iValue : -1;
}

/** Returns the rail style from the given userinfo string. */
int LQ3A_GetRailStyleFromUserInfo(pcchar pUserInfo)
{
	assert(pUserInfo);

	switch (g_forceRailStyle.integer)
	{
	case 1:
		/* Forced beam. */
		return 0;

	case 2:
		/* Forced spiral. */
		return 1;
	}

	/* User defined from cg_oldRail cvar. */
	return atoi(Info_ValueForKey(pUserInfo, "cg_oldRail")) ? qtrue : qfalse;
}

/** Checks the given client for camping and kills them if they have failed to follow the server rules. */
void LQ3A_ClientCampCheck(gclient_t *pClient)
{
	gentity_t	*pEntity;
	vec3_t		vResult;
	vec_t		vLength;
	int			iCampTime, iCampWarnTime;

	assert(pClient);

	/* The protection shield prevents camp checks. */
	if (!g_antiCamp.integer || pClient->ps.powerups[PW_PROTECTION])
	{
		return;
	}

	pEntity = LQ3A_ClientToEntity(pClient);

	/* Calculate the distance travelled from the current camp origin. */
	VectorSubtract(pClient->vCampOrigin, pClient->ps.origin, vResult);
	vLength = VectorLength(vResult);

	if (pClient->ps.stats[STAT_CAMPING] == 0)
	{
		iCampTime = (g_antiCampTime.value > 0) ? g_antiCampTime.integer * 1000 : 0;

		if (level.time < (pClient->iCampCheckTime + iCampTime))
		{
			/* If we have moved more than the threshold, reset the check. */
			if (vLength >= g_antiCampThreshold.integer)
			{
				VectorCopy(pClient->ps.origin, pClient->vCampOrigin);
				pClient->iCampCheckTime = level.time;
			}
		}
		else if (level.time  > (pClient->iCampCheckTime + iCampTime))
		{
			if (vLength < g_antiCampThreshold.integer)
			{
				iCampWarnTime = (g_antiCampWarnTime.integer > 0) ? g_antiCampWarnTime.integer : 0;

				pClient->ps.stats[STAT_CAMPING] = level.time + (iCampWarnTime * 1000);

				pClient->ps.eFlags |= EF_CAMPING;
				pClient->rewardTime = level.time + iCampWarnTime;
			}
		}
	}
	/* Has the client ran out of time to move? */
	else if (pClient->ps.stats[STAT_CAMPING] < level.time)
	{
		G_Damage(pEntity, NULL, pEntity, NULL, NULL, pClient->ps.stats[STAT_MAX_HEALTH]+10000, 0, MOD_CAMPING);
	}
	/* Have we moved enough to remove the camping status? */
	else if (vLength > g_antiCampThreshold.integer)
	{
		VectorCopy(pClient->ps.origin, pClient->vCampOrigin);
		pClient->iCampCheckTime = level.time;

		pClient->ps.stats[STAT_CAMPING] = 0;
		pClient->ps.eFlags &= ~EF_CAMPING;
		pClient->rewardTime = 0;
	}
}

/* Finds the level.sortedClients[] index for the given client and returns qtrue on success. */
qboolean LQ3A_GetClientIndexInSortedScores(int iClient, pint piIndex)
{
	uint i;

	assert(piIndex);

	/* Negative numbers auto follow a position so just invert the value. */
	if (iClient < 0)
	{
		*piIndex = iClient * -1;

		return (*piIndex <= g_maxclients.integer) ? qtrue : qfalse;
	}

	for (i=0; i<level.numNonSpectatorClients; i++)
	{
		if (level.sortedClients[i] == iClient)
		{
			*piIndex = i;
			return qtrue;
		}
	}

	return qfalse;
}

/***************
 * FILE SYSTEM *
 ***************/

/** Converts line endings in the given buffer to 'newline' characters only.
		This ensures consistency when reading from files within qvm's. */
static int LQ3A_FixCrLf(pchar pBuffer, int iSize)
{
	int		i = 0;
	pchar	str = pBuffer;

	assert(pBuffer && (iSize > 0));

	while (*str)
	{
		if (i == iSize)
		{
			break;
		}

		if (*str == '\r')
		{
			if (str[1])
			{
				if (str[1] == '\n')
				{
					pBuffer[i++] = '\n';

					str += 2;
					continue;
				}
				else
				{
					pBuffer[i++] = '\n';

					str++;
					continue;
				}
			}

			break;
		}

		if ((*str == '\n') && !str[1])
		{
			break;
		}

		pBuffer[i++] = *str++;
	}

	pBuffer[i] = 0;
	return i;
}

/** Returns qtrue when the given file exists. */
qboolean LQ3A_FileExists(pcchar pFileName)
{
	fileHandle_t hFile;

	trap_FS_FOpenFile(pFileName, &hFile, FS_READ);

	if (!hFile)
	{
		return qfalse;
	}

	trap_FS_FCloseFile(hFile);
	return qtrue;
}

/** Reads the count in bytes from the given file into the given buffer
		and returns the count of bytes read. LQ3A_INVALID_HANDLE is returned on error. */
int LQ3A_ReadFile(pcchar pFileName, pchar pBuffer, int iSize, pint puFileSize)
{
	fileHandle_t	hFile;
	int				iLen;

	assert(pFileName && pBuffer && (iSize > 0));

	if (!puFileSize)
	{
		puFileSize = &iLen;
	}

	*puFileSize = trap_FS_FOpenFile(pFileName, &hFile, FS_READ);

	if (!hFile)
	{
		return LQ3A_INVALID_HANDLE;
	}

	if (iSize > *puFileSize)
	{
		iSize = (*puFileSize);
	}

	trap_FS_Read(pBuffer, iSize, hFile);
	pBuffer[iSize] = 0;

	trap_FS_FCloseFile(hFile);

	/* Ensure line endings are consistent so the
		client module doesn't have to worry about them. */
	iLen = LQ3A_FixCrLf(pBuffer, iSize);

	return iLen;
}

/****************
 * MAP ROTATION *
 ****************/

/* Finds the index for the current map in the map list. */
static void LQ3A_FindCurrentMap(void)
{
	uint					i;
	plq3a_maplist_entry_t	pEntry;

	/* Search for the current map in the map list. */
	for (i=0; i<level.MapList.iCount; i++)
	{
		pEntry = &level.MapList.Map[i];

		if (Q_strncmp(pEntry->cName, level.cMapName, MAX_QPATH) == 0)
		{
			level.MapList.iCurrent = i;
			return;
		}
	}

	level.MapList.iCurrent = LQ3A_MAP_NOT_IN_LIST;
}

/** Parses all entries in the given string into the map list. */
static int LQ3A_ParseMapListEntries(pchar pIn, uint uSize, qboolean bReadFlags)
{
	pchar					pBuffer;
	char					cArg[MAX_TOKEN_CHARS];
	int						iRtn, iArg, iCount;
	uint					uLen;
	plq3a_maplist_entry_t	pEntry;

	assert(pIn && uSize);

	LQ3A_SetParseOptions(LQ3A_PARSE_COMMENTS|LQ3A_PARSE_BREAK_ON_CRLF|LQ3A_PARSE_BREAK_ON_EMPTY);

	iCount	= 0;
	pBuffer	= pIn;
	iArg	= 0;
	pEntry	= &level.MapList.Map[level.MapList.iCount];

	for (;;)
	{
		/* Parse the next argument from the buffer. */
		iRtn = LQ3A_ParseArg(&pBuffer, LQ3A_PARSE_IN_SIZE2(pIn, uSize, pBuffer), cArg, sizeof(cArg), &uLen);

skip_parse_arg:

		/* If we didn't parse anything in. */
		if ((uLen == 0) && (iRtn != LQ3A_PARSE_R_EMPTY))
		{
			if (iArg)
			{
				/* Save the entry when valid. */
				if (*pEntry->cName)
				{
					iCount++;
					pEntry = &level.MapList.Map[++level.MapList.iCount];
				}

				iArg = 0;
			}

			if (iRtn == LQ3A_PARSE_R_COMPLETE)
			{
				/* Done. */
				break;
			}

			continue;
		}

		switch (iArg++)
		{
		case LQ3A_MAPLIST_ARG_NAME:

			/* Ensure the map exists before adding it. */
			if (!LQ3A_FileExists(va("maps%c%s.bsp", PATH_SEP, cArg)))
			{
				G_Printf("Dropping \"%s\" from the map list, map not installed on server.\n", cArg);

				/* Skip over the rest of the line and process the return value. */
				iRtn = LQ3A_ParseToCrLf(&pBuffer, LQ3A_PARSE_IN_SIZE2(pIn, uSize, pBuffer));
				uLen = 0;
				goto skip_parse_arg;
			}

			Q_strncpyz(pEntry->cName, cArg, MAX_QPATH);
			break;

		case LQ3A_MAPLIST_ARG_TITLE:
			Q_strncpyz(pEntry->cTitle, cArg, MAX_TOKEN_CHARS);
			break;

		case LQ3A_MAPLIST_ARG_MIN:
			pEntry->iMin = atoi(cArg);
			break;

		case LQ3A_MAPLIST_ARG_MAX:
			pEntry->iMax = atoi(cArg);
			break;

		case LQ3A_MAPLIST_ARG_CONFIG:

			/* Ensure the configuration file exists before adding it. */
			if (LQ3A_FileExists(cArg))
			{
				Q_strncpyz(pEntry->cConfig, cArg, MAX_QPATH);
			}
			else
			{
				G_Printf("Configuration file \"%s\" for map \"%s\" could not be found, config ignored.\n",
					cArg, pEntry->cName);
			}

			break;

		case LQ3A_MAPLIST_ARG_FLAGS:

			/* Allow flags only when explicitly told to parse them,
				otherwise pretend they don't exist and fall through. */
			if (bReadFlags)
			{
				pEntry->uFlags = atoi(cArg);
				break;
			}

		default:

			/* Skip over the rest of the line and process the return value. */
			iRtn = LQ3A_ParseToCrLf(&pBuffer, LQ3A_PARSE_IN_SIZE2(pIn, uSize, pBuffer));
			uLen = 0;
			goto skip_parse_arg;
		}
	}

	return iCount;
}

/** Restores the current map list state from cvars when available. */
static qboolean LQ3A_RestoreMapListState(void)
{
	char	cBuffer[MAX_CVAR_VALUE_STRING], cArg[MAX_CVAR_VALUE_STRING];
	pchar	pBuffer;
	uint	uLen, i;
	int		iCount, iCurrent;

	LQ3A_SetParseOptions(0);

	trap_Cvar_VariableStringBuffer("__maplist", cBuffer, sizeof(cBuffer));

	if (!*cBuffer)
	{
		return qfalse;
	}

	pBuffer = cBuffer;

	LQ3A_ParseArg(&pBuffer, LQ3A_PARSE_IN_SIZE(cBuffer, pBuffer), cArg, sizeof(cArg), &uLen);

	if (!uLen)
	{
		return qfalse;
	}

	Q_strncpyz(level.MapList.cFile, cArg, sizeof(level.MapList.cFile));

	LQ3A_ParseArg(&pBuffer, LQ3A_PARSE_IN_SIZE(cBuffer, pBuffer), cArg, sizeof(cArg), &uLen);

	if (uLen == 0)
	{
		return qfalse;
	}

	iCount = atoi(cArg);

	LQ3A_ParseArg(&pBuffer, LQ3A_PARSE_IN_SIZE(cBuffer, pBuffer), cArg, sizeof(cArg), &uLen);

	if (uLen == 0)
	{
		return qfalse;
	}

	iCurrent = atoi(cArg);

	for (i=0; i<iCount; i++)
	{
		Com_sprintf(cArg, sizeof(cArg), "__map%i", i);
		trap_Cvar_VariableStringBuffer(cArg, cBuffer, sizeof(cBuffer));

		/* We can expect to parse exactly one map in on each pass,
			if nothing is parsed in we know something has gone wrong. */
		if (LQ3A_ParseMapListEntries(cBuffer, sizeof(cBuffer), qtrue) != 1)
		{
			return qfalse;
		}
	}

	level.MapList.iCurrent = iCurrent;

	/* Validate the current selection, initialise it if its wrong. */
	if ((iCurrent < 0) || (iCurrent > level.MapList.iCount-1))
	{
		LQ3A_FindCurrentMap();
	}

	return qtrue;
}

/** Parses the map list in from a file. */
void LQ3A_LoadMapList(void)
{
	char	cBuffer[LQ3A_MAX_FILE_SIZE];
	int		iFileSize, iSize;

	memset(&level.MapList, 0, sizeof(level.MapList));

	if (!*g_mapList.string)
	{
		G_Printf("Map rotation system is off.\n");
		return;
	}

	/* Restore the map list state from cvars when present. */
	if (LQ3A_RestoreMapListState())
	{
		G_Printf("Restored map list state, %i map%s previously read in from \"%s\".\n",
			level.MapList.iCount, (level.MapList.iCount != 1) ? "s" : "", g_mapList.string);
		return;
	}

	iSize = LQ3A_ReadFile(g_mapList.string, cBuffer, sizeof(cBuffer), &iFileSize);

	if (iSize == LQ3A_INVALID_HANDLE)
	{
		G_Printf("Failed to open map list file \"%s\".\n", g_mapList.string);
		return;
	}

	Q_strncpyz(level.MapList.cFile, g_mapList.string, sizeof(level.MapList.cFile));

	/* Highlight insufficient buffers size. */
	if (sizeof(cBuffer) < iFileSize)
	{
		G_Printf("Buffer size too small to parse file \"%s\", read %i byte%s of %i.\n",
			g_mapList.string, sizeof(cBuffer), (sizeof(cBuffer) != 1) ? "s" : "", iFileSize);
	}

	/* Parse the file content. */
	LQ3A_ParseMapListEntries(cBuffer, sizeof(cBuffer), qfalse);

	LQ3A_FindCurrentMap();

	/* Update the server info string. */
	Com_sprintf(cBuffer, sizeof(cBuffer), "%i", level.MapList.iCount);
	trap_Cvar_Set("g_mapsInRotation", cBuffer);
	
	G_Printf("Read %i map%s from map list file \"%s\".\n",
		level.MapList.iCount, (level.MapList.iCount != 1) ? "s" : "", g_mapList.string);
}

/** Creates a list of maps which are suitable for the nextmap selection.
		This function will recursively call itself with weaker criteria until a suitable list is found.
		At worst, the picklist will mirror the map list. */
static void LQ3A_GetMapListPickList(plq3a_maplist_picklist_t pPickList, qboolean bIgnoreCounts, int iRecursionCount)
{
	int						i;
	plq3a_maplist_entry_t	pMap;
	int						iMin, iMax, iVisitedCount;

	assert(pPickList);

	memset(pPickList, 0, sizeof(lq3a_maplist_picklist_t));

	for (i=0,pPickList->iCurrent=LQ3A_MAP_NOT_IN_LIST,iVisitedCount=0; i<level.MapList.iCount;i++)
	{
		pMap = &level.MapList.Map[i];

		if (!bIgnoreCounts)
		{
			iMin = (pMap->iMin > 0) ? pMap->iMin - iRecursionCount : 0;
			iMax = (pMap->iMax > 0) ? pMap->iMax + iRecursionCount : 0;

			if (iMin && (level.numConnectedClients < iMin))
			{
				/* Too few players. */
				continue;
			}

			if (iMax && (level.numConnectedClients > iMax))
			{
				/* Too many players. */
				continue;
			}
		}

		if (i == level.MapList.iCurrent)
		{
			pPickList->iCurrent = i;
		}


		if (pMap->uFlags & LQ3A_MAP_VISITED)
		{
			iVisitedCount++;
		}

		pPickList->pMap[pPickList->iCount++] = pMap;
	}

	/* Is the picklist suitable? */
	if ((level.MapList.iCount == pPickList->iCount) || (pPickList->iCount > 2) ||
			(
				(pPickList->iCount == 1) && (pPickList->iCurrent != LQ3A_MAP_NOT_IN_LIST) &&
				(Q_stricmp(level.cMapName, pPickList->pMap[pPickList->iCurrent]->cName) == 0)
			))
	{
		/* Reset the visited flag if we've visited all maps in this list. */
		if (pPickList->iCount == iVisitedCount)
		{
			for (i=0; i<pPickList->iCount; i++)
			{
				pPickList->pMap[i]->uFlags &= ~LQ3A_MAP_VISITED;
			}
		}

		return;
	}

	/* Not good enough, try again. */
	LQ3A_GetMapListPickList(pPickList, (iRecursionCount >= 3) ? qtrue : bIgnoreCounts, ++iRecursionCount);
}

static int LQ3A_PickMapFromPickList(plq3a_maplist_picklist_t pPickList)
{
	int i, iChoice;

	assert(pPickList && (pPickList->iCount > 0));

	/* Choose the next map. */
	iChoice = g_mapListRandomOrder.integer ? (rand() % pPickList->iCount) : pPickList->iCurrent + 1;

	/* Adjust the choice if its not suitable. */
	for (i=0; i<pPickList->iCount; i++,iChoice++)
	{
		if (iChoice >= pPickList->iCount)
		{
			iChoice = 0;
		}

		/* Select this map if its not the current map and we haven't visited it within the current cycle. */
		if ((Q_stricmp(level.cMapName, pPickList->pMap[iChoice]->cName) != 0) ||
				(((Q_stricmp(level.cMapName, pPickList->pMap[iChoice]->cName) == 0) &&
				(!(pPickList->pMap[iChoice]->uFlags & LQ3A_MAP_VISITED)))))
		{
			return iChoice;
		}
	}

	/* Give up. */
	return 0;
}

/** Chooses a suitable map from the map list and sets it as the next map. */
void LQ3A_SelectNextMap(void)
{
	lq3a_maplist_picklist_t	PickList;
	plq3a_maplist_entry_t	pMap;
	char					cNextMap[MAX_CVAR_VALUE_STRING];
	int						iLen;

	if (level.MapList.iCount == 0)
	{
		return;
	}

	/* Mark the current map as used. */
	if (level.MapList.iCurrent != LQ3A_MAP_NOT_IN_LIST)
	{
		level.MapList.Map[level.MapList.iCurrent].uFlags |= LQ3A_MAP_VISITED;
	}

	if (level.MapList.bSurpressNextCycle)
	{
		/* Skip next map selection. */
		level.MapList.bSurpressNextCycle = qfalse;
		return;
	}

	/* Get a list of suitable maps. */
	LQ3A_GetMapListPickList(&PickList, g_mapListIgnoreCounts.integer ? qtrue : qfalse, 0);

	/* Select the next map. */
	level.MapList.iCurrent = LQ3A_PickMapFromPickList(&PickList);
	pMap = &level.MapList.Map[level.MapList.iCurrent];

	if (!g_mapListIgnoreConfigs.integer && *pMap->cConfig)
	{
		/* Add a custom configuration to the nextmap command when one is provided. */
		iLen = Com_sprintf(cNextMap, sizeof(cNextMap), "exec \"%s\";", pMap->cConfig);
	}
	else
	{
		iLen = 0;
	}

	if (Q_stricmp(level.cMapName, pMap->cName) == 0)
	{
		/* Restart rather than reload if the nextmap is the same as the current map. */
		Com_sprintf(cNextMap+iLen, sizeof(cNextMap)-iLen, "map_restart 0\n");
		level.MapList.bRestartMap = qtrue;
	}
	else
	{
		Com_sprintf(cNextMap+iLen, sizeof(cNextMap)-iLen, "map %s", pMap->cName);
	}

	trap_Cvar_Set("nextmap", cNextMap);

	/* Announce the chosen map. */
	if (*pMap->cTitle)
	{
		LQ3A_SendServerCommand(NULL, "print \"%sNext Map:%s %s - %s\n\"", S_COLOR_YELLOW, S_COLOR_WHITE, pMap->cName, pMap->cTitle);
	}
	else
	{
		LQ3A_SendServerCommand(NULL, "print \"%sNext Map:%s %s\n\"", S_COLOR_YELLOW, S_COLOR_WHITE, pMap->cName);
	}
}

/** Writes the current map list to cvars so that we can preserve the state across levels. */
void LQ3A_SaveMapListState(void)
{
	char					cName[MAX_CVAR_VALUE_STRING], cBuffer[MAX_CVAR_VALUE_STRING];
	uint					uLen, i;
	plq3a_maplist_entry_t	pEntry;

	uLen = Com_sprintf(cBuffer, sizeof(cBuffer), "\"%s\" %i %i",
				level.MapList.cFile, level.MapList.iCount, level.MapList.iCurrent);

	trap_Cvar_Set("__maplist", cBuffer);

	for (i=0; i<level.MapList.iCount; i++)
	{
		pEntry = &level.MapList.Map[i];

		Com_sprintf(cName, sizeof(cName), "__map%i", i);

		Com_sprintf(cBuffer, sizeof(cBuffer), "\"%s\" \"%s\" %i %i \"%s\" %i",
			pEntry->cName, pEntry->cTitle, pEntry->iMin, pEntry->iMax, pEntry->cConfig, pEntry->uFlags);

		trap_Cvar_Set(cName, cBuffer);
	}
}

/**********************
 * MESSAGE OF THE DAY *
 **********************/

/* Reads the message of the day in from a file. */
void LQ3A_LoadMotd(void)
{
	char cBuffer[MAX_CONFIGSTRINGS];
	int iLen;

	if (!g_motd.string[0])
	{
		G_Printf("Motd is off.\n");
		return;
	}

	iLen = LQ3A_ReadFile(g_motd.string, cBuffer, sizeof(cBuffer), NULL);

	if (iLen == LQ3A_INVALID_HANDLE)
	{
		G_Printf("Failed to open motd file \"%s\".\n", g_motd.string);
		return;
	}

	trap_SetConfigstring(CS_MOTD, cBuffer);
	G_Printf("Read %i byte%s of data from motd file \"%s\".\n", iLen, (iLen != 1) ? "s" : "", g_motd.string);
}

/***************
 * HIGH SCORES *
 ***************/

/** Checks the game rules to ensure at least one limit is active. */
static qboolean LQ3A_ValidateRulesForHighScores(void)
{
	cvarTable_t *pCvar;

	/* Validate the g_highScoresTab cvar, we need to query the main cvar table
		to get the default value and set the modification count. */
	pCvar = LQ3A_FindCvarByName("g_highScoresTag");

	if (!pCvar)
	{
		/* We should never get here. */
		G_Printf("Unable to find \"g_highScoresTag\" cvar, high scores cannot be used without it.\n");
		return qfalse;
	}

	if (*pCvar->vmCvar->string == 0)
	{
		trap_Cvar_Set(pCvar->cvarName, pCvar->defaultString);
		trap_Cvar_Update(pCvar->vmCvar);

		/* Suppress change in G_UpdateCvars(). */
		pCvar->modificationCount = pCvar->vmCvar->modificationCount;

		G_Printf("%s must have a value, defaulting to \"%s\".\n", pCvar->cvarName, pCvar->defaultString);
	}

	/* MAX_CVAR_VALUE_STRING is too large for us to use in the file name
		so we need to limit the number of characters you can set it too. */
	if (strlen(pCvar->vmCvar->string) > LQ3A_MAX_HIGHSCORE_TAG_SIZE)
	{
		trap_Cvar_Set(pCvar->cvarName, pCvar->defaultString);
		trap_Cvar_Update(pCvar->vmCvar);

		/* Suppress track changes in G_UpdateCvars(). */
		pCvar->modificationCount = pCvar->vmCvar->modificationCount;

		G_Printf("%s is limited to %i characters, defaulting to \"%s\".\n",
			pCvar->cvarName, LQ3A_MAX_HIGHSCORE_TAG_SIZE, pCvar->defaultString);
	}

	if (LQ3A_GameHasLimits())
	{
		return qtrue;
	}

	G_Printf("At least one game limit needs to be active to use highscores, defaulting \"g_timelimit\" to 20 minutes.\n");
	trap_Cvar_Set("g_timelimit", "20");
	LQ3A_UpdateCvarByName("g_timelimit", qtrue);
 
	return qfalse;
}

/** Copies the high score file name for the current map to the given buffer up to the given byte count. */
static void LQ3A_GetHighScoreFileName(pchar pFileName, size_t uSize)
{
	int iCaptureLimit;

	assert(pFileName && level.cMapName[0] && uSize);

	/* Capture limit is zero for non-ctf gametypes. */
	iCaptureLimit = ((g_gametype.integer == GT_CTF) || (g_gametype.integer == GT_1FCTF)) ? g_capturelimit.integer : 0;

	Q_strncpyz(pFileName,
		va("%s-%s-t%i-f%i-c%i.dat",
			level.cMapName,
			g_highScoresTag.string,
			g_timelimit.integer,
			g_fraglimit.integer,
			iCaptureLimit),
		uSize);
}

/** Sets the CS_LQ3A_HIGHSCORES configuration string. */
static void LQ3A_SetHighScoreConfigString(void)
{
	char					cBuffer[1024];
	pchar					pBuffer;
	int						i;
	plq3a_highscore_entry_t	pEntry;

	memset(cBuffer, 0, sizeof(cBuffer));
	pBuffer = cBuffer;

	pBuffer += Com_sprintf(pBuffer, sizeof(cBuffer), "%i", level.iHighScoreCount);

	for (i=0; i<level.iHighScoreCount; i++)
	{
		pEntry = &level.HighScores[i];

		/* Note we cannot enclose the date in quotes as Quake 3 parses out
			empty quotes when parsing updates to the original config string.
			Instead, we use flags to inform the client as to whats present in each entry.

			From a server level we always reference the date, even in qvm's. The client is left to determine if the
			date column has data across all entries or not. This allows us to provide highscores mixed scores set by
			both a dll and qvm games. */
		pBuffer += Com_sprintf(pBuffer, sizeof(cBuffer)-(pBuffer-cBuffer),
			" \"%s\" %i %i %i %i %i %i %i %i %i %i %i %s %i",
				pEntry->cGamerTag,
				pEntry->uScore,
				pEntry->uFlags,
				pEntry->uBotSkill,
				pEntry->uImpresiveCount,
				pEntry->uExcellentCount,
				pEntry->uHumiliationCount,
				pEntry->uCaptureCount,
				pEntry->uAssistCount,
				pEntry->uDefenceCount,
				pEntry->uAccuracy,
				pEntry->uEfficiency,
				pEntry->cDate,
				pEntry->iClient);
	}

	trap_SetConfigstring(CS_LQ3A_HIGHSCORES, cBuffer);
}

/** Populates the given lq3a_highscore_entry_t structure by reading data from the given file handle. */
static void LQ3A_ReadNextHighScoreEntry(fileHandle_t hFile, plq3a_highscore_entry_t pEntry)
{
	char cDate[LQ3A_MAX_DATE];

	assert(hFile && pEntry);

	memset(pEntry, 0, sizeof(lq3a_highscore_entry_t));

	trap_FS_Read(pEntry->cGamerTag, MAX_NETNAME, hFile);

	trap_FS_Read(&pEntry->uScore, sizeof(uint), hFile);
	pEntry->uScore = LittleLong(pEntry->uScore);

	trap_FS_Read(&pEntry->uFlags, sizeof(uint), hFile);
	pEntry->uFlags = LittleLong(pEntry->uFlags);

	trap_FS_Read(&pEntry->uBotSkill, sizeof(uint), hFile);
	pEntry->uBotSkill = LittleLong(pEntry->uBotSkill);

	trap_FS_Read(&pEntry->uImpresiveCount, sizeof(uint), hFile);
	pEntry->uImpresiveCount = LittleLong(pEntry->uImpresiveCount);

	trap_FS_Read(&pEntry->uExcellentCount, sizeof(uint), hFile);
	pEntry->uExcellentCount = LittleLong(pEntry->uExcellentCount);

	trap_FS_Read(&pEntry->uHumiliationCount, sizeof(uint), hFile);
	pEntry->uHumiliationCount = LittleLong(pEntry->uHumiliationCount);

	trap_FS_Read(&pEntry->uCaptureCount, sizeof(uint), hFile);
	pEntry->uCaptureCount = LittleLong(pEntry->uCaptureCount);

	trap_FS_Read(&pEntry->uAssistCount, sizeof(uint), hFile);
	pEntry->uAssistCount = LittleLong(pEntry->uAssistCount);

	trap_FS_Read(&pEntry->uDefenceCount, sizeof(uint), hFile);
	pEntry->uDefenceCount = LittleLong(pEntry->uDefenceCount);

	trap_FS_Read(&pEntry->uAccuracy, sizeof(uint), hFile);
	pEntry->uAccuracy = LittleLong(pEntry->uAccuracy);

	trap_FS_Read(&pEntry->uEfficiency, sizeof(uint), hFile);
	pEntry->uEfficiency = LittleLong(pEntry->uEfficiency);

	trap_FS_Read(&cDate, LQ3A_MAX_DATE, hFile);

	if (pEntry->uFlags & LQ3A_HSEF_DATE)
	{
		strncpy(pEntry->cDate, cDate, LQ3A_MAX_DATE);
	}
}

/** Populates the level.HighScores array from file. */
void LQ3A_LoadHighScores(void)
{
	char					cFileName[MAX_QPATH];
	fileHandle_t			hFile;
	lq3a_highscore_header_t Header;
	int						i, iSize;

	/* Reset the current score count,
		this ensures we wipe the scores if the rules are changed at runtime. */
	level.iHighScoreCount = 0;

	if ((!g_highScores.integer) || (!LQ3A_ValidateRulesForHighScores()))
	{
		LQ3A_SetHighScoreConfigString();
		return; /* Disabled. */
	}

	LQ3A_GetHighScoreFileName(cFileName, sizeof(cFileName));

	iSize = trap_FS_FOpenFile(va("%s%c%s", LQ3A_HIGHSCORE_DIR, PATH_SEP, cFileName), &hFile, FS_READ);

	if (!hFile)
	{
		/* Unable to open file, new scores will be created. */
		LQ3A_SetHighScoreConfigString();
		return;
	}

	if (iSize < LQ3A_HIGHSCORE_HEADER_SIZEOF)
	{
		/* Invalid file size. */
		G_Printf("Unable to load highscore file \"%s\", invalid file size.\n", cFileName);
		goto done;
	}

	trap_FS_Read(&Header.uID, sizeof(Header.uID), hFile);

	if (LittleLong(Header.uID) != LQ3A_HIGHSCORE_IDENT)
	{
		G_Printf("Unable to load highscore file \"%s\", invalid file format.\n", cFileName);
		goto done;
	}

	trap_FS_Read(&Header.uVersion, sizeof(Header.uVersion), hFile);

	if (LittleLong(Header.uVersion) != LQ3A_HIGHSCORE_VERSION)
	{
		G_Printf("Unable to load highscore file \"%s\", incompatible version.\n", cFileName);
		goto done;
	}

	trap_FS_Read(&Header.uCRC32, sizeof(Header.uCRC32), hFile);

	/* @todo: Calculate CRC. */
	if (LittleLong(Header.uCRC32) != 0)
	{
		G_Printf("Unable to load highscore file \"%s\", CRC error.\n", cFileName);
		goto done;
	}

	trap_FS_Read(&Header.cMapName, sizeof(Header.cMapName), hFile);

	if (Q_stricmp(Header.cMapName, level.cMapName) != 0)
	{
		G_Printf("Unable to load highscore file \"%s\", map miss match.\n", cFileName);
		goto done;
	}

	trap_FS_Read(&Header.cTag, sizeof(Header.cTag), hFile);

	if (Q_stricmp(Header.cTag, g_highScoresTag.string) != 0)
	{
		G_Printf("Unable to load highscore file \"%s\", tag miss match.\n", cFileName);
		goto done;
	}

	/* Ensure the limits match up. */
	trap_FS_Read(&Header.iTimeLimit, sizeof(Header.iTimeLimit), hFile);
	trap_FS_Read(&Header.iFragLimit, sizeof(Header.iFragLimit), hFile);
	trap_FS_Read(&Header.iCaptureLimit, sizeof(Header.iCaptureLimit), hFile);

	if ((LittleLong(Header.iTimeLimit) != g_timelimit.integer) ||
		(LittleLong(Header.iFragLimit) != g_fraglimit.integer) ||
		(LittleLong(Header.iCaptureLimit) != g_capturelimit.integer))
	{
		G_Printf("Unable to load highscore file \"%s\", game limit miss match.\n", cFileName);
		goto done;
	}

	trap_FS_Read(&level.iHighScoreCount, sizeof(level.iHighScoreCount), hFile);
	level.iHighScoreCount = LittleLong(level.iHighScoreCount);

	/* Check the file size a second time now we know exactly how much data we're expecting. */
	if (iSize != (LQ3A_HIGHSCORE_HEADER_SIZEOF + (LQ3A_HIGHSCORE_ENTRY_SIZEOF * level.iHighScoreCount)))
	{
		/* Invalid file size. */
		G_Printf("Unable to load highscore file \"%s\", invalid file size.\n", cFileName);
		goto done;
	}

	for (i=0; i<LQ3A_MAX_HIGHSCORE_ENTRIES && i<level.iHighScoreCount; i++)
	{
		LQ3A_ReadNextHighScoreEntry(hFile, &level.HighScores[i]);
	}

	G_Printf("Read %i byte%s of data from high score file \"%s\".\n", iSize, (iSize != 1) ? "s" : "", cFileName);

done:
	trap_FS_FCloseFile(hFile);
	LQ3A_SetHighScoreConfigString();
}

/** Merges current scores with the level.HighScore array, returns qtrue when changes were made. */
static qboolean LQ3A_UpdateHighScores(void)
{
	uint					i, j, k, uScore;
	int						iClient;
	gclient_t				*pClient;
	qboolean				bNewScores;
	plq3a_highscore_entry_t	pEntry;
	char					cUserInfo[MAX_INFO_STRING];

/* The date functionality is only present in non-qvm builds
	since the Quake 3 engine does not provide us with an ability to query time. */
#ifndef Q3_VM
	time_t		t;
	struct tm	*t_local;

	/* Com_sprintf() needs an extra byte for a null terminator. */
	char		cDate[LQ3A_MAX_DATE+1];

	time(&t);
	t_local = localtime(&t);

	Com_sprintf(cDate, sizeof(cDate), "%02i/%02i/%04i",
		t_local->tm_mday, t_local->tm_mon + 1, 1900 + t_local->tm_year);

#endif /* Q3_VM */

	for (i=0, bNewScores=qfalse; i<level.numConnectedClients; i++)
	{
		iClient	= level.sortedClients[i];
		pClient	= &level.clients[iClient];

		if (pClient->sess.sessionTeam == TEAM_SPECTATOR)
		{
			continue;
		}

		/* Ignore bots if we don't want to save them. */
		if (!g_highScoresSaveBots.integer && (g_entities[iClient].r.svFlags & SVF_BOT))
		{
			continue;
		}

		if (pClient->ps.persistant[PERS_SCORE] < 1)
		{
			continue;
		}

		uScore = pClient->ps.persistant[PERS_SCORE];

		/* Convert the score to frags per hour when a fraglimit is set. */
		if (g_fraglimit.integer)
		{
			uScore = uScore * 3600000 / (level.time - pClient->pers.enterTime);
		}

		/* Has the client bettered an existing score. */
		for (j=0; j<level.iHighScoreCount; j++)
		{
			if (uScore > level.HighScores[j].uScore)
			{
				/* Shuffle the existing scores down one position. */
				for (k=level.iHighScoreCount; k>j; k--)
				{
					if (k == LQ3A_MAX_HIGHSCORE_ENTRIES)
					{
						continue;
					}

					memcpy(&level.HighScores[k], &level.HighScores[k-1], sizeof(level.HighScores[0]));
				}

				goto found;
			}
		}

		/* If we already have the maximum count of entries and this score hasn't bettered an existing score
			we can exit now since we are processing the game scores in order. */
		if (j == LQ3A_MAX_HIGHSCORE_ENTRIES)
		{
			return bNewScores;
		}

found:
		pEntry = &level.HighScores[j];

		memset(pEntry, 0, sizeof(level.HighScores[0]));
		Q_strncpyz(pEntry->cGamerTag, pClient->pers.netname, MAX_NETNAME);
		pEntry->uScore				= uScore;
		pEntry->uImpresiveCount		= pClient->ps.persistant[PERS_IMPRESSIVE_COUNT];
		pEntry->uHumiliationCount	= pClient->ps.persistant[PERS_GAUNTLET_FRAG_COUNT];
		pEntry->uExcellentCount		= pClient->ps.persistant[PERS_EXCELLENT_COUNT];
		pEntry->uCaptureCount		= pClient->ps.persistant[PERS_CAPTURES];
		pEntry->uAssistCount			= pClient->ps.persistant[PERS_ASSIST_COUNT];
		pEntry->uDefenceCount		= pClient->ps.persistant[PERS_DEFEND_COUNT];
		pEntry->uAccuracy			= (pClient->accuracy_shots) ? pClient->accuracy_hits * 100 / pClient->accuracy_shots : 0;
		pEntry->uEfficiency			= pClient->ps.persistant[PERS_SCORE] * 100 / (pClient->ps.persistant[PERS_SCORE] + pClient->ps.persistant[PERS_KILLED]);

		/* This addition is subtracted client-side. */
		pEntry->iClient				= iClient + 1;

		if (g_entities[iClient].r.svFlags & SVF_BOT)
		{
			pEntry->uFlags |= LQ3A_HSEF_BOT;

			trap_GetUserinfo(iClient, cUserInfo, sizeof(cUserInfo));
			pEntry->uBotSkill = atoi(Info_ValueForKey(cUserInfo, "skill"));
		}

#ifndef Q3_VM
		pEntry->uFlags	|= LQ3A_HSEF_DATE;
		strcpy(pEntry->cDate, cDate);
#endif /* Q3_VM */

		/* Ensure we don't record more than the maximum count of entries. */
		if (level.iHighScoreCount < LQ3A_MAX_HIGHSCORE_ENTRIES)
		{
			level.iHighScoreCount++;
		}

		/* Stop straight away if we only want to save the winner. */
		if (!g_highScoresSaveAll.integer)
		{
			return qtrue;
		}

		bNewScores = qtrue;
	}

	return bNewScores;
}

/** Broadcasts any change to the top high score position. */
static void LQ3A_BroadcastNewHighScore(void)
{
	plq3a_highscore_entry_t pEntry = &level.HighScores[0];

	if (pEntry->iClient < 1)
	{
		/* The top position has not changed. */
		return;
	}

	if (g_fraglimit.integer || (((g_gametype.integer == GT_CTF) || (g_gametype.integer == GT_1FCTF)) && g_capturelimit.integer))
	{
		LQ3A_SendServerCommand(NULL, "print \"%s%s has set a new high score of %i.\n\"",
			pEntry->cGamerTag, S_COLOR_WHITE, pEntry->uScore);
	}
	else
	{
		LQ3A_SendServerCommand(NULL, "print \"%s%s has set a new high score of %i in %i minutes.\n\"",
			pEntry->cGamerTag, S_COLOR_WHITE, pEntry->uScore, g_timelimit.integer);
	}
}

/** Merges the scoreboard into the high score table and writes the result to file. */
void LQ3A_SaveHighScores(void)
{
	char					cFileName[MAX_QPATH];
	fileHandle_t			hFile;
	int						i;
	plq3a_highscore_entry_t	pEntry;

	if (!g_highScores.integer)
	{
		return;
	}

	if (!LQ3A_UpdateHighScores())
	{
		/* Nothing to update. */
		return;
	}

	LQ3A_SetHighScoreConfigString();
	LQ3A_BroadcastNewHighScore();

	LQ3A_GetHighScoreFileName(cFileName, sizeof(cFileName));

	trap_FS_FOpenFile(va("%s%c%s", LQ3A_HIGHSCORE_DIR, PATH_SEP, cFileName), &hFile, FS_WRITE);

	if (!hFile)
	{
		G_Printf("Unable to open \"%s\" for writing, high scores could not be saved.\n", cFileName);
		return;
	}

	i = LQ3A_HIGHSCORE_IDENT;
	trap_FS_Write(&i, sizeof(i), hFile);

	i = LQ3A_HIGHSCORE_VERSION;
	trap_FS_Write(&i, sizeof(i), hFile);

	/* @todo: Calculate CRC. */
	i = 0;
	trap_FS_Write(&i, sizeof(i), hFile);

	trap_FS_Write(level.cMapName, sizeof(level.cMapName), hFile);
	trap_FS_Write(g_highScoresTag.string, LQ3A_MAX_HIGHSCORE_TAG_SIZE, hFile);
	trap_FS_Write(&g_timelimit.integer, sizeof(g_timelimit.integer), hFile);
	trap_FS_Write(&g_fraglimit.integer, sizeof(g_fraglimit.integer), hFile);
	trap_FS_Write(&g_capturelimit.integer, sizeof(g_capturelimit.integer), hFile);
	trap_FS_Write(&level.iHighScoreCount, sizeof(level.iHighScoreCount), hFile);

	for (i=0; i<level.iHighScoreCount; i++)
	{
		pEntry = &level.HighScores[i];

		trap_FS_Write(pEntry->cGamerTag, MAX_NETNAME, hFile);
		trap_FS_Write(&pEntry->uScore, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uFlags, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uBotSkill, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uImpresiveCount, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uExcellentCount, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uHumiliationCount, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uCaptureCount, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uAssistCount, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uDefenceCount, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uAccuracy, sizeof(uint), hFile);
		trap_FS_Write(&pEntry->uEfficiency, sizeof(uint), hFile);

		/* Always write the date, even in qvm builds to fix the file size.
			This ensures we can validate the file size and that there's enough
			bytes to keep trap_FS_Read() alive. */
		trap_FS_Write(pEntry->cDate, LQ3A_MAX_DATE, hFile);
	}

	trap_FS_FCloseFile(hFile);
}

/********
 * MAIN *
 ********/

/** Initialises the Loaded Q3A specific features. */
void LQ3A_InitGame(void)
{
	LQ3A_InitShortNameMap();

	level.bMissionPack = LQ3A_IsMissionPack();

	if (level.bMissionPack)
	{
		G_Printf("Mission pack content detected.\n");
	}

#if _DEBUG
	/* Write the default config to file, it's used as a base to create variants. */
	LQ3A_WriteCvarTableToFile("configs/default.cfg", qtrue);
#endif /* _DEBUG */

	trap_Cvar_VariableStringBuffer("mapname", level.cMapName, sizeof(level.cMapName));
	Q_strlwr(level.cMapName);

	LQ3A_SetLoadedConfigString();
	LQ3A_SetLimitsConfigString();
	LQ3A_LoadMapList();
	LQ3A_LoadMotd();
	LQ3A_LoadHighScores();

	/* Cache the start inventory parse result.
		There is no need to update CS_ITEMS here as it's done later on in G_InitGame(). */
	LQ3A_ParseStartItemsCvar(qfalse);
}
