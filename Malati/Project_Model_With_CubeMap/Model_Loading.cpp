//Cubemap Code refer from Superbible.
#include<windows.h>
#include<windowsx.h>
#include<C:\glew\include\GL\glew.h>
#include<gl/GL.h>
#include<stdio.h>

#include<vector>
#include<stdlib.h>
#include"Obj_Loader.h"
#include "Camera_2.h"

#include <C:\glm\glm.hpp>
#include <C:\glm\gtc\matrix_transform.hpp>
#include <C:\glm\gtc\type_ptr.hpp>

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"GDI32.lib")
#pragma comment(lib,"C:\\glew\\lib\\Release\\x64\\glew32.lib")
#pragma comment(lib,"opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

		
enum
{
	HAD_ATTRIBUTE_POSITION = 0,
	HAD_ATTRIBUTE_COLOR,
	HAD_ATTRIBUTE_NORMAL,
	HAD_ATTRIBUTE_TEXTURE0,
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define MODEL_X_TRANSLATE		0.0f	//X-translation of MODEL
#define MODEL_Y_TRANSLATE		-1.0f	//Y-translation of MODEL
#define MODEL_Z_TRANSLATE		-20.0f	//Z-translation of MODEL

#define MODEL_X_SCALE_FACTOR	1.5f	//X-scale factor of MODEL
#define MODEL_Y_SCALE_FACTOR	1.5f	//Y-scale factor of MODEL
#define MODEL_Z_SCALE_FACTOR	1.5f	//Z-scale factor of MODEL

#define START_ANGLE_POS			0.0f	//Marks beginning angle position of rotation
#define END_ANGLE_POS			360.0f	//Marks terminating angle position rotation
#define MODEL_ANGLE_INCREMENT	0.1f	//Increment angle for MODEL

FILE *gpFile;
HWND ghwnd;
HDC ghdc;
HGLRC ghrc;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbActiveWindow = false;
bool gbFullscreen = false;
bool gbIsEscapeKeyPressed = false;

GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLuint gShaderProgramObject;

GLuint gVao_road, gVao_Buildings;
GLuint gVbo_Position, gVbo_Normal;

GLuint gModelMatrixUniform, gViewMatrixUniform, gProjectionMatrixUniform;
GLuint gLKeyPressedUniform;

GLuint gLaUniform, gLdUniform, gLsUniform;
GLuint gLightPositionUniform;

GLuint gKaUniform, gKdUniform, gKsUniform;
GLuint gMaterialShininessUniform;

GLfloat gAngle_Cube;

glm::mat4 gPerspectiveProjectionMatrix;

bool gbAnimate = false;
bool gbLight = false;
bool gbIsAKeyPressed = false;
bool gbIsLKeyPressed = false;

GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightPosition[] = { 0.0f,20.0f,20.0f,0.0f };

GLfloat materialAmbient[] = { 0.25f,0.25f,0.25f,1.0f };
GLfloat materialDiffuse[] = { 0.4f,0.4f,0.4f,1.0f };
GLfloat materialSpecular[] = { 0.774597f,0.774597f,0.774597f,1.0f };
GLfloat materialShininess = 0.6f * 128.0f;

GLfloat g_rotate;

std::vector<float> gv_vertices_road, gv_textures_road, gv_normals_road;
std::vector<float> gv_vertices_buildings, gv_textures_buildings, gv_normals_buildings;
std::vector<int> gv_face_tri_1, gv_face_textures_1, gv_face_normals_1;

//for camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera;

float lastX = WIN_WIDTH / 2.0f;
float lastY = WIN_HEIGHT / 2.0f;

bool FirstMouse = true;
float deltaTime = 10.0f;
float _yaw = -90.0f;
float _pitch = 0.0f;

//Cubemap
typedef struct                                      // Create A Structure
{
	GLubyte *imageData;                             // Image Data (Up To 32 Bits)
	GLuint  bpp;                                    // Image Color Depth In Bits Per Pixel
	GLuint  width;                                  // Image Width
	GLuint  height;                                 // Image Height
	GLuint  texID;                                  // Texture ID Used To Select A Texture
} TextureImage;

TextureImage    textures[6];

GLuint gVertexShaderObjectSkyBox;
GLuint gFragmentShaderObjectSkyBox;
GLuint gShaderProgramObjectSkyBox;

GLuint skyboxVAO;
GLuint cubemapTexture;

GLuint gProjectionSkyBoxUniform;
GLuint gModelMatrixSkyBoxUniform;
GLuint gViewSkyBoxUniform;
GLuint gSkyboxUniform;

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

