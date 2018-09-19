#define _USE_MATH_DEFINES

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "fontRenderer.h"
#include "resources/resource.h"
#include "lib/logger/logger.h"

#define MAIN_CIRCLE_RADIUS 1.0f
#define LEFT_CIRCLE_RADIUS 0.5f
#define SPEED_POINTS_RADIUS 0.8f
#define FUEL_POINTS_RADIUS 0.325f
#define NUMBER_OF_SPEED_POINTS 10
#define NUMBER_OF_FUEL_POINTS 5
#define MIN_SPEED_ANGLE 0.0f
#define MAX_SPEED_ANGLE 270.0f
#define FUEL_JUMP 20.0f
#define MIN_FUEL_ANGLE 0.0f
#define MAX_FUEL_ANGLE 270.0f
#define SPEED_JUMP 30.0f
#define MAIN_CIRCLE_X_TRANSLATION 1.2f
#define MAIN_CIRCLE_Y_TRANSLATION 0.0f
#define LEFT_CIRCLE_X_TRANSLATION -0.25f
#define LEFT_CIRCLE_Y_TRANSLATION -0.5f
#define SPEED_POINT_X_TRANSLATION 1.1f
#define FUEL_POINT_X_TRANSLATION -0.375f
#define FUEL_POINT_Y_TRANSLATION -0.5f
#define Z_TRANSLATION -2.0f
#define Z_TRANSLATION -2.0f

HWND hWnd = NULL;
HDC hdc = NULL;
HGLRC hrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
RECT windowRect = {0, 0, 800, 600};

bool isFullscreen = false;
bool isActive = false;
bool isEscapeKeyPressed = false;

enum
{
    CG_ATTRIBUTE_VERTEX_POSITION = 0,
	CG_ATTRIBUTE_COLOR,
	CG_ATTRIBUTE_NORMAL,
	CG_ATTRIBUTE_TEXTURE0,
};

GLuint vertexShaderObject = 0;
GLuint fragmentShaderObject = 0;
GLuint shaderProgramObject = 0;

GLuint vaoMainCircle = 0;
GLuint vboMainCirclePosition = 0;
GLuint vboMainCircleTexture = 0;

GLuint vaoLeftCircle = 0;
GLuint vboLeftCirclePosition = 0;
GLuint vboLeftCircleTexture = 0;

GLuint vaoSpeedArrow = 0;
GLuint vboSpeedArrowPosition = 0;
GLuint vboSpeedArrowTexture = 0;

GLuint colorUniform = 0;
GLuint textureFlame = 0;
GLuint textureSamplerUniform = 0;
GLuint textureEnabledUniform = 0;
GLuint modelMatrixUniform = 0;
GLuint viewMatrixUniform = 0;
GLuint projectionMatrixUniform = 0;

glm::mat4x4 perspectiveProjectionMatrix;
glm::vec3 color;

int numberOfCirclePoints = 30000;

