/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//

#include "g_local.h"

level_locals_t	level;

gentity_t		g_entities[MAX_GENTITIES];
gclient_t		g_clients[MAX_CLIENTS];

vmCvar_t	g_gametype;
vmCvar_t	g_dmflags;
vmCvar_t	g_fraglimit;
vmCvar_t	g_timelimit;
vmCvar_t	g_capturelimit;
vmCvar_t	g_friendlyFire;
vmCvar_t	g_password;
vmCvar_t	g_needpass;
vmCvar_t	g_maxclients;
vmCvar_t	g_maxGameClients;
vmCvar_t	g_dedicated;
vmCvar_t	g_speed;
vmCvar_t	g_gravity;
vmCvar_t	g_cheats;
vmCvar_t	g_knockback;
vmCvar_t	g_quadfactor;
vmCvar_t	g_forcerespawn;
vmCvar_t	g_inactivity;
vmCvar_t	g_debugMove;
vmCvar_t	g_debugDamage;
vmCvar_t	g_debugAlloc;
vmCvar_t	g_weaponRespawn;
vmCvar_t	g_weaponTeamRespawn;
vmCvar_t	g_motd;
vmCvar_t	g_synchronousClients;
vmCvar_t	g_warmup;
vmCvar_t	g_doWarmup;
vmCvar_t	g_restarted;
vmCvar_t	g_log;
vmCvar_t	g_logSync;
vmCvar_t	g_blood;
vmCvar_t	g_podiumDist;
vmCvar_t	g_podiumDrop;
vmCvar_t	g_allowVote;
vmCvar_t	g_teamAutoJoin;
vmCvar_t	g_teamForceBalance;
vmCvar_t	g_banIPs;
vmCvar_t	g_filterBan;
vmCvar_t	g_smoothClients;
vmCvar_t	pmove_fixed;
vmCvar_t	pmove_msec;
vmCvar_t	g_rankings;
vmCvar_t	g_listEntity;
#ifdef MISSIONPACK
vmCvar_t	g_obeliskHealth;
vmCvar_t	g_obeliskRegenPeriod;
vmCvar_t	g_obeliskRegenAmount;
vmCvar_t	g_obeliskRespawnDelay;
vmCvar_t	g_cubeTimeout;
vmCvar_t	g_redteam;
vmCvar_t	g_blueteam;
vmCvar_t	g_singlePlayer;
vmCvar_t	g_enableDust;
vmCvar_t	g_enableBreath;
vmCvar_t	g_proxMineTimeout;
#endif

/* LQ3A */
vmCvar_t	g_version;
vmCvar_t	g_botCheckTime;
vmCvar_t	g_mapList;
vmCvar_t	g_mapListRandomOrder;
vmCvar_t	g_mapListIgnoreCounts;
vmCvar_t	g_mapListIgnoreConfigs;
vmCvar_t	g_mapsInRotation;		/**< Serverinfo only. */
vmCvar_t	g_highScores;
vmCvar_t	g_highScoresTag;
vmCvar_t	g_highScoresSaveAll;
vmCvar_t	g_highScoresSaveBots;
vmCvar_t	g_spectatorPassword;
vmCvar_t	g_spectatorFreePass;
vmCvar_t	g_spectatorMute;
vmCvar_t	g_hookOffhand;
vmCvar_t	g_hookSpeed;
vmCvar_t	g_hookPullSpeed;
vmCvar_t	g_hookMaxTime;
vmCvar_t	g_hookSky;
vmCvar_t	g_antiCamp;
vmCvar_t	g_antiCampTime;
vmCvar_t	g_antiCampThreshold;
vmCvar_t	g_antiCampWarnTime;
vmCvar_t	g_forceRailStyle;
vmCvar_t	g_intermissionTime;
vmCvar_t	g_intermissionSound;
vmCvar_t	g_spawnShard;
vmCvar_t	g_spawnCombatArmor;
vmCvar_t	g_spawnBodyArmor;
vmCvar_t	g_spawnSmallHealth;
vmCvar_t	g_spawnMediumHealth;
vmCvar_t	g_spawnLargeHealth;
vmCvar_t	g_spawnMegaHealth;
vmCvar_t	g_spawnQuad;
vmCvar_t	g_spawnEnviro;
vmCvar_t	g_spawnHaste;
vmCvar_t	g_spawnInvis;
vmCvar_t	g_spawnRegen;
vmCvar_t	g_spawnFlight;
#ifdef MISSIONPACK
vmCvar_t	g_spawnScout;
vmCvar_t	g_spawnGuard;
vmCvar_t	g_spawnDoubler;
vmCvar_t	g_spawnAmmoRegen;
#endif /* MISSIONPACK */
vmCvar_t	g_spawnHook;
vmCvar_t	g_spawnGauntlet;
vmCvar_t	g_spawnMachinegun;
vmCvar_t	g_spawnShotgun;
vmCvar_t	g_spawnGrenadeLauncher;
vmCvar_t	g_spawnRocketLauncher;
vmCvar_t	g_spawnLightninggun;
vmCvar_t	g_spawnRailgun;
vmCvar_t	g_spawnPlasmagun;
vmCvar_t	g_spawnBFG;
#ifdef MISSIONPACK
vmCvar_t	g_spawnNailgun;
vmCvar_t	g_spawnProxLauncher;
vmCvar_t	g_spawnChaingun;
#endif /* MISSIONPACK */
vmCvar_t	g_spawnTeleporter;
vmCvar_t	g_spawnMedkit;
#ifdef MISSIONPACK
vmCvar_t	g_spawnKamikaze;
vmCvar_t	g_spawnPortal;
vmCvar_t	g_spawnInvuln;
#endif /* MISSIONPACK */
vmCvar_t	g_spawnBullets;
vmCvar_t	g_spawnShells;
vmCvar_t	g_spawnGrenades;
vmCvar_t	g_spawnRockets;
vmCvar_t	g_spawnLightning;
vmCvar_t	g_spawnSlugs;
vmCvar_t	g_spawnCells;
vmCvar_t	g_spawnBFGAmmo;
#ifdef MISSIONPACK
vmCvar_t	g_spawnNails;
vmCvar_t	g_spawnMines;
vmCvar_t	g_spawnBelt;
#endif /* MISSIONPACK */
vmCvar_t	g_startProtection;
vmCvar_t	g_initialWeapon;
vmCvar_t	g_startHealth;
vmCvar_t	g_startArmor;
vmCvar_t	g_startItems;
vmCvar_t	g_startBullets;
vmCvar_t	g_startShells;
vmCvar_t	g_startGrenades;
vmCvar_t	g_startRockets;
vmCvar_t	g_startLightning;
vmCvar_t	g_startSlugs;
vmCvar_t	g_startCells;
vmCvar_t	g_startBFGAmmo;
#ifdef MISSIONPACK
vmCvar_t	g_startNails;
vmCvar_t	g_startMines;
vmCvar_t	g_startBelt;
#endif /* MISSIONPACK */
vmCvar_t	g_packShard;
vmCvar_t	g_packCombatArmor;
vmCvar_t	g_packHeavyArmor;
vmCvar_t	g_packSmallHealth;
vmCvar_t	g_packMediumHealth;
vmCvar_t	g_packLargeHealth;
vmCvar_t	g_packMegaHealth;
vmCvar_t	g_packMachinegun;
vmCvar_t	g_packShotgun;
vmCvar_t	g_packGrenadeLauncher;
vmCvar_t	g_packRocketLauncher;
vmCvar_t	g_packLightninggun;
vmCvar_t	g_packRailgun;
vmCvar_t	g_packPlasmagun;
vmCvar_t	g_packBFG;
#ifdef MISSIONPACK
vmCvar_t	g_packNailgun;
vmCvar_t	g_packProxLauncher;
vmCvar_t	g_packChaingun;
#endif  /* MISSIONPACK */
vmCvar_t	g_packBullets;
vmCvar_t	g_packShells;
vmCvar_t	g_packGrenades;
vmCvar_t	g_packRockets;
vmCvar_t	g_packLightning;
vmCvar_t	g_packSlugs;
vmCvar_t	g_packCells;
vmCvar_t	g_packBFGAmmo;
#ifdef MISSIONPACK
vmCvar_t	g_packNails;
vmCvar_t	g_packMines;
vmCvar_t	g_packBelt;
#endif /* MISSIONPACK */
vmCvar_t	g_maxHealth;
vmCvar_t	g_maxBullets;
vmCvar_t	g_maxShells;
vmCvar_t	g_maxGrenades;
vmCvar_t	g_maxRockets;
vmCvar_t	g_maxLightning;
vmCvar_t	g_maxSlugs;
vmCvar_t	g_maxCells;
vmCvar_t	g_maxBFGAmmo;
#ifdef MISSIONPACK
vmCvar_t	g_maxNails;
vmCvar_t	g_maxMines;
vmCvar_t	g_maxBelt;
#endif /* MISSIONPACK */
vmCvar_t	g_refireHook;
vmCvar_t	g_refireGauntlet;
vmCvar_t	g_refireMachinegun;
vmCvar_t	g_refireShotgun;
vmCvar_t	g_refireGrenadeLauncher;
vmCvar_t	g_refireRocketLauncher;
vmCvar_t	g_refireLightninggun;
vmCvar_t	g_refireRailgun;
vmCvar_t	g_refirePlasmagun;
vmCvar_t	g_refireBFG;
#ifdef MISSIONPACK
vmCvar_t	g_refireNailgun;
vmCvar_t	g_refireProxLauncher;
vmCvar_t	g_refireChaingun;
#endif /* MISSIONPACK */
vmCvar_t	g_switchSpeed;
vmCvar_t	g_quadTime;
vmCvar_t	g_battleSuiteTime;
vmCvar_t	g_hasteTime;
vmCvar_t	g_hasteFactor;
vmCvar_t	g_invisTime;
vmCvar_t	g_regenTime;
vmCvar_t	g_flightTime;
vmCvar_t	g_jumpVelocity;
vmCvar_t	g_waterTime;
vmCvar_t	g_grenadeSpeed;
vmCvar_t	g_grenadeTimer;
vmCvar_t	g_rocketSpeed;
vmCvar_t	g_plasmaSpeed;
vmCvar_t	g_bfgSpeed;
vmCvar_t	g_damageSelfFactor;
vmCvar_t	g_damageFallFactor;
vmCvar_t	g_damageHook;
vmCvar_t	g_damageGauntlet;
vmCvar_t	g_damageBullet;
vmCvar_t	g_damageBulletSpread;
vmCvar_t	g_damageShell;
vmCvar_t	g_damageShellSpread;
vmCvar_t	g_damageGrenade;
vmCvar_t	g_damageGrenadeSplash;
vmCvar_t	g_damageGrenadeRadius;
vmCvar_t	g_damageRocket;
vmCvar_t	g_damageRocketSplash;
vmCvar_t	g_damageRocketRadius;
vmCvar_t	g_damageLightning;
vmCvar_t	g_damageRail;
vmCvar_t	g_damagePlasma;
vmCvar_t	g_damagePlasmaSplash;
vmCvar_t	g_damagePlasmaRadius;
vmCvar_t	g_damageBFG;
vmCvar_t	g_damageBFGSplash;
vmCvar_t	g_damageBFGRadius;
vmCvar_t	g_damageSlime;
vmCvar_t	g_damageLava;
vmCvar_t	g_dropItemsOnDeath;

