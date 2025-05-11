g++ -Wall -Wextra -g3 *.cpp -o output/engine.exe
if %errorlevel% neq 0 goto end
@echo off
cd output
cls
@echo on
engine.exe
:end
pause