FontRenderer *fontRenderer = NULL;
std::vector<TextData *> speedPoints;
std::vector<TextData *> fuelPoints;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void initialize(void);
void initializefontRenderer(void);
void initializeSpeedPointText(void);
void initializeFuelPointText(void);
void initializeVertexShader(void);
void initializeFragmentShader(void);
void initializeShaderProgram(void);
void initializeBuffers(void);
void initializeSpeedArrowBuffer(void);
void initializeCircleBuffer(GLuint *vao, GLuint *vboPosition, GLuint *vboTexture, GLfloat radius);
void generateCircleVertices(GLfloat radius, std::vector<GLfloat> *vertices);
void generateCircleTextureCoordinates(std::vector<GLfloat> *textureCoordinates);
void update(void);
void display(void);
void drawCircle(GLuint vao, glm::vec3 position, glm::vec3 color);
void drawSpeedArrow(glm::vec3 position, glm::vec3 scale, GLfloat angle, glm::vec3 color);
void angleToPosition(GLfloat angle, GLfloat radius, glm::vec3 *position);
bool loadGLTextures(GLuint *texture, TCHAR resourceId[]);
void resize(int width, int height);
void toggleFullscreen(HWND hWnd, bool isFullscreen);
void cleanUp(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsatnce, LPSTR lpszCmdLine, int nCmdShow)
{
    WNDCLASSEX wndClassEx;
    MSG message;
    TCHAR szApplicationTitle[] = TEXT("CG Speedometer");
    TCHAR szApplicationClassName[] = TEXT("RTR_OPENGL_SPEEDOMETER");
    bool done = false;

    if(!Logger::initialize("debug.log"))
    {
        printf("Cannot create log file.\n");
    }

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

    isFullscreen = true;
    toggleFullscreen(hWnd, isFullscreen);


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
                break;

                case VK_DOWN:
                break;

                case VK_LEFT:
                break;

                case VK_RIGHT:
                break;

                default:
                break;
            }

        break;

        case WM_CHAR:
            switch(wParam)
            {
                case 'r':
                    color = glm::vec3(1.0f, 0.0f, 0.0f);
                break;

                case 'g':
                    color = glm::vec3(0.0f, 1.0f, 0.0f);
                break;

                case 'b':
                    color = glm::vec3(0.0f, 0.0f, 1.0f);
                break;

                case 'w':
                    color = glm::vec3(1.0f, 1.0f, 1.0f);
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
        logError("Cannot initialize GLEW, Error: %d", glewError);
        cleanUp();
        exit(EXIT_FAILURE);
	}

    initializefontRenderer();
    initializeSpeedPointText();
    initializeFuelPointText();
    initializeVertexShader();
    initializeFragmentShader();
    initializeShaderProgram();
    initializeBuffers();
    initializeSpeedArrowBuffer();

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    perspectiveProjectionMatrix = glm::mat4x4();
    color = glm::vec3(1.0f, 0.0f, 0.0f);

    loadGLTextures(&textureFlame, MAKEINTRESOURCE(FIRE_BMP));

    // This is required for DirectX
    resize(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
}

void initializefontRenderer(void)
{
    fontRenderer = new FontRenderer("resources/fonts/ubuntuMono.ttf", 48);
    FT_Error error = fontRenderer->initialize();

    if(error != 0)
    {
        logInfo("[Error] | Not able to initialize FreeType, error code: %d", error);
        cleanUp();
        exit(EXIT_FAILURE);
    }
}

void initializeSpeedPointText(void)
{
    GLfloat step = (MAX_SPEED_ANGLE - MIN_SPEED_ANGLE) / NUMBER_OF_SPEED_POINTS;

    for(int counter = 0; counter <= NUMBER_OF_SPEED_POINTS; ++counter)
    {
        GLfloat angleRadians = glm::radians(counter * step);
        GLfloat x = SPEED_POINT_X_TRANSLATION + cosf(angleRadians) * SPEED_POINTS_RADIUS;
        GLfloat y = sinf(angleRadians) * SPEED_POINTS_RADIUS;
        GLfloat z = Z_TRANSLATION;

        TextData *textSpeedText = (TextData *)malloc(sizeof(TextData));
        memset(textSpeedText, 0, sizeof(TextData));

        textSpeedText->text = (char *)malloc(sizeof(char) * 4);
        itoa(SPEED_JUMP * (NUMBER_OF_SPEED_POINTS - counter), textSpeedText->text, 10);
        textSpeedText->textSize = strlen(textSpeedText->text);
        textSpeedText->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
        textSpeedText->textPosition = glm::vec3(x, y, z);
        textSpeedText->scale = 0.003f;

        fontRenderer->loadCharacters(textSpeedText->text, textSpeedText->textSize);
        speedPoints.push_back(textSpeedText);
    }
}

