@echo On
@echo deleting exist messages...
@echo off
rem for /f %%I in ('dir /a:d /b') do 

for /r . %%a in (.) do for /f %%i in ('dir /ad /b %%a') do rd /s /q %%i

@echo On
@echo mission completed, now generating...
pause

@echo off
protoc --cpp_out=%cd% chatMsg.proto
pause