// bk001129 - made static to avoid aliasing
static cvarTable_t		gameCvarTable[] = {
	// don't override the cheat state set by the system
	{ &g_cheats, "sv_cheats", "", 0, 0, qfalse },

	// noset vars
	{ NULL, "gamename", GAMEVERSION , CVAR_SERVERINFO | CVAR_ROM, 0, qfalse  },
	{ NULL, "gamedate", __DATE__ , CVAR_ROM, 0, qfalse  },
	{ &g_restarted, "g_restarted", "0", CVAR_ROM, 0, qfalse  },
	{ NULL, "sv_mapname", "", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse  },

	// latched vars

	{ &g_gametype, "g_gametype", "0", CVAR_SERVERINFO | CVAR_USERINFO | CVAR_LATCH, 0, qfalse  },

	{ &g_maxclients, "sv_maxclients", "8", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse  },
	{ &g_maxGameClients, "g_maxGameClients", "0", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse  },

	// change anytime vars
	{ &g_dmflags, "dmflags", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue  },
	{ &g_fraglimit, "fraglimit", "20", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },
	{ &g_timelimit, "timelimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },
	{ &g_capturelimit, "capturelimit", "8", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },

	{ &g_synchronousClients, "g_synchronousClients", "0", CVAR_SYSTEMINFO, 0, qfalse  },

	{ &g_friendlyFire, "g_friendlyFire", "0", CVAR_ARCHIVE, 0, qtrue  },

	{ &g_teamAutoJoin, "g_teamAutoJoin", "0", CVAR_ARCHIVE  },
	{ &g_teamForceBalance, "g_teamForceBalance", "0", CVAR_ARCHIVE  },

	{ &g_warmup, "g_warmup", "20", CVAR_ARCHIVE, 0, qtrue  },
	{ &g_doWarmup, "g_doWarmup", "0", 0, 0, qtrue  },
	{ &g_log, "g_log", "games.log", CVAR_ARCHIVE, 0, qfalse  },
	{ &g_logSync, "g_logSync", "0", CVAR_ARCHIVE, 0, qfalse  },

	{ &g_password, "g_password", "", CVAR_USERINFO, 0, qfalse  },

	{ &g_banIPs, "g_banIPs", "", CVAR_ARCHIVE, 0, qfalse  },
	{ &g_filterBan, "g_filterBan", "1", CVAR_ARCHIVE, 0, qfalse  },

	{ &g_needpass, "g_needpass", "0", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse },

	{ &g_dedicated, "dedicated", "0", 0, 0, qfalse  },

	{ &g_speed, "g_speed", "320", 0, 0, qtrue  },
	{ &g_gravity, "g_gravity", "800", 0, 0, qtrue  },
	{ &g_knockback, "g_knockback", "1000", 0, 0, qtrue  },
	{ &g_quadfactor, "g_quadfactor", "3", 0, 0, qtrue  },
	{ &g_weaponRespawn, "g_weaponrespawn", "5", 0, 0, qtrue  },
	{ &g_weaponTeamRespawn, "g_weaponTeamRespawn", "30", 0, 0, qtrue },
	{ &g_forcerespawn, "g_forcerespawn", "20", 0, 0, qtrue },
	{ &g_inactivity, "g_inactivity", "0", 0, 0, qtrue },
	{ &g_debugMove, "g_debugMove", "0", 0, 0, qfalse },
	{ &g_debugDamage, "g_debugDamage", "0", 0, 0, qfalse },
	{ &g_debugAlloc, "g_debugAlloc", "0", 0, 0, qfalse },

	/* LQ3A: Changed default and enabled tracking. */
	{&g_motd, "g_motd", "motd.txt", 0, 0, qtrue},

	{ &g_blood, "com_blood", "1", 0, 0, qfalse },

	{ &g_podiumDist, "g_podiumDist", "80", 0, 0, qfalse },
	{ &g_podiumDrop, "g_podiumDrop", "70", 0, 0, qfalse },

	{ &g_allowVote, "g_allowVote", "1", CVAR_ARCHIVE, 0, qfalse },
	{ &g_listEntity, "g_listEntity", "0", 0, 0, qfalse },

#ifdef MISSIONPACK
	{ &g_obeliskHealth, "g_obeliskHealth", "2500", 0, 0, qfalse },
	{ &g_obeliskRegenPeriod, "g_obeliskRegenPeriod", "1", 0, 0, qfalse },
	{ &g_obeliskRegenAmount, "g_obeliskRegenAmount", "15", 0, 0, qfalse },
	{ &g_obeliskRespawnDelay, "g_obeliskRespawnDelay", "10", CVAR_SERVERINFO, 0, qfalse },

	{ &g_cubeTimeout, "g_cubeTimeout", "30", 0, 0, qfalse },
	{ &g_redteam, "g_redteam", "Stroggs", CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO , 0, qtrue, qtrue },
	{ &g_blueteam, "g_blueteam", "Pagans", CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO , 0, qtrue, qtrue  },
	{ &g_singlePlayer, "ui_singlePlayerActive", "", 0, 0, qfalse, qfalse  },

	{ &g_enableDust, "g_enableDust", "0", CVAR_SERVERINFO, 0, qtrue, qfalse },
	{ &g_enableBreath, "g_enableBreath", "0", CVAR_SERVERINFO, 0, qtrue, qfalse },
	{ &g_proxMineTimeout, "g_proxMineTimeout", "20000", 0, 0, qfalse },
#endif
	{ &g_smoothClients, "g_smoothClients", "1", 0, 0, qfalse},
	{ &pmove_fixed, "pmove_fixed", "0", CVAR_SYSTEMINFO, 0, qfalse},
	{ &pmove_msec, "pmove_msec", "8", CVAR_SYSTEMINFO, 0, qfalse},

	{ &g_rankings, "g_rankings", "0", 0, 0, qfalse},

	/* LQ3A */
	{&g_version,				"g_version",				LQ3A_VERSION,		CVAR_SERVERINFO|CVAR_ROM,	0,	qfalse},
	{&g_botCheckTime,			"g_botCheckTime",			"6",				CVAR_ARCHIVE,	0,	qfalse},	/* Q3A default was 10. */
	{&g_mapList,				"g_mapList",				"maplist.txt",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_mapListRandomOrder,		"g_mapListRandomOrder",		"1",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_mapListIgnoreCounts,	"g_mapListIgnoreCounts",	"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_mapListIgnoreConfigs,	"g_mapListIgnoreConfigs",	"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_mapsInRotation,			"g_mapsInRotation",			"0",				CVAR_SERVERINFO|CVAR_ROM,		0,	qfalse},
	{&g_highScores,				"g_highScores",				"1",				CVAR_SERVERINFO|CVAR_ARCHIVE,	0,	qtrue}, /* CS_LQ3A_CONFIG */
	{&g_highScoresTag,			"g_highScoresTag",			"lq3a",				CVAR_ARCHIVE,	0,	qtrue},
	{&g_highScoresSaveAll,		"g_highScoresSaveAll",		"1",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_highScoresSaveBots,		"g_highScoresSaveBots",		"1",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_spectatorPassword,		"g_spectatorPassword",		"",					CVAR_ARCHIVE|CVAR_LATCH,	0,	qfalse},
	{&g_spectatorFreePass,		"g_spectatorFreePass",		"85",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_spectatorMute,			"g_spectatorMute",			"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_hookOffhand,			"g_hookOffhand",			"0",				CVAR_ARCHIVE,	0,	qtrue},
	{&g_hookSpeed,				"g_hookSpeed",				"960",				CVAR_ARCHIVE,	0,	qfalse},	/* Q3A default was 800. */
	{&g_hookPullSpeed,			"g_hookPullSpeed",			"850",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG, Q3A default was 800. */
	{&g_hookMaxTime,			"g_hookMaxTime",			"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_hookSky,				"g_hookSky",				"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_antiCamp,				"g_antiCamp",				"1",				CVAR_SERVERINFO|CVAR_ARCHIVE,	0,	qfalse},
	{&g_antiCampTime,			"g_antiCampTime",			"3",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_antiCampThreshold,		"g_antiCampThreshold",		"220",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_antiCampWarnTime,		"g_antiCampWarnTime",		"3",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_forceRailStyle,			"g_forceRailStyle",			"0",				CVAR_ARCHIVE,	0,	qtrue},
	{&g_intermissionTime,		"g_intermissionTime",		"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_intermissionSound,		"g_intermissionSound",		"music/win.wav",	CVAR_ARCHIVE,	0,	qfalse},
	{&g_spawnShard,				"g_spawnShard",				"shard",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnCombatArmor,		"g_spawnCombatArmor",		"combatArmor",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnBodyArmor,			"g_spawnBodyArmor",			"bodyArmor",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnSmallHealth,		"g_spawnSmallHealth",		"smallHealth",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnMediumHealth,		"g_spawnMediumHealth",		"mediumHealth",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnLargeHealth,		"g_spawnLargeHealth",		"largeHealth",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnMegaHealth,		"g_spawnMegaHealth",		"megaHealth",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnQuad,				"g_spawnQuad",				"quad",				CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnEnviro,			"g_spawnEnviro",			"enviro",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnHaste,				"g_spawnHaste",				"haste",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnInvis,				"g_spawnInvis",				"invis",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnRegen,				"g_spawnRegen",				"regen",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnFlight,			"g_spawnFlight",			"flight",			CVAR_ARCHIVE,	0,	qtrue},
#ifdef MISSIONPACK
	{&g_spawnScout,				"g_spawnScout",				"scout",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnGuard,				"g_spawnGuard",				"guard",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnDoubler,			"g_spawnDoubler",			"doubler",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnAmmoRegen,			"g_spawnAmmoRegen",			"ammoRegen",		CVAR_ARCHIVE,	0,	qtrue},
#endif /* MISSIONPACK */
	{&g_spawnHook,				"g_spawnHook",				"hook",				CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnGauntlet,			"g_spawnGauntlet",			"gauntlet",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnMachinegun,		"g_spawnMachinegun",		"machinegun",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnShotgun,			"g_spawnShotgun",			"shotgun",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnGrenadeLauncher,	"g_spawnGrenadeLauncher",	"glauncher",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnRocketLauncher,	"g_spawnRocketLauncher",	"rlauncher",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnLightninggun,		"g_spawnLightninggun",		"lightninggun",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnRailgun,			"g_spawnRailgun",			"railgun",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnPlasmagun,			"g_spawnPlasmagun",			"plasmagun",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnBFG,				"g_spawnBFG",				"bfg",				CVAR_ARCHIVE,	0,	qtrue},
#ifdef MISSIONPACK
	{&g_spawnNailgun,			"g_spawnNailgun",			"nailgun",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnProxLauncher,		"g_spawnProxLauncher",		"plauncher",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnChaingun,			"g_spawnChaingun",			"chaingun",			CVAR_ARCHIVE,	0,	qtrue},
#endif /* MISSIONPACK */
	{&g_spawnTeleporter,		"g_spawnTeleporter",		"teleporter",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnMedkit,			"g_spawnMedkit",			"medkit",			CVAR_ARCHIVE,	0,	qtrue},
#ifdef MISSIONPACK
	{&g_spawnKamikaze,			"g_spawnKamikaze",			"kamikaze",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnPortal,			"g_spawnPortal",			"portal",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnInvuln,			"g_spawnInvuln",			"invuln",			CVAR_ARCHIVE,	0,	qtrue},
#endif /* MISSIONPACK */
	{&g_spawnBullets,			"g_spawnBullets",			"bullets",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnShells,			"g_spawnShells",			"shells",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnGrenades,			"g_spawnGrenades",			"grenades",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnRockets,			"g_spawnRockets",			"rockets",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnLightning,			"g_spawnLightning",			"lightning",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnSlugs,				"g_spawnSlugs",				"slugs",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnCells,				"g_spawnCells",				"cells",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnBFGAmmo,			"g_spawnBFGAmmo",			"bfgAmmo",			CVAR_ARCHIVE,	0,	qtrue},
#ifdef MISSIONPACK
	{&g_spawnNails,				"g_spawnNails",				"nails",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnMines,				"g_spawnMines",				"mines",			CVAR_ARCHIVE,	0,	qtrue},
	{&g_spawnBelt,				"g_spawnBelt",				"belt",				CVAR_ARCHIVE,	0,	qtrue},
#endif /* MISSIONPACK */	
	{&g_startProtection,		"g_startProtection",		"3",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_initialWeapon,			"g_initialWeapon",			"machinegun",		CVAR_ARCHIVE,	0,	qtrue},
	{&g_startHealth,			"g_startHealth",			"125",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startItems,				"g_startItems",				"gauntlet,machinegun",	CVAR_ARCHIVE,	0,	qtrue},
	{&g_startArmor,				"g_startArmor",				"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startBullets,			"g_startBullets",			"50",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startShells,			"g_startShells",			"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startGrenades,			"g_startGrenades",			"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startRockets,			"g_startRockets",			"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startLightning,			"g_startLightning",			"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startSlugs,				"g_startSlugs",				"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startCells,				"g_startCells",				"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startBFGAmmo,			"g_startBFGAmmo",			"0",				CVAR_ARCHIVE,	0,	qfalse},
#ifdef MISSIONPACK
	{&g_startNails,				"g_startNails",				"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startMines,				"g_startMines",				"0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_startBelt,				"g_startBelt",				"0",				CVAR_ARCHIVE,	0,	qfalse},
#endif /* MISSIONPACK */
	{&g_packShard,				"g_packShard",				"5",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packCombatArmor,		"g_packCombatArmor",		"50",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packHeavyArmor,			"g_packHeavyArmor",			"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packSmallHealth,		"g_packSmallHealth",		"5",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packMediumHealth,		"g_packMediumHealth",		"25",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packLargeHealth,		"g_packLargeHealth",		"50",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packMegaHealth,			"g_packMegaHealth",			"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packMachinegun,			"g_packMachinegun",			"40",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packShotgun,			"g_packShotgun",			"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packGrenadeLauncher,	"g_packGrenadeLauncher",	"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packRocketLauncher,		"g_packRocketLauncher",		"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packLightninggun,		"g_packLightninggun",		"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packRailgun,			"g_packRailgun",			"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packPlasmagun,			"g_packPlasmagun",			"50",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packBFG,				"g_packBFG",				"20",				CVAR_ARCHIVE,	0,	qfalse},
#ifdef MISSIONPACK
	{&g_packNailgun,			"g_packNailgun",			"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packProxLauncher,		"g_packProxLauncher",		"5",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packChaingun,			"g_packChaingun",			"80",				CVAR_ARCHIVE,	0,	qfalse},
#endif  /* MISSIONPACK */
	{&g_packBullets,			"g_packBullets",			"50",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packShells,				"g_packShells",				"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packGrenades,			"g_packGrenades",			"5",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packRockets,			"g_packRockets",			"5",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packLightning,			"g_packLightning",			"60",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packSlugs,				"g_packSlugs",				"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packCells,				"g_packCells",				"30",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packBFGAmmo,			"g_packBFGAmmo",			"15",				CVAR_ARCHIVE,	0,	qfalse},
#ifdef MISSIONPACK
	{&g_packNails,				"g_packNails",				"20",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packMines,				"g_packMines",				"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_packBelt,				"g_packBelt",				"100",				CVAR_ARCHIVE,	0,	qfalse},
#endif /* MISSIONPACK */
	{&g_maxHealth,				"g_maxHealth",				"100",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxBullets,				"g_maxBullets",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxShells,				"g_maxShells",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxGrenades,			"g_maxGrenades",			"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxRockets,				"g_maxRockets",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxLightning,			"g_maxLightning",			"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxSlugs,				"g_maxSlugs",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxCells,				"g_maxCells",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxBFGAmmo,				"g_maxBFGAmmo",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
#ifdef MISSIONPACK
	{&g_maxNails,				"g_maxNails",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxMines,				"g_maxMines",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
	{&g_maxBelt,				"g_maxBelt",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_LIMITS */
#endif /* MISSIONPACK */
	{&g_refireHook,				"g_refireHook",				"400",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireGauntlet,			"g_refireGauntlet",			"400",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireMachinegun,		"g_refireMachinegun",		"100",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireShotgun,			"g_refireShotgun",			"1000",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireGrenadeLauncher,	"g_refireGrenadeLauncher",	"800",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireRocketLauncher,	"g_refireRocketLauncher",	"800",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireLightninggun,		"g_refireLightninggun",		"50",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireRailgun,			"g_refireRailgun",			"1500",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refirePlasmagun,		"g_refirePlasmagun",		"100",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireBFG,				"g_refireBFG",				"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
#ifdef MISSIONPACK
	{&g_refireNailgun,			"g_refireNailgun",			"1000",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireProxLauncher,		"g_refireProxLauncher",		"800",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_refireChaingun,			"g_refireChaingun",			"30",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
#endif /* MISSIONPACK */
	{&g_switchSpeed,			"g_switchSpeed",			"200",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_quadTime,				"g_quadTime",				"30",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_battleSuiteTime,		"g_battleSuiteTime",		"30",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_hasteTime,				"g_hasteTime",				"30",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_hasteFactor,			"g_hasteFactor",			"1.3",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_invisTime,				"g_invisTime",				"30",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_regenTime,				"g_regenTime",				"30",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_flightTime,				"g_flightTime",				"60",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_jumpVelocity,			"g_jumpVelocity",			"270",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_waterTime,				"g_waterTime",				"25",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_grenadeSpeed,			"g_grenadeSpeed",			"700",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_grenadeTimer,			"g_grenadeTimer",			"2.5",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_rocketSpeed,			"g_rocketSpeed",			"900",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_plasmaSpeed,			"g_plasmaSpeed",			"2000",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_bfgSpeed,				"g_bfgSpeed",				"2000",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageSelfFactor,		"g_damageSelfFactor",		"0.5",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageFallFactor,		"g_damageFallFactor",		"1.0",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageHook,				"g_damageHook",				"8",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageGauntlet,			"g_damageGauntlet",			"50",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageBullet,			"g_damageBullet",			"7",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageBulletSpread,		"g_damageBulletSpread",		"200",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageShell,			"g_damageShell",			"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageShellSpread,		"g_damageShellSpread",		"700",				CVAR_ARCHIVE,	0,	qtrue},		/* CS_LQ3A_CONFIG */
	{&g_damageGrenade,			"g_damageGrenade",			"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageGrenadeSplash,	"g_damageGrenadeSplash",	"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageGrenadeRadius,	"g_damageGrenadeRadius",	"150",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageRocket,			"g_damageRocket",			"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageRocketSplash,		"g_damageRocketSplash",		"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageRocketRadius,		"g_damageRocketRadius",		"120",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageLightning,		"g_damageLightning",		"8",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageRail,				"g_damageRail",				"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damagePlasma,			"g_damagePlasma",			"20",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damagePlasmaSplash,		"g_damagePlasmaSplash",		"15",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damagePlasmaRadius,		"g_damagePlasmaRadius",		"20",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageBFG,				"g_damageBFG",				"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageBFGSplash,		"g_damageBFGSplash",		"100",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageBFGRadius,		"g_damageBFGRadius",		"120",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageSlime,			"g_damageSlime",			"10",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_damageLava,				"g_damageLava",				"30",				CVAR_ARCHIVE,	0,	qfalse},
	{&g_dropItemsOnDeath,		"g_dropItemsOnDeath",		"1",				CVAR_ARCHIVE,	0,	qfalse}
};

// bk001129 - made static to avoid aliasing
static int gameCvarTableSize = sizeof( gameCvarTable ) / sizeof( gameCvarTable[0] );

void G_InitGame( int levelTime, int randomSeed, int restart );
void G_RunFrame( int levelTime );
void G_ShutdownGame( int restart );
void CheckExitRules( void );


/*
================
vmMain

This is the only way control passes into the module.
This must be the very first function compiled into the .q3vm file
================
*/
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) {

	/* LQ3A */
	UNREFERENCED_PARAMETER(arg3);
	UNREFERENCED_PARAMETER(arg4);
	UNREFERENCED_PARAMETER(arg5);
	UNREFERENCED_PARAMETER(arg6);
	UNREFERENCED_PARAMETER(arg7);
	UNREFERENCED_PARAMETER(arg8);
	UNREFERENCED_PARAMETER(arg9);
	UNREFERENCED_PARAMETER(arg10);
	UNREFERENCED_PARAMETER(arg11);

	switch ( command ) {
	case GAME_INIT:
		G_InitGame( arg0, arg1, arg2 );
		return 0;
	case GAME_SHUTDOWN:
		G_ShutdownGame( arg0 );
		return 0;
	case GAME_CLIENT_CONNECT:
		return (int)ClientConnect( arg0, arg1, arg2 );
	case GAME_CLIENT_THINK:
		ClientThink( arg0 );
		return 0;
	case GAME_CLIENT_USERINFO_CHANGED:
		ClientUserinfoChanged( arg0 );
		return 0;
	case GAME_CLIENT_DISCONNECT:
		ClientDisconnect( arg0 );
		return 0;
	case GAME_CLIENT_BEGIN:
		ClientBegin( arg0 );
		return 0;
	case GAME_CLIENT_COMMAND:
		ClientCommand( arg0 );
		return 0;
	case GAME_RUN_FRAME:
		G_RunFrame( arg0 );
		return 0;
	case GAME_CONSOLE_COMMAND:
		return ConsoleCommand();
	case BOTAI_START_FRAME:
		return BotAIStartFrame( arg0 );
	}

	return -1;
}

/** LQ3A: Creates a config file with all the game variables and their values. */
void LQ3A_WriteCvarTableToFile(pcchar pFileName, qboolean bDefaultValues)
{
	fileHandle_t	hFile;
	int				i;
	size_t			uLen, uMaxLen, uTabs, uMaxTabs;
	cvarTable_t		*pCvar;
	char			cBuffer[MAX_TOKENLENGTH];
	pchar			pValue;

	/* Find the longest line length and work out how many
		tabs it'll need to pad values out to the same length. */
	for (i=0,uMaxLen=0; i<gameCvarTableSize; i++)
	{
		pCvar = &gameCvarTable[i];

		if (pCvar->cvarFlags & CVAR_ROM)
		{
			continue;
		}

		uLen = strlen(pCvar->cvarName);

		if (uLen > uMaxLen)
		{
			uMaxLen = uLen;
		}
	}

	uMaxTabs = (float)((sizeof("seta ")+uMaxLen) / 4.0f) + 1;

	/* Write the cvar table to file. */
	trap_FS_FOpenFile(pFileName, &hFile, FS_WRITE);

	for (i=0; i<gameCvarTableSize; i++)
	{
		pCvar = &gameCvarTable[i];

		if (pCvar->cvarFlags & CVAR_ROM)
		{
			continue;
		}

		pValue = (bDefaultValues) ? pCvar->defaultString : pCvar->vmCvar->string;

		uLen = Com_sprintf(cBuffer, sizeof(cBuffer), "seta %s", pCvar->cvarName);

		/* Pad the line out with tabs to ensure it lines up with the longest entry. */
		uTabs = (size_t)((float)uLen / 4.0f);

		for (;uTabs<uMaxTabs;uTabs++)
		{
			Q_strcat(cBuffer, sizeof(cBuffer), "\t");
		}

		/* Enclose string values in double quotes. */
		if ((atoi(pValue) == 0) && (Q_stricmp(pValue, "0") != 0))
		{
			Q_strcat(cBuffer, sizeof(cBuffer), va("\"%s\"", pValue));
		}
		else
		{
			Q_strcat(cBuffer, sizeof(cBuffer), pValue);
		}

		/* End with a line break on everything except the final entry. */
		if (i != (gameCvarTableSize-1))
		{
			Q_strcat(cBuffer, sizeof(cBuffer), "\r\n");
		}

		trap_FS_Write(cBuffer, strlen(cBuffer), hFile);
	}

	trap_FS_FCloseFile(hFile);
}

/** LQ3A: Searches the cvar table for a cvar with the given name and returns a reference to it.
		Placed here to avoid having to game gameCvarTable and gameCvarTableSize global #bk001129. */
cvarTable_t *LQ3A_FindCvarByName(pcchar pName)
{
	/** @fixme: Global function returns pointer to static variable. */

	cvarTable_t *pCvar;
	uint		i;

	if (!pName)
	{
		assert(pName);
		return NULL;
	}

	for (i=0; i<gameCvarTableSize; i++)
	{
		pCvar = &gameCvarTable[i];

		if (Q_stricmp(pCvar->cvarName, pName) == 0)
		{
			return pCvar;
		}
	}

	return NULL;
}

/** LQ3A: Returns a pointer to the given cvar in the cvar table,
		NULL is returned when the given cvar could not be found. */
static cvarTable_t *LQ3A_GetCvarFromVmCvar(vmCvar_t *pVmCvar)
{
	uint i;

	assert(pVmCvar);

	for (i=0; i<gameCvarTableSize; i++)
	{
		if (gameCvarTable[i].vmCvar == pVmCvar)
		{
			return &gameCvarTable[i];
		}
	}

	return NULL;
}

/** LQ3A: Copies the name of the given cvar to the given buffer and returns qtrue on success.*/
qboolean LQ3A_GetCvarName(vmCvar_t *pVmCvar, pchar pBuffer, int iSize)
{
	cvarTable_t *pCvar;

	assert(pVmCvar && pBuffer && iSize);

	pCvar = LQ3A_GetCvarFromVmCvar(pVmCvar);

	if (pCvar)
	{
		Q_strncpyz(pBuffer, pCvar->cvarName, iSize);
		return qtrue;
	}

	return qfalse;
}

/* LQ3A: Executes an update instruction for the cvar with the given name.
	Setting bSurpressTracking to qtrue will suppress tracking in the next G_UpdateCvars() call. 
	Placed here to avoid having to game gameCvarTable and gameCvarTableSize global #bk001129. */
void LQ3A_UpdateCvarByName(pcchar pName, qboolean bSurpressTracking)
{
	cvarTable_t	*pCvar = LQ3A_FindCvarByName(pName);

	if (!pCvar)
	{
		trap_Cvar_Update(pCvar->vmCvar);

		if (bSurpressTracking)
		{
			pCvar->modificationCount = pCvar->vmCvar->modificationCount;
		}
	}
}

void QDECL G_Printf( const char *fmt, ... ) {
	va_list		argptr;
	char		text[1024];

	va_start (argptr, fmt);
	vsprintf (text, fmt, argptr);
	va_end (argptr);

	trap_Printf( text );
}

void QDECL G_Error( const char *fmt, ... ) {
	va_list		argptr;
	char		text[1024];

	va_start (argptr, fmt);
	vsprintf (text, fmt, argptr);
	va_end (argptr);

	trap_Error( text );
}

/*
================
G_FindTeams

Chain together all entities with a matching team field.
Entity teams are used for item groups and multi-entity mover groups.

All but the first will have the FL_TEAMSLAVE flag set and teammaster field set
All but the last will have the teamchain field set to the next one
================
*/
void G_FindTeams( void ) {
	gentity_t	*e, *e2;
	int		i, j;
	int		c, c2;

	c = 0;
	c2 = 0;
	for ( i=1, e=g_entities+i ; i < level.num_entities ; i++,e++ ){
		if (!e->inuse)
			continue;
		if (!e->team)
			continue;
		if (e->flags & FL_TEAMSLAVE)
			continue;
		e->teammaster = e;
		c++;
		c2++;
		for (j=i+1, e2=e+1 ; j < level.num_entities ; j++,e2++)
		{
			if (!e2->inuse)
				continue;
			if (!e2->team)
				continue;
			if (e2->flags & FL_TEAMSLAVE)
				continue;
			if (!strcmp(e->team, e2->team))
			{
				c2++;
				e2->teamchain = e->teamchain;
				e->teamchain = e2;
				e2->teammaster = e;
				e2->flags |= FL_TEAMSLAVE;

				// make sure that targets only point at the master
				if ( e2->targetname ) {
					e->targetname = e2->targetname;
					e2->targetname = NULL;
				}
			}
		}
	}

	G_Printf ("%i teams with %i entities\n", c, c2);
}

void G_RemapTeamShaders() {
#ifdef MISSIONPACK
	char string[1024];
	float f = level.time * 0.001;
	Com_sprintf( string, sizeof(string), "team_icon/%s_red", g_redteam.string );
	AddRemap("textures/ctf2/redteam01", string, f); 
	AddRemap("textures/ctf2/redteam02", string, f); 
	Com_sprintf( string, sizeof(string), "team_icon/%s_blue", g_blueteam.string );
	AddRemap("textures/ctf2/blueteam01", string, f); 
	AddRemap("textures/ctf2/blueteam02", string, f); 
	trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
#endif
}


/*
=================
G_RegisterCvars
=================
*/
void G_RegisterCvars( void ) {
	int			i;
	cvarTable_t	*cv;
	qboolean remapped = qfalse;

	for ( i = 0, cv = gameCvarTable ; i < gameCvarTableSize ; i++, cv++ ) {
		trap_Cvar_Register( cv->vmCvar, cv->cvarName,
			cv->defaultString, cv->cvarFlags );
		if ( cv->vmCvar )
			cv->modificationCount = cv->vmCvar->modificationCount;

		if (cv->teamShader) {
			remapped = qtrue;
		}
	}

	if (remapped) {
		G_RemapTeamShaders();
	}

	// check some things
	if ( g_gametype.integer < 0 || g_gametype.integer >= GT_MAX_GAME_TYPE ) {
		G_Printf( "g_gametype %i is out of range, defaulting to 0\n", g_gametype.integer );
		trap_Cvar_Set( "g_gametype", "0" );
	}

	level.warmupModificationCount = g_warmup.modificationCount;
}

/*
=================
G_UpdateCvars
=================
*/
void G_UpdateCvars( void ) {
	int			i;
	cvarTable_t	*cv;
	qboolean remapped = qfalse;

	for ( i = 0, cv = gameCvarTable ; i < gameCvarTableSize ; i++, cv++ ) {
		if ( cv->vmCvar ) {
			trap_Cvar_Update( cv->vmCvar );

			if ( cv->modificationCount != cv->vmCvar->modificationCount ) {
				cv->modificationCount = cv->vmCvar->modificationCount;
				
				if ( cv->trackChange ) {

					/* LQ3A: Process the change, broadcast only when qtrue is returned. */
					if (LQ3A_CvarChanged(cv))
					{
						trap_SendServerCommand(-1, va("print \"Server: %s changed to %s\n\"", 
							cv->cvarName, cv->vmCvar->string));
					}
				}

				if (cv->teamShader) {
					remapped = qtrue;
				}
			}
		}
	}

	if (remapped) {
		G_RemapTeamShaders();
	}

	/* LQ3A: Communicate CS_ITEMS changes to all clients. */
	if (level.bUpdateRegisteredItems)
	{
		SaveRegisteredItems();
		level.bUpdateRegisteredItems = qfalse;
	}
}

/*
============
G_InitGame

============
*/
void G_InitGame( int levelTime, int randomSeed, int restart ) {
	int					i;

	G_Printf ("------- Game Initialization -------\n");
	G_Printf ("gamename: %s\n", GAMEVERSION);
	G_Printf ("gamedate: %s\n", __DATE__);

	srand( randomSeed );

	G_RegisterCvars();

	G_ProcessIPBans();

	G_InitMemory();

	// set some level globals
	memset( &level, 0, sizeof( level ) );
	level.time = levelTime;
	level.startTime = levelTime;

	/* LQ3A */
	LQ3A_InitGame();

	level.snd_fry = G_SoundIndex("sound/player/fry.wav");	// FIXME standing in lava / slime

	if ( g_gametype.integer != GT_SINGLE_PLAYER && g_log.string[0] ) {
		if ( g_logSync.integer ) {
			trap_FS_FOpenFile( g_log.string, &level.logFile, FS_APPEND_SYNC );
		} else {
			trap_FS_FOpenFile( g_log.string, &level.logFile, FS_APPEND );
		}
		if ( !level.logFile ) {
			G_Printf( "WARNING: Couldn't open logfile: %s\n", g_log.string );
		} else {
			char	serverinfo[MAX_INFO_STRING];

			trap_GetServerinfo( serverinfo, sizeof( serverinfo ) );

			G_LogPrintf("------------------------------------------------------------\n" );
			G_LogPrintf("InitGame: %s\n", serverinfo );
		}
	} else {
		G_Printf( "Not logging to disk.\n" );
	}

	G_InitWorldSession();

	// initialize all entities for this game
	memset( g_entities, 0, MAX_GENTITIES * sizeof(g_entities[0]) );
	level.gentities = g_entities;

	// initialize all clients for this game
	level.maxclients = g_maxclients.integer;
	memset( g_clients, 0, MAX_CLIENTS * sizeof(g_clients[0]) );
	level.clients = g_clients;

	// set client fields on player ents
	for ( i=0 ; i<level.maxclients ; i++ ) {
		g_entities[i].client = level.clients + i;
	}

	// always leave room for the max number of clients,
	// even if they aren't all used, so numbers inside that
	// range are NEVER anything but clients
	level.num_entities = MAX_CLIENTS;

	// let the server system know where the entites are
	trap_LocateGameData( level.gentities, level.num_entities, sizeof( gentity_t ), 
		&level.clients[0].ps, sizeof( level.clients[0] ) );

	// reserve some spots for dead player bodies
	InitBodyQue();

	ClearRegisteredItems();

	// parse the key/value pairs and spawn gentities
	G_SpawnEntitiesFromString();

	// general initialization
	G_FindTeams();

	// make sure we have flags for CTF, etc
	if( g_gametype.integer >= GT_TEAM ) {
		G_CheckTeamItems();
	}

	SaveRegisteredItems();

	G_Printf ("-----------------------------------\n");

	if( g_gametype.integer == GT_SINGLE_PLAYER || trap_Cvar_VariableIntegerValue( "com_buildScript" ) ) {
		G_ModelIndex( SP_PODIUM_MODEL );
		G_SoundIndex( "sound/player/gurp1.wav" );
		G_SoundIndex( "sound/player/gurp2.wav" );
	}

	if ( trap_Cvar_VariableIntegerValue( "bot_enable" ) ) {
		BotAISetup( restart );
		BotAILoadMap( restart );
		G_InitBots( restart );
	}

	G_RemapTeamShaders();

}



/*
=================
G_ShutdownGame
=================
*/
void G_ShutdownGame( int restart ) {
	G_Printf ("==== ShutdownGame ====\n");

	if ( level.logFile ) {
		G_LogPrintf("ShutdownGame:\n" );
		G_LogPrintf("------------------------------------------------------------\n" );
		trap_FS_FCloseFile( level.logFile );
	}

	// write all the client session data so we can get it back
	G_WriteSessionData();

	/* LQ3A */
	LQ3A_SaveMapListState();

	if ( trap_Cvar_VariableIntegerValue( "bot_enable" ) ) {
		BotAIShutdown( restart );
	}
}



//===================================================================

#ifndef GAME_HARD_LINKED
// this is only here so the functions in q_shared.c and bg_*.c can link

void QDECL Com_Error ( int level, const char *error, ... ) {
	va_list		argptr;
	char		text[1024];

	/* LQ3A */
	UNREFERENCED_PARAMETER(level);

	va_start (argptr, error);
	vsprintf (text, error, argptr);
	va_end (argptr);

	G_Error( "%s", text);
}

void QDECL Com_Printf( const char *msg, ... ) {
	va_list		argptr;
	char		text[1024];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	G_Printf ("%s", text);
}

#endif

/*
========================================================================

PLAYER COUNTING / SCORE SORTING

========================================================================
*/

/*
=============
AddTournamentPlayer

If there are less than two tournament players, put a
spectator in the game and restart
=============
*/
void AddTournamentPlayer( void ) {
	int			i;
	gclient_t	*client;
	gclient_t	*nextInLine;

	if ( level.numPlayingClients >= 2 ) {
		return;
	}

	// never change during intermission
	if ( level.intermissiontime ) {
		return;
	}

	nextInLine = NULL;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		client = &level.clients[i];
		if ( client->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( client->sess.sessionTeam != TEAM_SPECTATOR ) {
			continue;
		}
		// never select the dedicated follow or scoreboard clients
		if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD || 
			client->sess.spectatorClient < 0  ) {
			continue;
		}

		if ( !nextInLine || client->sess.spectatorTime < nextInLine->sess.spectatorTime ) {
			nextInLine = client;
		}
	}

	if ( !nextInLine ) {
		return;
	}

	level.warmupTime = -1;

	// set them to free-for-all team
	/* LQ3A */
	SetTeam(&g_entities[ nextInLine - level.clients ], "f", qtrue);
}

/*
=======================
RemoveTournamentLoser

Make the loser a spectator at the back of the line
=======================
*/
void RemoveTournamentLoser( void ) {
	int			clientNum;

	if ( level.numPlayingClients != 2 ) {
		return;
	}

	clientNum = level.sortedClients[1];

	if ( level.clients[ clientNum ].pers.connected != CON_CONNECTED ) {
		return;
	}

	/* LQ3A: Make them a spectator but don't broadcast the change. */
	SetTeam(&g_entities[ clientNum ], "s", qfalse);
}

/*
=======================
RemoveTournamentWinner
=======================
*/
void RemoveTournamentWinner( void ) {
	int			clientNum;

	if ( level.numPlayingClients != 2 ) {
		return;
	}

	clientNum = level.sortedClients[0];

	if ( level.clients[ clientNum ].pers.connected != CON_CONNECTED ) {
		return;
	}

	/* LQ3A: Make them a spectator but don't broadcast the change. */
	SetTeam(&g_entities[ clientNum ], "s", qfalse);
}

/*
=======================
AdjustTournamentScores
=======================
*/
void AdjustTournamentScores( void ) {
	int			clientNum;

	clientNum = level.sortedClients[0];
	if ( level.clients[ clientNum ].pers.connected == CON_CONNECTED ) {
		level.clients[ clientNum ].sess.wins++;
		ClientUserinfoChanged( clientNum );
	}

	clientNum = level.sortedClients[1];
	if ( level.clients[ clientNum ].pers.connected == CON_CONNECTED ) {
		level.clients[ clientNum ].sess.losses++;
		ClientUserinfoChanged( clientNum );
	}

}

/*
=============
SortRanks

=============
*/
int QDECL SortRanks( const void *a, const void *b ) {
	gclient_t	*ca, *cb;

	ca = &level.clients[*(int *)a];
	cb = &level.clients[*(int *)b];

	// sort special clients last
	if ( ca->sess.spectatorState == SPECTATOR_SCOREBOARD || ca->sess.spectatorClient < 0 ) {
		return 1;
	}
	if ( cb->sess.spectatorState == SPECTATOR_SCOREBOARD || cb->sess.spectatorClient < 0  ) {
		return -1;
	}

	// then connecting clients
	if ( ca->pers.connected == CON_CONNECTING ) {
		return 1;
	}
	if ( cb->pers.connected == CON_CONNECTING ) {
		return -1;
	}


	// then spectators
	if ( ca->sess.sessionTeam == TEAM_SPECTATOR && cb->sess.sessionTeam == TEAM_SPECTATOR ) {
		if ( ca->sess.spectatorTime < cb->sess.spectatorTime ) {
			return -1;
		}
		if ( ca->sess.spectatorTime > cb->sess.spectatorTime ) {
			return 1;
		}
		return 0;
	}
	if ( ca->sess.sessionTeam == TEAM_SPECTATOR ) {
		return 1;
	}
	if ( cb->sess.sessionTeam == TEAM_SPECTATOR ) {
		return -1;
	}

	// then sort by score
	if ( ca->ps.persistant[PERS_SCORE]
		> cb->ps.persistant[PERS_SCORE] ) {
		return -1;
	}
	if ( ca->ps.persistant[PERS_SCORE]
		< cb->ps.persistant[PERS_SCORE] ) {
		return 1;
	}
	return 0;
}

/*
============
CalculateRanks

Recalculates the score ranks of all players
This will be called on every client connect, begin, disconnect, death,
and team change.
============
*/
void CalculateRanks( void ) {
	int		i;
	int		rank;
	int		score;
	int		newScore;
	gclient_t	*cl;

	level.follow1 = -1;
	level.follow2 = -1;
	level.numConnectedClients = 0;
	level.numNonSpectatorClients = 0;
	level.numPlayingClients = 0;
	level.numVotingClients = 0;		// don't count bots
	for ( i = 0; i < TEAM_NUM_TEAMS; i++ ) {
		level.numteamVotingClients[i] = 0;
	}
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].pers.connected != CON_DISCONNECTED ) {
			level.sortedClients[level.numConnectedClients] = i;
			level.numConnectedClients++;

			if ( level.clients[i].sess.sessionTeam != TEAM_SPECTATOR ) {
				level.numNonSpectatorClients++;
			
				// decide if this should be auto-followed
				if ( level.clients[i].pers.connected == CON_CONNECTED ) {
					level.numPlayingClients++;
					if ( !(g_entities[i].r.svFlags & SVF_BOT) ) {
						level.numVotingClients++;
						if ( level.clients[i].sess.sessionTeam == TEAM_RED )
							level.numteamVotingClients[0]++;
						else if ( level.clients[i].sess.sessionTeam == TEAM_BLUE )
							level.numteamVotingClients[1]++;
					}
					if ( level.follow1 == -1 ) {
						level.follow1 = i;
					} else if ( level.follow2 == -1 ) {
						level.follow2 = i;
					}
				}
			}
		}
	}

	qsort( level.sortedClients, level.numConnectedClients, 
		sizeof(level.sortedClients[0]), SortRanks );

	// set the rank value for all clients that are connected and not spectators
	if ( g_gametype.integer >= GT_TEAM ) {
		// in team games, rank is just the order of the teams, 0=red, 1=blue, 2=tied
		for ( i = 0;  i < level.numConnectedClients; i++ ) {
			cl = &level.clients[ level.sortedClients[i] ];
			if ( level.teamScores[TEAM_RED] == level.teamScores[TEAM_BLUE] ) {
				cl->ps.persistant[PERS_RANK] = 2;
			} else if ( level.teamScores[TEAM_RED] > level.teamScores[TEAM_BLUE] ) {
				cl->ps.persistant[PERS_RANK] = 0;
			} else {
				cl->ps.persistant[PERS_RANK] = 1;
			}
		}
	} else {	
		rank = -1;
		score = 0;
		for ( i = 0;  i < level.numPlayingClients; i++ ) {
			cl = &level.clients[ level.sortedClients[i] ];
			newScore = cl->ps.persistant[PERS_SCORE];
			if ( i == 0 || newScore != score ) {
				rank = i;
				// assume we aren't tied until the next client is checked
				level.clients[ level.sortedClients[i] ].ps.persistant[PERS_RANK] = rank;
			} else {
				// we are tied with the previous client
				level.clients[ level.sortedClients[i-1] ].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
				level.clients[ level.sortedClients[i] ].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
			}
			score = newScore;
			if ( g_gametype.integer == GT_SINGLE_PLAYER && level.numPlayingClients == 1 ) {
				level.clients[ level.sortedClients[i] ].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
			}
		}
	}

	// set the CS_SCORES1/2 configstrings, which will be visible to everyone
	if ( g_gametype.integer >= GT_TEAM ) {
		trap_SetConfigstring( CS_SCORES1, va("%i", level.teamScores[TEAM_RED] ) );
		trap_SetConfigstring( CS_SCORES2, va("%i", level.teamScores[TEAM_BLUE] ) );
	} else {
		if ( level.numConnectedClients == 0 ) {
			trap_SetConfigstring( CS_SCORES1, va("%i", SCORE_NOT_PRESENT) );
			trap_SetConfigstring( CS_SCORES2, va("%i", SCORE_NOT_PRESENT) );
		} else if ( level.numConnectedClients == 1 ) {
			trap_SetConfigstring( CS_SCORES1, va("%i", level.clients[ level.sortedClients[0] ].ps.persistant[PERS_SCORE] ) );
			trap_SetConfigstring( CS_SCORES2, va("%i", SCORE_NOT_PRESENT) );
		} else {
			trap_SetConfigstring( CS_SCORES1, va("%i", level.clients[ level.sortedClients[0] ].ps.persistant[PERS_SCORE] ) );
			trap_SetConfigstring( CS_SCORES2, va("%i", level.clients[ level.sortedClients[1] ].ps.persistant[PERS_SCORE] ) );
		}
	}

	// see if it is time to end the level
	CheckExitRules();

	// if we are at the intermission, send the new info to everyone
	if ( level.intermissiontime ) {
		SendScoreboardMessageToAllClients();
	}
}


/*
========================================================================

MAP CHANGING

========================================================================
*/

/*
========================
SendScoreboardMessageToAllClients

Do this at BeginIntermission time and whenever ranks are recalculated
due to enters/exits/forced team changes
========================
*/
void SendScoreboardMessageToAllClients( void ) {
	int		i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[ i ].pers.connected == CON_CONNECTED ) {
			DeathmatchScoreboardMessage( g_entities + i );
		}
	}
}

/*
========================
MoveClientToIntermission

When the intermission starts, this will be called for all players.
If a new client connects, this will be called after the spawn function.
========================
*/
void MoveClientToIntermission( gentity_t *ent ) {
	// take out of follow mode if needed
	if ( ent->client->sess.spectatorState == SPECTATOR_FOLLOW ) {
		StopFollowing( ent );
	}


	// move to the spot
	VectorCopy( level.intermission_origin, ent->s.origin );
	VectorCopy( level.intermission_origin, ent->client->ps.origin );
	VectorCopy (level.intermission_angle, ent->client->ps.viewangles);
	ent->client->ps.pm_type = PM_INTERMISSION;

	// clean up powerup info
	memset( ent->client->ps.powerups, 0, sizeof(ent->client->ps.powerups) );

	ent->client->ps.eFlags = 0;
	ent->s.eFlags = 0;
	ent->s.eType = ET_GENERAL;
	ent->s.modelindex = 0;
	ent->s.loopSound = 0;
	ent->s.event = 0;
	ent->r.contents = 0;
}

/*
==================
FindIntermissionPoint

This is also used for spectator spawns
==================
*/
void FindIntermissionPoint( void ) {
	gentity_t	*ent, *target;
	vec3_t		dir;

	// find the intermission spot
	ent = G_Find (NULL, FOFS(classname), "info_player_intermission");
	if ( !ent ) {	// the map creator forgot to put in an intermission point...
		SelectSpawnPoint ( vec3_origin, level.intermission_origin, level.intermission_angle );
	} else {
		VectorCopy (ent->s.origin, level.intermission_origin);
		VectorCopy (ent->s.angles, level.intermission_angle);
		// if it has a target, look towards it
		if ( ent->target ) {
			target = G_PickTarget( ent->target );
			if ( target ) {
				VectorSubtract( target->s.origin, level.intermission_origin, dir );
				vectoangles( dir, level.intermission_angle );
			}
		}
	}

}

/*
==================
BeginIntermission
==================
*/
void BeginIntermission( void ) {
	int			i;
	gentity_t	*client;

	if ( level.intermissiontime ) {
		return;		// already active
	}

	// if in tournament mode, change the wins / losses
	if ( g_gametype.integer == GT_TOURNAMENT ) {
		AdjustTournamentScores();
	}

	level.intermissiontime = level.time;
	FindIntermissionPoint();

#ifdef MISSIONPACK
	if (g_singlePlayer.integer) {
		trap_Cvar_Set("ui_singlePlayerActive", "0");
		UpdateTournamentInfo();
	}
#else
	// if single player game
	if ( g_gametype.integer == GT_SINGLE_PLAYER ) {
		UpdateTournamentInfo();
		SpawnModelsOnVictoryPads();
	}
#endif

	// move all clients to the intermission point
	for (i=0 ; i< level.maxclients ; i++) {
		client = g_entities + i;
		if (!client->inuse)
			continue;
		// respawn if dead
		if (client->health <= 0) {
			respawn(client);
		}
		MoveClientToIntermission( client );
	}

	/* LQ3A: Teleportation effects are suppressed in respawn() when the intermission is active.
		This prevents multiple effects being triggered in the same place at the same time
		(which doesn't look or sound right) so we send a single effect now. */
	client = g_entities + i;

	if (client->inuse)
	{
		client				= G_TempEntity(client->client->ps.origin, EV_PLAYER_TELEPORT_IN);
		client->s.clientNum	= client->s.clientNum;
	}

	// send the current scoring to all clients
	SendScoreboardMessageToAllClients();

	/* LQ3A: Play the intermission sound. */
	if (*g_intermissionSound.string && level.numConnectedClients)
	{
		trap_SetConfigstring(CS_MUSIC, g_intermissionSound.string);
	}
}


/*
=============
ExitLevel

When the intermission has been exited, the server is either killed
or moved to a new level based on the "nextmap" cvar 

=============
*/
void ExitLevel (void) {
	int		i;
	gclient_t *cl;

	//bot interbreeding
	BotInterbreedEndMatch();

	/* LQ3A: Reset CS_INTERMISSION. */
	trap_SetConfigstring(CS_INTERMISSION, "0");

	// if we are running a tournament map, kick the loser to spectator status,
	// which will automatically grab the next spectator and restart
	if ( g_gametype.integer == GT_TOURNAMENT  ) {

		/* LQ3A: Remove the loser, fall through to restart or change the map. */
		RemoveTournamentLoser();
	}

	/* LQ3A: Perform a fast restart if we are continuing the game on the same map. */
	if (level.MapList.bRestartMap)
	{
		LQ3A_SaveMapListState();
		trap_SendConsoleCommand(EXEC_APPEND, "vstr nextmap\n");
		LQ3A_RestartMap(0.0f);

		level.MapList.bRestartMap = qfalse;
		return;
	}

	/* LQ3A: Suppress G_RunFrame() until the restart command has been issued. */
	level.restarted = level.MapList.bRestartMap;

	trap_SendConsoleCommand( EXEC_APPEND, "vstr nextmap\n" );
	level.changemap = NULL;
	level.intermissiontime = 0;

	// reset all the scores so we don't enter the intermission again
	level.teamScores[TEAM_RED] = 0;
	level.teamScores[TEAM_BLUE] = 0;
	for ( i=0 ; i< g_maxclients.integer ; i++ ) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		cl->ps.persistant[PERS_SCORE] = 0;
	}

	// we need to do this here before changing to CON_CONNECTING
	G_WriteSessionData();

	// change all client states to connecting, so the early players into the
	// next level will know the others aren't done reconnecting
	for (i=0 ; i< g_maxclients.integer ; i++) {
		if ( level.clients[i].pers.connected == CON_CONNECTED ) {
			level.clients[i].pers.connected = CON_CONNECTING;
		}
	}

}

/*
=================
G_LogPrintf

Print to the logfile with a time stamp if it is open
=================
*/
void QDECL G_LogPrintf( const char *fmt, ... ) {
	va_list		argptr;
	char		string[1024];
	int			min, tens, sec;

	sec = level.time / 1000;

	min = sec / 60;
	sec -= min * 60;
	tens = sec / 10;
	sec -= tens * 10;

	Com_sprintf( string, sizeof(string), "%3i:%i%i ", min, tens, sec );

	va_start( argptr, fmt );
	vsprintf( string +7 , fmt,argptr );
	va_end( argptr );

	if ( g_dedicated.integer ) {
		G_Printf( "%s", string + 7 );
	}

	if ( !level.logFile ) {
		return;
	}

	trap_FS_Write( string, strlen( string ), level.logFile );
}

/*
================
LogExit

Append information about this game to the log file
================
*/
void LogExit( const char *string ) {
	int				i, numSorted;
	gclient_t		*cl;
#ifdef MISSIONPACK // bk001205
	qboolean won = qtrue;
#endif
	G_LogPrintf( "Exit: %s\n", string );

	level.intermissionQueued = level.time;

	// this will keep the clients from playing any voice sounds
	// that will get cut off when the queued intermission starts

	/* LQ3A: Use CS_INTERMISSION to communicate the intermission time,
		this allows the client module to know when to show the scoreboard
		and when to show the high score table. */
	trap_SetConfigstring(CS_INTERMISSION, (g_intermissionTime.value > 0.0f) ? va("%i", (int)((g_intermissionTime.value * 1000.0f) + 0.5f)) : "10000");

	// don't send more than 32 scores (FIXME?)
	numSorted = level.numConnectedClients;
	if ( numSorted > 32 ) {
		numSorted = 32;
	}

	if ( g_gametype.integer >= GT_TEAM ) {
		G_LogPrintf( "red:%i  blue:%i\n",
			level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE] );
	}

	for (i=0 ; i < numSorted ; i++) {
		int		ping;

		cl = &level.clients[level.sortedClients[i]];

		if ( cl->sess.sessionTeam == TEAM_SPECTATOR ) {
			continue;
		}
		if ( cl->pers.connected == CON_CONNECTING ) {
			continue;
		}

		ping = cl->ps.ping < 999 ? cl->ps.ping : 999;

		G_LogPrintf( "score: %i  ping: %i  client: %i %s\n", cl->ps.persistant[PERS_SCORE], ping, level.sortedClients[i],	cl->pers.netname );
#ifdef MISSIONPACK
		if (g_singlePlayer.integer && g_gametype.integer == GT_TOURNAMENT) {
			if (g_entities[cl - level.clients].r.svFlags & SVF_BOT && cl->ps.persistant[PERS_RANK] == 0) {
				won = qfalse;
			}
		}
#endif

	}

#ifdef MISSIONPACK
	if (g_singlePlayer.integer) {
		if (g_gametype.integer >= GT_CTF) {
			won = level.teamScores[TEAM_RED] > level.teamScores[TEAM_BLUE];
		}
		trap_SendConsoleCommand( EXEC_APPEND, (won) ? "spWin\n" : "spLose\n" );
	}
#endif


}


/*
=================
CheckIntermissionExit

The level will stay at the intermission for a minimum of 5 seconds
If all players wish to continue, the level will then exit.
If one or more players have not acknowledged the continue, the game will
wait 10 seconds before going on.
=================
*/
void CheckIntermissionExit( void ) {
	int			ready, notReady;
	int			i;
	gclient_t	*cl;
	int			readyMask;

	if ( g_gametype.integer == GT_SINGLE_PLAYER ) {
		return;
	}

	// see which players are ready
	ready = 0;
	notReady = 0;
	readyMask = 0;
	for (i=0 ; i< g_maxclients.integer ; i++) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( g_entities[cl->ps.clientNum].r.svFlags & SVF_BOT ) {
			continue;
		}

		if ( cl->readyToExit ) {
			ready++;
			if ( i < 16 ) {
				readyMask |= 1 << i;
			}
		} else {
			notReady++;
		}
	}

	// copy the readyMask to each player's stats so
	// it can be displayed on the scoreboard
	for (i=0 ; i< g_maxclients.integer ; i++) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		cl->ps.stats[STAT_CLIENTS_READY] = readyMask;
	}

	/* LQ3A: Never exit before the intermission time has past. */
	if (level.time < level.intermissiontime + (g_intermissionTime.value * 1000))
	{
		return;
	}

	/* LQ3A: don't allow the intermission to last longer than half again. */
	if (level.time < level.intermissiontime + ((g_intermissionTime.value + (g_intermissionTime.value / 2)) * 1000))
	{
		// if nobody wants to go, clear timer
		if ( !ready ) {
			level.readyToExit = qfalse;
			return;
		}

		// if everyone wants to go, go now
		if ( !notReady ) {
			ExitLevel();
			return;
		}

		// the first person to ready starts the ten second timeout
		if ( !level.readyToExit ) {
			level.readyToExit = qtrue;
			level.exitTime = level.time;
		}

		// if we have waited ten seconds since at least one player
		// wanted to exit, go ahead
		if ( level.time < level.exitTime + 10000 ) {
			return;
		}
	}

	ExitLevel();
}

/*
=============
ScoreIsTied
=============
*/
qboolean ScoreIsTied( void ) {
	int		a, b;

	if ( level.numPlayingClients < 2 ) {
		return qfalse;
	}
	
	if ( g_gametype.integer >= GT_TEAM ) {
		return level.teamScores[TEAM_RED] == level.teamScores[TEAM_BLUE];
	}

	a = level.clients[level.sortedClients[0]].ps.persistant[PERS_SCORE];
	b = level.clients[level.sortedClients[1]].ps.persistant[PERS_SCORE];

	return a == b;
}

/*
=================
CheckExitRules

There will be a delay between the time the exit is qualified for
and the time everyone is moved to the intermission spot, so you
can see the last frag.
=================
*/
void CheckExitRules( void ) {
 	int			i;
	gclient_t	*cl;
	// if at the intermission, wait for all non-bots to
	// signal ready, then go to next level
	if ( level.intermissiontime ) {
		CheckIntermissionExit ();
		return;
	}

	if ( level.intermissionQueued ) {
#ifdef MISSIONPACK
		int time = (g_singlePlayer.integer) ? SP_INTERMISSION_DELAY_TIME : INTERMISSION_DELAY_TIME;
		if ( level.time - level.intermissionQueued >= time ) {
			level.intermissionQueued = 0;
			BeginIntermission();
		}
#else
		if ( level.time - level.intermissionQueued >= INTERMISSION_DELAY_TIME ) {
			level.intermissionQueued = 0;

			/* LQ3A */
			LQ3A_SaveHighScores();

			BeginIntermission();

			/* LQ3A */
			LQ3A_SelectNextMap();
		}
#endif
		return;
	}

	// check for sudden death
	if ( ScoreIsTied() ) {
		// always wait for sudden death
		return;
	}

	if ( g_timelimit.integer && !level.warmupTime ) {
		if ( level.time - level.startTime >= g_timelimit.integer*60000 ) {
			trap_SendServerCommand( -1, "print \"Timelimit hit.\n\"");
			LogExit( "Timelimit hit." );
			return;
		}
	}

	if ( level.numPlayingClients < 2 ) {
		return;
	}

	if ( g_gametype.integer < GT_CTF && g_fraglimit.integer ) {
		if ( level.teamScores[TEAM_RED] >= g_fraglimit.integer ) {
			trap_SendServerCommand( -1, "print \"Red hit the fraglimit.\n\"" );
			LogExit( "Fraglimit hit." );
			return;
		}

		if ( level.teamScores[TEAM_BLUE] >= g_fraglimit.integer ) {
			trap_SendServerCommand( -1, "print \"Blue hit the fraglimit.\n\"" );
			LogExit( "Fraglimit hit." );
			return;
		}

		for ( i=0 ; i< g_maxclients.integer ; i++ ) {
			cl = level.clients + i;
			if ( cl->pers.connected != CON_CONNECTED ) {
				continue;
			}
			if ( cl->sess.sessionTeam != TEAM_FREE ) {
				continue;
			}

			if ( cl->ps.persistant[PERS_SCORE] >= g_fraglimit.integer ) {
				LogExit( "Fraglimit hit." );
				trap_SendServerCommand( -1, va("print \"%s" S_COLOR_WHITE " hit the fraglimit.\n\"",
					cl->pers.netname ) );
				return;
			}
		}
	}

	if ( g_gametype.integer >= GT_CTF && g_capturelimit.integer ) {

		if ( level.teamScores[TEAM_RED] >= g_capturelimit.integer ) {
			trap_SendServerCommand( -1, "print \"Red hit the capturelimit.\n\"" );
			LogExit( "Capturelimit hit." );
			return;
		}

		if ( level.teamScores[TEAM_BLUE] >= g_capturelimit.integer ) {
			trap_SendServerCommand( -1, "print \"Blue hit the capturelimit.\n\"" );
			LogExit( "Capturelimit hit." );
			return;
		}
	}
}



/*
========================================================================

FUNCTIONS CALLED EVERY FRAME

========================================================================
*/


/*
=============
CheckTournament

Once a frame, check for changes in tournament player state
=============
*/
void CheckTournament( void ) {
	// check because we run 3 game frames before calling Connect and/or ClientBegin
	// for clients on a map_restart
	if ( level.numPlayingClients == 0 ) {
		return;
	}

	if ( g_gametype.integer == GT_TOURNAMENT ) {

		// pull in a spectator if needed
		if ( level.numPlayingClients < 2 ) {
			AddTournamentPlayer();
		}

		// if we don't have two players, go back to "waiting for players"
		if ( level.numPlayingClients != 2 ) {
			if ( level.warmupTime != -1 ) {
				level.warmupTime = -1;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
				G_LogPrintf( "Warmup:\n" );
			}
			return;
		}

		if ( level.warmupTime == 0 ) {
			return;
		}

		// if the warmup is changed at the console, restart it
		if ( g_warmup.modificationCount != level.warmupModificationCount ) {
			level.warmupModificationCount = g_warmup.modificationCount;
			level.warmupTime = -1;
		}

		// if all players have arrived, start the countdown
		if ( level.warmupTime < 0 ) {
			if ( level.numPlayingClients == 2 ) {
				// fudge by -1 to account for extra delays
				level.warmupTime = level.time + ( g_warmup.integer - 1 ) * 1000;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
			}
			return;
		}

		// if the warmup time has counted down, restart
		if ( level.time > level.warmupTime ) {

			/* LQ3A: Reset the map. */
			LQ3A_RestartMap(0.0f);

			return;
		}
	} else if ( g_gametype.integer != GT_SINGLE_PLAYER && level.warmupTime != 0 ) {
		int		counts[TEAM_NUM_TEAMS];
		qboolean	notEnough = qfalse;

		if ( g_gametype.integer > GT_TEAM ) {
			counts[TEAM_BLUE] = TeamCount( -1, TEAM_BLUE );
			counts[TEAM_RED] = TeamCount( -1, TEAM_RED );

			if (counts[TEAM_RED] < 1 || counts[TEAM_BLUE] < 1) {
				notEnough = qtrue;
			}
		} else if ( level.numPlayingClients < 2 ) {
			notEnough = qtrue;
		}

		if ( notEnough ) {
			if ( level.warmupTime != -1 ) {
				level.warmupTime = -1;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
				G_LogPrintf( "Warmup:\n" );
			}
			return; // still waiting for team members
		}

		if ( level.warmupTime == 0 ) {
			return;
		}

		// if the warmup is changed at the console, restart it
		if ( g_warmup.modificationCount != level.warmupModificationCount ) {
			level.warmupModificationCount = g_warmup.modificationCount;
			level.warmupTime = -1;
		}

		// if all players have arrived, start the countdown
		if ( level.warmupTime < 0 ) {
			// fudge by -1 to account for extra delays
			level.warmupTime = level.time + ( g_warmup.integer - 1 ) * 1000;
			trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
			return;
		}

		// if the warmup time has counted down, restart
		if ( level.time > level.warmupTime ) {

			/* LQ3A: Reset the map. */
			LQ3A_RestartMap(0.0f);

			return;
		}
	}
}


/*
==================
CheckVote
==================
*/
void CheckVote( void ) {
	if ( level.voteExecuteTime && level.voteExecuteTime < level.time ) {
		level.voteExecuteTime = 0;
		trap_SendConsoleCommand( EXEC_APPEND, va("%s\n", level.voteString ) );
	}
	if ( !level.voteTime ) {
		return;
	}
	if ( level.time - level.voteTime >= VOTE_TIME ) {
		trap_SendServerCommand( -1, "print \"Vote failed.\n\"" );
	} else {
		// ATVI Q3 1.32 Patch #9, WNF
		if ( level.voteYes > level.numVotingClients/2 ) {
			// execute the command, then remove the vote
			trap_SendServerCommand( -1, "print \"Vote passed.\n\"" );
			level.voteExecuteTime = level.time + 3000;
		} else if ( level.voteNo >= level.numVotingClients/2 ) {
			// same behaviour as a timeout
			trap_SendServerCommand( -1, "print \"Vote failed.\n\"" );
		} else {
			// still waiting for a majority
			return;
		}
	}
	level.voteTime = 0;
	trap_SetConfigstring( CS_VOTE_TIME, "" );

}

/*
==================
PrintTeam
==================
*/
void PrintTeam(int team, char *message) {
	int i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if (level.clients[i].sess.sessionTeam != team)
			continue;
		trap_SendServerCommand( i, message );
	}
}

/*
==================
SetLeader
==================
*/
void SetLeader(int team, int client) {
	int i;

	if ( level.clients[client].pers.connected == CON_DISCONNECTED ) {
		PrintTeam(team, va("print \"%s is not connected\n\"", level.clients[client].pers.netname) );
		return;
	}
	if (level.clients[client].sess.sessionTeam != team) {
		PrintTeam(team, va("print \"%s is not on the team anymore\n\"", level.clients[client].pers.netname) );
		return;
	}
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if (level.clients[i].sess.sessionTeam != team)
			continue;
		if (level.clients[i].sess.teamLeader) {
			level.clients[i].sess.teamLeader = qfalse;
			ClientUserinfoChanged(i);
		}
	}
	level.clients[client].sess.teamLeader = qtrue;
	ClientUserinfoChanged( client );
	PrintTeam(team, va("print \"%s is the new team leader\n\"", level.clients[client].pers.netname) );
}

/*
==================
CheckTeamLeader
==================
*/
void CheckTeamLeader( int team ) {
	int i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if (level.clients[i].sess.sessionTeam != team)
			continue;
		if (level.clients[i].sess.teamLeader)
			break;
	}
	if (i >= level.maxclients) {
		for ( i = 0 ; i < level.maxclients ; i++ ) {
			if (level.clients[i].sess.sessionTeam != team)
				continue;
			if (!(g_entities[i].r.svFlags & SVF_BOT)) {
				level.clients[i].sess.teamLeader = qtrue;
				break;
			}
		}
		for ( i = 0 ; i < level.maxclients ; i++ ) {
			if (level.clients[i].sess.sessionTeam != team)
				continue;
			level.clients[i].sess.teamLeader = qtrue;
			break;
		}
	}
}

