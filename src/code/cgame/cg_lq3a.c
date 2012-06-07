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

#include "cg_local.h"

/* Globals. */
qboolean g_bInitilised	= qfalse;	/** True once we have loaded all resources and we are ready to start the game. */

/** Parses the CS_LQ3A_CONFIG configuration string. */
void LQ3A_ParseLoadedConfigString(pchar pString, uint uSize)
{
	char	cString[MAX_STRING_CHARS], cArg[MAX_TOKEN_CHARS];
	int		iRtn;
	uint	uLen, uArg;

	if (!pString || (*pString == 0))
	{
default_config:
		/* Process the default config when the string is empty. */
		Com_sprintf(cString, sizeof(cString),
			"0 0 0 850 400 400 100 1000 800 800 50 150 100 200 1000 800 30 200 1.3 %i 700", JUMP_VELOCITY);
		pString = cString;
	}

	for (uArg=0;;)
	{
		iRtn = LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);

		if (uLen)
		{
			switch (uArg++)
			{
			case LQ3A_CS_CONFIG_QVM:
				cgs.bQVM = (atoi(cArg) != 0) ? qtrue : qfalse;
				break;

			case LQ3A_CS_CONFIG_MISSIONPACK:
				cgs.bMissionPack = (atoi(cArg) != 0) ? qtrue : qfalse;
				break;

			case LQ3A_CS_CONFIG_HIGHSCORES:
				cgs.HighScores.bEnabled = (atoi(cArg) != 0) ? qtrue : qfalse;
				break;

			case LQ3A_CS_CONFIG_HOOK_PULLSPEED:
				g_pm_hookPullSpeed = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_HOOK:
				g_pm_refireTime[WP_GRAPPLING_HOOK] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_GAUNTLET:
				g_pm_refireTime[WP_GAUNTLET] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_MACHINEGUN:
				g_pm_refireTime[WP_MACHINEGUN] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_SHOTGUN:
				g_pm_refireTime[WP_SHOTGUN] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_GRENADE_LAUNCHER:
				g_pm_refireTime[WP_GRENADE_LAUNCHER] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_ROCKET_LAUNCHER:
				g_pm_refireTime[WP_ROCKET_LAUNCHER] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_LIGHTNINGGUN:
				g_pm_refireTime[WP_LIGHTNING] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_RAILGUN:
				g_pm_refireTime[WP_RAILGUN] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_PLASMAGUN:
				g_pm_refireTime[WP_PLASMAGUN] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_BFG:
				g_pm_refireTime[WP_BFG] = atoi(cArg);
				break;
#ifdef MISSIONPACK
			case LQ3A_CS_CONFIG_REFIRE_NAILGUN:
				g_pm_refireTime[WP_NAILGUN] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_PROX_LAUNCHER:
				g_pm_refireTime[WP_PROX_LAUNCHER] = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_REFIRE_CHAINGUN:
				g_pm_refireTime[WP_CHAINGUN] = atoi(cArg);
				break;
#endif /* MISSIONPACK */
			case LQ3A_CS_CONFIG_SWITCH_SPEED:
				g_pm_switchSpeed = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_HASTE_FACTOR:
				g_pm_hasteFactor = (float)atof(cArg);
				break;

			case LQ3A_CS_CONFIG_JUMP_VELOCITY:
				g_pm_jumpVelocity = atoi(cArg);
				break;

			case LQ3A_CS_CONFIG_SHELL_SPREAD:
				cgs.iShellSpread = atoi(cArg);
				break;
			}

			uSize -= uLen;
		}

		if (iRtn == LQ3A_PARSE_R_COMPLETE)
		{
			/* Done. */
			break;
		}
	}

	if (uArg != LQ3A_CS_CONFIG_NUM_ENTRIES)
	{
		CG_Error("Unexpected number of arguments in CS_LQ3A_CONFIG.\n");
		goto default_config;
	}
}

