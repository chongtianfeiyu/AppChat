@echo On
@echo deleting exist messages...
@echo off
rem ɾ����ǰ����Ŀ¼�������ļ�
for /r . %%a in (.) do for /f %%i in ('dir /ad /b %%a') do rd /s /q %%i

@echo On
@echo mission completed, now generating...

@echo off
protoc --plugin=protoc-gen-as3=protoc-gen-as3.bat --as3_out=%cd% chatMsg.proto
pause