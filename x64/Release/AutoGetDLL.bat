
for /r "%cd%" %%i in (*.exe) do (   
 
D:\software\QT5\5.14.0\msvc2017_64\bin\windeployqt.exe "%%~nxi")
 
pause