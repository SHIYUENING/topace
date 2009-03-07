PATH %windir%\Microsoft.NET\Framework\v3.5;%PATH%

MSBuild TOP_ACE_VS2008.sln /t:Rebuild /p:Configuration=Release
pause
