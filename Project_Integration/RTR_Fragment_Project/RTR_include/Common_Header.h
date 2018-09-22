#pragma once
#include <windows.h>
#include <windowsx.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Obj_Loader.h"
#include "camera.h"
#include "../RTR_lib/audioManager/audioManager.h"
#include "../RTR_lib/audioManager/soundSource.h"
#include"../RTR_lib/logger/logger.h"


#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"kernel32.lib")

#define GLM_ENABLE_EXPERIMENTAL

HWND ghwnd;
HDC ghdc;
HGLRC ghrc;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbActiveWindow = false;
bool gbFullscreen = false;
bool gbIsEscapeKeyPressed = false;
bool gbAnimate = false;
bool gbLight = false;
bool gbIsAKeyPressed = false;
bool gbIsLKeyPressed = false;
bool FirstMouse = true;
