#include <windows.h>
#include <windowsx.h>
#include <stdio.h> 
#include <gl/glew.h> 
#include <gl/GL.h>

#include "glm/glm.hpp" 
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.h"


#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//using namespace vmath;

enum
{
	ASHARSH_ATTRIBUTE_VERTEX = 0,
	ASHARSH_ATTRIBUTE_COLOR,
	ASHARSH_ATTRIBUTE_NORMAL,
	ASHARSH_ATTRIBUTE_TEXTURE,
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

FILE *gpFile = NULL;

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullscreen = false;
bool FirstMouse = true;

GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLuint gShaderProgramObject;

GLfloat viewTranslateOnX = 0.0f;
GLfloat viewTranslateOnY = 0.0f;
GLfloat viewTranslateOnZ = 0.0f;

GLfloat lastX = WIN_WIDTH / 2.0;
GLfloat lastY = WIN_HEIGHT / 2.0;

glm::vec3 cameraPosition;
glm::vec3 cameraTarget;
glm::vec3 cameraUP;

Camera  camera;

GLfloat deltaTime = 0.0f;

GLuint gVao_Pyramid;
GLuint gVbo_Position, gVbo_Color;
GLuint gMVPUniform;

glm::mat4 gPerspectiveProjectionMatrix;

uint64_t initTime, initFrequency, changingTime;

GLfloat currentFrame = 0.0f, lastFrame = 0.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void uninitialize(void);
	void display(void);

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("OpenGL Programable Pipeline");
	bool bDone = false;