/** Parses the CS_LQ3A_LIMITS configuration string. */
void LQ3A_ParseLimitsConfigString(pchar pString, uint uSize)
{
	char	cArg[MAX_TOKEN_CHARS];
	int		iRtn;
	uint	uLen, uArg;

	if (!pString || (*pString == 0))
	{
		/* Process the default config when the string is empty. */
		pString = "200 200 200 200 200 200 200 200 200 200 200";
	}

	/* Some weapons are fixed. */
	cgs.iAmmoLimits[WP_GAUNTLET]		= -1;
	cgs.iAmmoLimits[WP_GRAPPLING_HOOK]	= -1;

	for (uArg=WP_MACHINEGUN;;)
	{
		iRtn = LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);

		if (uLen)
		{
			cgs.iAmmoLimits[uArg++] = atoi(cArg);
			uSize -= uLen;
		}

		if ((iRtn == LQ3A_PARSE_R_COMPLETE) || (uArg == WP_NUM_WEAPONS))
		{
			/* Done. */
			break;
		}
	}
}

/** Parses the CS_ITEMS configuration string. */
void LQ3A_ParseItemsConfigString(pchar pString)
{
	int i;

	for (i=1; i<bg_numItems; i++)
	{
		if ((pString[i] == '1') || cg_buildScript.integer)
		{
			CG_RegisterItemVisuals(i);
			CG_RegisterItemSounds(i);
		}
	}
}

/** Applies screen blending when the camera is in solids. */
void LQ3A_BlendScreen(void)
{
	int		iContents;
	vec4_t	cColor;

	/** @fixme: CG_PointContents() returns 0 when you exceed the bounds of the map,
			the time when it's needed the most. */
#if 0
	/* Check the contents of the camera location. */
	iContents = CG_PointContents(cg.refdef.vieworg, 0);
#else
	/* Always apply screen blending, the low alpha value makes this an acceptable work around. */
	iContents |= CONTENTS_SOLID;
#endif /* 0 */

	if (iContents & CONTENTS_SOLID)
	{
		cColor[0] = 0.9f;
		cColor[1] = 0.9f;
		cColor[2] = 0.9f;
		cColor[3] = 0.028f;

		CG_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cColor);
	}
}

/** Calculates the fade in alpha color. */
qboolean LQ3A_FadeInColor(vec4_t *vIn, int iStartTime, int iEndTime)
{
	int t;

	(*vIn)[0] = (*vIn)[1] = (*vIn)[2] = 1.0f;

	t = cg.time - iStartTime;

	if (t < 0)
	{
		/* Hasn't started yet. */
		(*vIn)[3] = 0.0f;
		return qfalse;
	}

	if (iEndTime && (t >= (iEndTime-iStartTime)))
	{
		/* End time as now past. */
		(*vIn)[3] = 0.0f;
		return qfalse;
	}

	if (t < FADE_TIME)
	{
		/* Fade in. */
		(*vIn)[3] = t * (1.0f / FADE_TIME);
	}
	else
	{
		/* Fully opaque. */
		(*vIn)[3] = 1.0f;
	}

	return qtrue;
}

/** Returns the number of lines in the given string. */
uint LQ3A_GetLineCount(pchar pBuffer)
{
	uint i = 0;

	if (!pBuffer)
	{
		return 0;
	}

	while (*pBuffer)
	{
		if (*pBuffer == '\n')
		{
			i++;
		}

		pBuffer++;
	}

	return ++i;
}

/** Calculates the new X coordinate from given the current X coordinate and alignment. */
int LQ3A_GetDrawAlignment(int x, pcchar pString, int iCharWidth, uint uFlags)
{
	switch (uFlags & UI_FORMATMASK)
	{
	case UI_CENTER:
		return x - (CG_DrawStrlen(pString) * (iCharWidth / 2));

	case UI_RIGHT:
		return x - (CG_DrawStrlen(pString) * iCharWidth);

	case UI_LEFT:
	default:
		return x;
	}
}