void initializeFuelPointText(void)
{
    GLfloat step = (MAX_FUEL_ANGLE - MIN_FUEL_ANGLE) / NUMBER_OF_FUEL_POINTS;

    for(int counter = 0; counter <= NUMBER_OF_FUEL_POINTS; ++counter)
    {
        GLfloat angleRadians = glm::radians(counter * step);
        GLfloat x = FUEL_POINT_X_TRANSLATION + cosf(angleRadians) * FUEL_POINTS_RADIUS;
        GLfloat y = FUEL_POINT_Y_TRANSLATION + sinf(angleRadians) * FUEL_POINTS_RADIUS;
        GLfloat z = Z_TRANSLATION;

        TextData *textFuelText = (TextData *)malloc(sizeof(TextData));
        memset(textFuelText, 0, sizeof(TextData));

        textFuelText->text = (char *)malloc(sizeof(char) * 4);
        itoa(FUEL_JUMP * (NUMBER_OF_FUEL_POINTS - counter), textFuelText->text, 10);
        textFuelText->textSize = strlen(textFuelText->text);
        textFuelText->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
        textFuelText->textPosition = glm::vec3(x, y, z);
        textFuelText->scale = 0.003f;

        fontRenderer->loadCharacters(textFuelText->text, textFuelText->textSize);
        fuelPoints.push_back(textFuelText);
    }
}

void initializeVertexShader()
{
    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

    const GLchar *vertexShaderCode = "#version 450 core" \
        "\n" \
        "in vec4 vertexPosition;" \
        "in vec2 vertexTextureCoordinate0;" \
        "\n" \
        "out vec2 outVertexTextureCoordinate0;" \
        "\n" \
        "uniform mat4x4 modelMatrix;" \
        "uniform mat4x4 viewMatrix;" \
        "uniform mat4x4 projectionMatrix;" \
        "\n" \
        "void main(void)" \
        "{" \
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexPosition;" \
        "   outVertexTextureCoordinate0 = vertexTextureCoordinate0;" \
        "}";

    glShaderSource(vertexShaderObject, 1, (const char**)&vertexShaderCode, NULL);
    glCompileShader(vertexShaderObject);

    GLint infoLogLength = 0;
    GLint shaderCompileStatus = 0;
    char *infoLog = NULL;

    glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &shaderCompileStatus);

    if(shaderCompileStatus == GL_FALSE)
    {
        glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if(infoLogLength > 0)
        {
            infoLog = (char *)malloc(infoLogLength);

            if(infoLog != NULL)
            {
                GLsizei written = 0;
                glGetShaderInfoLog(vertexShaderObject, infoLogLength, &written, infoLog);
                logError("Vertex shader compilation log: %s\n", infoLog);
                free(infoLog);
                cleanUp();
                exit(EXIT_FAILURE);
            }
        }
    }
}

void initializeFragmentShader()
{
    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar *fragmentShaderCode = "#version 450 core" \
        "\n" \
        "in vec2 outVertexTextureCoordinate0;" \
        "\n" \
        "out vec4 fragmentColor;" \
        "\n" \
        "uniform sampler2D textureSampler0;"
        "uniform vec3 color;"
        "uniform int textureEnabled;"
        "\n" \
        "void main(void)" \
        "{" \
        "   if(textureEnabled == 1)" \
        "   {" \
        "       vec4 sampled = texture(textureSampler0, outVertexTextureCoordinate0);" \
        "       fragmentColor = vec4(color, 1.0) * sampled;" \
        "   }" \
        "   else" \
        "   {" \
        "       fragmentColor = vec4(color, 1.0);" \
        "   }" \
        "}";

    glShaderSource(fragmentShaderObject, 1, (const char**)&fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderObject);

    GLint infoLogLength = 0;
    GLint shaderCompileStatus = 0;
    char *infoLog = NULL;

    glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &shaderCompileStatus);

    if(shaderCompileStatus == GL_FALSE)
    {
        glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if(infoLogLength > 0)
        {
            infoLog = (char *)malloc(infoLogLength);

            if(infoLog != NULL)
            {
                GLsizei written = 0;
                glGetShaderInfoLog(fragmentShaderObject, infoLogLength, &written, infoLog);
                logError("Fragment shader compilation log: %s\n", infoLog);
                free(infoLog);
                cleanUp();
                exit(EXIT_FAILURE);
            }
        }
    }
}

