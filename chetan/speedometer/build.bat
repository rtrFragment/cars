set root=%CD%
cd resources
rc.exe /V resource.rc
cd %root%

cl.exe /EHsc /DUNICODE /Zi /I %GLEW_PATH%\include /I %GLM_PATH% /Fe:main.exe /I ".\lib\freetype\include" *.cpp lib/logger/*.cpp /link resources\resource.res /LIBPATH:%GLEW_LIB_PATH% /LIBPATH:%OPENAL_LIB_PATH% /LIBPATH:".\lib\freetype\win64" user32.lib kernel32.lib gdi32.lib openGL32.lib glew32.lib OpenAL32.lib freetype.lib