/** Fixes the length of the draw string. */
void LQ3A_FixDrawLength(pcchar pString, size_t uFixedSize, pchar pBuffer, size_t uSize)
{
	pcchar	pStr;
	size_t	uLen, uDrawLen;

	pStr		= pString;
	uLen		= 0;
	uDrawLen	= 0;

	while (*pStr)
	{
		if (Q_IsColorString(pStr))
		{
			if ((uLen + 2) >= uSize)
			{
				/* Done. */
				break;
			}

			pStr += 2;
			uLen += 2;
			continue;
		}

		if ((uLen + 1) == uSize)
		{
			/* Done. */
			break;
		}

		if (uDrawLen == uFixedSize)
		{
			/* Done. */
			break;
		}

		uLen++;
		uDrawLen++;
		pStr++;
	}

	strncpy(pBuffer, pString, uLen);

	for (;uLen<uSize && uDrawLen<uFixedSize;uLen++,uDrawLen++)
	{
		pBuffer[uLen] = ' ';
	}

	/* Terminate the string. */
	if (uLen < uSize)
	{
		pBuffer[uLen] = 0;
	}
	else
	{
		pBuffer[uLen-1] = 0;
	}
}

/** Registers key down event for the given layout. This information prevents LQ3A_RemoveLayout() from
		removing forced layouts (ie Scoreboard when dead) when the key bound to the command is latched. */
ID_INLINE void LQ3A_LayoutKeyDown(int iLayout)
{
	cgs.uLatchedLayoutKeys |= (1 << iLayout);
}

/** Registers a key up event for the given layout. */
ID_INLINE void LQ3A_LayoutKeyUp(int iLayout)
{
	cgs.uLatchedLayoutKeys &= ~(1 << iLayout);
}

/** Returns qtrue when a key bound to the layout command is currently latched. */
ID_INLINE static qboolean LQ3A_IsLayoutKeyLatched(int iLayout)
{
	return (cgs.uLatchedLayoutKeys & (1 << iLayout)) ? qtrue : qfalse;
}

/** Returns qtrue when a key bound to the current layout command is currently latched. */
ID_INLINE static qboolean LQ3A_IsCurrentLayoutKeyLatched(void)
{
	return LQ3A_IsLayoutKeyLatched(cg.iLayout);
}

/** Promotes the next layout in the queue to active. */
static void LQ3A_ChangeLayout(void)
{
	/* Clear the current score cache when moving away from the scoreboard,
		we'll request a new set next time. */
	if (cg.iLayout == LQ3A_LAYOUT_SCOREBOARD)
	{
		cg.numScores			= 0;
		cg.scoresRequestTime	= 0;

		/* Don't print the killer next time the scoreboard comes up. */
		cg.deferredPlayerLoading = 0;
		cg.killerName[0] = 0;
	}

	if (cg.iNextLayout == LQ3A_LAYOUT_HIGHSCORES)
	{
		/* Announce new high scores at the intermission. */
		if ((cg.predictedPlayerState.pm_type == PM_INTERMISSION) && (!cg.bHighScoreAnnounced) &&
				cg.snap && (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR))
		{
			uint i;

			/* Check the high score table for a new score set by the local client. */
			for (i=0; i<cgs.HighScores.uCount; i++)
			{
				if (cg.snap && (cg.snap->ps.clientNum == cgs.HighScores.Table[i].iClient-1) &&
						(!(cg.snap->ps.pm_flags & PMF_FOLLOW)))
				{
					trap_S_StartLocalSound(cgs.media.impressiveSound, CHAN_ANNOUNCER);
					break;
				}
			}

			/* This ensures the announcement is played only once,
				We set this all the time to prevent looking for the local client each time. */
			cg.bHighScoreAnnounced = qtrue;
		}
	}

	/* Promote the next layout. */
	cg.iLayout				= cg.iNextLayout;
	cg.iLayoutStartTime		= cg.iNextLayoutStartTime;
	cg.iLayoutEndTime		= cg.iNextLayoutEndTime;
	cg.iLayoutDuration		= cg.iLayoutEndTime - cg.iLayoutStartTime;

	cg.iNextLayout			= LQ3A_LAYOUT_NONE;
	cg.iNextLayoutStartTime	= 0;
	cg.iNextLayoutEndTime	= 0;
}

