@echo off
REM 體育器材租借系統 - Windows 編譯腳本

echo ========================================
echo  體育器材租借系統 - 編譯腳本
echo ========================================
echo.

REM 檢查是否裝有 g++
where g++ >nul 2>&1
if %errorlevel% equ 0 (
    echo 偵測到 MinGW/g++，正在使用 g++ 編譯...
    if not exist obj mkdir obj
    
    g++ -std=c++17 -Wall -Wextra -I./include -c ./src/main.cpp -o ./obj/main.o
    g++ -std=c++17 -Wall -Wextra -I./include -c ./src/Equipment.cpp -o ./obj/Equipment.o
    g++ -std=c++17 -Wall -Wextra -I./include -c ./src/Ball.cpp -o ./obj/Ball.o
    g++ -std=c++17 -Wall -Wextra -I./include -c ./src/Racket.cpp -o ./obj/Racket.o
    g++ -std=c++17 -Wall -Wextra -I./include -c ./src/ProtectiveGear.cpp -o ./obj/ProtectiveGear.o
    g++ -std=c++17 -Wall -Wextra -I./include -c ./src/RentalRecord.cpp -o ./obj/RentalRecord.o
    g++ -std=c++17 -Wall -Wextra -I./include -c ./src/RentalSystem.cpp -o ./obj/RentalSystem.o
    
    echo 正在鏈結目標檔案...
    g++ -o ./rental_system.exe ./obj/*.o
    goto check_result
)

REM 偵測是否已在 MSVC 環境中 (cl)
where cl >nul 2>&1
if %errorlevel% equ 0 (
    echo 偵測到 MSVC 環境，正在編譯...
    cl.exe /utf-8 /EHsc /std:c++17 /Iinclude src/main.cpp src/Equipment.cpp src/Ball.cpp src/Racket.cpp src/ProtectiveGear.cpp src/RentalRecord.cpp src/RentalSystem.cpp /Fe:rental_system.exe
    goto check_result
)

REM 使用 vswhere 偵測 Visual Studio
set "VS_PATH="
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath`) do (
        set "VS_PATH=%%i"
    )
)

if defined VS_PATH (
    echo 偵測到 Visual Studio: "%VS_PATH%"
    echo 正在載入編譯器環境變數...
    call "%VS_PATH%\Common7\Tools\VsDevCmd.bat" >nul
    
    echo 正在使用 MSVC (cl.exe) 編譯...
    cl.exe /utf-8 /EHsc /std:c++17 /Iinclude src/main.cpp src/Equipment.cpp src/Ball.cpp src/Racket.cpp src/ProtectiveGear.cpp src/RentalRecord.cpp src/RentalSystem.cpp /Fe:rental_system.exe
    
    REM 清除 MSVC 產生的 .obj 暫存檔
    del /f /q *.obj >nul 2>&1
    goto check_result
)

echo.
echo ✗ 未能偵測到 g++ 或 Visual Studio C++ 編譯器。
echo 請先安裝 MinGW 或 Visual Studio (包含 C++ 開發環境)。
goto end

:check_result
if exist rental_system.exe (
    echo.
    echo ✓ 編譯成功！
    echo 執行檔位置: rental_system.exe
) else (
    echo.
    echo ✗ 編譯失敗！
)

:end
pause

