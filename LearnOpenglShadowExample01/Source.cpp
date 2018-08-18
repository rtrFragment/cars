#include <windows.h>
#include <windowsx.h> //For GET_X_LPARAM and GET_Y_LPARAM

#include <stdio.h> // for FILE I/O

#include <gl\glew.h>//use it before other GL.h

#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//here using glm library instead of vmath library

#include "vmath.h"
#include "camera.h" 
//#include "cameraLearnOpengl.h"

#include "Header.h"
#include "Sphere.h"
#include "Obj_Loader.h"


#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"Sphere.lib")

//using namespace vmath;
//char gszLogFileName[] = "Log.txt";

const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
enum
{
	MALATI_ATTRIBUTE_VERTEX = 0,
	MALATI_ATTRIBUTE_COLOR,
	MALATI_ATTRIBUTE_NORMAL,
	MALATI_ATTRIBUTE_TEXTURE
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//FILE *gpFile = NULL;

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullscreen = false;

GLuint gVertexShaderObjectShader;
GLuint gFragmentShaderObjectShader;
GLuint gShaderProgramObjectShader;

GLuint gVertexShaderObjectSimpleDepthShader;
GLuint gFragmentShaderObjectSimpleDepthShader;
GLuint gShaderProgramObjectSimpleDepthShader;

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

//Shadow Mapping Uniform
GLuint gdiffuseTextureUniform;
GLuint gshadowMapUniform;
GLuint glightPosUniform;
GLuint gviewPosUniform;
GLuint gprojectionUniform;
GLuint gviewUniform;
GLuint gmodelUniform;
GLuint glightSpaceMatrixUniform;

//SimpleDepthShader Uniform
GLuint glightSpaceMatrixSimpleDepthShaderUniform;
GLuint gmodelSimpleDepthShaderUniform;

GLuint planeVAO;
GLuint planeVBOposition;
GLuint planeVBOnormal;
GLuint planeVBOtexture;

GLuint gVao_sphere;
GLuint gVbo_sphere_position;
GLuint gVbo_sphere_normal;
GLuint gVbo_sphere_texture;
GLuint gVbo_sphere_element;

GLuint gNumElements;
GLuint gNumVertices;
float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLuint cubeVAO;
GLuint cubeVBOposition;
GLuint cubeVBOnormal;
GLuint cubeVBOtexture;

GLuint depthMapFBO;
GLuint depthMap;
GLuint woodTexture;


glm::mat4 gPerspectiveProjectionMatrix;
//vmath::mat4 gPerspectiveProjectionMatrix;
//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool FirstMouse = true;

GLfloat lastX = (float)SCR_WIDTH / 2.0;
GLfloat lastY = (float)SCR_HEIGHT / 2.0;

float xLightPosMove = -2.0f;
float yPositionMove = 1.5f;
float xPositionMove = 0.0f;
float zPositionMove = -3.0f;

std::vector<float> gv_vertices_1, gv_textures_1, gv_normals_1;

GLuint gVao_Car_1;
GLuint gVbo_Position, gVbo_Normal, gVbo_Texture;
int count_of_vertices_car_1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function prototype
	void initialize(void);
	void uninitialize(void);
	void display(void);
	//void Update(void);

	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("OpenGLPP");
	bool bDone = false;

	//code
	fopen_s(&gpFile, gszLogFileName, "w");
	fprintf_s(gpFile, "Log File Is Successfully Opened.\n");
	fclose(gpFile);

	//initializing members of struct WNDCLASSEX
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
	//Registering Class
	RegisterClassEx(&wndclass);

	//Create Window
	//Parallel to glutInitWindowSize(), glutInitWindowPosition() and glutCreateWindow() all three together
	hwnd = CreateWindow(szClassName,
		TEXT("OpenGL Programmable Pipeline Window"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		SCR_WIDTH,
		SCR_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//initialize
	initialize();

	//Message Loop
	while (bDone == false) //Parallel to glutMainLoop();
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
			// rendring function
			display();
			//Update();
			if (gbActiveWindow == true)
			{
				if (gbEscapeKeyIsPressed == true) //Continuation to glutLeaveMainLoop();
					bDone = true;
			}
		}
	}

	uninitialize();

	return((int)msg.wParam);
}

//WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function prototype
	void resize(int, int);
	void ToggleFullscreen(void);
	void uninitialize(void);

	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	void MouseMovement(double xpos, double ypos);

	static bool bIsAKeyPressed = false;
	static bool bIsLKeyPressed = false;
	
	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0) //if 0, the window is active
			gbActiveWindow = true;
		else //if non-zero, the window is not active
			gbActiveWindow = false;
		break;
	case WM_ERASEBKGND:
		return(0);
	case WM_SIZE: //Parallel to glutReshapeFunc();
		resize(LOWORD(lParam), HIWORD(lParam)); //Parallel to glutReshapeFunc(resize);
		break;
	case WM_MOUSEMOVE:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		MouseMovement((double)xPos, (double)yPos);
		break;
	case WM_KEYDOWN: //Parallel to glutKeyboardFunc();
		switch (wParam)
		{
		case VK_ESCAPE: //case 27
			if (gbEscapeKeyIsPressed == false)
				gbEscapeKeyIsPressed = true; //Parallel to glutLeaveMainLoop();
			break;
		case WM_MOUSEWHEEL:
			
			break;
		case 0x41://A
			zPositionMove += 0.1f;
			break;
		case 0x42://B
			zPositionMove -= 0.1f;
			break;
		case 0x43://C
			xLightPosMove += 0.1f;
			break;
		case 0x44://D
			xLightPosMove -= 0.1f;
			break;
		case 0x46: //for 'f' or 'F'
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
		case VK_RIGHT:
			
			xPositionMove += 0.1f;
			break;
		case VK_LEFT:
			
			xPositionMove -= 0.1f;
			break;
		case VK_UP:
			yPositionMove += 0.1f;
			break;
		case VK_DOWN:
			yPositionMove -= 0.1f;
			break;
		/*case 0x25: //%
			camera.MoveCamera(CameraMoveOnX, 0.1f);
			break;
		case 0x26:
			camera.MoveCamera(CameraMoveOnZ, 0.1f);
			break;
		case 0x27:
			camera.MoveCamera(CameraMoveOnX, -0.1f);
			break;
		case 0x28:
			camera.MoveCamera(CameraMoveOnZ, -0.1f);
			break;*/
		default:
			break;
		}
		break;
	case WM_LBUTTONDOWN:  //Parallel to glutMouseFunc();
		break;
	case WM_CLOSE: //Parallel to glutCloseFunc();
		uninitialize(); //Parallel to glutCloseFunc(uninitialize);
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
	//variable declarations
	MONITORINFO mi;

	//code
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
		//code
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}
}

//FUNCTION DEFINITIONS
void initialize(void)
{
	void ShadowMappingShaderBuildNCompileShader();
	void SimpleDepthShaderBuildNCompileShader();
	
	void uninitialize(void);
	void resize(int, int);

	int LoadGLTextures(GLuint *, TCHAR[]);
	void GenerateDepthMap(void);

	void DrawPlane();
	void DrawSphere();
	void DrawCar();
	void DrawCube();

	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//Initialization of structure 'PIXELFORMATDESCRIPTOR'
	//Parallel to glutInitDisplayMode()
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

	//choose a pixel format which best matches with that of 'pfd'
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//set the pixel format chosen above
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == false)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//create OpenGL rendering context
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//make the rendering context created above as current n the current hdc
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
	fopen_s(&gpFile, gszLogFileName, "a+");
	fprintf_s(gpFile, "%s\n", glGetString(GL_VERSION));
	fprintf_s(gpFile, "Shading Lang Version : %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	fclose(gpFile);

	glEnable(GL_DEPTH_TEST);
	
	ShadowMappingShaderBuildNCompileShader();
	SimpleDepthShaderBuildNCompileShader();

	DrawPlane();
	//DrawSphere();
	DrawCube();
	//count_of_vertices_car_1 = LoadMeshData("resources/sls_amg.obj", gv_vertices_1, gv_textures_1, gv_normals_1);
	//DrawCar();

	// load textures
	// -------------
	LoadGLTextures(&woodTexture, MAKEINTRESOURCE(IDBITMAP_WOOD));
	
	// configure depth map FBO
	// -----------------------
	GenerateDepthMap();

	glUseProgram(gShaderProgramObjectShader);
	glUniform1i(gdiffuseTextureUniform, 0);
	glUniform1i(gshadowMapUniform, 1);

/*
	cameraPosition = glm::vec3(0.0f, 0.0f, -6.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = Camera(cameraPosition, cameraTarget, cameraUP);
	*/
	resize(SCR_WIDTH, SCR_HEIGHT);

}