		case 0x41:
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
}

void initialize(void)
{
	void resize(int, int);
	void uninitialize(int);
	void LoadModel(char *, std::vector<float>, std::vector<float>, std::vector<float>);
	
	void LoadSkyBoxShader(void);
	unsigned int loadCubemap(std::vector<std::string> faces);

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
	LoadMeshData("Project_Model_Only_Roads.obj", gv_vertices_road, gv_textures_road, gv_normals_road);
	MessageBox(ghwnd, TEXT("After LoadMeshData 1"), TEXT("MSG"), MB_OK);
	LoadMeshData("Project_Model_Without_Roads.obj", gv_vertices_buildings, gv_textures_buildings, gv_normals_buildings);
	MessageBox(ghwnd, TEXT("After LoadMeshData 2"), TEXT("MSG"), MB_OK);

	//Vertex Shader
	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_lighting_enabled;" \
		"uniform vec4 u_light_position;" \
		"out vec3 transformed_normals;" \
		"out vec3 light_direction;" \
		"out vec3 viewer_vector;" \
		"void main(void)" \
		"{" \
		"if(u_lighting_enabled==1)" \
		"{" \
		"vec4 eye_coordinates = u_view_matrix*u_model_matrix*vPosition;" \
		"transformed_normals = mat3(u_view_matrix*u_model_matrix)*vNormal;" \
		"light_direction = vec3(u_light_position)-eye_coordinates.xyz;" \
		"viewer_vector = -eye_coordinates.xyz;" \
		"}" \
		"gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;" \
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
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Fragment Shader
	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec3 transformed_normals;" \
		"in vec3 light_direction;" \
		"in vec3 viewer_vector;" \
		"out vec4 FragColor;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;" \
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform float u_material_shininess;" \
		"uniform int u_lighting_enabled;" \
		"void main(void)" \
		"{" \
		"vec3 phong_ads_color;" \
		"if(u_lighting_enabled == 1)" \
		"{" \
		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(light_direction);" \
		"vec3 normalized_viewer_vector = normalize(viewer_vector);" \
		"vec3 ambient = u_La * u_Ka;" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess);" \
		"phong_ads_color = ambient + diffuse + specular;" \
		"}" \
		"else" \
		"{" \
		"phong_ads_color = vec3(1.0f,1.0f,1.0f);" \
		"}" \
		"FragColor = vec4(phong_ads_color,1.0);" \
		"}";

	glShaderSource(gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(gFragmentShaderObject);

	glGetShaderiv(gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program
	gShaderProgramObject = glCreateProgram();

	glAttachShader(gShaderProgramObject, gVertexShaderObject);

	glAttachShader(gShaderProgramObject, gFragmentShaderObject);

	glBindAttribLocation(gShaderProgramObject, HAD_ATTRIBUTE_POSITION, "vPosition");

	glBindAttribLocation(gShaderProgramObject, HAD_ATTRIBUTE_NORMAL, "vNormal");

	glLinkProgram(gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	gModelMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_model_matrix");
	gViewMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_view_matrix");
	gProjectionMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_projection_matrix");

	gLKeyPressedUniform = glGetUniformLocation(gShaderProgramObject, "u_lighting_enabled");

	gLaUniform = glGetUniformLocation(gShaderProgramObject, "u_La");
	gLdUniform = glGetUniformLocation(gShaderProgramObject, "u_Ld");
	gLsUniform = glGetUniformLocation(gShaderProgramObject, "u_Ls");

	gLightPositionUniform = glGetUniformLocation(gShaderProgramObject, "u_light_position");

	gKaUniform = glGetUniformLocation(gShaderProgramObject, "u_Ka");
	gKdUniform = glGetUniformLocation(gShaderProgramObject, "u_Kd");
	gKsUniform = glGetUniformLocation(gShaderProgramObject, "u_Ks");

	gMaterialShininessUniform = glGetUniformLocation(gShaderProgramObject, "u_material_shininess");

	/*****************VAO For Road*****************/
	glGenVertexArrays(1, &gVao_road);
	glBindVertexArray(gVao_road);

	/*****************Road Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, gv_vertices_road.size() * sizeof(float), &gv_vertices_road[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Road Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, gv_normals_road.size() * sizeof(float), &gv_normals_road[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Buildings*************/
	glGenVertexArrays(1, &gVao_Buildings);
	glBindVertexArray(gVao_Buildings);

	/**************Building Vertices**************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, gv_vertices_buildings.size() * sizeof(float), &gv_vertices_buildings[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Building Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, gv_normals_buildings.size() * sizeof(float), &gv_normals_buildings[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//SkyBox
	LoadSkyBoxShader();

	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);
	glBindVertexArray(0);

	std::vector<std::string> Faces
	{
		"resources/RotateMirMar/right.tga",
		"resources/RotateMirMar/left.tga",
		"resources/RotateMirMar/new_up.tga",
		"resources/RotateMirMar/dwn.tga",
		"resources/RotateMirMar/front.tga",
		"resources/RotateMirMar/bck.tga",
	};

	cubemapTexture = loadCubemap(Faces);

	//glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glClearColor(0.75f, 0.75f, 0.75f, 0.0f);

	gPerspectiveProjectionMatrix = glm::mat4();

	camera = Camera(cameraPos, cameraUp, _yaw, _pitch);
	resize(WIN_WIDTH, WIN_HEIGHT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glm::mat4 modelMatrix = glm::mat4();
	glm::mat4 viewMatrix = glm::mat4();
	glm::mat4 scaleMatrix = glm::mat4();
	glm::mat4 rotationMatrix = glm::mat4();

	viewMatrix = camera.GetViewMatrix();
	//viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));


	glUseProgram(gShaderProgramObjectSkyBox);
	glDisable(GL_DEPTH_TEST);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));
	glUniformMatrix4fv(gModelMatrixSkyBoxUniform, 1,  GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(gViewSkyBoxUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform1i(gSkyboxUniform, 0);

	glBindVertexArray(skyboxVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(0);

	//Use Shader Program Object
	glUseProgram(gShaderProgramObject);
	
	if (gbLight == true)
	{
		glUniform1i(gLKeyPressedUniform, 1);

		glUniform3fv(gLaUniform, 1, lightAmbient);
		glUniform3fv(gLdUniform, 1, lightDiffuse);
		glUniform3fv(gLsUniform, 1, lightSpecular);
		glUniform4fv(gLightPositionUniform, 1, lightPosition);

		glUniform3fv(gKaUniform, 1, materialAmbient);
		glUniform3fv(gKdUniform, 1, materialDiffuse);
		glUniform3fv(gKsUniform, 1, materialSpecular);
		glUniform1f(gMaterialShininessUniform, materialShininess);
	}
	else
	{
		glUniform1i(gLKeyPressedUniform, 0);
	}

	viewMatrix = glm::mat4();
	modelMatrix = glm::mat4();
	modelMatrix = translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	//rotationMatrix = vmath::rotate(180.0f, 0.0f, 1.0f, 0.0f);
	//modelMatrix = modelMatrix*rotationMatrix;

	//rotationMatrix = vmath::rotate(g_rotate, 0.0f, 1.0f, 0.0f);
	//modelMatrix = modelMatrix*rotationMatrix;

	//viewMatrix = lookat(vec3(0.0f, 1.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	viewMatrix = camera.GetViewMatrix();

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glBindVertexArray(gVao_road);

	glDrawArrays(GL_TRIANGLES, 0, gv_vertices_road.size());
	
	glBindVertexArray(0);

	if (gbLight == true)
	{
		glUniform1i(gLKeyPressedUniform, 1);

		glUniform3fv(gLaUniform, 1, lightAmbient);
		glUniform3fv(gLdUniform, 1, lightDiffuse);
		glUniform3fv(gLsUniform, 1, lightSpecular);
		glUniform4fv(gLightPositionUniform, 1, lightPosition);

		glUniform3fv(gKaUniform, 1, materialAmbient);
		glUniform3fv(gKdUniform, 1, materialDiffuse);
		glUniform3fv(gKsUniform, 1, materialSpecular);
		glUniform1f(gMaterialShininessUniform, materialShininess);
	}
	else
	{
		glUniform1i(gLKeyPressedUniform, 0);
	}

	viewMatrix = glm::mat4();
	modelMatrix = glm::mat4();
	modelMatrix = translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	//rotationMatrix = vmath::rotate(180.0f, 0.0f, 1.0f, 0.0f);
	//modelMatrix = modelMatrix*rotationMatrix;

	//rotationMatrix = vmath::rotate(g_rotate, 0.0f, 1.0f, 0.0f);
	//modelMatrix = modelMatrix*rotationMatrix;

	//viewMatrix = lookat(vec3(0.0f, 1.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	viewMatrix = camera.GetViewMatrix();

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glBindVertexArray(gVao_Buildings);

	glDrawArrays(GL_TRIANGLES, 0, gv_vertices_buildings.size());

	glBindVertexArray(0);

	glUseProgram(0);

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

	gPerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);
	//gPerspectiveProjectionMatrix = glm::perspective(camera.Zoom, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);
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

void LoadSkyBoxShader()
{
	fopen_s(&gpFile, "Log.txt", "a+");

	fprintf(gpFile, "In LoadSkyBoxShader \n");
	fclose(gpFile);
	void uninitialize(int);
	//VERTEX SHADER
	gVertexShaderObjectSkyBox = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCodeSkyBox =
		"#version 460" \
		"\n" \
		"out VS_OUT" \
		"{" \
		"vec3    tc;" \
		"} vs_out;" \
		"uniform mat4 model_matrix;" \
		"uniform mat4 view_matrix;" \
		"void main(void)" \
		"{" \
		"vec3[4] vertices = vec3[4](vec3(-1.0, -1.0, 1.0)," \
		"vec3(1.0, -1.0, 1.0)," \
		"vec3(-1.0, 1.0, 1.0)," \
		"vec3(1.0, 1.0, 1.0)); "\

		"vs_out.tc = mat3(view_matrix * model_matrix) * vertices[gl_VertexID];" \
		"gl_Position = vec4(vertices[gl_VertexID], 1.0);" \
		"}";


	glShaderSource(gVertexShaderObjectSkyBox, 1, (const GLchar**)&vertextShaderSourceCodeSkyBox, NULL);

	//compile shader
	glCompileShader(gVertexShaderObjectSkyBox);

	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(gVertexShaderObjectSkyBox, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObjectSkyBox, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObjectSkyBox, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);


				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}
	//FRAGMENT SHADER

	gFragmentShaderObjectSkyBox = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCodeSkyBox =
		"#version 460"\
		"\n" \
		"uniform samplerCube tex_cubemap;" \
		"in VS_OUT" \
		"{" \
		"vec3    tc;" \
		"} fs_in;" \
		"layout (location = 0) out vec4 color;" \
		"void main(void)" \
		"{" \
		//"color = texture(tex_cubemap, vec3(fs_in.tc.x, -fs_in.tc.y, fs_in.tc.z));" 
		"color = texture(tex_cubemap, fs_in.tc);" \
		"}";

	glShaderSource(gFragmentShaderObjectSkyBox, 1, (const GLchar **)&fragmentShaderSourceCodeSkyBox, NULL);

	glCompileShader(gFragmentShaderObjectSkyBox);

	glGetShaderiv(gFragmentShaderObjectSkyBox, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObjectSkyBox, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObjectSkyBox, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);


				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program

	gShaderProgramObjectSkyBox = glCreateProgram();

	glAttachShader(gShaderProgramObjectSkyBox, gVertexShaderObjectSkyBox);

	glAttachShader(gShaderProgramObjectSkyBox, gFragmentShaderObjectSkyBox);

	//glBindAttribLocation(gShaderProgramObjectSkyBox, MALATI_ATTRIBUTE_VERTEX, "aPos");
	//glBindAttribLocation(gShaderProgramObjectSkyBox, MALATI_ATTRIBUTE_TEXTURE0, "vTexture0_Coord");

	glLinkProgram(gShaderProgramObjectSkyBox);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObjectSkyBox, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObjectSkyBox, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObjectSkyBox, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);


				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	gModelMatrixSkyBoxUniform = glGetUniformLocation(gShaderProgramObjectSkyBox, "model_matrix");
	gViewSkyBoxUniform = glGetUniformLocation(gShaderProgramObjectSkyBox, "view_matrix");
	gSkyboxUniform = glGetUniformLocation(gShaderProgramObjectSkyBox, "tex_cubemap");


}
unsigned int loadCubemap(std::vector<std::string> faces)
{
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In loadCubemap....\n");
	fclose(gpFile);
	TextureImage* LoadTGA(TextureImage *texture, const char *filename, int i);
	bool returnType = false;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		TextureImage* textureIm = LoadTGA(&textures[i], faces[i].c_str(), i);
		if (textureIm->imageData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureIm->width, textureIm->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureIm->imageData);
		}
		else
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "CubeMap texture failed to load..\n");
			fclose(gpFile);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	/*glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);*/


	return textureID;
}

TextureImage* LoadTGA(TextureImage *texture, const char *filename, int num)                 // Loads A TGA File Into Memory
{
	void _check_gl_error();

	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA : FileName : %s\n", filename);
	fclose(gpFile);

	GLubyte     TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };           // Uncompressed TGA Header
	GLubyte     TGAcompare[12];                         // Used To Compare TGA Header
	GLubyte     header[6];                          // First 6 Useful Bytes From The Header
	GLuint      bytesPerPixel;                          // Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint      imageSize;                          // Used To Store The Image Size When Setting Aside Ram
	GLuint      temp;                               // Temporary Variable
	GLuint      type = GL_RGBA;                           // Set The Default GL Mode To RBGA (32 BPP)
	FILE *file = NULL;
	fopen_s(&file, filename, "rb");                     // Open The TGA File

	if (file == NULL ||                               // Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||  // Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||  // Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))            // If So Read Next 6 Header Bytes
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "Does File EVen Exist..\n");
		fclose(gpFile);

		if (file == NULL)                           // Did The File Even Exist? *Added Jim Strong*
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "No..File Not Exists..\n");
			fclose(gpFile);
			return NULL;                           // Return False
		}
		else
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "Any Other thing Failed\n");
			fclose(gpFile);
			fclose(file);                           // If Anything Failed, Close The File
			return NULL;                           // Return False
		}
	}
	texture->width = header[1] * 256 + header[0];                   // Determine The TGA Width  (highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];                   // Determine The TGA Height (highbyte*256+lowbyte)
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 100\n");
	fclose(gpFile);
	if (texture->width <= 0 ||                      // Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||                      // Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))                   // Is The TGA 24 or 32 Bit?
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "In LoadTGA 1\n");
		fclose(gpFile);
		fclose(file);                               // If Anything Failed, Close The File
		return NULL;                               // Return False
	}
	texture->bpp = header[4];                            // Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;                        // Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width*texture->height*bytesPerPixel;           // Calculate The Memory Required For The TGA Data
	texture->imageData = (GLubyte *)malloc(imageSize);             // Reserve Memory To Hold The TGA Data
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 101\n");
	fclose(gpFile);
	if (texture->imageData == NULL ||                      // Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)        // Does The Image Size Match The Memory Reserved?
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "In LoadTGA 500\n");
		fclose(gpFile);
		if (texture->imageData != NULL)                     // Was Image Data Loaded
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "In LoadTGA 501\n");
			fclose(gpFile);
			free(texture->imageData);                    // If So, Release The Image Data
		}
		fclose(file);                               // Close The File
		return NULL;                               // Return False
	}
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 102\n");
	fclose(gpFile);
	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)              // Loop Through The Image Data
	{   // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)

		temp = texture->imageData[i];                      // Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];            // Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;                    // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	return texture;                                    // Texture Building Went Ok, Return True
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

	if (skyboxVAO)
	{
		glDeleteVertexArrays(1, &skyboxVAO);
		skyboxVAO = 0;
	}

	if (gVao_road)
	{
		glDeleteVertexArrays(1, &gVao_road);
		gVao_road = 0;
	}

	if (gVao_Buildings)
	{
		glDeleteVertexArrays(1, &gVao_Buildings);
		gVao_Buildings = 0;
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

	//Detach Shader 
	glDetachShader(gShaderProgramObject, gVertexShaderObject);
	glDetachShader(gShaderProgramObject, gFragmentShaderObject);

	//Delete Shader
	glDeleteShader(gVertexShaderObject);
	gVertexShaderObject = 0;

	glDeleteShader(gFragmentShaderObject);
	gFragmentShaderObject = 0;

	//Delete Program
	glDeleteProgram(gShaderProgramObject);
	gShaderProgramObject = 0;

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