/** Adds the given layout to the queue. */
void LQ3A_SetLayout(int iLayout, int iDelayTime, qboolean bForce)
{
	/* Do nothing if the requested layout is already active or its the next layout and the switch over is already happening. */
	if ((cg.iLayout == iLayout) ||
		((cg.iNextLayout != LQ3A_LAYOUT_NONE) && (cg.iNextLayout == iLayout) && (cg.iNextLayoutStartTime <= (cg.time + FADE_TIME))))
	{
		return;
	}

	/* Layouts are forced at the intermission, only allow changes when forced. */
	if ((cg.predictedPlayerState.pm_type == PM_INTERMISSION) && !bForce)
	{
		return;
	}

	switch (iLayout)
	{
	case LQ3A_LAYOUT_SCOREBOARD:

		/* Request a newer set of scores if our cache is out of date. */
		if (cg.scoresRequestTime + 2000 < cg.time)
		{
			cg.scoresRequestTime = cg.time;
			trap_SendClientCommand("score");
		}

		cg.iNextLayoutEndTime = 0;
		break;

	case LQ3A_LAYOUT_CENTERSTRING:

		cg.iNextLayoutEndTime = cg.time + (cg_centertime.value * 1000);
		break;

	case LQ3A_LAYOUT_MOTD:

		cg.iNextLayoutEndTime = cg.time + LQ3A_MOTD_DISPLAY_TIME;
		break;

	case LQ3A_LAYOUT_HIGHSCORES:

		if (!cgs.HighScores.bEnabled)
		{
			CG_Printf("High scores are disabled.\n");
			return; /* Disabled. */
		}

		cg.iNextLayoutEndTime = 0;
		break;
	}

	cg.iNextLayout			= iLayout;
	cg.iNextLayoutStartTime	= cg.time + iDelayTime;

	/* Bring the layout up if there is nothing currently on screen. */
	if (cg.iLayout == LQ3A_LAYOUT_NONE)
	{
		LQ3A_ChangeLayout();
		return;
	}

	/* Do not overwrite the current layout if the key bound to it is latched. */
	if ((iLayout == LQ3A_LAYOUT_CENTERSTRING) && LQ3A_IsCurrentLayoutKeyLatched())
	{
		return;
	}

	cg.iLayoutEndTime	= cg.time + FADE_TIME;
	cg.iLayoutDuration	= cg.iLayoutEndTime - cg.iLayoutStartTime;
}

/** Removes the given layout from the queue. */
void LQ3A_RemoveLayout(int iLayout)
{
	/* Scoreboard is forced when dead or at the intermission so ignore the request,
		otherwise the scoreboard will fade out and fade back in again.

		cg.predictedPlayerState.pm_type == PM_DEAD works for players but not when following.
		cg.snap->ps.pm_time == PM_DEAD works when following but not for players.
		cg.snap->ps.stats[STAT_HEALTH] <= 0 works in all cases. */
	if ((iLayout == LQ3A_LAYOUT_SCOREBOARD) &&
		((cg.snap && (cg.snap->ps.stats[STAT_HEALTH] <= 0)) || (cg.predictedPlayerState.pm_type == PM_INTERMISSION)) ||
		LQ3A_IsLayoutKeyLatched(iLayout))
	{
		return;
	}	

	/* Fade out if showing. */
	if (cg.iLayout == iLayout)
	{
		LQ3A_SetLayout(LQ3A_LAYOUT_NONE, 0, qfalse);
		return;
	}

	/* Cancel if a request is pending. */
	if (cg.iNextLayout == iLayout)
	{
		cg.iNextLayout			= LQ3A_LAYOUT_NONE;
		cg.iNextLayoutStartTime	= 0;
		return;
	}
}

