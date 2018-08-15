cl.exe /EHsc /DUNICODE /Zi /Fe:main.exe /I "%OPENAL_PATH%\include" *.cpp libs/cWaves/*.cpp /link /LIBPATH:"%OPENAL_LIB_PATH%" user32.lib kernel32.lib gdi32.lib OpenAL32.lib
