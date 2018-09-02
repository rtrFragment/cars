# Text Rendering

###### Dependency

-   We need FreeType library, it is available in `lib/freetype` folder. The `build.bat` file is also modified to use this path while compiling. Right now it configured to build `x64` version, if you want to build `x86` version, then modify the build file to point to `.\lib\freetype\win32` folder for 32-bit free type lib.

###### How to compile

-   First compile the resource file.

```
set root=%CD%
cd resources
rc.exe /V resource.rc
cd %root%
```

-   Compile the x64 version

```
cl.exe /EHsc /DUNICODE /Zi /I %GLEW_PATH%\include /I ".\lib\freetype\include" /Fe:font *.cpp /link resources\resource.res /LIBPATH:%GLEW_LIB_PATH% /LIBPATH:".\lib\freetype\win64" user32.lib kernel32.lib gdi32.lib openGL32.lib glew32.lib freetype.lib
```

-   Compile the x86 version

```
cl.exe /EHsc /DUNICODE /Zi /I %GLEW_PATH%\include /I ".\lib\freetype\include" /Fe:font *.cpp /link resources\resource.res /LIBPATH:%GLEW_LIB_PATH% /LIBPATH:".\lib\freetype\win32" user32.lib kernel32.lib gdi32.lib openGL32.lib glew32.lib freetype.lib
```

###### Keyboard shortcuts

-   Press `Esc` key to quit.
-   Press `1` to `9` key to increase the speed.
-   Press `f` key to toggle fullscreen mode.
-   Press `a` key to toggle animation.
-   Press `l` key to toggle lighting.

###### Preview

-   Pyramid Light Disabled

    ![pyramidLightDisabled][pyramid-light-disabled-image]

-   Pyramid Light Enabled

    ![pyramidLightEnabled][pyramid-light-enabled-image]

[//]: # "Image declaration"
[pyramid-light-disabled-image]: ./preview/pyramidLightDisabled.png "Pyramid Light Disabled"
[pyramid-light-enabled-image]: ./preview/pyramidLightEnabled.png "Pyramid Light Enabled"
