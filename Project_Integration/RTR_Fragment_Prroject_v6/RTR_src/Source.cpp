
#include"../RTR_include/Scene1.h"
#include"../RTR_include/CommonHeaer_Secne2.h"
#include "../RTR_include/Scene3.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void ToggleFullscreen(void);
	void display(void);
	void update(void);
	void uninitialize(int);
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("My App");
	bool bDone = false;

	if (!Logger::initialize("debug.log"))
	{
		MessageBox(NULL, TEXT("Cannot Create Log File !!!"), TEXT("Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, TEXT("The Ultimate Juggad"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		logError("Cannot Create Window...\n");
		uninitialize(EXIT_FAILURE);
	}

	ghwnd = hwnd;

	ShowWindow(hwnd, iCmdShow);
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);

	initialize();

	//MessageBox(hwnd, TEXT("After init"), TEXT("MSG"), MB_OK);

	ToggleFullscreen();
	ShowCursor(FALSE);

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				if (gbIsEscapeKeyPressed == true)
					bDone = true;
				if (gbAnimate == true)
					update();
				display();
			}
		}
	}

	uninitialize(EXIT_SUCCESS);
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void resize(int, int);
	void MouseMovement(double xpos, double ypos);
	void ToggleFullscreen(void);

	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);

	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;
		break;
	case WM_CREATE:
		break;
	case WM_SIZE:

		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		/*if (GetAsyncKeyState(VK_DOWN))
		{
			Scene1_camera.MoveCamera(CameraMoveOnZ, 0.06f, deltaTime);
			Scene1_camera_Z_counter--;

			if (g_scene3_bShowScene3)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::BACKWARD, deltaTime + 5.0f);
		}
		if (GetAsyncKeyState(VK_UP))
		{
			Scene1_camera.MoveCamera(CameraMoveOnZ, -0.06f, deltaTime);
			Scene1_camera_Z_counter++;

			if (g_scene3_bShowScene3)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::FORWARD, deltaTime + 5.0f);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			Scene1_camera.MoveCamera(CameraMoveOnX, 0.1f, deltaTime);

			if (g_scene3_bShowScene3)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::RIGHT, deltaTime + 5.0f);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			Scene1_camera.MoveCamera(CameraMoveOnX, -0.1f, deltaTime);

			if (g_scene3_bShowScene3)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::LEFT, deltaTime + 5.0f);
		}*/
		switch (wParam)
		{
		/*case 0x41:
			//isTranslateY = true;
			//gfTranslate_X = gfTranslate_X + 10.0f;
			//break;
			blackout -= 0.1f;
			break;
		case 0x42:
			//gfTranslate_X = gfTranslate_X - 10.0f;
			//break;
			//gbScene3_Car_Update_Flag = true;
		    //blackout += 0.1f;
			break;
		case 0x43:
			gfTranslate_Z = gfTranslate_Z + 10.0f;
			break;
		case 0x44:
			gfTranslate_Z = gfTranslate_Z - 10.0f;
			break;
			*/
		/*case 0x41:
			logInfo("Scene1_camera_Z_counter : %d\n", Scene1_camera_Z_counter);
			break;

		case 0x42:
			Scene1_camera.MoveCamera(CameraMoveOnY, -0.1f, deltaTime);
			break;

		case VK_UP:
			gfTranslate_Z= gfTranslate_Z - 10.0f;
			break;

		case VK_DOWN:
			gfTranslate_Z= gfTranslate_Z + 10.0f;
			break;

		case VK_LEFT:
			gfTranslate_X= gfTranslate_X - 10.0f;
			break;

		case VK_RIGHT:
			gfTranslate_X= gfTranslate_X + 10.0f;
			break;

		case 0x41:
			gfTranslate_Y = gfTranslate_Y - 1.0f;
			break;

		case 0x42:
			gfTranslate_Y = gfTranslate_Y + 1.0f;
			break;
*/
		case 0x50:
			logInfo("\nHrishi : Translate X : %f Translate Y : %f Translate Z : %f\n", gfTranslate_X, gfTranslate_Y, gfTranslate_Z);
			//logInfo("\nHrishi : Translate X : %f Translate Y : %f Translate Z : %f\n", gfTranslate_X, gfTranslate_Y, gfTranslate_Z);
			break;

		case VK_ESCAPE:
			gbIsEscapeKeyPressed = true;
			break;
		case 0x46:
			if (gbFullscreen == false)
			{
				ToggleFullscreen();
				gbFullscreen = true;
			}
			else
			{
				ToggleFullscreen();
				gbFullscreen = false;
			}
			break;

		case VK_TAB:

			if (gbIsAKeyPressed == false)
			{
				gbAnimate = true;
				gbIsAKeyPressed = true;
			}
			else
			{
				gbAnimate = false;
				gbIsAKeyPressed = false;
			}

			if (gbIsLKeyPressed == false)
			{
				gbLight = true;
				gbIsLKeyPressed = true;

				if (Scene1_soundSourcePointLight != NULL)
				{
					Scene1_soundSourcePointLight->play(Scene1_audioBufferIdPointLight);
				}
			}
			else
			{
				gbLight = false;
				gbIsLKeyPressed = false;
			}
			//g_scene3_bShowScene3 = true;
			break;

		case VK_SPACE:
			/*if ((g_scene2_bGoToScene3 == false) & (g_scene1_bShowScene1 == false))
				g_scene2_bGoToScene3 = true;*/
			if ((g_scene2_bBeginFadeOut == false) & (g_scene1_bShowScene1 == false))
				g_scene2_bBeginFadeOut = true;
			break;

		}
		break;
	case WM_MOUSEMOVE:
		/*if (g_scene3_bShowScene3)
		{
			xPos = GET_X_LPARAM(lParam);
			yPos = GET_Y_LPARAM(lParam);
			MouseMovement((double)xPos, (double)yPos);
		}*/

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void initialize(void)
{
	void resize(int, int);
	void initializeObjects(void);
	void uninitialize(int);
	void LoadModel(char *, std::vector<float>, std::vector<float>, std::vector<float>);
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		logError("GetDC() Failed.\n");
		uninitialize(EXIT_FAILURE);
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		logError("ChoosePixelFormat() Failed.\n");
		uninitialize(EXIT_FAILURE);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		logError("SetPixelFormat() Failed.\n");
		uninitialize(EXIT_FAILURE);
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		logError("wglCreateContext() Failed.\n");
		uninitialize(EXIT_FAILURE);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		logError("wglMakeCurrent() Failed\n");
		uninitialize(EXIT_FAILURE);
	}

	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	Init_Scene1();
	Scene2_Initialize();
	Init_Scene3();

	QueryPerformanceFrequency((LARGE_INTEGER*)&initFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&initTime);

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void MouseMovement(double xpos, double ypos)
{


	if (FirstMouse)
	{
		lastX = (GLfloat)xpos;
		lastY = (GLfloat)ypos;
		FirstMouse = false;
	}

	GLfloat xoffset = (GLfloat)xpos - lastX;
	GLfloat yoffset = lastY - (GLfloat)ypos;

	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;

	//Scene1_camera.ProcessMouseMovement(xoffset, yoffset);
	Scene3_camera.ProcessMouseMovement(xoffset, yoffset);
	if (lastX != (float)midX || lastY != (float)midY)
		SetCursorPos(midX, midY);

	lastX = (float)midX;
	lastY = (float)midY;
}


