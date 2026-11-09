@echo off
setlocal
cd /d "%~dp0"
if not exist results mkdir results
build\lab5.exe > results\output.txt
if errorlevel 1 exit /b 1
type results\output.txt
echo RUN FINISHED: output saved to results\output.txt