/*
==================
CheckTeamVote
==================
*/
void CheckTeamVote( int team ) {
	int cs_offset;

	if ( team == TEAM_RED )
		cs_offset = 0;
	else if ( team == TEAM_BLUE )
		cs_offset = 1;
	else
		return;

	if ( !level.teamVoteTime[cs_offset] ) {
		return;
	}
	if ( level.time - level.teamVoteTime[cs_offset] >= VOTE_TIME ) {
		trap_SendServerCommand( -1, "print \"Team vote failed.\n\"" );
	} else {
		if ( level.teamVoteYes[cs_offset] > level.numteamVotingClients[cs_offset]/2 ) {
			// execute the command, then remove the vote
			trap_SendServerCommand( -1, "print \"Team vote passed.\n\"" );
			//
			if ( !Q_strncmp( "leader", level.teamVoteString[cs_offset], 6) ) {
				//set the team leader
				SetLeader(team, atoi(level.teamVoteString[cs_offset] + 7));
			}
			else {
				trap_SendConsoleCommand( EXEC_APPEND, va("%s\n", level.teamVoteString[cs_offset] ) );
			}
		} else if ( level.teamVoteNo[cs_offset] >= level.numteamVotingClients[cs_offset]/2 ) {
			// same behaviour as a timeout
			trap_SendServerCommand( -1, "print \"Team vote failed.\n\"" );
		} else {
			// still waiting for a majority
			return;
		}
	}
	level.teamVoteTime[cs_offset] = 0;
	trap_SetConfigstring( CS_TEAMVOTE_TIME + cs_offset, "" );

}


