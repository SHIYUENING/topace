PATH %windir%\Microsoft.NET\Framework\v2.0.50727;%PATH%

MSBuild TOP_ACE_VS2005.sln /t:Rebuild /p:Configuration=Release
pause
