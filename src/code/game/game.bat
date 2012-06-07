REM Make sure we have a safe environement
SET LIBRARY=
SET INCLUDE=

IF NOT EXIST ..\..\builds\vm\qagame MKDIR ..\..\builds\vm\qagame
CD ..\..\builds\vm\qagame

SET GSRCDIR=../../../code/game
SET CSRCDIR=../../../code/cgame
SET UISRCDIR=../../../code/ui

REM -DMISSIONPACK
SET CC=lcc -DQ3_VM -S -Wf-target=bytecode -Wf-g -I%GSRCDIR% -I%CSRCDIR% -I%UISRCDIR% %1

%CC% %GSRCDIR%/g_main.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/bg_items.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/bg_misc.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/bg_lib.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/bg_pmove.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/bg_slidemove.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/q_math.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/q_shared.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/ai_dmnet.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/ai_dmq3.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/ai_main.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/ai_chat.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/ai_cmd.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/ai_team.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_active.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_arenas.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_bot.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_client.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_cmds.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_combat.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_items.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_mem.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_misc.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_missile.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_mover.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_session.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_spawn.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_svcmds.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_target.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_team.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_trigger.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_utils.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_weapon.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/ai_vcmd.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/bg_lq3a.c
@if errorlevel 1 goto quit
%CC%  %GSRCDIR%/g_lq3a.c
@if errorlevel 1 goto quit

q3asm -f %GSRCDIR%/game

MOVE /Y ..\qagame.map qagame.map

:quit
CD %GSRCDIR%