	if (fopen_s(&gpFile, "Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Log File Can Not Be Created\nExitting ..."), TEXT("Error"), MB_OK | MB_TOPMOST | MB_ICONSTOP);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Log File Is Successfully Opened.\n");
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szClassName,
		TEXT("OpenGL Programmable Cammera Controll"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	initialize();

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
			display();
			if (gbActiveWindow == true)
			{
				if (gbEscapeKeyIsPressed == true)
					bDone = true;
			}
		}
	}

	uninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void resize(int, int);
	void ToggleFullscreen(void);
	void uninitialize(void);
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
	case WM_ERASEBKGND:
		return(0);
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		if (GetAsyncKeyState(VK_UP))
		{
			camera.MoveCamera(CameraMoveOnZ, 0.1f, deltaTime);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			camera.MoveCamera(CameraMoveOnZ, -0.1f, deltaTime);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			camera.MoveCamera(CameraMoveOnX, 0.1f, deltaTime);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			camera.MoveCamera(CameraMoveOnX, -0.1f, deltaTime);
		}
		switch (wParam)
		{
			
		case VK_ESCAPE:
			if (gbEscapeKeyIsPressed == false)
				gbEscapeKeyIsPressed = true;
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
		case 0x58:
			break;

		/*case 0x25: 
			camera.MoveCamera(CameraMoveOnX, 0.1f , deltaTime);
			break;
		case 0x26: 
			camera.MoveCamera(CameraMoveOnZ, 0.1f , deltaTime);
			break;
		case 0x27: 
			camera.MoveCamera(CameraMoveOnX, -0.1f , deltaTime);
			break;
		case 0x28:
			camera.MoveCamera(CameraMoveOnZ, -0.1f , deltaTime);
			break;*/

		case 0x20:
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		break;
	case WM_MOUSEMOVE:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		MouseMovement((double)xPos, (double)yPos);
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_CLOSE:
		uninitialize();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void MouseMovement(double xpos, double ypos)
{
	if (FirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		FirstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void ToggleFullscreen(void)
{
	MONITORINFO mi;
	if (gbFullscreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };
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
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

void initialize(void)
{
	void uninitialize(void);
	void resize(int, int);

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;
	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == false)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (wglMakeCurrent(ghdc, ghrc) == false)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 440" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec4 vColor;" \
		"out vec4 out_Color;" \
		"uniform mat4 u_mvp_matrix;" \
		"void main(void)" \
		"{" \
		"gl_Position = u_mvp_matrix * vPosition;" \
		"out_Color = vColor;" \
		"}";
	glShaderSource(gVertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	glCompileShader(gVertexShaderObject);
	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;
	glGetShaderiv(gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 440" \
		"\n" \
		"in vec4 out_Color;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = out_Color;" \
		"}";
	glShaderSource(gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(gFragmentShaderObject);
	glGetShaderiv(gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	gShaderProgramObject = glCreateProgram();
	glAttachShader(gShaderProgramObject, gVertexShaderObject);
	glAttachShader(gShaderProgramObject, gFragmentShaderObject);
	glBindAttribLocation(gShaderProgramObject, ASHARSH_ATTRIBUTE_VERTEX, "vPosition");
	glLinkProgram(gShaderProgramObject);
	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);

	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	gMVPUniform = glGetUniformLocation(gShaderProgramObject, "u_mvp_matrix");

	const GLfloat pyramidVertices[] =
	{
		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,

		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f
	};

	const GLfloat pyramidColors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};


	glGenVertexArrays(1, &gVao_Pyramid);
	glBindVertexArray(gVao_Pyramid);

	glGenBuffers(1, &gVbo_Color);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidColors), pyramidColors, GL_STATIC_DRAW);
	glVertexAttribPointer(ASHARSH_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ASHARSH_ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ASHARSH_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ASHARSH_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gPerspectiveProjectionMatrix = glm::mat4(1.0f);
	cameraPosition = glm::vec3(0.0f, 0.0f, -6.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = Camera(cameraPosition, cameraTarget, cameraUP);

	QueryPerformanceFrequency((LARGE_INTEGER*)&initFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&initTime);

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void display(void)
{
	float getTime(void);
	
	currentFrame = getTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(gShaderProgramObject);

	glm::mat4 modelViewProjectionMatrix = glm::mat4(1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 modelViewMatrix = glm::mat4(1.0f);
	
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = camera.getViewMatrix();

	modelViewProjectionMatrix = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	modelViewMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -6.0f));
	modelViewMatrix = viewMatrix * modelMatrix;
	modelViewProjectionMatrix = glm::mat4(1.0f);

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;
	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
	glBindVertexArray(gVao_Pyramid);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);

	modelViewProjectionMatrix = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	modelViewMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -6.0f));
	modelViewMatrix = viewMatrix * modelMatrix;
	modelViewProjectionMatrix = glm::mat4(1.0f);

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;
	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
	glBindVertexArray(gVao_Pyramid);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);

	modelViewProjectionMatrix = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	modelViewMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(3.0f, 0.0f, -6.0f));
	modelViewMatrix = viewMatrix * modelMatrix;
	modelViewProjectionMatrix = glm::mat4(1.0f);

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;
	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
	glBindVertexArray(gVao_Pyramid);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.0f, 4.0f, -9.0f));
	modelViewMatrix = viewMatrix * modelMatrix;
	modelViewProjectionMatrix = glm::mat4(1.0f);

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;
	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
	glBindVertexArray(gVao_Pyramid);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);


	glUseProgram(0);
	SwapBuffers(ghdc);
}

void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	gPerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

float getTime(void)
{
	float time = (float)(QueryPerformanceCounter((LARGE_INTEGER*)&changingTime) - initTime) / initFrequency;
	return(time);
}

void uninitialize(void)
{
	if (gbFullscreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
	if (gVao_Pyramid)
	{
		glDeleteVertexArrays(1, &gVao_Pyramid);
		gVao_Pyramid = 0;
	}
	if (gVbo_Position)
	{
		glDeleteBuffers(1, &gVbo_Position);
		gVbo_Position = 0;
	}
	if (gVbo_Color)
	{
		glDeleteBuffers(1, &gVbo_Color);
		gVbo_Color = 0;
	}
	glDetachShader(gShaderProgramObject, gVertexShaderObject);
	glDetachShader(gShaderProgramObject, gFragmentShaderObject);
	glDeleteShader(gVertexShaderObject);
	gVertexShaderObject = 0;
	glDeleteShader(gFragmentShaderObject);
	gFragmentShaderObject = 0;
	glDeleteProgram(gShaderProgramObject);
	gShaderProgramObject = 0;
	glUseProgram(0);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ghrc);
	ghrc = NULL;
	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;

	if (gpFile)
	{
		fprintf(gpFile, "Log File Is Successfully Closed.\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