void display(void)
{
	float getTime(void);

	currentFrame = getTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if(g_scene1_bShowScene1==true)
		Display_Scene1();

	if(g_scene2_bShowScene2==true)
		Scene2_Display();

	if (g_scene3_bShowScene3 == true)
	{
		Draw_Scene3();
	}

	SwapBuffers(ghdc);
}

void update(void)
{
	// Scene1_audioManager->setListenerPosition(camera.Position[0], camera.Position[1], camera.Position[2]);

	if (g_scene1_bShowScene1 == true)
		Update_Scene1();

	if (g_scene2_bShowScene2 == true)
		Scene2_Update();

	if (g_scene3_bShowScene3 == true)
	{
		Scene3_Update();
	}
}

float getTime(void)
{
	float time = (float)(QueryPerformanceCounter((LARGE_INTEGER*)&changingTime) - initTime) / initFrequency;
	return(time);
}

void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	Scene1_gPerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100000.0f);
	gPerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100000.0f);

	currentWidth = width;
	currentHeight = height;
	//if (g_scene2_bShowScene2 == true)
	g_scene2_1_PerspectiveProjectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100000.0f);

	g_Scene3_Ocean_PerspectiveProjectionMatrix = g_Scene3_CityModel_PerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100000.0f);

	Scene3_resize(width, height);
}

void ToggleFullscreen(void)
{
	MONITORINFO mi = { sizeof(MONITORINFO) };
	if (gbFullscreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}

	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

void uninitialize(int i_Exit_Flag)
{
	if (gbFullscreen == false)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	Uninitialize_Scene1();
	Scene2_UnInitialize(i_Exit_Flag);
	Uninitialize_Scene3();

	//Stray call to glUseProgram(0)
	glUseProgram(0);

	wglMakeCurrent(NULL, NULL);

	if (ghrc != NULL)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if (ghdc != NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (i_Exit_Flag == EXIT_FAILURE)
	{
		logError("Program exited erroneously\n");
	}

	Logger::close();
	DestroyWindow(ghwnd);
}