/** Draws the center string layout on the screen, replaces CG_DrawCenterString(). */
static ID_INLINE void LQ3A_DrawCenterString(void)
{
	CG_DrawStringExt2(320, cg.centerPrintY, cg.centerPrint, cg.fLayoutColor,
		qfalse, qtrue, cg.centerPrintCharWidth, cg.centerPrintCharWidth, 0, UI_CENTER);
}

/** Draws the motd layout on the screen. */
static void LQ3A_DrawMotd(void)
{
	int x = 408 - (cgs.Motd.uLines * (SMALLCHAR_HEIGHT + 2));

	CG_DrawStringExt(36, x, cgs.Motd.cMessage, cg.fLayoutColor, qfalse, qtrue, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);
}

/** Draws the high score layout on the screen. */
static void LQ3A_DrawHighScores(void)
{
	char					cString[1024];
	int						i, x, y, iLen, iRowLen;
	plq3a_highscore_entry_t	pEntry;
	vec4_t					cColor;

	/* Color match for the standard scoreboard red. */
	cColor[0] = 0.76f;
	cColor[1] = 0.0f;
	cColor[2] = 0.0f;
	cColor[3] = cg.fLayoutColor[3];

	CG_DrawStringExt2(320, 72, "HIGH SCORES", cg.fLayoutColor,
		qfalse, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0, UI_CENTER);

	Com_sprintf(cString, sizeof(cString), cgs.cMap);

	CG_DrawStringExt2(320, 92, cString, cColor,
		qfalse, qtrue, 10, SMALLCHAR_HEIGHT, 0, UI_CENTER);

	/* Header */
	iRowLen = Com_sprintf(cString, sizeof(cString),
		"   NAME            %5s              ACC  EFF", cgs.fraglimit ? "  FPH" : "SCORE");

	if (cgs.HighScores.bIncludeDate)
	{
		Q_strncpyz(cString + iRowLen, " DATE      ", sizeof(cString)-iRowLen);
		iRowLen += sizeof(" DATE      ")-1;
	}

	x = LQ3A_GetDrawAlignment(320, cString, 10, UI_CENTER);

	CG_DrawStringExt2(320, 132, cString, cColor,
		qfalse, qtrue, 10, SMALLCHAR_HEIGHT, 0, UI_CENTER);

	trap_R_SetColor(cg.fLayoutColor);
	CG_DrawPic(x+255, 123, 26, 26, cgs.media.medalImpressive);
	CG_DrawPic(x+294, 123, 26, 26, cgs.media.medalExcellent);
	CG_DrawPic(x+334, 123, 26, 26, cgs.media.medalGauntlet);
	trap_R_SetColor(NULL);

	for (i=0, y=150, iLen=0; i<LQ3A_MAX_HIGHSCORE_ENTRIES; i++)
	{
		pEntry = &cgs.HighScores.Table[i];

		if (i < cgs.HighScores.uCount)
		{
			/* Highlight new additions to the table. */
			if (pEntry->iClient)
			{
				/* Flash scores set by the local client. */
				if (cg.snap && (cg.snap->ps.clientNum == pEntry->iClient-1) &&
						(!(cg.snap->ps.pm_flags & PMF_FOLLOW)))
				{
					if ((cg.time % 1000) - (cg.time % 500))
					{
						cColor[0] = 0.76f;
						cColor[1] = 0.0f;
						cColor[2] = 0.0f;
						cColor[3] = 0.4f * cg.fLayoutColor[3];

						CG_FillRect(x-2, y, (10 * iRowLen) + 6, SMALLCHAR_HEIGHT + 2, cColor);
					}
				}
				else
				{
					/* Highlight other clients. */
					cColor[0] = 1.0f;
					cColor[1] = 1.0f;
					cColor[2] = 1.0f;
					cColor[3] = 0.4f * cg.fLayoutColor[3];

					CG_FillRect(x-2, y, (10 * iRowLen) + 6, SMALLCHAR_HEIGHT + 2, cColor);
				}
			}

			iLen = Com_sprintf(cString, sizeof(cString), "%2i %s%s %5i %3i %3i %3i %3i%% %3i%%",
				i+1, pEntry->cGamerTag,
				S_COLOR_WHITE,
				pEntry->uScore,
				pEntry->uImpresiveCount,
				pEntry->uExcellentCount,
				pEntry->uHumiliationCount,
				pEntry->uAccuracy,
				pEntry->uEfficiency);

			if (cgs.HighScores.bIncludeDate)
			{
				Com_sprintf(cString+iLen, sizeof(cString)-iLen, " %s", pEntry->cDate);
			}

			/* Draw skill levels next to bot scores. */
			if (pEntry->uFlags & LQ3A_HSEF_BOT)
			{
				trap_R_SetColor(cg.fLayoutColor);
				CG_DrawPic(x-21, y, 16, 16, cgs.media.botSkillShaders[pEntry->uBotSkill]);
				trap_R_SetColor(NULL);
			}
		}
		else
		{
			/* Empty slot. */
			iLen = Com_sprintf(cString, sizeof(cString), "%2i <Empty>                                    ",
				i+1, pEntry->cGamerTag);

			if (cgs.HighScores.bIncludeDate)
			{
				Q_strncpyz(cString+iLen, "           ", sizeof(cString)-iLen);
			}
		}

		CG_DrawStringExt2(320, y, cString, cg.fLayoutColor,
			qfalse, qtrue, 10, SMALLCHAR_HEIGHT, 0, UI_CENTER);

		y += SMALLCHAR_HEIGHT + 2;
	}

	if (cgs.timelimit && cgs.fraglimit)
	{
		Com_sprintf(cString, sizeof(cString)-iLen,
			"%sScores after %s%i%s minute%s or %s%i%s frag%s",
				S_COLOR_WHITE, S_COLOR_REVERT, cgs.timelimit, S_COLOR_WHITE, (cgs.timelimit != 1) ? "s" : "",
				S_COLOR_REVERT, cgs.fraglimit, S_COLOR_WHITE, (cgs.fraglimit != 1) ? "s" : "");
	}
	else if (cgs.timelimit)
	{
		Com_sprintf(cString, sizeof(cString)-iLen,
			"%sScores after %s%i%s minute%s", S_COLOR_WHITE, S_COLOR_REVERT,
				cgs.timelimit, S_COLOR_WHITE, (cgs.timelimit != 1) ? "s" : "");
	}
	else
	{
		/* Fraglimit only. */
		Com_sprintf(cString, sizeof(cString)-iLen,
			"%sScores after %s%i%s frag%s", S_COLOR_WHITE, S_COLOR_REVERT,
				cgs.fraglimit, S_COLOR_WHITE, (cgs.fraglimit != 1) ? "s" : "");
	}

	cColor[0] = 0.76f;
	cColor[1] = 0.0f;
	cColor[2] = 0.0f;
	cColor[3] = cg.fLayoutColor[3];

	CG_DrawStringExt2(320, y + SMALLCHAR_HEIGHT + 6, cString, cColor,
		qfalse, qtrue, TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0, UI_CENTER);
}

