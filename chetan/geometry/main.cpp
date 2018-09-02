#include <windows.h>
#include <stdio.h>
#include <gl/glew.h>
#include <gl/gl.h>

#include "resources/resource.h"
#include "logger.h"
#include "pyramid.h"

HWND hWnd = NULL;
HDC hdc = NULL;
HGLRC hrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
RECT windowRect = {0, 0, 800, 600};

bool isFullscreen = false;
bool isActive = false;
bool isEscapeKeyPressed = false;
bool isLightingEnabled = false;
bool isAnimationEnabled = false;

GLuint modelMatrixUniform = 0;
GLuint viewMatrixUniform = 0;
GLuint projectionMatrixUniform = 0;
GLuint laZeroUniform = 0;
GLuint ldZeroUniform = 0;
GLuint lsZeroUniform = 0;
GLuint laOneUniform = 0;
GLuint ldOneUniform = 0;
GLuint lsOneUniform = 0;
GLuint kaUniform = 0;
GLuint kdUniform = 0;
GLuint ksUniform = 0;
GLuint materialShininessUniform = 0;
GLuint lightZeroPositionUniform = 0;
GLuint lightOnePositionUniform = 0;
GLuint isLightingEnabledUniform = 0;

glm::mat4 perspectiveProjectionMatrix;
glm::vec3 modalTranslate = glm::vec3(0.0f, 0.0f, -6.0f);

GLfloat lightZeroAmbient[] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat lightZeroDiffuse[] = {1.0f, 0.0f, 0.0f, 0.0f};
GLfloat lightZeroSpecular[] = {1.0f, 0.0f, 0.0f, 0.0f};
GLfloat lightZeroPosition[] = {2.0f, 1.0f, 1.0f, 0.0f};

GLfloat lightOneAmbient[] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat lightOneDiffuse[] = {0.0f, 0.0f, 1.0f, 0.0f};
GLfloat lightOneSpecular[] = {0.0f, 0.0f, 1.0f, 0.0f};
GLfloat lightOnePosition[] = {-2.0f, 1.0f, 1.0f, 0.0f};

GLfloat materialAmbient[] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat materialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 0.0f};
GLfloat materialShininess = 50.0f;

GLfloat anglePyramid = 0.0f;
GLfloat speed = 0.01f;

