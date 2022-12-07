for /r "%cd%" %%i in (*.exe) do (   
 
D:\software\QT5\5.14.0\mingw73_32\bin\windeployqt.exe "%%~nxi")
 
pause