/** Draws the active layout on screen. */
void LQ3A_DrawLayout(void)
{
	float	*fColor;

	if (cg.predictedPlayerState.pm_type == PM_INTERMISSION)
	{
		/* Layouts are forced at the intermission.
			We show the scoreboard to start with, followed by the high score table. We revert back to the
			scoreboard when the intermission time has past and we're still waiting for players to ready up. */
		if ((!cgs.HighScores.bEnabled) || (cg.time < (cg.iIntermissionStartTime + (cg.intermissionStarted / 2)))
				|| (cg.time > (cg.iIntermissionStartTime + cg.intermissionStarted)))
		{
			LQ3A_SetLayout(LQ3A_LAYOUT_SCOREBOARD, 0, qtrue);
		}
		else
		{
			LQ3A_SetLayout(LQ3A_LAYOUT_HIGHSCORES, 0, qtrue);
		}
	}
	else if (cg.predictedPlayerState.pm_type == PM_DEAD)
	{
		/* Force the scoreboard layout once when dead,
			the player is however allowed to overwrite it. */
		if (!cg.bShownScoreboardToDeadPerson)
		{
			LQ3A_SetLayout(LQ3A_LAYOUT_SCOREBOARD, 0, qfalse);
			cg.bShownScoreboardToDeadPerson = qtrue;
		}
		/* Force the scoreboard again when the overwriting layout has finished. */
		else if (cg.iLayout == LQ3A_LAYOUT_NONE)
		{
			LQ3A_SetLayout(LQ3A_LAYOUT_SCOREBOARD, 0, qfalse);
		}
	}
	else if ((cg.iLayout == LQ3A_LAYOUT_NONE) || (cg.time < cg.iNextLayoutStartTime))
	{
		return;
	}

	/* Fade in. */
	LQ3A_FadeInColor(&cg.fLayoutColor, cg.iLayoutStartTime, cg.iLayoutEndTime);

	/* Check for fade out when there is a scheduled end time. */
	if (cg.iLayoutEndTime)
	{
		fColor = CG_FadeColor(cg.iLayoutStartTime, cg.iLayoutDuration);

		if (!fColor)
		{
			/* Promote the next layout once the current layout has completely faded out. */
			LQ3A_ChangeLayout();
			return; /* Finished. */
		}

		/* Keep a smooth transition between the fade in and fade out effects. */
		if (fColor[3] < cg.fLayoutColor[3])
		{
			cg.fLayoutColor[3] = fColor[3];
		}
	}

	/* Draw the active layout. */
	switch (cg.iLayout)
	{
	case LQ3A_LAYOUT_SCOREBOARD:
		CG_DrawOldScoreboard();
		break;
	case LQ3A_LAYOUT_CENTERSTRING:
		LQ3A_DrawCenterString();
		break;
	case LQ3A_LAYOUT_MOTD:
		LQ3A_DrawMotd();
		break;
	case LQ3A_LAYOUT_HIGHSCORES:
		LQ3A_DrawHighScores();
		break;
	}
}

