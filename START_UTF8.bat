@echo off
REM Start Sports Equipment Rental System with GBK encoding (Chinese)
REM This ensures proper Chinese character display on Windows
cmd.exe /k "cd /d %~dp0 && chcp 936 >nul && title Sports Equipment Rental System && rental_system.exe"
