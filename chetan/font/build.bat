set root=%CD%
cd resources
rc.exe /V resource.rc
cd %root%

cl.exe /EHsc /DUNICODE /Zi /I %GLEW_PATH%\include /I ".\lib\freetype\include" /Fe:font *.cpp /link resources\resource.res /LIBPATH:%GLEW_LIB_PATH% /LIBPATH:".\lib\freetype\win64" user32.lib kernel32.lib gdi32.lib openGL32.lib glew32.lib freetype.lib
