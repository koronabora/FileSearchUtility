@echo off
cd Debug
d:\Qt\5.12.6\msvc2017\bin\windeployqt.exe --debug --compiler-runtime FileSearchUtility.exe
xcopy .\FileSearchUtility\FileSearchUtility_en.ts .\Debug /y
xcopy .\FileSearchUtility\FileSearchUtility_ru.ts .\Debug /y