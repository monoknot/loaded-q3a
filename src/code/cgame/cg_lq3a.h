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
#ifndef __CG_LQ3A_H__
#define __CG_LQ3A_H__

#define LQ3A_MOTD_DELAY			600		/**< Delay before showing the motd after request in milliseconds. */
#define LQ3A_MOTD_DISPLAY_TIME	5500	/**< Duration of message of the day layout in milliseconds. */

/** Information tag append to the server motd. */
#define LQ3A_LAYOUT_TAG				"\n\n^3Loaded Q3A " LQ3A_VERSION "\nhttp://www.kevin-fell.co.uk/"

/** Sizeof config string variables which include the info tag. */
#define MAX_CONFIGSTRINGS_WITH_TAG	(MAX_CONFIGSTRINGS+sizeof(LQ3A_LAYOUT_TAG))

/* Layouts. */
enum
{
	LQ3A_LAYOUT_NONE,
	LQ3A_LAYOUT_SCOREBOARD,		/**< Scoreboard. */
	LQ3A_LAYOUT_CENTERSTRING,	/**< Replaces the CG_CenterString() function. */
	LQ3A_LAYOUT_MOTD,			/**< Enhanced "Message of the day". */
	LQ3A_LAYOUT_HIGHSCORES		/**< High score table. */
};

typedef struct
{
	int	iType;			/**< Type of layout. See LQ3A_LAYOUT_* definitions. */
	int	iStartTime;		/**< cg.time the layout should begin to fade into the screen. */
	int	iEndTime;		/**< cg.time the layout should no longer appear on the screen and have completely faded out. */
	int	iDuration;

} lq3a_layout_t;

/** Message of the Day information. Updated by LQ3A_ParseMotd(). */
typedef struct
{
	char	cMessage[MAX_CONFIGSTRINGS];	/**< String to display. */
	uint	uLines;							/**< Count of lines in lq3a_motd_t::cMessage. */

} lq3a_motd_t;

/** High score information. Updated by LQ3A_ParseLoadedConfigString() and LQ3A_ParseHighScores(). */
typedef struct
{
	qboolean				bEnabled;							/**< True when the high scoring system is enabled. */
	lq3a_highscore_entry_t	Table[LQ3A_MAX_HIGHSCORE_ENTRIES];	/**< High score table for the current map. */
	uint					uCount;								/**< Count of entries in the high score table. */
	qboolean				bIncludeDate;						/**< True when there is one or more high score entries with a date. */

} lq3a_highscores_t;

/* Globals. */
extern qboolean	g_bInitilised;
extern int		g_pm_hookPullSpeed;					/**< bg_pmove.c */
extern int		g_pm_refireTime[WP_NUM_WEAPONS];	/**< bg_pmove.c */
extern int		g_pm_switchSpeed;					/**< bg_pmove.c */
extern float	g_pm_hasteFactor;					/**< bg_pmove.c */
extern int		g_pm_jumpVelocity;					/**< bg_pmove.c */

/* Function definitions. */
extern void		LQ3A_ParseLoadedConfigString(pchar pString, uint uSize);
extern void		LQ3A_ParseLimitsConfigString(pchar pString, uint uSize);
extern void		LQ3A_ParseItemsConfigString(pchar pString);
extern int		LQ3A_GetPlayingClientCount(void);
extern void		LQ3A_BlendScreen(void);
extern qboolean	LQ3A_FadeInColor(vec4_t *vIn, int iStartTime, int iEndTime);
extern uint		LQ3A_GetLineCount(pchar pBuffer);
extern int		LQ3A_GetDrawAlignment(int x, pcchar pString, int iCharWidth, uint uFlags);
extern void		LQ3A_FixDrawLength(pcchar pString, size_t uFixedSize, pchar pBuffer, size_t uSize);
extern void		LQ3A_LayoutKeyDown(int iLayout);
extern void		LQ3A_LayoutKeyUp(int iLayout);
extern void		LQ3A_SetLayout(int iLayout, int iDelayTime, qboolean bForce);
extern void		LQ3A_RemoveLayout(int iLayout);
extern void		LQ3A_DrawLayout(void);
extern void		LQ3A_ParseCenterPrint(pcchar pString, int y, int charWidth);
extern void		LQ3A_ParseMotd(pchar pString, qboolean bDisplay);
extern void		LQ3A_MotdCmd(void);
extern void		LQ3A_ParseHighScores(pchar pString, size_t uSize);
extern void		LQ3A_HighScoreDownCmd(void);
extern void		LQ3A_HighScoreUpCmd(void);
extern void		LQ3A_ExecuteOneTimeActions(void);

#endif /* __CG_LQ3A_H__ */