/** Parses the 'cp' command string. */
void LQ3A_ParseCenterPrint(pcchar pString, int y, int charWidth)
{
	if (!pString || (*pString == 0))
	{
		/* Not set. */
		cg.centerPrintLines = 0;
		return;
	}

	Q_strncpyz(cg.centerPrint, pString, sizeof(cg.centerPrint));

	cg.centerPrintY			= y;
	cg.centerPrintCharWidth	= charWidth;
	cg.centerPrintLines		= LQ3A_GetLineCount(cg.centerPrint);

	LQ3A_SetLayout(LQ3A_LAYOUT_CENTERSTRING, 0, qfalse);
}

/** Parses the CS_MOTD configuration string. */
void LQ3A_ParseMotd(pchar pString, qboolean bDisplay)
{
	if (!pString || (*pString == 0))
	{
		/* Not set. */
		cgs.Motd.uLines = 0;
		return;
	}

	/* Store the message and append the layout tag to the end of it. */
	Com_sprintf(cgs.Motd.cMessage, sizeof(cgs.Motd.cMessage), "%s%s",
		pString, LQ3A_LAYOUT_TAG);

	cgs.Motd.uLines = LQ3A_GetLineCount(cgs.Motd.cMessage);

	if (bDisplay)
	{
		/* Display now. */
		LQ3A_SetLayout(LQ3A_LAYOUT_MOTD, LQ3A_MOTD_DELAY, qfalse);
	}
}

