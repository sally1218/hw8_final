@echo off
REM Run rental_system with UTF-8 code page and keep console open for Explorer users
chcp 65001 >nul
powershell -NoProfile -Command "Set-Location '%~dp0'; & '.\rental_system.exe'; Read-Host '按 Enter 關閉'"