void initializeShaderProgram()
{
    shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);

    // Bind the position attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_ATTRIBUTE_VERTEX_POSITION, "vertexPosition");

    // Bind the texture attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_ATTRIBUTE_TEXTURE0, "vertexTextureCoordinate0");

    // Now link and check for error.
    glLinkProgram(shaderProgramObject);

    GLint infoLogLength = 0;
    GLint shaderProgramLinkStatus = 0;
    char *infoLog = NULL;

    glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &shaderProgramLinkStatus);

    if(shaderProgramLinkStatus == GL_FALSE)
    {
        glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if(infoLogLength > 0)
        {
            infoLog = (char *)malloc(infoLogLength);

            if(infoLog != NULL)
            {
                GLsizei written = 0;
                glGetProgramInfoLog(shaderProgramObject, infoLogLength, &written, infoLog);
                logError("Shader program link log: %s\n", infoLog);
                free(infoLog);
                cleanUp();
                exit(EXIT_FAILURE);
            }
        }
    }

    // After linking get the value of modelView and projection uniform location from the shader program.
    modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "modelMatrix");
    viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "viewMatrix");
    projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "projectionMatrix");

    // Get the texture sampler uniform location from shader program.
    textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "textureSampler0");
    colorUniform = glGetUniformLocation(shaderProgramObject, "color");
    textureEnabledUniform = glGetUniformLocation(shaderProgramObject, "textureEnabled");
}

