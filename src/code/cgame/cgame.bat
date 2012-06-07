REM Make sure we have a safe environement
SET LIBRARY=
SET INCLUDE=

MKDIR ..\..\builds\vm\cgame
CD ..\..\builds\vm\cgame

SET GSRCDIR=../../../code/game
SET CSRCDIR=../../../code/cgame
SET UISRCDIR=../../../code/ui

set CC=lcc -DQ3_VM -DCGAME -S -Wf-target=bytecode -Wf-g -I%GSRCDIR% -I%CSRCDIR% -I%UISRCDIR% %1

%CC% %GSRCDIR%/bg_misc.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/bg_items.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/bg_pmove.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/bg_slidemove.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/bg_lib.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/q_math.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/q_shared.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_consolecmds.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_draw.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_drawtools.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_effects.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_ents.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_event.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_info.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_localents.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_main.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_marks.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_players.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_playerstate.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_predict.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_scoreboard.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_servercmds.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_snapshot.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_view.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_weapons.c
@if errorlevel 1 goto quit
%CC% %GSRCDIR%/bg_lq3a.c
@if errorlevel 1 goto quit
%CC% %CSRCDIR%/cg_lq3a.c
@if errorlevel 1 goto quit

q3asm -f %CSRCDIR%/cgame

MOVE /Y ..\cgame.map cgame.map

:quit
cd %CSRCDIR%
