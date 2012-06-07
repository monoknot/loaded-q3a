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


/*
=======================================================================

  SESSION DATA

Session data is the only data that stays persistant across level loads
and tournament restarts.
=======================================================================
*/

/*
================
G_WriteClientSessionData

Called on game shutdown
================
*/
void G_WriteClientSessionData( gclient_t *client ) {
	const char	*s;
	const char	*var;

	s = va("%i %i %i %i %i %i %i", 
		client->sess.sessionTeam,
		client->sess.spectatorTime,
		client->sess.spectatorState,
		client->sess.spectatorClient,
		client->sess.wins,
		client->sess.losses,
		client->sess.teamLeader
		);

	var = va( "session%i", client - level.clients );

	trap_Cvar_Set( var, s );
}

/*
================
G_ReadSessionData

Called on a reconnect
================
*/
/** LQ3A: Changed return from void to qboolean.
	This function reads the session data from cvars and assigns a team to the client,
	if we cannot assign a team it returns qfalse and the client should be dropped from the server.
	@see ClientConnect(). */
qboolean G_ReadSessionData(gclient_t *client) {
	char	s[MAX_STRING_CHARS];
	const char	*var;

	// bk001205 - format
	int teamLeader;
	int spectatorState;
	int sessionTeam;
	/* LQ3A */
	qboolean bCanClientSpectate;

	var = va( "session%i", client - level.clients );
	trap_Cvar_VariableStringBuffer( var, s, sizeof(s) );

	sscanf( s, "%i %i %i %i %i %i %i",
		&sessionTeam,                 // bk010221 - format
		&client->sess.spectatorTime,
		&spectatorState,              // bk010221 - format
		&client->sess.spectatorClient,
		&client->sess.wins,
		&client->sess.losses,
		&teamLeader                   // bk010221 - format
		);

	/* LQ3A */
	bCanClientSpectate = LQ3A_CanClientSpectate(LQ3A_ClientToEntity(client));

	/* Place clients into the same teams they were in previously. */
	if (g_gametype.integer >= GT_TEAM)
	{
		client->sess.sessionTeam = (team_t)sessionTeam;

		/* Force spectators into the game if we can no longer spectate. */
		if ((client->sess.sessionTeam == TEAM_SPECTATOR) && !bCanClientSpectate)
		{
			client->sess.sessionTeam = PickTeam(-1);
			BroadcastTeamChange(client, -1);
		}
	}
	/* Always default as spectator. */
	else if (bCanClientSpectate)
	{
		client->sess.sessionTeam = TEAM_SPECTATOR;
	}
	/* If we cannot spectate, can we join the game? */
	else if (LQ3A_GetVacantPlayerSlots())
	{
		client->sess.sessionTeam = TEAM_FREE;
	}
	else
	{
		/* No vacant player slots and we cannot spectate. */
		return qfalse;
	}

	if (client->sess.sessionTeam == TEAM_SPECTATOR)
	{
		/* Force free floating spectator mode each level load. */
		client->sess.spectatorState		= SPECTATOR_FREE;
		client->sess.spectatorClient	= 0;
	}

	client->sess.teamLeader = (qboolean)teamLeader;

	/* LQ3A */
	return qtrue;
}

/*
================
G_InitSessionData

Called on a first-time connect
================
*/
/** LQ3A: Changed return from void to qboolean.
	This function initilises the session data and assigns a team to the client,
	if we cannot assign a team it returns qfalse and the client should be dropped from the server.
	@see ClientConnect(). */
qboolean G_InitSessionData( gclient_t *client, char *userinfo ) {
	clientSession_t	*sess;
	/* LQ3A */
//	const char	*value;
	qboolean	bCanClientSpectate;
	int			iVacantPlayerSlots;

	/* LQ3A */
	UNREFERENCED_PARAMETER(userinfo);

	sess = &client->sess;

	/* LQ3A */
	bCanClientSpectate	= LQ3A_CanClientSpectate(LQ3A_ClientToEntity(client));
	iVacantPlayerSlots	= LQ3A_GetVacantPlayerSlots();

	// initial team determination
	if (g_gametype.integer >= GT_TEAM)
	{
		/* LQ3A: Added support for g_maxGameClients in team games.
			Force auto join when the client cannot spectate. */
		if (iVacantPlayerSlots && (g_teamAutoJoin.integer || !bCanClientSpectate))
		{
			sess->sessionTeam = PickTeam( -1 );
			BroadcastTeamChange( client, -1 );
		}
		else if (bCanClientSpectate)
		{
			sess->sessionTeam = TEAM_SPECTATOR;	
		}
		else
		{
			/* No vacant player slots and we cannot spectate. */
			return qfalse;
		}

	} else {

		/* LQ3A: Place clients into spectator mode by default where possible. */
		if (bCanClientSpectate)
		{
			sess->sessionTeam = TEAM_SPECTATOR;
		}
		/* If we cannot spectate, place the client in the game when there are vacant slots. */
		else if (iVacantPlayerSlots)
		{
			sess->sessionTeam = TEAM_FREE;
		}
		else
		{
			/* No vacant player slots and we cannot spectate. */
			return qfalse;
		}
	}

	sess->spectatorState = SPECTATOR_FREE;
	sess->spectatorTime = level.time;

	/* LQ3A */
	if (sess->sessionTeam == TEAM_SPECTATOR)
	{
		LQ3A_CompleteClientMoveToSpectatorTeam(LQ3A_ClientToEntity(client));
	}

	G_WriteClientSessionData( client );

	/* LQ3A */
	return qtrue;
}


/*
==================
G_InitWorldSession

==================
*/
void G_InitWorldSession( void ) {
	char	s[MAX_STRING_CHARS];
	int			gt;

	trap_Cvar_VariableStringBuffer( "session", s, sizeof(s) );
	gt = atoi( s );
	
	// if the gametype changed since the last session, don't use any
	// client sessions
	if ( g_gametype.integer != gt ) {
		level.newSession = qtrue;
		G_Printf( "Gametype changed, clearing session data.\n" );
	}
}

/*
==================
G_WriteSessionData

==================
*/
void G_WriteSessionData( void ) {
	int		i;

	trap_Cvar_Set( "session", va("%i", g_gametype.integer) );

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].pers.connected == CON_CONNECTED ) {
			G_WriteClientSessionData( &level.clients[i] );
		}
	}
}
