set root=%CD%
cd resources
rc.exe /V resource.rc
cd %root%

cl.exe /EHsc /DUNICODE /Zi /I %GLEW_PATH%\include /I %FREETYPE_PATH%\include /Fe:font *.cpp /link resources\resource.res /LIBPATH:%GLEW_LIB_PATH% /LIBPATH:%FREETYPE_LIB_PATH% user32.lib kernel32.lib gdi32.lib openGL32.lib glew32.lib freetype.lib
