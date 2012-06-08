Loaded Q3A Readme
=================

-	**Version**: 2.0 RC1
-	**Licence:** [GPL Version 2](http://www.gnu.org/licenses/gpl-2.0.html)
-	**Author:** [Kevin Fell](http://www.kevin-fell.co.uk/)
-	**Copyright:** (C) 1999-2012 Kevin Fell

Introduction
------------

Loaded Q3A is a server and client modification for Quake 3 Arena which
adds a highly customisable layer of server side administration while
staying true to the original game play.

The main additions are as follows: 

-	Enhanced spectator modes to ensure you don't miss the action.
-	Stylish "Message of the Day" to communicate information to players.
-	Sophisticated map rotation system which includes ideal head counts
	and custom configuration files per map.
-	High scoring system to record the best players to grace your server.
-	Respawn protection shield to eradicate spawn spot opportunists.
-	Anti-camp options to keep players on the move.
-	Offhand grappling hook to reach the unreachable.
-	Real-time item management system.
-	Speed and damage customisation, complete with client-side prediction.
-	Extended bot AI to ensure they understand the new features.

This is a complete rewrite of the original Loaded Q3A source code which
adds compatibility with the final point release.


Installation
------------

A full retail version of Quake 3 is required to play this modification
patched to the 1.32 point release.

If for some reason you don't already own a copy, you can purchase it
online from [Steam](http://store.steampowered.com/app/2200). The 1.32
point release can be found on the
[Id Software](ftp://ftp.idsoftware.com/idstuff/quake3/) ftp server.

Extract the content of this archive to your Quake 3 installation. You
can run it either by selecting "Loaded Q3A" from the in-game "Mods"
menu or by using the following command line:

> `quake3 +set fs_game loaded +map q3dm1`

If you prefer to run the server DLL over the QVM you can use the
following command line:

> `quake3 +set fs_game loaded + set sv_pure 0 + set vm_game 0 +map q3dm1`

Loaded Q3A has been tested with [ioQuake3](http://ioquake3.org/) and I
recommend you use this over the official Id releases.

There is a very small addition to the DLL version of Loaded Q3A which is
detailed later this this document.

**If you are upgrading from a previous release of Loaded Q3A you must
delete the "loaded" directory prior to installing this version.**


Setup
-----

Loaded Q3A is packed full of goodies, all of which can be individually
configured and tuned to your taste. Please refer to
"readme-config.txt" for a description of the additional functionality.


QVM vs DLL
----------

This distribution includes compiled QVM's for the server, client and
ui modules.

The server DLL has been included for those of you who want to record
dates against the high score entries since the Quake 3 engine provides
no means to query the system date within it's virtual machine environment.
Its identical in every other way.

The other modules offer little benefit in DLL format on modern day
computers and are therefore not included in this distribution, they
can however be compiled from source if for some reason you have a
compelling reason to run them.

	
Source Code
-----------

The source code is available under the terms of the GNU GPL Version 2
open source licence and can be downloaded from my
[GitHub repository](https://github.com/monoknot/loaded-q3a).

The package includes project files to build everything in MSVC++ 2010.
Each project is setup to compile using the "Windows7.1SDK" platform
toolset, you can either update your Windows platform SDK or change the
platform toolset with in each projects properties menu.

The main changes can be found in the following files:

> Server

>- g_lq3a.c
>- g_lq3a.h

> Client

>- cg_lq3a.c
>- cg_lq3a.h

> Shared

>- bg_lq3a.c
>- bg_lq3a.h

Changes to the original source code have been clearly tagged with "LQ3A",
an accompanying description is also provided along side changes that
warrant an explanation.

There are no changes to the UI module, its has only been included to
prevent Quake 3 kicking you out the game with a "baseq3-lq3a" miss
match error.

Additional Team Arena support exists in the source code. While these
additions are not compiled in the release it should leave the door open
for anyone who wishes to add them in. My intention was to have a single
release which would support both the standard game and the Team Arena
mission pack by simply copying the mod content to the "missionpack"
directory.

The game sets the level.bMissionPack variable to qtrue when the mission
pack content is detected, this is communicated to the client module and
subsequently sets cgs.bMissionPack. With a bit of effort, the Team Arena
code could then be integrated into the standard code base to create a
single release to supports both games.


Licence
-------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.

Quake III Arena (C) 1999-2005 Id Software, Inc. All Rights Reserved.