Pyramid *pyramid = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void initialize(void);
GLint initializePyramid(void);
void initializePyramidUniform(void);
void initializePyramidBuffers(void);
void cleanUp(void);
void update(void);
void display(void);
void drawPyramid(void);
void resize(int width, int height);
void toggleFullscreen(HWND hWnd, bool isFullscreen);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsatnce, LPSTR lpszCmdLine, int nCmdShow)
{
    WNDCLASSEX wndClassEx;
    MSG message;
    TCHAR szApplicationTitle[] = TEXT("CG - Geometry");
    TCHAR szApplicationClassName[] = TEXT("RTR_OPENGL_GEOMETRY");
    bool done = false;

    Logger::initialize("debug.log");

    wndClassEx.cbSize = sizeof(WNDCLASSEX);
    wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndClassEx.cbClsExtra = 0;
    wndClassEx.cbWndExtra = 0;
    wndClassEx.lpfnWndProc = WndProc;
    wndClassEx.hInstance = hInstance;
    wndClassEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(CP_ICON));
    wndClassEx.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(CP_ICON_SMALL));
    wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClassEx.lpszClassName = szApplicationClassName;
    wndClassEx.lpszMenuName = NULL;

    if(!RegisterClassEx(&wndClassEx))
    {
        MessageBox(NULL, TEXT("Cannot register class."), TEXT("Error"), MB_OK | MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    DWORD styleExtra = WS_EX_APPWINDOW;
    dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;

    hWnd = CreateWindowEx(styleExtra,
        szApplicationClassName,
        szApplicationTitle,
        dwStyle,
        windowRect.left,
        windowRect.top,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,
        NULL,
        hInstance,
        NULL);

    if(!hWnd)
    {
        MessageBox(NULL, TEXT("Cannot create windows."), TEXT("Error"), MB_OK | MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    initialize();

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    SetForegroundWindow(hWnd);
    SetFocus(hWnd);

    while(!done)
    {
        if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if(message.message == WM_QUIT)
            {
                done = true;
            }
            else
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
        else
        {
            if(isActive)
            {
                if(isEscapeKeyPressed)
                {
                    done = true;
                }
                else
                {
                    update();
                    display();
                }
            }
        }
    }

    cleanUp();
    return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    RECT rect;

    switch(iMessage)
    {
        case WM_ACTIVATE:
            isActive = (HIWORD(wParam) == 0);
        break;

        case WM_SIZE:
            resize(LOWORD(lParam), HIWORD(lParam));
        break;

        case WM_KEYDOWN:
            switch(wParam)
            {
                case VK_ESCAPE:
                    isEscapeKeyPressed = true;
                break;

                // 0x46 is hex value for key 'F' or 'f'
                case 0x46:
                    isFullscreen = !isFullscreen;
                    toggleFullscreen(hWnd, isFullscreen);
                break;

                case VK_UP:
                    modalTranslate[1] += speed;
                break;

                case VK_DOWN:
                    modalTranslate[1] -= speed;
                break;

                case VK_LEFT:
                    modalTranslate[0] -= speed;
                break;

                case VK_RIGHT:
                    modalTranslate[0] += speed;
                break;

                default:
                break;
            }

            if(wParam > 0x30 && wParam < 0x40)
            {
                speed = 0.1f * (wParam - 0x30);
            }
            else if(wParam > 0x60 && wParam < 0x70)
            {
                speed = 0.1f * (wParam - 0x60);
            }

        break;

        case WM_CHAR:
            switch(wParam)
            {
                case 'A':
                case 'a':
                    isAnimationEnabled = !isAnimationEnabled;
                break;

                case 'L':
                case 'l':
                    isLightingEnabled = !isLightingEnabled;
                break;

                default:
                break;
            }

        break;

        case WM_LBUTTONDOWN:
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
        break;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void initialize(void)
{
    PIXELFORMATDESCRIPTOR pfd;
    int pixelFormatIndex = 0;

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

    hdc = GetDC(hWnd);

    pixelFormatIndex = ChoosePixelFormat(hdc, &pfd);

    if(pixelFormatIndex == 0)
    {
        ReleaseDC(hWnd, hdc);
        hdc = NULL;
    }

    if(!SetPixelFormat(hdc, pixelFormatIndex, &pfd))
    {
        ReleaseDC(hWnd, hdc);
        hdc = NULL;
    }

    hrc = wglCreateContext(hdc);
    if(hrc == NULL)
    {
        ReleaseDC(hWnd, hdc);
        hdc = NULL;
    }

    if(!wglMakeCurrent(hdc, hrc))
    {
        wglDeleteContext(hrc);
        hrc = NULL;

        ReleaseDC(hWnd, hdc);
        hdc = NULL;
    }

    GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
        logError("Cannot initialize GLEW, error code: %d", glewError);

        cleanUp();
        exit(EXIT_FAILURE);
	}

    // Initialize the pyramid;
    GLint pyramidInitialized = initializePyramid();

    if(pyramidInitialized == GL_FALSE)
    {
        cleanUp();
        exit(EXIT_FAILURE);
    }

    initializePyramidUniform();
    initializePyramidBuffers();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

    // Disable face culling to see back side of object when rotated.
    // glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    perspectiveProjectionMatrix = glm::mat4();

    isAnimationEnabled = false;
    isLightingEnabled = true;

    // This is required for DirectX
    resize(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
}

GLint initializePyramid(void)
{
    char *error = NULL;
    ShaderProgramBindAttributes bindAttributes;
    memset((void *)&bindAttributes, 0, sizeof(ShaderProgramBindAttributes));

    bindAttributes.vertexPosition = "vertexPosition";
    bindAttributes.normal = "vertexNormal";

    const GLchar *vertexShaderCode = "#version 450 core" \
        "\n" \
        "in vec4 vertexPosition;" \
        "in vec3 vertexNormal;" \
        "\n" \
        "out vec3 tNormal;" \
		"out vec3 lightZeroDirection;" \
		"out vec3 lightOneDirection;" \
		"out vec3 viewVector;" \
		"\n" \
        "uniform mat4 modelMatrix;" \
        "uniform mat4 viewMatrix;" \
        "uniform mat4 projectionMatrix;" \
        "uniform vec4 lightZeroPosition;" \
        "uniform vec4 lightOnePosition;" \
        "uniform int isLightingEnabled;" \
        "\n" \
        "void main(void)" \
        "{" \
        "   if(isLightingEnabled == 1)" \
        "   {" \
        "       vec4 eyeCoordinates = viewMatrix * modelMatrix * vertexPosition;" \
        "       tNormal = mat3(viewMatrix * modelMatrix) * vertexNormal;" \
        "       lightZeroDirection = vec3(lightZeroPosition) - eyeCoordinates.xyz;" \
        "       lightOneDirection = vec3(lightOnePosition) - eyeCoordinates.xyz;" \
        "       viewVector = -eyeCoordinates.xyz;" \
        "   }" \
        "\n" \
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexPosition;" \
        "}";

    const GLchar *fragmentShaderCode = "#version 450 core" \
        "\n" \
		"in vec3 tNormal;" \
		"in vec3 lightZeroDirection;" \
		"in vec3 lightOneDirection;" \
		"in vec3 viewVector;" \
        "\n" \
        "out vec4 fragmentColor;" \
        "\n" \
        "uniform int isLightingEnabled;" \
        "uniform vec3 laZero;" \
        "uniform vec3 ldZero;" \
        "uniform vec3 lsZero;" \
        "uniform vec3 laOne;" \
        "uniform vec3 ldOne;" \
        "uniform vec3 lsOne;" \
        "uniform vec3 ka;" \
        "uniform vec3 kd;" \
        "uniform vec3 ks;" \
        "uniform float materialShininess;" \
        "\n" \
        "void main(void)" \
        "{" \
        "   vec3 phongAdsColor;" \
        "   if(isLightingEnabled == 1)" \
        "   {" \
        "       vec3 normalizedTNormal = normalize(tNormal);" \
        "       vec3 normalizedViewVector = normalize(viewVector);" \
        "\n" \
        "       vec3 normalizedLightZeroDirection = normalize(lightZeroDirection);" \
        "       float tNormalDotLightZeroDirection = max(dot(normalizedTNormal, normalizedLightZeroDirection), 0.0);" \
        "       vec3 ambientLightZero = laZero * ka;" \
        "       vec3 diffuseLightZero = ldZero * kd * tNormalDotLightZeroDirection;" \
        "       vec3 reflectionVectorLightZero = reflect(-normalizedLightZeroDirection, normalizedTNormal);" \
        "       vec3 specularLightZero = lsZero * ks * pow(max(dot(reflectionVectorLightZero, normalizedViewVector), 0.0), materialShininess);" \
        "\n" \
        "       vec3 normalizedLightOneDirection = normalize(lightOneDirection);" \
        "       float tNormalDotLightOneDirection = max(dot(normalizedTNormal, normalizedLightOneDirection), 0.0);" \
        "       vec3 ambientLightOne = laOne * ka;" \
        "       vec3 diffuseLightOne = ldOne * kd * tNormalDotLightOneDirection;" \
        "       vec3 reflectionVectorLightOne = reflect(-normalizedLightOneDirection, normalizedTNormal);" \
        "       vec3 specularLightOne = lsOne * ks * pow(max(dot(reflectionVectorLightOne, normalizedViewVector), 0.0), materialShininess);" \
        "\n" \
        "       phongAdsColor = ambientLightZero + diffuseLightZero + specularLightZero + ambientLightOne + diffuseLightOne + specularLightOne;" \
        "   }" \
        "   else" \
        "   {" \
        "       phongAdsColor = vec3(1.0, 1.0, 1.0);" \
        "   }" \
        "\n" \
        "   fragmentColor = vec4(phongAdsColor, 1.0);" \
        "}";

    pyramid = new Pyramid();
	GLint initialized = pyramid->initialize(vertexShaderCode, fragmentShaderCode, bindAttributes, &error);

	if(initialized == GL_FALSE && error != NULL)
    {
        logError("Not able to initialized pyramid, error message: %s\n", error);
        free(error);
        error = NULL;
    }

    return initialized;
}

void initializePyramidUniform(void)
{
    modelMatrixUniform = pyramid->getUniformLocation("modelMatrix");
    viewMatrixUniform = pyramid->getUniformLocation("viewMatrix");
    projectionMatrixUniform = pyramid->getUniformLocation("projectionMatrix");
    isLightingEnabledUniform = pyramid->getUniformLocation("isLightingEnabled");
    laZeroUniform = pyramid->getUniformLocation("laZero");
    ldZeroUniform = pyramid->getUniformLocation("ldZero");
    lsZeroUniform = pyramid->getUniformLocation("lsZero");
    laOneUniform = pyramid->getUniformLocation("laOne");
    ldOneUniform = pyramid->getUniformLocation("ldOne");
    lsOneUniform = pyramid->getUniformLocation("lsOne");
    kaUniform = pyramid->getUniformLocation("ka");
    kdUniform = pyramid->getUniformLocation("kd");
    ksUniform = pyramid->getUniformLocation("ks");
    lightZeroPositionUniform = pyramid->getUniformLocation("lightZeroPosition");
    lightOnePositionUniform = pyramid->getUniformLocation("lightOnePosition");
    materialShininessUniform = pyramid->getUniformLocation("materialShininess");

    logInfo("modelMatrix: %d\n", modelMatrixUniform);
    logInfo("viewMatrix: %d\n", viewMatrixUniform);
    logInfo("projectionMatrix: %d\n", projectionMatrixUniform);
    logInfo("isLightingEnabled: %d\n", isLightingEnabledUniform);
    logInfo("laZero: %d\n", laZeroUniform);
    logInfo("ldZero: %d\n", ldZeroUniform);
    logInfo("lsZero: %d\n", lsZeroUniform);
    logInfo("laOne: %d\n", laOneUniform);
    logInfo("ldOne: %d\n", ldOneUniform);
    logInfo("lsOne: %d\n", lsOneUniform);
    logInfo("ka: %d\n", kaUniform);
    logInfo("kd: %d\n", kdUniform);
    logInfo("ks: %d\n", ksUniform);
    logInfo("lightZeroPosition: %d\n", lightZeroPositionUniform);
    logInfo("lightOnePosition: %d\n", lightOnePositionUniform);
    logInfo("materialShininess: %d\n", materialShininessUniform);
}

void initializePyramidBuffers()
{
    GLfloat pyramidVerticesArray[] = {
        // Front face
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        // Right face
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,

        // Back face
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        // Left face
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f
    };

    GLfloat pyramidNormalsArray[] = {
        // Front face
        0.0f, 0.447214f, 0.894427f,
        0.0f, 0.447214f, 0.894427f,
        0.0f, 0.447214f, 0.894427f,

        // Right face
        0.894427f, 0.447214f, 0.0f,
        0.894427f, 0.447214f, 0.0f,
        0.894427f, 0.447214f, 0.0f,

        // Back face
        0.0f, 0.447214f, -0.894427f,
        0.0f, 0.447214f, -0.894427f,
        0.0f, 0.447214f, -0.894427f,

        // Left face
        -0.894427f, 0.447214f, 0.0f,
        -0.894427f, 0.447214f, 0.0f,
        -0.894427f, 0.447214f, 0.0f
    };

    std::vector<GLfloat> pyramidVertices;
    std::vector<GLfloat> pyramidNormals;

    for(int counter = 0; counter < sizeof(pyramidVerticesArray) / sizeof(pyramidVerticesArray[0]); ++counter)
    {
        pyramidVertices.push_back(pyramidVerticesArray[counter]);
    }

    for(int counter = 0; counter < sizeof(pyramidNormalsArray) / sizeof(pyramidNormalsArray[0]); ++counter)
    {
        pyramidNormals.push_back(pyramidNormalsArray[counter]);
    }

    logInfo("pyramidVertices.size(): %d\n", pyramidVertices.size());

    pyramid->setVertexPosition(pyramidVertices);
    pyramid->setNormals(pyramidNormals);
}

void update(void)
{
    if(isAnimationEnabled)
    {
        anglePyramid += speed;

        if(anglePyramid >= 360.0f)
        {
            anglePyramid = 0.0f;
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    pyramid->startRendering();

    // if(isLightingEnabled)
    // {
        pyramid->setUniform1i(isLightingEnabledUniform, 1);

        pyramid->setUniform3fv(laZeroUniform, 1, lightZeroAmbient);
        pyramid->setUniform3fv(ldZeroUniform, 1, lightZeroDiffuse);
        pyramid->setUniform3fv(lsZeroUniform, 1, lightZeroSpecular);

        pyramid->setUniform3fv(laOneUniform, 1, lightOneAmbient);
        pyramid->setUniform3fv(ldOneUniform, 1, lightOneDiffuse);
        pyramid->setUniform3fv(lsOneUniform, 1, lightOneSpecular);

        pyramid->setUniform4fv(lightZeroPositionUniform, 1, lightZeroPosition);
        pyramid->setUniform4fv(lightOnePositionUniform, 1, lightOnePosition);

        pyramid->setUniform3fv(kaUniform, 1, materialAmbient);
        pyramid->setUniform3fv(kdUniform, 1, materialDiffuse);
        pyramid->setUniform3fv(ksUniform, 1, materialSpecular);
        pyramid->setUniform1f(materialShininessUniform, materialShininess);
    // }
    // else
    // {
    //     pyramid->setUniform1i(isLightingEnabledUniform, 0);
    // }

    glm::mat4 modelMatrix = glm::mat4();
    glm::mat4 viewMatrix = glm::mat4();

    pyramid->setModelMatrix(modelMatrix);
    pyramid->setViewMatrix(modelMatrix);
    pyramid->translate(modalTranslate);
    pyramid->rotate(anglePyramid, glm::vec3(0.0f, 1.0f, 0.0f));
    pyramid->setUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    pyramid->setUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    pyramid->setUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjectionMatrix));
    pyramid->render(12);
    pyramid->stopRendering();

    SwapBuffers(hdc);
}

void resize(int width, int height)
{
    if(height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    perspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
}

void toggleFullscreen(HWND hWnd, bool isFullscreen)
{
    MONITORINFO monitorInfo;
    dwStyle = GetWindowLong(hWnd, GWL_STYLE);

    if(isFullscreen)
    {
        if(dwStyle & WS_OVERLAPPEDWINDOW)
        {
            monitorInfo = { sizeof(MONITORINFO) };

            if(GetWindowPlacement(hWnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(hWnd, MONITORINFOF_PRIMARY), &monitorInfo))
            {
                SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(hWnd, HWND_TOP, monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top, monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }

        ShowCursor(FALSE);
    }
    else
    {
        SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(hWnd, &wpPrev);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        ShowCursor(TRUE);
    }
}

void cleanUp(void)
{
    if(isFullscreen)
    {
        dwStyle = GetWindowLong(hWnd, GWL_STYLE);
        SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(hWnd, &wpPrev);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        ShowCursor(TRUE);
    }

    if(pyramid != NULL)
    {
        delete pyramid;
        pyramid = NULL;
    }

    glUseProgram(0);
    wglMakeCurrent(NULL, NULL);

    wglDeleteContext(hrc);
    hrc = NULL;

    ReleaseDC(hWnd, hdc);
    hdc = NULL;

    DestroyWindow(hWnd);
    hWnd = NULL;

    Logger::close();
}
