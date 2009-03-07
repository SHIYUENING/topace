@echo off
@PATH %ProgramFiles%\WinRar;%PATH%

@cd ..
@del TopACE.rar
@rar a -av- -m5 -md4096 -tsm -tsc -s -k -t TopACE.rar del -xSrc\*.user Src Bin
@if not exist Versions md Versions
@copy TopACE.rar Versions\
