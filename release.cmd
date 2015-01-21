@mkdir bin
@mkdir bin\WAM
@if "%PROCESSOR_ARCHITECTURE%" == "AMD64" @pushd "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin"
@if "%PROCESSOR_ARCHITECTURE%" == "x86"   @pushd "C:\Program Files\Microsoft Visual Studio 12.0\VC\bin"
@set TARGET_ARCHITECTURE="%PROCESSOR_ARCHITECTURE%"
@if not "%2" == ""   @set TARGET_ARCHITECTURE=%1
@if not "%1" == ""    @set "DEBUG=/D NDEBUG=1"
@if %TARGET_ARCHITECTURE% == "AMD64" @call x86_amd64\vcvarsx86_amd64.bat
@if %TARGET_ARCHITECTURE% == "x86"   @call vcvars32.bat
popd
@xcopy /y /q /s /e SDL2\%TARGET_ARCHITECTURE%\. bin\
@xcopy /y /q /s /e LICENSES\. bin\
@xcopy /y /q /s /e res\. bin\WAM\
cl.exe /Fo.\bin\ /EHsc /nologo /MD /O2 /I inc /D NDEBUG=1 /I SGE\inc ws2_32.lib bin\*.lib src\*.cc SGE\src\*.cc
@move main.exe bin\wam.exe
@del bin\*.obj bin\*.lib
pause
