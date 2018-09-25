#include<windows.h>
#include<windowsx.h>
#include<C:\glew\include\GL\glew.h>
#include<gl/GL.h>
#include<stdio.h>

#include<vector>
#include<stdlib.h>
#include"Obj_Loader.h"

#include "Scene3.h"

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"GDI32.lib")
#pragma comment(lib,"C:\\glew\\lib\\Release\\x64\\glew32.lib")
#pragma comment(lib,"opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


#define MODEL_X_SCALE_FACTOR	1.5f	//X-scale factor of MODEL
#define MODEL_Y_SCALE_FACTOR	1.5f	//Y-scale factor of MODEL
#define MODEL_Z_SCALE_FACTOR	1.5f	//Z-scale factor of MODEL

#define START_ANGLE_POS			0.0f	//Marks beginning angle position of rotation
#define END_ANGLE_POS			360.0f	//Marks terminating angle position rotation
#define MODEL_ANGLE_INCREMENT	0.1f	//Increment angle for MODEL


HWND ghwnd;
HDC ghdc;
HGLRC ghrc;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbActiveWindow = false;
bool gbFullscreen = false;
bool gbIsEscapeKeyPressed = false;


bool gbAnimate = false;
bool gbIsAKeyPressed = false;
bool gbIsLKeyPressed = false;


GLfloat g_rotate;

//for camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


float lastX = WIN_WIDTH / 2.0f;
float lastY = WIN_HEIGHT / 2.0f;

bool FirstMouse = true;
float deltaTime = 20.0f;
float _yaw = -90.0f;
float _pitch = 0.0f;


float midX = WIN_WIDTH / 2.0f;
float midY = WIN_HEIGHT / 2.0f;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void display(void);
	void update(void);
	void uninitialize(int);
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("My App");
	bool bDone = false;

	/*if (fopen_s(&gpFile, "Log.txt", "w") != NULL)
	{
		MessageBox(NULL, TEXT("Cannot Create Log File !!!"), TEXT("Error"), MB_OK);
		exit(EXIT_FAILURE);
	}
	else*/
	fopen_s(&gpFile, "Log.txt", "w");
		fprintf(gpFile, "Log File Created Successfully...\n");
		fclose(gpFile);

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

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, TEXT("OpenGLPP : 3D Rotation"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "Cannot Create Window...\n");
		fclose(gpFile);
		uninitialize(1);
	}

	ghwnd = hwnd;

	ShowWindow(hwnd, iCmdShow);
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);

	initialize();

	MessageBox(hwnd, TEXT("After init"), TEXT("MSG"), MB_OK);

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

	uninitialize(0);
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void resize(int, int);
	void ToggleFullscreen(void);
	void MouseMovement(double xpos, double ypos);

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
	case WM_MOUSEMOVE:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		MouseMovement((double)xPos, (double)yPos);
		break;
	case WM_KEYDOWN:
		if (GetAsyncKeyState(0x25))
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}

		if (GetAsyncKeyState(VK_UP))
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}

		switch (wParam)
		{
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

		case 0x4C:
			if (gbIsLKeyPressed == false)
			{
				gbLight = true;
				gbIsLKeyPressed = true;
			}
			else
			{
				gbLight = false;
				gbIsLKeyPressed = false;
			}
			break;

		case 0x41://a
			//lightPosition[0] = lightPosition[0] - 1.0f;
			LIGHT_X_TRANSLATE -= 1.0f;
			break;

		case 0x44://d
			//lightPosition[0] = lightPosition[0] + 1.0f;
			LIGHT_X_TRANSLATE += 1.0f;
			break;

		case 0x53://s
			//lightPosition[2] = lightPosition[2] + 1.0f;
			LIGHT_Y_TRANSLATE += 1.0f;
			break;

		case 0x57://w
			LIGHT_Y_TRANSLATE -= 1.0f;
			//lightPosition[2] = lightPosition[2] - 1.0f;
			break;

		case 0x45://e
			LIGHT_Z_TRANSLATE -= 1.0f;
		//	lightPosition[1] = lightPosition[1] - 1.0f;
			break;

		case 0x51://q
			LIGHT_Z_TRANSLATE += 1.0f;
			//lightPosition[1] = lightPosition[1] + 1.0f;
			break;

		case 0x50://p
			fopen_s(&gpFile, "Log.txt", "a+");
			//fprintf(gpFile, "Light Pos X : %f\t Y : %f\t Z : %f\n", lightPosition[0], lightPosition[1], lightPosition[2]);
			fprintf(gpFile, "Light Pos X : %f\t Y : %f\t Z : %f\n", LIGHT_X_TRANSLATE, LIGHT_Y_TRANSLATE, LIGHT_Z_TRANSLATE);
			fclose(gpFile);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void MouseMovement(double xpos, double ypos)
{
	if (FirstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		FirstMouse = false;
	}

	GLfloat xoffset = (float)xpos - lastX;
	GLfloat yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
	if (lastX != (float)midX || lastY != (float)midY)
		SetCursorPos(midX, midY);

	lastX = (float)midX;
	lastY = (float)midY;

}

void initialize(void)
{
	void resize(int, int);
	void uninitialize(int);
	void ToggleFullscreen(void);

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
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "GetDC() Failed.\n");
		fclose(gpFile);
		uninitialize(1);
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "ChoosePixelFormat() Failed.\n");
		fclose(gpFile);
		uninitialize(1);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "SetPixelFormat() Failed.\n");
		fclose(gpFile);
		uninitialize(1);
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "wglCreateContext() Failed.\n");
		fclose(gpFile);
		uninitialize(1);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "wglMakeCurrent() Failed");
		fclose(gpFile);
		uninitialize(1);
	}

	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}


	MessageBox(ghwnd, TEXT("Before LoadMeshData"), TEXT("MSG"), MB_OK);
	
	Init_Scene3();
	
	//glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glClearColor(0.75f, 0.75f, 0.75f, 0.0f);

	g_Scene3_CityModel_PerspectiveProjectionMatrix = glm::mat4();

	gWidth = WIN_WIDTH;
	gHeight = WIN_HEIGHT;

	camera = Camera(cameraPos, cameraUp, _yaw, _pitch);
	resize(WIN_WIDTH, WIN_HEIGHT);
	ToggleFullscreen();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	Draw_Scene3();

	SwapBuffers(ghdc);
}

void update(void)
{
	g_rotate = g_rotate + MODEL_ANGLE_INCREMENT;
	if (g_rotate >= END_ANGLE_POS)
		g_rotate = START_ANGLE_POS;
}



void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	gWidth = width;
	gHeight = height;
	g_Scene3_CityModel_PerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);
	//g_Scene3_CityModel_PerspectiveProjectionMatrix = glm::perspective(camera.Zoom, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);
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
	void uninitializeGrass(void);

	if (gbFullscreen == false)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	Uninitialize_Scene3();

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

	if (i_Exit_Flag == 0)
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "Log File Closed Successfully");
		fclose(gpFile);
	}
	else if (i_Exit_Flag == 1)
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "Log File Closed Erroniously");
		fclose(gpFile);
	}

	fclose(gpFile);
	gpFile = NULL;

	DestroyWindow(ghwnd);
}

