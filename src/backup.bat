@ECHO OFF

SET APP="C:\Program Files\7-Zip\7z"
SET PROJECT=loaded-q3a
SET OUTPUT=%PROJECT%-backup-%date:~6,4%-%date:~3,2%-%date:~0,2%.7z

IF EXIST _backups/%OUTPUT% DEL _backups/%OUTPUT%

%APP% a -mmt -mx9 -p%1 -r -t7z _backups/%OUTPUT% -x@backup_excludes.txt