#include <windows.h>
#include <windowsx.h>
// #include <C:\glew\include\GL\glew.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Obj_Loader.h"
#include "camera.h"
#include "lib/audioManager/audioManager.h"
#include "lib/audioManager/soundSource.h"
#include "lib/logger/logger.h"

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"openal32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//using namespace vmath;

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
#define MODEL_Z_TRANSLATE		-5.0f	//Z-translation of MODEL

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
bool gbLight = false;
bool gbIsAKeyPressed = false;
bool gbIsLKeyPressed = false;
bool FirstMouse = true;
bool gbDoor_Open_Flag = false;
bool gbUpper_Middle_Light_On_Flag = false;
bool gbUpper_Side_Light_On_Flag = false;
bool gbInner_Side_Light_On_Flag = false;

struct PointLight
{
	GLfloat lightAmbient[4] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat lightDiffuse[4] = { 0.5f,0.5f,0.5f,1.0f };
	GLfloat lightSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightPosition[3] = { -3.899998f, -0.600000f, -15.000002f };
	GLfloat gConstant = 1.0f;
	GLfloat gLinear = 1.419999f;
	GLfloat gQuadratic = 0.090000f;
	GLuint gLaUniform;
	GLuint gLdUniform;
	GLuint gLsUniform;
	GLuint gConstantUniform;
	GLuint gLinearUniform;
	GLuint gQuadraticUniform;
	GLuint gLightPositionUniform;
}pointLight;

struct SpotLight
{
	GLfloat lightAmbient[4] = { 0.1f,0.1f,0.1f,1.0f };
	GLfloat lightDiffuse[4] = { 0.8f,0.8f,0.8f,1.0f };
	GLfloat lightSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightPosition[3] = { 0.099999f, 2.299999f, -48.299911f };
	GLfloat lightDirection[3] = { 0.0f, -1.0f, 0.0f };
	GLfloat gConstant = 1.0f;
	GLfloat gLinear = 0.09f;
	GLfloat gQuadratic = 0.032f;
	GLfloat cutoff_angle = 12.5f;
	GLfloat outer_cutoff_angle = 17.5f;
	GLuint gLaUniform;
	GLuint gLdUniform;
	GLuint gLsUniform;
	GLuint gLightPositionUniform;
	GLuint gLightDirectionUniform;
	GLuint gConstantUniform;
	GLuint gLinearUniform;
	GLuint gQuadraticUniform;
	GLuint gCutOffUniform;
	GLuint gOuterCutOffUniform;
}spotLight;