/*
==================
CheckCvars
==================
*/
void CheckCvars( void ) {
	static int lastMod = -1;

	if ( g_password.modificationCount != lastMod ) {
		lastMod = g_password.modificationCount;
		if ( *g_password.string && Q_stricmp( g_password.string, "none" ) ) {
			trap_Cvar_Set( "g_needpass", "1" );
		} else {
			trap_Cvar_Set( "g_needpass", "0" );
		}
	}
}

/*
=============
G_RunThink

Runs thinking code for this frame if necessary
=============
*/
void G_RunThink (gentity_t *ent) {
	float	thinktime;

	thinktime = ent->nextthink;
	if (thinktime <= 0) {
		return;
	}
	if (thinktime > level.time) {
		return;
	}
	
	ent->nextthink = 0;
	if (!ent->think) {
		G_Error ( "NULL ent->think");
	}
	ent->think (ent);
}

/*
================
G_RunFrame

Advances the non-player objects in the world
================
*/
void G_RunFrame( int levelTime ) {
	int			i;
	gentity_t	*ent;
	int			msec;
int start, end;

	// if we are waiting for the level to restart, do nothing
	if ( level.restarted ) {
		return;
	}

	level.framenum++;
	level.previousTime = level.time;
	level.time = levelTime;
	msec = level.time - level.previousTime;

	// get any cvar changes
	G_UpdateCvars();

	//
	// go through all allocated objects
	//
	start = trap_Milliseconds();
	ent = &g_entities[0];
	for (i=0 ; i<level.num_entities ; i++, ent++) {
		if ( !ent->inuse ) {
			continue;
		}

		// clear events that are too old
		if ( level.time - ent->eventTime > EVENT_VALID_MSEC ) {
			if ( ent->s.event ) {
				ent->s.event = 0;	// &= EV_EVENT_BITS;
				if ( ent->client ) {
					ent->client->ps.externalEvent = 0;
					// predicted events should never be set to zero
					//ent->client->ps.events[0] = 0;
					//ent->client->ps.events[1] = 0;
				}
			}
			if ( ent->freeAfterEvent ) {
				// tempEntities or dropped items completely go away after their event
				G_FreeEntity( ent );
				continue;
			} else if ( ent->unlinkAfterEvent ) {
				// items that will respawn will hide themselves after their pickup event
				ent->unlinkAfterEvent = qfalse;
				trap_UnlinkEntity( ent );
			}
		}

		// temporary entities don't think
		if ( ent->freeAfterEvent ) {
			continue;
		}

		if ( !ent->r.linked && ent->neverFree ) {
			continue;
		}

		if ( ent->s.eType == ET_MISSILE ) {
			G_RunMissile( ent );
			continue;
		}

		if ( ent->s.eType == ET_ITEM || ent->physicsObject ) {
			G_RunItem( ent );
			continue;
		}

		if ( ent->s.eType == ET_MOVER ) {
			G_RunMover( ent );
			continue;
		}

		if ( i < MAX_CLIENTS ) {
			G_RunClient( ent );
			continue;
		}

		G_RunThink( ent );
	}
end = trap_Milliseconds();

start = trap_Milliseconds();
	// perform final fixups on the players
	ent = &g_entities[0];
	for (i=0 ; i < level.maxclients ; i++, ent++ ) {
		if ( ent->inuse ) {
			ClientEndFrame( ent );
		}
	}
end = trap_Milliseconds();

	// see if it is time to do a tournament restart
	CheckTournament();

	// see if it is time to end the level
	CheckExitRules();

	// update to team status?
	CheckTeamStatus();

	// cancel vote if timed out
	CheckVote();

	// check team votes
	CheckTeamVote( TEAM_RED );
	CheckTeamVote( TEAM_BLUE );

	// for tracking changes
	CheckCvars();

	if (g_listEntity.integer) {
		for (i = 0; i < MAX_GENTITIES; i++) {
			G_Printf("%4i: %s\n", i, g_entities[i].classname);
		}
		trap_Cvar_Set("g_listEntity", "0");
	}
}
