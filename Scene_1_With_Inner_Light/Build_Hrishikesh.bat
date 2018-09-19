REM cl.exe /EHsc Model_Loading.cpp

cl.exe /EHsc /I "%OPENAL_PATH%\include" Model_Loading.cpp lib\audioManager\audioManager.cpp lib\audioManager\soundSource.cpp lib\cWaves\CWaves.cpp lib\logger\logger.cpp lib\logger\utils.cpp /link /LIBPATH:"%OPENAL_LIB_PATH%"