struct MaterialProperties
{
	GLfloat materialAmbient[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat materialDiffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat materialSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat materialShininess = 50.0f;
	GLuint gKaUniform;
	GLuint gKdUniform;
	GLuint gKsUniform;
	GLuint gMaterialShininessUniform;
}materialProperties;

struct Model
{
	GLuint Vao;
	std::vector<float> gv_vertices;
	std::vector<float> gv_textures;
	std::vector<float> gv_normals;
	int count_of_vertices;
}Gaurage_Body, Gaurage_Outer_Light, Gaurage_Inner_Upper_Middle_Light, Gaurage_Inner_Upper_Side_Light, Gaurage_Inner_Side_Light, Mustang, Left_Door, Right_Door;

struct PointLight_Position
{
	glm::vec3 Position;
};

GLfloat pointLight1[3] = { 3.899998f, -0.700000f, -8.899998f };
GLfloat pointLight2[3] = { 3.999998f, 2.100000f, -8.899998f };
GLfloat pointLight3[3] = { -3.799999f, 2.000000f, -8.699999f };
GLfloat pointLight4[3] = { -3.999998f, -0.600000f, -8.899998f };
GLfloat pointLight5[3] = { 3.899998f, -0.700000f, -15.000002f };
GLfloat pointLight6[3] = { 3.899998f, 2.000000f, -15.000002f };
GLfloat pointLight7[3] = { -3.899998f, 2.000000f, -15.000002f };
GLfloat pointLight8[3] = { -3.899998f, -0.600000f, -15.000002f };
GLfloat pointLight9[3] = { 3.899999f, -0.700000f, -21.300026f };
GLfloat pointLight10[3] = { 3.899999f, 2.100000f, -21.300026f };
GLfloat pointLight11[3] = { -4.099998f, 2.100000f, -21.300026f };
GLfloat pointLight12[3] = { -4.099998f, -0.600000f, -21.300026f };
GLfloat pointLight13[3] = { 3.799999f, -0.700000f, -27.300049f };
GLfloat pointLight14[3] = { 3.899999f, 2.000000f, -27.300049f };
GLfloat pointLight15[3] = { -3.799998f, 2.000000f, -27.400049f };
GLfloat pointLight16[3] = { -3.799998f, -0.600000f, -27.400049f };
GLfloat pointLight17[3] = { 3.799999f, -0.700000f, -33.600073f};
GLfloat pointLight18[3] = { 3.899999f, 2.000000f, -33.600073f };
GLfloat pointLight19[3] = { -3.799998f, 2.100000f, -33.600073f };
GLfloat pointLight20[3] = { -3.799998f, -0.600000f, -33.600073f };
GLfloat pointLight21[3] = { -1.700001f, 2.299999f, -49.599892f };
GLfloat pointLight22[3] = { 1.700000f, 2.299999f, -49.599892f };
GLfloat pointLight23[3] = { 1.600000f, 2.299999f, -53.999825f };
GLfloat pointLight24[3] = { -1.700001f, 2.299999f, -53.999825f };
GLfloat pointLight25[3] = { -4.899998f, 2.399999f, -45.099960f };
GLfloat pointLight26[3] = { 4.999997f, 2.399999f, -45.099960f };
GLfloat pointLight27[3] = { 4.899997f, 2.299999f, -58.499756f };
GLfloat pointLight28[3] = { -5.099998f, 2.299999f, -58.499756f };
GLfloat pointLight29[3] = { -7.199996f, 0.699999f, -46.699936f };
GLfloat pointLight30[3] = { -7.199996f, 0.699999f,-51.599861f };
GLfloat pointLight31[3] = { -7.199996f, 0.699999f, -56.699783f };
GLfloat pointLight32[3] = { 7.199995f, 0.699999f, -56.699783f };
GLfloat pointLight33[3] = { 7.199995f, 0.699999f, -51.699860f };
GLfloat pointLight34[3] = { 7.199996f, 0.699999f, -46.699936f };

GLuint gLightUniform[34];

GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLuint gShaderProgramObject;

GLuint gVao_Cube;
GLuint gVbo_Position, gVbo_Normal;

GLuint gModelMatrixUniform, gViewMatrixUniform, gProjectionMatrixUniform;
GLuint gLKeyPressedUniform;

GLuint gViewPositionUniform;
GLuint gNumberOfLightsUniform;

glm::mat4 gPerspectiveProjectionMatrix;

glm::vec3 gViewPosition = glm::vec3(0.0f, 0.0f, 3.0f);

GLfloat gAngle_Cube;
GLfloat viewTranslateOnX = 0.0f;
GLfloat viewTranslateOnY = 0.0f;
GLfloat viewTranslateOnZ = 0.0f;

GLfloat lastX = WIN_WIDTH / 2.0;
GLfloat lastY = WIN_HEIGHT / 2.0;

glm::vec3 cameraPosition;
glm::vec3 cameraTarget;
glm::vec3 cameraUP;
Camera  camera;

AudioManager *audioManager = NULL;
SoundSource *soundSource = NULL;
ALuint audioBufferId = 0;

int giNumberOfLights = 20;
int camera_Z_counter = 0.0f;
GLfloat deltaTime = 0.0f;
uint64_t initTime, initFrequency, changingTime;
GLfloat currentFrame = 0.0f, lastFrame = 0.0f;
GLfloat gfLeft_Door_Translate = 0.0f;
GLfloat gfRight_Door_Translate = 0.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
 	void initializeAudio(void);
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

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, TEXT("OpenGLPP : 3D Rotation"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
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
	initializeAudio();

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
		if (GetAsyncKeyState(VK_DOWN))
		{
			camera.MoveCamera(CameraMoveOnZ, 0.1f, deltaTime);
			camera_Z_counter--;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			camera.MoveCamera(CameraMoveOnZ, -0.1f, deltaTime);
			camera_Z_counter++;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			camera.MoveCamera(CameraMoveOnX, 0.1f, deltaTime);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			camera.MoveCamera(CameraMoveOnX, -0.1f, deltaTime);
		}
		switch (wParam)
		{
		case VK_ADD:
			pointLight.gLinear = pointLight.gLinear + 0.01f;
			break;

		case VK_SUBTRACT:
			pointLight.gLinear = pointLight.gLinear - 0.01f;
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
			break;

		case 0x41://A
			pointLight21[0] = pointLight21[0] - 0.1f;
			spotLight.lightPosition[0] = spotLight.lightPosition[0] - 0.1f;
			break;

		case 0x44://D
			pointLight21[0] = pointLight21[0] + 0.1f;
			spotLight.lightPosition[0] = spotLight.lightPosition[0] + 0.1f;
			break;

		case 0x51://Q
			pointLight21[1] = pointLight21[1] + 0.1f;
			spotLight.lightPosition[1] = spotLight.lightPosition[1] + 0.1f;
			break;

		case 0x45://E
			pointLight21[1] = pointLight21[1] - 0.1f;
			spotLight.lightPosition[1] = spotLight.lightPosition[1] - 0.1f;
			break;

		case 0x53://S
			pointLight21[2] = pointLight21[2] + 0.1f;
			spotLight.lightPosition[2] = spotLight.lightPosition[2] + 0.1f;
			break;

		case 0x57://W
			pointLight21[2] = pointLight21[2] - 0.1f;
			spotLight.lightPosition[2] = spotLight.lightPosition[2] - 0.1f;
			break;

		case 0x50://P
			//logInfo("Camera Counter :%i\n", camera_Z_counter);
			//logInfo("Linear :%f\n", pointLight.gLinear);
			break;

		case 0x4C:
			if (gbIsLKeyPressed == false)
			{
				gbLight = true;
				gbIsLKeyPressed = true;

				if(soundSource != NULL && audioBufferId != 0)
				{
					soundSource->play(audioBufferId);
				}
			}
			else
			{
				gbLight = false;
				gbIsLKeyPressed = false;
			}
			break;
		}
		break;
	case WM_MOUSEMOVE:
		// xPos = GET_X_LPARAM(lParam);
		// yPos = GET_Y_LPARAM(lParam);
		// MouseMovement((double)xPos, (double)yPos);
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
		logError("wglMakeCurrent() Failed");
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

	//MessageBox(ghwnd, TEXT("Before LoadMeshData"), TEXT("MSG"), MB_OK);
	Gaurage_Body.count_of_vertices = LoadMeshData("Gaurage_Body.obj", Gaurage_Body.gv_vertices, Gaurage_Body.gv_textures, Gaurage_Body.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 1"), TEXT("MSG"), MB_OK);
	Gaurage_Outer_Light.count_of_vertices = LoadMeshData("Outer_Lights.obj", Gaurage_Outer_Light.gv_vertices, Gaurage_Outer_Light.gv_textures, Gaurage_Outer_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 2"), TEXT("MSG"), MB_OK);
	Gaurage_Inner_Upper_Middle_Light.count_of_vertices = LoadMeshData("Inner_Gaurage_Upper_Light_Middle.obj", Gaurage_Inner_Upper_Middle_Light.gv_vertices, Gaurage_Inner_Upper_Middle_Light.gv_textures, Gaurage_Inner_Upper_Middle_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 3"), TEXT("MSG"), MB_OK);
	Gaurage_Inner_Upper_Side_Light.count_of_vertices = LoadMeshData("Inner_Gaurage_Upper_Light_Side.obj", Gaurage_Inner_Upper_Side_Light.gv_vertices, Gaurage_Inner_Upper_Side_Light.gv_textures, Gaurage_Inner_Upper_Side_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 4"), TEXT("MSG"), MB_OK);
	Gaurage_Inner_Side_Light.count_of_vertices = LoadMeshData("Inner_Gaurage_Side_Light.obj", Gaurage_Inner_Side_Light.gv_vertices, Gaurage_Inner_Side_Light.gv_textures, Gaurage_Inner_Side_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 5"), TEXT("MSG"), MB_OK);
	Left_Door.count_of_vertices = LoadMeshData("Left_Door.obj", Left_Door.gv_vertices, Left_Door.gv_textures, Left_Door.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 6"), TEXT("MSG"), MB_OK);
	Right_Door.count_of_vertices = LoadMeshData("Right_Door.obj", Right_Door.gv_vertices, Right_Door.gv_textures, Right_Door.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 6"), TEXT("MSG"), MB_OK);
	Mustang.count_of_vertices = LoadMeshData("Mustang_GT\\mustang_GT_new.obj", Mustang.gv_vertices, Mustang.gv_textures, Mustang.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 6"), TEXT("MSG"), MB_OK);


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
		"out vec3 transformed_normals;" \
		"out vec3 FragPos;" \
		"void main(void)" \
		"{" \
		"if(u_lighting_enabled==1)" \
		"{" \
		"transformed_normals = mat3(u_view_matrix*u_model_matrix)*vNormal;" \
		"FragPos = vec3(u_model_matrix * vPosition);" \
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
				logError("Vertex Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	//Fragment Shader
	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec3 transformed_normals;" \
		"in vec3 FragPos;" \

		"struct PointLight" \
		"{" \
		"vec3 u_La;" \
		"vec3 u_Ld;" \
		"vec3 u_Ls;" \
		"float u_constant;" \
		"float u_linear;" \
		"float u_quadratic;" \
		/*"vec3 u_light_position;" \*/
		"};" \

		"struct SpotLight" \
		"{" \
		"vec3 u_La;" \
		"vec3 u_Ld;" \
		"vec3 u_Ls;" \
		"float constant;" \
		"float linear;" \
		"float quadratic;" \
		"vec3 u_light_position;" \
		"vec3 u_light_direction;" \
		"float u_cutOff;" \
		"float u_outerCutOff;" \
		"};" \

		"struct Material" \
		"{" \
		"float u_material_shininess;" \
		"vec3 u_Ka;" \
		"vec3 u_Kd;" \
		"vec3 u_Ks;" \
		"};" \

		"uniform int u_lighting_enabled;" \
		"uniform vec3 u_viewPos;" \
		"uniform PointLight pointlight;" \
		"uniform SpotLight spotlight;" \
		"uniform Material material;" \
		"uniform vec3 u_light_position[34];" \
		"uniform int u_number_of_lights;" \

		"out vec4 FragColor;" \

		"vec3 CalculatePointLight(vec3 lightpos)" \
		"{" \
		"vec3 ambient = pointlight.u_La * material.u_Ka;" \
		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(lightpos);" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = pointlight.u_Ld * material.u_Kd * tn_dot_ld;" \
		"vec3 view_direction = normalize(u_viewPos - FragPos);" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = pointlight.u_Ls * material.u_Ks * pow(max(dot(reflection_vector,view_direction),0.0),material.u_material_shininess);" \
		"float distance = length(lightpos-FragPos);" \
		"float attenuation = 1.0 / (pointlight.u_constant + pointlight.u_linear * distance + pointlight.u_quadratic * (distance * distance));" \
		/*"ambient = ambient * attenuation;" \*/
		"diffuse = diffuse * attenuation;" \
		"specular = specular * attenuation;" \
		"return(ambient + diffuse + specular);" \
		"}" \

		"vec3 CalculateSpotLight(void)" \
		"{" \
		"vec3 ambient = spotlight.u_La * material.u_Ka;" \

		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(spotlight.u_light_position - FragPos);" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = spotlight.u_Ld * material.u_Kd * tn_dot_ld;" \

		"vec3 view_direction = normalize(u_viewPos - FragPos);" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = spotlight.u_Ls * material.u_Ks * pow(max(dot(reflection_vector,view_direction),0.0),material.u_material_shininess);" \

		"float theta = dot(normalized_light_direction,normalize(-spotlight.u_light_direction));" \
		"float epsilon = (spotlight.u_cutOff - spotlight.u_outerCutOff);" \
		"float intensity = clamp((theta - spotlight.u_outerCutOff) / epsilon, 0.0, 1.0);" \
		"diffuse = diffuse + intensity;" \
		"specular = specular + intensity;" \

		"float distance = length(spotlight.u_light_position-FragPos);" \
		"float attenuation = 1.0 / (spotlight.constant + spotlight.linear * distance + spotlight.quadratic * (distance * distance));" \
		"ambient = ambient * attenuation;" \
		"diffuse = diffuse * attenuation;" \
		"specular = specular * attenuation;" \
		"return(ambient + diffuse + specular);" \
		"}" \

		"void main(void)" \
		"{" \
		"vec3 phong_ads_color;" \
		"if(u_lighting_enabled == 1)" \
		"{" \
		/*"phong_ads_color = CalculatePointLight(u_light_position);" \*/
		"for(int i = 0; i < u_number_of_lights; i++)" \
		"{" \
		"phong_ads_color += CalculatePointLight(u_light_position[i]);" \
		/*"phong_ads_color += CalculateSpotLight();" \*/
		"}" \
		/*"phong_ads_color += CalculateSpotLight();"*/
		"}" \
		"else if(u_lighting_enabled == 0)" \
		"{" \
		"phong_ads_color = vec3(0.0f,0.0f,0.0f);" \
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
				logError("Fragment Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
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
				logError("Shader Program Link Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	gModelMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_model_matrix");
	gViewMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_view_matrix");
	gProjectionMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_projection_matrix");

	gLKeyPressedUniform = glGetUniformLocation(gShaderProgramObject, "u_lighting_enabled");

	gNumberOfLightsUniform = glGetUniformLocation(gShaderProgramObject, "u_number_of_lights");

	//Point Light Uniform
	pointLight.gLaUniform = glGetUniformLocation(gShaderProgramObject, "pointlight.u_La");
	pointLight.gLdUniform = glGetUniformLocation(gShaderProgramObject, "pointlight.u_Ld");
	pointLight.gLsUniform = glGetUniformLocation(gShaderProgramObject, "pointlight.u_Ls");

	//pointLight.gLightPositionUniform = glGetUniformLocation(gShaderProgramObject, "pointlight.u_light_position");
	pointLight.gConstantUniform = glGetUniformLocation(gShaderProgramObject, "pointlight.u_constant");
	pointLight.gLinearUniform = glGetUniformLocation(gShaderProgramObject, "pointlight.u_linear");
	pointLight.gQuadraticUniform = glGetUniformLocation(gShaderProgramObject, "pointlight.u_quadratic");

	materialProperties.gKaUniform = glGetUniformLocation(gShaderProgramObject, "material.u_Ka");
	materialProperties.gKdUniform = glGetUniformLocation(gShaderProgramObject, "material.u_Kd");
	materialProperties.gKsUniform = glGetUniformLocation(gShaderProgramObject, "material.u_Ks");

	materialProperties.gMaterialShininessUniform = glGetUniformLocation(gShaderProgramObject, "material.u_material_shininess");

	gViewPositionUniform = glGetUniformLocation(gShaderProgramObject, "u_viewPos");

	//Spot Light Uniform
	spotLight.gLaUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.u_La");
	spotLight.gLdUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.u_Ld");
	spotLight.gLsUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.u_Ls");
	spotLight.gLightPositionUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.u_light_position");

	spotLight.gConstantUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.constant");
	spotLight.gLinearUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.linear");
	spotLight.gQuadraticUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.quadratic");

	spotLight.gLightDirectionUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.u_light_direction");
	spotLight.gCutOffUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.u_cutOff");
	spotLight.gOuterCutOffUniform = glGetUniformLocation(gShaderProgramObject, "spotlight.u_outerCutOff");

	gLightUniform[0] = glGetUniformLocation(gShaderProgramObject, "u_light_position[0]");
	gLightUniform[1] = glGetUniformLocation(gShaderProgramObject, "u_light_position[1]");
	gLightUniform[2] = glGetUniformLocation(gShaderProgramObject, "u_light_position[2]");
	gLightUniform[3] = glGetUniformLocation(gShaderProgramObject, "u_light_position[3]");
	gLightUniform[4] = glGetUniformLocation(gShaderProgramObject, "u_light_position[4]");
	gLightUniform[5] = glGetUniformLocation(gShaderProgramObject, "u_light_position[5]");
	gLightUniform[6] = glGetUniformLocation(gShaderProgramObject, "u_light_position[6]");
	gLightUniform[7] = glGetUniformLocation(gShaderProgramObject, "u_light_position[7]");
	gLightUniform[8] = glGetUniformLocation(gShaderProgramObject, "u_light_position[8]");
	gLightUniform[9] = glGetUniformLocation(gShaderProgramObject, "u_light_position[9]");
	gLightUniform[10] = glGetUniformLocation(gShaderProgramObject, "u_light_position[10]");
	gLightUniform[11] = glGetUniformLocation(gShaderProgramObject, "u_light_position[11]");
	gLightUniform[12] = glGetUniformLocation(gShaderProgramObject, "u_light_position[12]");
	gLightUniform[13] = glGetUniformLocation(gShaderProgramObject, "u_light_position[13]");
	gLightUniform[14] = glGetUniformLocation(gShaderProgramObject, "u_light_position[14]");
	gLightUniform[15] = glGetUniformLocation(gShaderProgramObject, "u_light_position[15]");
	gLightUniform[16] = glGetUniformLocation(gShaderProgramObject, "u_light_position[16]");
	gLightUniform[17] = glGetUniformLocation(gShaderProgramObject, "u_light_position[17]");
	gLightUniform[18] = glGetUniformLocation(gShaderProgramObject, "u_light_position[18]");
	gLightUniform[19] = glGetUniformLocation(gShaderProgramObject, "u_light_position[19]");
	gLightUniform[20] = glGetUniformLocation(gShaderProgramObject, "u_light_position[20]");
	gLightUniform[21] = glGetUniformLocation(gShaderProgramObject, "u_light_position[21]");
	gLightUniform[22] = glGetUniformLocation(gShaderProgramObject, "u_light_position[22]");
	gLightUniform[23] = glGetUniformLocation(gShaderProgramObject, "u_light_position[23]");
	gLightUniform[24] = glGetUniformLocation(gShaderProgramObject, "u_light_position[24]");
	gLightUniform[25] = glGetUniformLocation(gShaderProgramObject, "u_light_position[25]");
	gLightUniform[26] = glGetUniformLocation(gShaderProgramObject, "u_light_position[26]");
	gLightUniform[27] = glGetUniformLocation(gShaderProgramObject, "u_light_position[27]");
	gLightUniform[28] = glGetUniformLocation(gShaderProgramObject, "u_light_position[28]");
	gLightUniform[29] = glGetUniformLocation(gShaderProgramObject, "u_light_position[29]");
	gLightUniform[30] = glGetUniformLocation(gShaderProgramObject, "u_light_position[30]");
	gLightUniform[31] = glGetUniformLocation(gShaderProgramObject, "u_light_position[31]");
	gLightUniform[32] = glGetUniformLocation(gShaderProgramObject, "u_light_position[32]");
	gLightUniform[33] = glGetUniformLocation(gShaderProgramObject, "u_light_position[33]");

	initializeObjects();

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	gPerspectiveProjectionMatrix = glm::mat4(1.0f);
	cameraPosition = glm::vec3(0.0f, 0.0f, -5.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -100.0f);
	cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = Camera(cameraPosition, cameraTarget, cameraUP);

	QueryPerformanceFrequency((LARGE_INTEGER*)&initFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&initTime);

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void initializeAudio(void)
{
    audioManager = new AudioManager();
    ALboolean audioManagerrInitialize = audioManager->initialize();

    if(!audioManagerrInitialize)
    {
        logError("Not able to initialize audio manager.\n");
    }
    else
    {
        audioManager->setListenerPosition(0.0f, 0.0f, 0.0f);
        audioManager->setListenerVelocity(0.0f, 0.0f, 0.0f);

        alGenBuffers(1, &audioBufferId);

        ALenum error = alGetError();

        if(error != AL_NO_ERROR)
        {
            logError("Not able to create audio buffer, error code: %d\n", error);
        }

        error = AL_NO_ERROR;

        ALboolean waveDataLoaded = audioManager->loadWaveAudio("resources/audio/SpotLightSound.wav", audioBufferId);

        if(!waveDataLoaded)
        {
            logError("Not able to load audio file.\n");
        }

	 	soundSource = new SoundSource();
        soundSource->setSourcef(AL_ROLLOFF_FACTOR, 1.0f);
        soundSource->setSourcef(AL_REFERENCE_DISTANCE, 1.0f);
    }
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

void initializeObjects(void)
{
	/*****************VAO For Gaurage Body*****************/
	glGenVertexArrays(1, &Gaurage_Body.Vao);
	glBindVertexArray(Gaurage_Body.Vao);

	/*****************Gaurage Body Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Body.gv_vertices.size() * sizeof(float), &Gaurage_Body.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Body Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Body.gv_normals.size() * sizeof(float), &Gaurage_Body.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Outer Light*****************/
	glGenVertexArrays(1, &Gaurage_Outer_Light.Vao);
	glBindVertexArray(Gaurage_Outer_Light.Vao);

	/*****************Gaurage Body Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Outer_Light.gv_vertices.size() * sizeof(float), &Gaurage_Outer_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Body Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Outer_Light.gv_normals.size() * sizeof(float), &Gaurage_Outer_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Inner Upper Middle Light*****************/
	glGenVertexArrays(1, &Gaurage_Inner_Upper_Middle_Light.Vao);
	glBindVertexArray(Gaurage_Inner_Upper_Middle_Light.Vao);

	/*****************Gaurage Inner Upper Middle Light Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Inner_Upper_Middle_Light.gv_vertices.size() * sizeof(float), &Gaurage_Inner_Upper_Middle_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Inner Upper Middle Light Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Inner_Upper_Middle_Light.gv_normals.size() * sizeof(float), &Gaurage_Inner_Upper_Middle_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Inner Upper Side Light*****************/
	glGenVertexArrays(1, &Gaurage_Inner_Upper_Side_Light.Vao);
	glBindVertexArray(Gaurage_Inner_Upper_Side_Light.Vao);

	/*****************Gaurage Inner Upper Side Light Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Inner_Upper_Side_Light.gv_vertices.size() * sizeof(float), &Gaurage_Inner_Upper_Side_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Inner Upper Side Light Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Inner_Upper_Side_Light.gv_normals.size() * sizeof(float), &Gaurage_Inner_Upper_Side_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Inner Side Light*****************/
	glGenVertexArrays(1, &Gaurage_Inner_Side_Light.Vao);
	glBindVertexArray(Gaurage_Inner_Side_Light.Vao);

	/*****************Gaurage Inner Side Light Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Inner_Side_Light.gv_vertices.size() * sizeof(float), &Gaurage_Inner_Side_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Inner Side Light Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Gaurage_Inner_Side_Light.gv_normals.size() * sizeof(float), &Gaurage_Inner_Side_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Left Door*****************/
	glGenVertexArrays(1, &Left_Door.Vao);
	glBindVertexArray(Left_Door.Vao);

	/*****************Gaurage Left Door****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Left_Door.gv_vertices.size() * sizeof(float), &Left_Door.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Left Door****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Left_Door.gv_normals.size() * sizeof(float), &Left_Door.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Right Door*****************/
	glGenVertexArrays(1, &Right_Door.Vao);
	glBindVertexArray(Right_Door.Vao);

	/*****************Gaurage Right Door****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Right_Door.gv_vertices.size() * sizeof(float), &Right_Door.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Right Door****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Right_Door.gv_normals.size() * sizeof(float), &Right_Door.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO Mustang*****************/
	glGenVertexArrays(1, &Mustang.Vao);
	glBindVertexArray(Mustang.Vao);

	/*****************Mustang Position****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Mustang.gv_vertices.size() * sizeof(float), &Mustang.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Mustang Normal****************/
	glGenBuffers(1, &gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Mustang.gv_normals.size() * sizeof(float), &Mustang.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	const GLfloat cubeVertices[] =
	{
		1.0f,1.0f,1.0f,
		-1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,1.0f,

		1.0f,1.0f,-1.0f,
		1.0f,1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,

		-1.0f,1.0f,-1.0f,
		1.0f,1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,1.0f,1.0f,
		-1.0f,1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,1.0f,

		1.0f,1.0f,-1.0f,
		-1.0f,1.0f,-1.0f,
		-1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,

		1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f
	};

	/****************Cube************/
	glGenVertexArrays(1, &gVao_Cube);
	glBindVertexArray(gVao_Cube);

	/******************Cube Vertices*****************/
	glGenBuffers(1, &gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindVertexArray(0);
}

void display(void)
{
	float getTime(void);

	currentFrame = getTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//Use Shader Program Object
	glUseProgram(gShaderProgramObject);

	if (gbLight == true)
	{
		if (gbUpper_Middle_Light_On_Flag == true)
			giNumberOfLights = 24;
		if (gbUpper_Side_Light_On_Flag == true)
			giNumberOfLights = 28;
		if (gbInner_Side_Light_On_Flag == true)
			giNumberOfLights = 34;

		glUniform1i(gLKeyPressedUniform, 1);//1 For Material and Light Calculation
		glUniform1i(gNumberOfLightsUniform, giNumberOfLights);

		//Point Light
		glUniform3fv(pointLight.gLaUniform, 1, pointLight.lightAmbient);
		glUniform3fv(pointLight.gLdUniform, 1, pointLight.lightDiffuse);
		glUniform3fv(pointLight.gLsUniform, 1, pointLight.lightSpecular);
		glUniform3fv(pointLight.gLightPositionUniform, 1, pointLight.lightPosition);
		glUniform1f(pointLight.gConstantUniform, pointLight.gConstant);
		glUniform1f(pointLight.gLinearUniform, pointLight.gLinear);
		glUniform1f(pointLight.gQuadraticUniform, pointLight.gQuadratic);

		//Material
		glUniform3fv(materialProperties.gKaUniform, 1, materialProperties.materialAmbient);
		glUniform3fv(materialProperties.gKdUniform, 1, materialProperties.materialDiffuse);
		glUniform3fv(materialProperties.gKsUniform, 1, materialProperties.materialSpecular);
		glUniform1f(materialProperties.gMaterialShininessUniform, materialProperties.materialShininess);
		glUniform3fv(gViewPositionUniform, 1, glm::value_ptr(gViewPosition));

		//Spot Light
		glUniform3fv(spotLight.gLaUniform, 1, spotLight.lightAmbient);
		glUniform3fv(spotLight.gLdUniform, 1, spotLight.lightDiffuse);
		glUniform3fv(spotLight.gLsUniform, 1, spotLight.lightSpecular);
		glUniform3fv(spotLight.gLightPositionUniform, 1, spotLight.lightPosition);
		glUniform1f(spotLight.gConstantUniform, spotLight.gConstant);
		glUniform1f(spotLight.gLinearUniform, spotLight.gLinear);
		glUniform1f(spotLight.gQuadraticUniform, spotLight.gQuadratic);
		glUniform3fv(spotLight.gLightDirectionUniform, 1, spotLight.lightDirection);
		glUniform1f(spotLight.gCutOffUniform, glm::radians(spotLight.cutoff_angle));
		glUniform1f(spotLight.gOuterCutOffUniform, glm::radians(spotLight.outer_cutoff_angle));

		glUniform3fv(gLightUniform[0], 1, pointLight1);
		glUniform3fv(gLightUniform[1], 1, pointLight2);
		glUniform3fv(gLightUniform[2], 1, pointLight3);
		glUniform3fv(gLightUniform[3], 1, pointLight4);
		glUniform3fv(gLightUniform[4], 1, pointLight5);
		glUniform3fv(gLightUniform[5], 1, pointLight6);
		glUniform3fv(gLightUniform[6], 1, pointLight7);
		glUniform3fv(gLightUniform[7], 1, pointLight8);
		glUniform3fv(gLightUniform[8], 1, pointLight9);
		glUniform3fv(gLightUniform[9], 1, pointLight10);
		glUniform3fv(gLightUniform[10], 1, pointLight11);
		glUniform3fv(gLightUniform[11], 1, pointLight12);
		glUniform3fv(gLightUniform[12], 1, pointLight13);
		glUniform3fv(gLightUniform[13], 1, pointLight14);
		glUniform3fv(gLightUniform[14], 1, pointLight15);
		glUniform3fv(gLightUniform[15], 1, pointLight16);
		glUniform3fv(gLightUniform[16], 1, pointLight17);
		glUniform3fv(gLightUniform[17], 1, pointLight18);
		glUniform3fv(gLightUniform[18], 1, pointLight19);
		glUniform3fv(gLightUniform[19], 1, pointLight20);
		glUniform3fv(gLightUniform[20], 1, pointLight21);
		glUniform3fv(gLightUniform[21], 1, pointLight22);
		glUniform3fv(gLightUniform[22], 1, pointLight23);
		glUniform3fv(gLightUniform[23], 1, pointLight24);
		glUniform3fv(gLightUniform[24], 1, pointLight25);
		glUniform3fv(gLightUniform[25], 1, pointLight26);
		glUniform3fv(gLightUniform[26], 1, pointLight27);
		glUniform3fv(gLightUniform[27], 1, pointLight28);
		glUniform3fv(gLightUniform[28], 1, pointLight29);
		glUniform3fv(gLightUniform[29], 1, pointLight30);
		glUniform3fv(gLightUniform[30], 1, pointLight31);
		glUniform3fv(gLightUniform[31], 1, pointLight32);
		glUniform3fv(gLightUniform[32], 1, pointLight33);
		glUniform3fv(gLightUniform[33], 1, pointLight34);

	}
	else
	{
		glUniform1i(gLKeyPressedUniform, 0);//0 For Black Color
	}

	/*************Gaurage Body*************/

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	viewMatrix = camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glBindVertexArray(Gaurage_Body.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Gaurage_Body.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Outer Light*************/

	if (gbLight == true)
	{
		glUniform1i(gLKeyPressedUniform, 2);//White Color
	}
	else
	{
		glUniform1i(gLKeyPressedUniform, 0);
	}

	glBindVertexArray(Gaurage_Outer_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Gaurage_Outer_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Inner Upper Middle Light*************/

	if (gbUpper_Middle_Light_On_Flag == true)
		glUniform1i(gLKeyPressedUniform, 2);//White Color
	else
		glUniform1i(gLKeyPressedUniform, 0);//Black Color

	glBindVertexArray(Gaurage_Inner_Upper_Middle_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Gaurage_Inner_Upper_Middle_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Inner Upper Side Light*************/
	if (gbUpper_Side_Light_On_Flag == true)
		glUniform1i(gLKeyPressedUniform, 2);//White Color
	else
		glUniform1i(gLKeyPressedUniform, 0);//Black Color

	glBindVertexArray(Gaurage_Inner_Upper_Side_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Gaurage_Inner_Upper_Side_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Inner Side Light*************/
	if (gbInner_Side_Light_On_Flag == true)
		glUniform1i(gLKeyPressedUniform, 2);//White Color
	else
		glUniform1i(gLKeyPressedUniform, 0);//Black Color

	glBindVertexArray(Gaurage_Inner_Side_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Gaurage_Inner_Side_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Mustang*************/

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	viewMatrix = camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE + 0.1f, MODEL_Z_TRANSLATE - 43.0f));

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glUniform1i(gLKeyPressedUniform, 1);

	glBindVertexArray(Mustang.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Mustang.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Left Door*************/

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	viewMatrix = camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE + gfLeft_Door_Translate, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(-6.900008, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glUniform1i(gLKeyPressedUniform, 1);

	glBindVertexArray(Left_Door.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Left_Door.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Right Door*************/

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	viewMatrix = camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE + gfRight_Door_Translate, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	//modelMatrix = glm::translate(modelMatrix, glm::vec3(6.900008, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glUniform1i(gLKeyPressedUniform, 1);

	glBindVertexArray(Right_Door.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Right_Door.count_of_vertices);

	glBindVertexArray(0);

	/*******************Cube 1**********************/

	/*modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(pointLight21[0], pointLight21[1], pointLight21[2]));

	viewMatrix = camera.getViewMatrix();

	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.04f, 0.04f, 0.04f));
	modelMatrix = modelMatrix * scaleMatrix;

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glUniform1i(gLKeyPressedUniform, 2);

	glBindVertexArray(gVao_Cube);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);*/

	glUseProgram(0);

	SwapBuffers(ghdc);
}

void update(void)
{
	if (camera_Z_counter < 600)
	{
		camera.MoveCamera(CameraMoveOnZ, -0.06f, deltaTime);
		camera_Z_counter++;
		if (camera_Z_counter == 410)
			gbDoor_Open_Flag = true;
		if (camera_Z_counter == 460)
			gbUpper_Middle_Light_On_Flag = true;
		if (camera_Z_counter == 500)
		{
			gbUpper_Side_Light_On_Flag = true;
			//gbUpper_Middle_Light_On_Flag = false;
		}
		if (camera_Z_counter == 558)
		{
			gbInner_Side_Light_On_Flag = true;
			//gbUpper_Side_Light_On_Flag = false;
			//gbUpper_Middle_Light_On_Flag = false;
		}
	}

	if (gbDoor_Open_Flag == true)
	{
		if (gfLeft_Door_Translate > -6.900008 && gfRight_Door_Translate < 6.900008)
		{
			gfLeft_Door_Translate = gfLeft_Door_Translate - 0.05f;
			gfRight_Door_Translate = gfRight_Door_Translate + 0.05f;
		}
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

	gPerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
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

	if(soundSource != NULL)
    {
        delete soundSource;
        soundSource = NULL;
    }

    if(audioBufferId != 0)
    {
        alDeleteBuffers(1, &audioBufferId);
        audioBufferId = 0;
    }

    if(audioManager != NULL)
    {
        delete audioManager;
        audioManager = NULL;
    }

	if (Gaurage_Body.Vao)
	{
		glDeleteVertexArrays(1, &Gaurage_Body.Vao);
		Gaurage_Body.Vao = 0;
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

	if (i_Exit_Flag == EXIT_FAILURE)
	{
		logError("Program exited erroneously");
	}

	Logger::close();
	DestroyWindow(ghwnd);
}