void initializeCircleBuffer(GLuint *vao, GLuint *vboPosition, GLuint *vboTexture, GLfloat radius)
{
    std::vector<GLfloat> circleVertices;
    std::vector<GLfloat> circleTextureCoordinates;
    generateCircleVertices(radius, &circleVertices);
    generateCircleTextureCoordinates(&circleTextureCoordinates);

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vboPosition);
    glBindBuffer(GL_ARRAY_BUFFER, *vboPosition);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circleVertices.size(), circleVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(CG_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_ATTRIBUTE_VERTEX_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, vboTexture);
    glBindBuffer(GL_ARRAY_BUFFER, *vboTexture);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circleTextureCoordinates.size(), circleTextureCoordinates.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(CG_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_ATTRIBUTE_TEXTURE0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void initializeSpeedArrowBuffer()
{
    const GLfloat triangleVertices[] = {
        0.0f, -0.6f, 0.0f,
        -0.04f, 0.0f, 0.0f,
        0.04f, 0.0f, 0.0f
    };

    glGenVertexArrays(1, &vaoSpeedArrow);
    glBindVertexArray(vaoSpeedArrow);

    glGenBuffers(1, &vboSpeedArrowPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vboSpeedArrowPosition);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(CG_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_ATTRIBUTE_VERTEX_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void initializeBuffers(void)
{
    initializeCircleBuffer(&vaoMainCircle, &vboMainCirclePosition, &vboMainCircleTexture, MAIN_CIRCLE_RADIUS);
    initializeCircleBuffer(&vaoLeftCircle, &vboLeftCirclePosition, &vboLeftCircleTexture, LEFT_CIRCLE_RADIUS);
    initializeSpeedArrowBuffer();
}

void generateCircleVertices(GLfloat radius, std::vector<GLfloat> *vertices)
{
    for (int pointCounter = 0; pointCounter <= numberOfCirclePoints; ++pointCounter)
    {
        GLfloat angle = (2.0f * M_PI * pointCounter / numberOfCirclePoints);
        GLfloat xCos = cosf(angle);
        GLfloat ySin = sinf(angle);
        GLfloat x = xCos * radius;
        GLfloat y = ySin * radius;
        GLfloat z = 0.0f;
        vertices->push_back(x);
        vertices->push_back(y);
        vertices->push_back(z);
    }
}

void generateCircleTextureCoordinates(std::vector<GLfloat> *textureCoordinates)
{
    for (int pointCounter = 0; pointCounter <= numberOfCirclePoints; ++pointCounter)
    {
        GLfloat angle = (2.0f * M_PI * pointCounter / numberOfCirclePoints);
        GLfloat xCos = cosf(angle);
        GLfloat ySin = sinf(angle);
        textureCoordinates->push_back((xCos + 1.0f) * 0.5f);
        textureCoordinates->push_back((ySin + 1.0f) * 0.5f);
    }
}

void update(void)
{
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glUseProgram(shaderProgramObject);

    glm::mat4x4 viewMatrix = glm::mat4x4();
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjectionMatrix));

    drawCircle(vaoMainCircle, glm::vec3(MAIN_CIRCLE_X_TRANSLATION, MAIN_CIRCLE_Y_TRANSLATION, Z_TRANSLATION), color);
    drawCircle(vaoLeftCircle, glm::vec3(LEFT_CIRCLE_X_TRANSLATION, LEFT_CIRCLE_Y_TRANSLATION, Z_TRANSLATION), color);

    drawSpeedArrow(glm::vec3(MAIN_CIRCLE_X_TRANSLATION, 0.0f, Z_TRANSLATION), glm::vec3(1.0f, 1.0f, 1.0f), -200.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    drawSpeedArrow(glm::vec3(LEFT_CIRCLE_X_TRANSLATION, LEFT_CIRCLE_Y_TRANSLATION, Z_TRANSLATION), glm::vec3(0.5f, 0.5f, 0.5f), -180.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    // The font renderer has its own program object, hence stop using current program.
    glUseProgram(0);

    for(int counter = 0; counter < speedPoints.size(); ++counter)
    {
        fontRenderer->renderText(speedPoints[counter], glm::mat4x4(), viewMatrix, perspectiveProjectionMatrix);
    }

    for(int counter = 0; counter < fuelPoints.size(); ++counter)
    {
        fontRenderer->renderText(fuelPoints[counter], glm::mat4x4(), viewMatrix, perspectiveProjectionMatrix);
    }

    SwapBuffers(hdc);
}

void angleToPosition(GLfloat angle, GLfloat radius, glm::vec3 *position)
{
    GLfloat angleRadians = glm::radians(angle);
    GLfloat x = cosf(angleRadians) * radius;
    GLfloat y = sinf(angleRadians) * radius;
    GLfloat z = Z_TRANSLATION;

    glm::vec3 positionLocal = glm::vec3(x, y, z);
    position = &positionLocal;
}

void drawCircle(GLuint vao, glm::vec3 position, glm::vec3 color)
{
    glm::mat4x4 modelMatrix = glm::mat4x4();
    modelMatrix = glm::translate(modelMatrix, position);
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, textureFlame);
    glUniform1i(textureSamplerUniform, 0);
    glUniform3fv(colorUniform, 1, glm::value_ptr(color));
    glUniform1i(textureEnabledUniform, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, (numberOfCirclePoints + 1) * 3);
    glBindVertexArray(0);
}

void drawSpeedArrow(glm::vec3 position, glm::vec3 scale, GLfloat angle, glm::vec3 color)
{
    glm::mat4x4 modelMatrix = glm::mat4x4();
    glm::mat4x4 translationMatrix = glm::mat4x4();
    glm::mat4x4 scaleMatrix = glm::mat4x4();
    glm::mat4x4 rotationMatrix = glm::mat4x4();

    scaleMatrix = glm::scale(scaleMatrix, scale);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    translationMatrix = glm::translate(translationMatrix, position);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));


    glBindVertexArray(vaoSpeedArrow);
    glUniform3fv(colorUniform, 1, glm::value_ptr(color));
    glUniform1i(textureEnabledUniform, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

bool loadGLTextures(GLuint *texture, TCHAR resourceId[])
{
	bool textureLoaded = false;
	BITMAP bmp;
	HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), resourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (hBitmap)
	{
		textureLoaded = true;
		GetObject(hBitmap, sizeof(bmp), &bmp);
	    glGenTextures(1, texture);
        // For programmable pipeline set 1 instead of 4 for better performation.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Generate the mipmapped texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.bmWidth, bmp.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		glGenerateMipmap(GL_TEXTURE_2D);
        DeleteObject(hBitmap);

        // Unbind the texture else the last loaded texture will be shown in display
        // if we forgot to specify to which texture to bind in display.
        glBindTexture(GL_TEXTURE_2D, 0);
	}

	return textureLoaded;
}

void resize(int width, int height)
{
    if(height == 0)
    {
        height = 1;
    }

    GLsizei viewportWidth = 400;
    GLsizei viewportHeight = 200;
    GLsizei viewportX = width - viewportWidth;
    GLsizei viewportY = 0;
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    perspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)viewportWidth / (GLfloat)viewportHeight, 1.0f, 100.0f);
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

    for(int counter = 0; counter < speedPoints.size(); ++counter)
    {
        free(speedPoints[counter]->text);
        free(speedPoints[counter]);
    }

    speedPoints.clear();

    for(int counter = 0; counter < fuelPoints.size(); ++counter)
    {
        free(fuelPoints[counter]->text);
        free(fuelPoints[counter]);
    }

    fuelPoints.clear();

    if(fontRenderer != NULL)
    {
        delete fontRenderer;
        fontRenderer = NULL;
    }

    if(vaoSpeedArrow)
    {
        glDeleteVertexArrays(1, &vaoSpeedArrow);
        vaoSpeedArrow = 0;
    }

    if(vboMainCirclePosition)
    {
        glDeleteBuffers(1, &vboSpeedArrowPosition);
        vboSpeedArrowPosition = 0;
    }

    if(vboMainCircleTexture)
    {
        glDeleteBuffers(1, &vboMainCircleTexture);
        vboMainCircleTexture = 0;
    }

    if(vaoMainCircle)
    {
        glDeleteVertexArrays(1, &vaoMainCircle);
        vaoMainCircle = 0;
    }

    if(vaoLeftCircle)
    {
        glDeleteVertexArrays(1, &vaoLeftCircle);
        vaoLeftCircle = 0;
    }

    if(vboMainCircleTexture)
    {
        glDeleteBuffers(1, &vboMainCircleTexture);
        vboMainCircleTexture = 0;
    }

    if(vboLeftCirclePosition)
    {
        glDeleteBuffers(1, &vboLeftCirclePosition);
        vboLeftCirclePosition = 0;
    }

    if(vboMainCircleTexture)
    {
        glDeleteBuffers(1, &vboMainCircleTexture);
        vboMainCircleTexture = 0;
    }

    if(vboLeftCircleTexture)
    {
        glDeleteBuffers(1, &vboLeftCircleTexture);
        vboLeftCircleTexture = 0;
    }

    if(shaderProgramObject)
    {
        if(vertexShaderObject)
        {
            glDetachShader(shaderProgramObject, vertexShaderObject);
        }

        if(fragmentShaderObject)
        {
            glDetachShader(shaderProgramObject, fragmentShaderObject);
        }
    }

    if(vertexShaderObject)
    {
        glDeleteShader(vertexShaderObject);
        vertexShaderObject = 0;
    }

    if(fragmentShaderObject)
    {
        glDeleteShader(fragmentShaderObject);
        fragmentShaderObject = 0;
    }

    if(shaderProgramObject)
    {
        glDeleteProgram(shaderProgramObject);
        shaderProgramObject = 0;
    }

    glUseProgram(0);

    if(textureFlame != 0)
    {
        glDeleteTextures(1, &textureFlame);
        textureFlame = 0;
    }

    wglMakeCurrent(NULL, NULL);

    wglDeleteContext(hrc);
    hrc = NULL;

    ReleaseDC(hWnd, hdc);
    hdc = NULL;

    DestroyWindow(hWnd);
    hWnd = NULL;

    Logger::close();
}
