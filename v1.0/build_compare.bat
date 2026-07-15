@echo off
chcp 65001 > nul
echo ========================================
echo  编译 AI方案对比实验
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
"%CL_EXE%" /utf-8 /Fe%PROJ_DIR%\compare.exe %PROJ_DIR%\test\compare.c

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo  编译成功！生成 compare.exe
    echo ========================================
) else (
    echo.
    echo ========================================
    echo  编译失败！请检查错误信息
    echo ========================================
)

pause