void GenerateDepthMap(void)
{
//Create a framebuffer object for rendering depth map
glGenFramebuffers(1, &depthMapFBO);

//Create 2D texture that we'll use as framebuffer's depth buffer

//Create depth texture
glGenTextures(1, &depthMap);
//glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, depthMap);
glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

// attach depth texture as FBO's depth buffer
glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

glDrawBuffer(GL_NONE);
glReadBuffer(GL_NONE);
glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DrawPlane()
{

	float planeVertices[] = {
		// positions            // normals         // texcoords
		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};

	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);

	//position
	glGenBuffers(1, &planeVBOposition);

	glBindBuffer(GL_ARRAY_BUFFER, planeVBOposition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);


	glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(MALATI_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &planeVBOnormal);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBOnormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(MALATI_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(MALATI_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &planeVBOtexture);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBOtexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(MALATI_ATTRIBUTE_TEXTURE, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(MALATI_ATTRIBUTE_TEXTURE);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}
void DrawCar()
{
	/*****************VAO For Cube*****************/
	glGenVertexArrays(1, &gVao_Car_1);
	glBindVertexArray(gVao_Car_1);

	/*****************Cube Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, gv_vertices_1.size() * sizeof(float), &gv_vertices_1[0], GL_STATIC_DRAW);

	glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(MALATI_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Cube Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, gv_normals_1.size() * sizeof(float), &gv_normals_1[0], GL_STATIC_DRAW);

	glVertexAttribPointer(MALATI_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(MALATI_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glGenBuffers(1, &gVbo_Texture);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Texture);
	glBufferData(GL_ARRAY_BUFFER, gv_textures_1.size() * sizeof(float), &gv_textures_1[0], GL_STATIC_DRAW);

	glVertexAttribPointer(MALATI_ATTRIBUTE_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(MALATI_ATTRIBUTE_TEXTURE);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);
}

void DrawSphere()
{
	//Sphere sphere;
	getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
	gNumVertices = getNumberOfSphereVertices();
	gNumElements = getNumberOfSphereElements();



	glGenVertexArrays(1, &gVao_sphere);
	glBindVertexArray(gVao_sphere);

	//position
	glGenBuffers(1, &gVbo_sphere_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_sphere_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertices), sphere_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(MALATI_ATTRIBUTE_VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//normal
	glGenBuffers(1, &gVbo_sphere_normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_sphere_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normals), sphere_normals, GL_STATIC_DRAW);

	glVertexAttribPointer(MALATI_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(MALATI_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVbo_sphere_texture);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_sphere_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_textures), sphere_textures, GL_STATIC_DRAW);

	glVertexAttribPointer(MALATI_ATTRIBUTE_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(MALATI_ATTRIBUTE_TEXTURE);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &gVbo_sphere_element);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glBindVertexArray(0);
}

void DrawCube(void)
{
	float vertices[] = {
		// back face
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
															  // front face
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		 -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		// left face
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		// right face
		1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	    1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	    1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
	   -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	   -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		 // top face
		 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	};
	
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	glGenBuffers(1, &cubeVBOposition);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOposition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(MALATI_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &cubeVBOnormal);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOnormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(MALATI_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(MALATI_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &cubeVBOtexture);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOtexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(MALATI_ATTRIBUTE_TEXTURE, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(MALATI_ATTRIBUTE_TEXTURE);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void display(void)
{
	void renderScene(const GLuint &shader, GLuint &NewModel);
	glm::vec3 lightPos(xLightPosMove, 4.0f, -1.0f);
	//vmath::vec3 lightPos(xPosMove, 4.0f, -1.0f);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 7.5f;

	//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); 
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

	lightSpaceMatrix = lightProjection * lightView;

	// render scene from light's point of view
	glUseProgram(gShaderProgramObjectSimpleDepthShader);
	glUniformMatrix4fv(glightSpaceMatrixSimpleDepthShaderUniform, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, woodTexture);

	//glCullFace(GL_FRONT);
	renderScene(gShaderProgramObjectSimpleDepthShader, gmodelSimpleDepthShaderUniform);
	//glCullFace(GL_BACK);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// reset viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2. render scene as normal using the generated depth/shadow map  
	// --------------------------------------------------------------

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(gShaderProgramObjectShader);
	
	//gPerspectiveProjectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	gPerspectiveProjectionMatrix = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//glm::lookAt(Position, Position + Front, Up);
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 3.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	glm::mat4 view = camera.getViewMatrix();
	//glm::mat4 view = camera.GetViewMatrix();
	glUniformMatrix4fv(gprojectionUniform, 1, GL_FALSE, &gPerspectiveProjectionMatrix[0][0]);
	
	glUniformMatrix4fv(gviewUniform, 1, GL_FALSE, &view[0][0]);

	// set light uniforms
	glUniform3fv(gviewPosUniform, 1, &camera.Position[0]);
	glUniform3fv(glightPosUniform, 1, &lightPos[0]);
	glUniformMatrix4fv(glightSpaceMatrixUniform, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, woodTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	renderScene(gShaderProgramObjectShader, gmodelUniform);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	SwapBuffers(ghdc);


}

void renderScene(const GLuint &shader, GLuint &NewModel)
{
	void renderCube();
	void renderSphere();
	void renderPlane();
	void renderCar();

	glm::mat4 model;
	glUniformMatrix4fv(NewModel, 1, GL_FALSE, &model[0][0]);

	renderPlane();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(xPositionMove, yPositionMove, zPositionMove));
	model = glm::scale(model, glm::vec3(0.5f));
	glUniformMatrix4fv(NewModel, 1, GL_FALSE, &model[0][0]);
	
	renderCube();
	//renderCar();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.5f));
	glUniformMatrix4fv(NewModel, 1, GL_FALSE, &model[0][0]);
	renderCube();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.25f));
	glUniformMatrix4fv(NewModel, 1, GL_FALSE, &model[0][0]);
	renderCube();
}

void renderCar()
{
	glBindVertexArray(gVao_Car_1);

	glDrawArrays(GL_TRIANGLES, 0, count_of_vertices_car_1);

	glBindVertexArray(0);
}

void renderPlane()
{
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void renderSphere()
{
	glBindVertexArray(gVao_sphere);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
}

void renderCube()
{
	// render Cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

int LoadGLTextures(GLuint *texture, TCHAR imageResourceId[])
{
	HBITMAP hBitmap;
	BITMAP bmp;
	int iStatus = FALSE;
	glGenTextures(1, texture);
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap)
	{
		fopen_s(&gpFile, gszLogFileName, "a+");
		fprintf(gpFile, "Image Successfully Loaded.\n");
		fclose(gpFile);

		iStatus = TRUE;
		GetObject(hBitmap, sizeof(bmp), &bmp);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, *texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGB,
			bmp.bmWidth,
			bmp.bmHeight,
			0,
			GL_BGR,
			GL_UNSIGNED_BYTE,
			bmp.bmBits);

		glGenerateMipmap(GL_TEXTURE_2D);
		DeleteObject(hBitmap);
	}
	else
	{
		fopen_s(&gpFile, gszLogFileName, "a+");
		fprintf(gpFile, "Image loading Unsuccessfull.\n");
		fclose(gpFile);

	}
	return (iStatus);
}

//shadow_mapping
void ShadowMappingShaderBuildNCompileShader()
{
	fopen_s(&gpFile, gszLogFileName, "a+");
	fprintf(gpFile, "In ShadowMappingShaderBuildNCompileShader.\n");
	fclose(gpFile);

	void uninitialize();
	//VERTEX SHADE
	gVertexShaderObjectShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCodeShader =
		"#version 460" \
		"\n" \
		"layout (location = 0) in vec3 aPos;" \
		"layout (location = 2) in vec3 aNormal;" \
		"layout (location = 3) in vec2 aTexCoords;" \
		"out vec2 TexCoords;" \
		"out VS_OUT{" \
		"vec3 FragPos;" \
		"vec3 Normal;" \
		"vec2 TexCoords;" \
		"vec4 FragPosLightSpace;" \
		"} vs_out;" \
		"uniform mat4 projection;" \
		"uniform mat4 view;" \
		"uniform mat4 model;" \
		"uniform mat4 lightSpaceMatrix;" \
		"void main()" \
		"{" \
		"vs_out.FragPos = vec3(model * vec4(aPos, 1.0));" \
		"vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;" \
		"vs_out.TexCoords = aTexCoords;" \
		"vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);" \
		"gl_Position = projection * view * model * vec4(aPos, 1.0);" \
		"}";
	
	glShaderSource(gVertexShaderObjectShader, 1, (const GLchar **)&vertextShaderSourceCodeShader, NULL);

	//compile shader
	glCompileShader(gVertexShaderObjectShader);

	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(gVertexShaderObjectShader, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObjectShader, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObjectShader, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, gszLogFileName, "a+");
				fprintf(gpFile, "Vertex Shader Shadow Sampling Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);

				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	//FRAGMENT SHADER
	gFragmentShaderObjectShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCodeShader =
		"#version 460" \
		"\n" \
		"out vec4 FragColor;" \
		"in VS_OUT{" \
		"vec3 FragPos;" \
		"vec3 Normal;" \
		"vec2 TexCoords;" \
		"vec4 FragPosLightSpace;" \
		"} fs_in;" \
		"uniform sampler2D diffuseTexture;" \
		"uniform sampler2D shadowMap;" \
		"uniform vec3 lightPos;" \
		"uniform vec3 viewPos;" \
		"float ShadowCalculation(vec4 fragPosLightSpace)" \
		"{" \
		"vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;" \
		"projCoords = projCoords * 0.5 + 0.5; " \
		"float closestDepth = texture(shadowMap, projCoords.xy).r; " \
		"float currentDepth = projCoords.z;" \
		"vec3 normal = normalize(fs_in.Normal);" \
		"vec3 lightDir = normalize(lightPos - fs_in.FragPos);" \
		"float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);" \
		"float shadow = 0.0;" \
		"vec2 texelSize = 1.0 / textureSize(shadowMap, 0);" \
		"for (int x = -1; x <= 1; ++x)" \
		"{" \
		"for (int y = -1; y <= 1; ++y)" \
		"{" \
		"float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; " \
		"shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;" \
		"}" \
		"}" \
		"shadow /= 9.0;" \
		"if (projCoords.z > 1.0)" \
		"shadow = 0.0; " \
		"return shadow;" \
		"}" \

		"void main()" \
		"{" \
		"vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;" \
		"vec3 normal = normalize(fs_in.Normal);" \
		"vec3 lightColor = vec3(0.3);" \
		// ambient
		"vec3 ambient = 0.3 * color;" \
		// diffuse
		"vec3 lightDir = normalize(lightPos - fs_in.FragPos);" \
		"float diff = max(dot(lightDir, normal), 0.0);" \
		"vec3 diffuse = diff * lightColor;"\
		// specular
		"vec3 viewDir = normalize(viewPos - fs_in.FragPos);" \
		"vec3 reflectDir = reflect(-lightDir, normal); " \
		"float spec = 0.0;" \
		"vec3 halfwayDir = normalize(lightDir + viewDir);" \
		"spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);"\
		"vec3 specular = spec * lightColor;"\
		// calculate shadow
		"float shadow = ShadowCalculation(fs_in.FragPosLightSpace);"\
		"vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;"\

		"FragColor = vec4(lighting, 1.0);"\
		"}";

	glShaderSource(gFragmentShaderObjectShader, 1, (const GLchar **)&fragmentShaderSourceCodeShader, NULL);

	glCompileShader(gFragmentShaderObjectShader);

	glGetShaderiv(gFragmentShaderObjectShader, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObjectShader, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObjectShader, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, gszLogFileName, "a+");
				fprintf(gpFile, "Fragment Shader Shadow Sampling Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);

				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	//Shader Program

	gShaderProgramObjectShader = glCreateProgram();

	glAttachShader(gShaderProgramObjectShader, gVertexShaderObjectShader);

	glAttachShader(gShaderProgramObjectShader, gFragmentShaderObjectShader);

	glBindAttribLocation(gShaderProgramObjectShader, MALATI_ATTRIBUTE_VERTEX, "aPos");
	glBindAttribLocation(gShaderProgramObjectShader, MALATI_ATTRIBUTE_NORMAL, "aNormal");
	glBindAttribLocation(gShaderProgramObjectShader, MALATI_ATTRIBUTE_TEXTURE, "aTexCoords");

	glLinkProgram(gShaderProgramObjectShader);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObjectShader, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObjectShader, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObjectShader, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, gszLogFileName, "a+");
				fprintf(gpFile, "Shader Program Link Shadow Sampling Log : %s\n", szInfoLog);
				fclose(gpFile);

				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	gdiffuseTextureUniform = glGetUniformLocation(gShaderProgramObjectShader, "diffuseTexture");
	gshadowMapUniform = glGetUniformLocation(gShaderProgramObjectShader, "shadowMap");
	
	glightPosUniform = glGetUniformLocation(gShaderProgramObjectShader, "lightPos");
	gviewPosUniform = glGetUniformLocation(gShaderProgramObjectShader, "viewPos");
	
	gprojectionUniform = glGetUniformLocation(gShaderProgramObjectShader, "projection");
	gviewUniform = glGetUniformLocation(gShaderProgramObjectShader, "view");
	gmodelUniform = glGetUniformLocation(gShaderProgramObjectShader, "model");
	glightSpaceMatrixUniform = glGetUniformLocation(gShaderProgramObjectShader, "lightSpaceMatrix");
}

void SimpleDepthShaderBuildNCompileShader()
{
	fopen_s(&gpFile, gszLogFileName, "a+");
	fprintf(gpFile, "In SimpleDepthShaderBuildNCompileShader \n ");
	fclose(gpFile);

	void uninitialize();
	//VERTEX SHADE
	gVertexShaderObjectSimpleDepthShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCodeSimpleDepthShader =
		"#version 460" \
		"\n" \
		"layout (location = 0) in vec3 aPos;" \
		"uniform mat4 lightSpaceMatrix;" \
		"uniform mat4 model;" \
		"void main()" \
		"{" \
		"gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);" \
		"}";

	glShaderSource(gVertexShaderObjectSimpleDepthShader, 1, (const GLchar **)&vertextShaderSourceCodeSimpleDepthShader, NULL);

	//compile shader
	glCompileShader(gVertexShaderObjectSimpleDepthShader);

	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(gVertexShaderObjectSimpleDepthShader, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObjectSimpleDepthShader, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObjectSimpleDepthShader, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, gszLogFileName, "a+");
				fprintf(gpFile, "Vertex Shader SimpleDepthShader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	//FRAGMENT SHADER
	gFragmentShaderObjectSimpleDepthShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCodeSimpleDepthShader =
		"#version 460" \
		"\n" \
		"void main(void)" \
		"{" \
		"}";

	glShaderSource(gFragmentShaderObjectSimpleDepthShader, 1, (const GLchar **)&fragmentShaderSourceCodeSimpleDepthShader, NULL);

	glCompileShader(gFragmentShaderObjectSimpleDepthShader);

	glGetShaderiv(gFragmentShaderObjectSimpleDepthShader, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObjectSimpleDepthShader, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObjectSimpleDepthShader, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, gszLogFileName, "a+");
				fprintf(gpFile, "Fragment Shader SimpleDepthShader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);

				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	//Shader Program
	gShaderProgramObjectSimpleDepthShader = glCreateProgram();

	glAttachShader(gShaderProgramObjectSimpleDepthShader, gVertexShaderObjectSimpleDepthShader);
	glAttachShader(gShaderProgramObjectSimpleDepthShader, gFragmentShaderObjectSimpleDepthShader);

	glBindAttribLocation(gShaderProgramObjectSimpleDepthShader, MALATI_ATTRIBUTE_VERTEX, "aPos");

	glLinkProgram(gShaderProgramObjectSimpleDepthShader);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObjectSimpleDepthShader, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObjectSimpleDepthShader, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObjectSimpleDepthShader, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Program Link SimpleDepthShader Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}
	glightSpaceMatrixSimpleDepthShaderUniform = glGetUniformLocation(gShaderProgramObjectSimpleDepthShader, "lightSpaceMatrix");
	gmodelSimpleDepthShaderUniform = glGetUniformLocation(gShaderProgramObjectSimpleDepthShader, "model");
}
void resize(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	gPerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	//gPerspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}
void UninitializeCar(void)
{
	if (gVao_Car_1)
	{
		glDeleteVertexArrays(1, &gVao_Car_1);
		gVao_Car_1 = 0;
	}
	if (gVbo_Position)
	{
		glDeleteBuffers(1, &gVbo_Position);
		gVbo_Position = 0;
	}
	if (gVbo_Normal)
	{
		glDeleteBuffers(1, &gVbo_Normal);
		gVbo_Normal = 0;
	}
	if (gVbo_Texture)
	{
		glDeleteBuffers(1, &gVbo_Texture);
		gVbo_Texture = 0;
	}
}
void UninitializePlane(void)
{
	if (planeVAO)
	{
		glDeleteVertexArrays(1, &planeVAO);
		planeVAO = 0;
	}
	if (planeVBOposition)
	{
		glDeleteBuffers(1, &planeVBOposition);
		planeVBOposition = 0;
	}
	if (planeVBOnormal)
	{
		glDeleteBuffers(1, &planeVBOnormal);
		planeVBOnormal = 0;
	}
	if (planeVBOtexture)
	{
		glDeleteBuffers(1, &planeVBOtexture);
		planeVBOtexture = 0;
	}
}
void UninitializeSphere(void)
{
	if (gVao_sphere)
	{
		glDeleteVertexArrays(1, &gVao_sphere);
		gVao_sphere = 0;
	}
	if (gVbo_sphere_position)
	{
		glDeleteBuffers(1, &gVbo_sphere_position);
		gVbo_sphere_position = 0;
	}
	if (gVbo_sphere_normal)
	{
		glDeleteBuffers(1, &gVbo_sphere_normal);
		gVbo_sphere_normal = 0;
	}
	if (gVbo_sphere_texture)
	{
		glDeleteBuffers(1, &gVbo_sphere_texture);
		gVbo_sphere_texture = 0;
	}
	if (gVbo_sphere_element)
	{
		glDeleteBuffers(1, &gVbo_sphere_element);
		gVbo_sphere_element = 0;
	}
}
void UninitializeCube(void)
{
	if (cubeVAO)
	{
		glDeleteVertexArrays(1, &cubeVAO);
		cubeVAO = 0;
	}
	if (cubeVBOposition)
	{
		glDeleteBuffers(1, &cubeVBOposition);
		cubeVBOposition = 0;
	}
	if (cubeVBOnormal)
	{
		glDeleteBuffers(1, &cubeVBOnormal);
		cubeVBOnormal = 0;
	}
	if (cubeVBOtexture)
	{
		glDeleteBuffers(1, &cubeVBOtexture);
		cubeVBOtexture = 0;
	}
}

void uninitialize(void)
{
	void UninitializeCube(void);
	void UninitializeSphere(void);
	void UninitializePlane(void);
	void UninitializeCar(void);

	//UNINITIALIZATION CODE
	if (gbFullscreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

	UninitializePlane();
	UninitializeCube();

	glDetachShader(gShaderProgramObjectShader, gVertexShaderObjectShader);
	glDetachShader(gShaderProgramObjectShader, gFragmentShaderObjectShader);

	glDeleteShader(gVertexShaderObjectShader);
	gVertexShaderObjectShader = 0;
	glDeleteShader(gFragmentShaderObjectShader);
	gFragmentShaderObjectShader = 0;

	glDeleteProgram(gShaderProgramObjectShader);
	gShaderProgramObjectShader = 0;

	glDetachShader(gShaderProgramObjectSimpleDepthShader, gVertexShaderObjectSimpleDepthShader);
	glDetachShader(gShaderProgramObjectSimpleDepthShader, gFragmentShaderObjectSimpleDepthShader);

	glDeleteShader(gVertexShaderObjectSimpleDepthShader);
	gVertexShaderObjectSimpleDepthShader = 0;
	glDeleteShader(gFragmentShaderObjectSimpleDepthShader);
	gFragmentShaderObjectSimpleDepthShader = 0;

	glDeleteProgram(gShaderProgramObjectSimpleDepthShader);
	gShaderProgramObjectSimpleDepthShader = 0;

	glUseProgram(0);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ghrc);
	ghrc = NULL;

	//Delete the device context
	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;

	fopen_s(&gpFile, gszLogFileName, "a+");
	fprintf_s(gpFile, "Log File Is Successfully Closed.\n");
	fclose(gpFile);
}