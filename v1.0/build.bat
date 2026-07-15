@echo off
chcp 65001 > nul
echo ========================================
echo   Metro Ticket System - 编译脚本
echo ========================================
echo.

set "PROJ_DIR=d:\桌面\MetroTicketSystem\v1.0"
set "VC_DIR=C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207"
set "KITS_DIR=C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0"
set "KITS_LIB=C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0"

set "INCLUDE=%VC_DIR%\include;%KITS_DIR%\ucrt;%KITS_DIR%\um;%KITS_DIR%\shared"
set "LIB=%VC_DIR%\lib\x64;%KITS_LIB%\ucrt\x64;%KITS_LIB%\um\x64"

set "CL_EXE=%VC_DIR%\bin\Hostx64\x64\cl.exe"

echo 编译中...
"%CL_EXE%" /utf-8 /Fe:%PROJ_DIR%\MetroTicketSystem.exe /I %PROJ_DIR%\include %PROJ_DIR%\src\main.c %PROJ_DIR%\src\welcome.c %PROJ_DIR%\src\menu.c %PROJ_DIR%\src\file.c %PROJ_DIR%\src\instruction.c %PROJ_DIR%\src\station.c %PROJ_DIR%\src\price.c %PROJ_DIR%\src\ticket.c %PROJ_DIR%\src\payment.c %PROJ_DIR%\src\history.c %PROJ_DIR%\src\search.c %PROJ_DIR%\src\test.c %PROJ_DIR%\src\map.c

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo  编译成功！生成 MetroTicketSystem.exe
    echo ========================================
) else (
    echo.
    echo ========================================
    echo  编译失败！请检查错误信息
    echo ========================================
)

pause
