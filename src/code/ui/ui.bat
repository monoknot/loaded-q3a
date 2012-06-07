REM Make sure we have a safe environement
set LIBRARY=
set INCLUDE=

IF NOT EXIST ..\..\builds\vm\ui MKDIR ..\..\builds\vm\ui
CD ..\..\builds\vm\ui

SET GSRCDIR=../../../code/game
SET CSRCDIR=../../../code/cgame
SET UISRCDIR=../../../code/ui

REM -DMISSIONPACK
SET CC=lcc -DQ3_VM -S -Wf-target=bytecode -Wf-g -I%GSRCDIR% -I%CSRCDIR% -I%UISRCDIR% %1

%CC% %UISRCDIR%/ui_main.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_cdkey.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_ingame.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_serverinfo.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_confirm.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_setup.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/bg_items.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/bg_lib.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/q_math.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/q_shared.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_gameinfo.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_atoms.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_connect.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_controls2.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_demo2.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_mfield.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_credits.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_menu.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_options.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_display.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_sound.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_network.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_playermodel.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_players.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_playersettings.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_preferences.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_qmenu.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_servers2.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_sparena.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_specifyserver.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_splevel.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_sppostgame.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_startserver.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_team.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_video.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_cinematics.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_spskill.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_addbots.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_removebots.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_teamorders.c
@if errorlevel 1 goto quit
%CC% %UISRCDIR%/ui_mods.c
@if errorlevel 1 goto quit

q3asm -f %UISRCDIR%/ui

MOVE /Y ..\ui.map ui.map

:quit
cd %UISRCDIR%
