@echo off
cd Release
d:\Qt\5.12.6\msvc2017\bin\windeployqt.exe --release --compiler-runtime FileSearchUtility.exe
xcopy .\FileSearchUtility\FileSearchUtility_en.ts .\Release /y
xcopy .\FileSearchUtility\FileSearchUtility_ru.ts .\Release /y