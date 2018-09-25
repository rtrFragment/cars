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
//#include "Obj_Loader.h"
#include"Obj_Loader1.h"
#include"Read_Mtl.h"
#include"Arrange_Material.h"
#include "camera.h"
//#include "Camera_2.h"

#include"../RTR_lib/fontRenderer/fontRenderer.h"
#include "../RTR_lib/audioManager/audioManager.h"
#include "../RTR_lib/audioManager/soundSource.h"
#include"../RTR_lib/logger/logger.h"



#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"openal32.lib")
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

glm::vec3 Scene1_cameraPosition;
glm::vec3 Scene1_cameraTarget;
glm::vec3 Scene1_cameraUP;
Camera Scene1_camera;

bool gbScene1_BlackOut_Flag = false;
GLfloat gfBlackOut = 1.0f;


extern bool g_scene1_bShowScene1 = false;

extern bool g_scene2_bShowScene2 = false;
extern bool g_scene2_1_PlayAudio = false;

extern bool g_scene3_bShowScene3 = false;

extern AudioManager *Scene1_audioManager = NULL;

extern GLfloat currentWidth = 0;
extern GLfloat currentHeight = 0;

void CommonHeader_InitializeAudioManager()
{
	Scene1_audioManager = new AudioManager();
	ALboolean Scene1_audioManagerrInitialize = Scene1_audioManager->initialize();

	if (!Scene1_audioManagerrInitialize)
	{
		logError("Not able to initialize audio manager.\n");
	}
}