/** Displays the motd. */
void LQ3A_MotdCmd(void)
{
	LQ3A_SetLayout(LQ3A_LAYOUT_MOTD, 0, qfalse);
}

/** Parses the CS_LQ3A_HIGHSCORES configuration string. */
void LQ3A_ParseHighScores(pchar pString, size_t uSize)
{
	char					cArg[MAX_TOKEN_CHARS];
	uint					i, uLen;
	plq3a_highscore_entry_t	pEntry;

	if (!pString || (!*pString))
	{
		return;
	}

	cgs.HighScores.bIncludeDate = qfalse;

	LQ3A_SetParseOptions(0);

	/* We use LQ3A_GetArg() to parse arguments here as the given string
		isn't tokenized by the engine rendering CG_Argv() useless here. */
	LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
	uSize -= uLen;
	cgs.HighScores.uCount = atoi(cArg);

	for (i=0; i<cgs.HighScores.uCount; i++)
	{
		pEntry = &cgs.HighScores.Table[i];

		LQ3A_ParseArg(&pString, uSize, cArg, MAX_NETNAME, &uLen);
		uSize -= uLen;
		LQ3A_FixDrawLength(cArg, 15, pEntry->cGamerTag, MAX_NETNAME);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uScore = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uFlags = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uBotSkill = (pEntry->uFlags & LQ3A_HSEF_BOT) ? atoi(cArg)-1 : 0;

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uImpresiveCount = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uExcellentCount = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uHumiliationCount = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uCaptureCount = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uAssistCount = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		pEntry->uDefenceCount = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		pEntry->uAccuracy = atoi(cArg);

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->uEfficiency = atoi(cArg);

		/* Parse the date when we have one. */
		if (pEntry->uFlags & LQ3A_HSEF_DATE)
		{
			/* Date length is fixed. */
			LQ3A_ParseArg(&pString, uSize, pEntry->cDate, LQ3A_MAX_DATE+1, &uLen);
			uSize -= uLen;
		}
		else
		{
			uLen = 0;
		}

		if (uLen == LQ3A_MAX_DATE)
		{
			cgs.HighScores.bIncludeDate = qtrue;
		}
		else
		{
			/* Default to "NA", we may need to publish this if one of the high scores contains a date. */
			strcpy(pEntry->cDate, "NA        ");
		}

		LQ3A_ParseArg(&pString, uSize, cArg, sizeof(cArg), &uLen);
		uSize -= uLen;
		pEntry->iClient = atoi(cArg);
	}
}

/** Displays the high scores. */
void LQ3A_HighScoreDownCmd(void)
{
	LQ3A_LayoutKeyDown(LQ3A_LAYOUT_HIGHSCORES);
	LQ3A_SetLayout(LQ3A_LAYOUT_HIGHSCORES, 0, qfalse);
}

/** Removes the high scores. */
void LQ3A_HighScoreUpCmd(void)
{
	LQ3A_LayoutKeyUp(LQ3A_LAYOUT_HIGHSCORES);
	LQ3A_RemoveLayout(LQ3A_LAYOUT_HIGHSCORES);
}

/** Executes one time actions per map. */
void LQ3A_ExecuteOneTimeActions(void)
{
	if (g_bInitilised)
	{
		/* Already executed. */
		return;
	}

	g_bInitilised = qtrue;

	/* Bring the motd up. */
	LQ3A_SetLayout(LQ3A_LAYOUT_MOTD, LQ3A_MOTD_DELAY, qfalse);
}

/** Returns the maximum inventory value of the given ammo type.
		A variation of this function exists in both server and client modules. */
int LQ3A_GetMaxAmmoValue(int iWeapon)
{
	return cgs.iAmmoLimits[iWeapon];
}
