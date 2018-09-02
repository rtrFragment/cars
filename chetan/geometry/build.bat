set root=%CD%
cd resources
rc.exe /V resource.rc
cd %root%

cl.exe /EHsc /DUNICODE /Fe:main.exe /Zi /I %GLEW_PATH%\include /I %GLM_PATH% *.cpp /link resources\resource.res /LIBPATH:%GLEW_LIB_PATH% /LIBPATH:".\lib" user32.lib kernel32.lib gdi32.lib openGL32.lib glew32.lib
