@ECHO OFF
TITLE Windows Driver Kit 7.1.0

    set target=amd64
REM set target=i386

set DDK=C:\WinDDK\7600.16385.1
set MSVC=%DDK%\bin\x86\amd64
set incl=/I"%DDK%\inc\crt" /I"%DDK%\inc\api"
set libs=/LIBPATH:"%DDK%\lib\crt\%target%" /LIBPATH:"%DDK%\lib\wnet\%target%"

set LINK_FLAGS=%libs% /OUT:mh.exe /SUBSYSTEM:CONSOLE,5.2 /MERGE:.rdata=.text
set C_FLAGS=/Wall /O1 /Os /Ob1 /Oi /MD /TC /link %LINK_FLAGS%

%MSVC%\cl.exe %CD%\doors.c %CD%\input.c %CD%\main.c %incl% %C_FLAGS%

PAUSE
