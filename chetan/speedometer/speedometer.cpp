#pragma once

#define _USE_MATH_DEFINES

#include "speedometer.h"
#include "resources/resource.h"
#include "lib/logger/logger.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <chrono>

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

Speedometer::Speedometer()
{
    logInfo("Speedometer created.\n");
    speedAngle = MIN_SPEED_ANGLE;
    fuelAngle = MAX_FUEL_ANGLE;
}

void Speedometer::initialize(void)
{
    initializefontRenderer();
    initializeSpeedPointText();
    initializeFuelPointText();
    initializeVertexShader();
    initializeFragmentShader();
    initializeShaderProgram();
    initializeBuffers();
    initializeSpeedArrowBuffer();

    perspectiveProjectionMatrix = glm::mat4x4();
    color = glm::vec3(1.0f, 1.0f, 1.0f);

    bool flameTestureLoaded = loadGLTextures(&textureFlame, MAKEINTRESOURCE(FIRE_BMP));

	if (!flameTestureLoaded)
	{
		logError("Not able to load flame texture.");
	}
}

void Speedometer::initializefontRenderer(void)
{
    fontRenderer = new FontRenderer("resources/fonts/arial.ttf", 48);
    FT_Error error = fontRenderer->initialize();

    if(error != 0)
    {
        logError("Not able to initialize FreeType, error code: %d\n", error);
    }
}

void Speedometer::initializeSpeedPointText(void)
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
        _itoa_s((int)SPEED_JUMP * (NUMBER_OF_SPEED_POINTS - counter), textSpeedText->text, sizeof(char) * 5, 10);
        textSpeedText->textSize = strlen(textSpeedText->text);
        textSpeedText->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
        textSpeedText->textPosition = glm::vec3(x, y, z);
        textSpeedText->scale = 0.003f;

        fontRenderer->loadCharacters(textSpeedText);
        speedPoints.push_back(textSpeedText);
    }
}

void Speedometer::initializeFuelPointText(void)
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
        _itoa_s((int)FUEL_JUMP * (NUMBER_OF_FUEL_POINTS - counter), textFuelText->text, sizeof(char) * 4, 10);
        textFuelText->textSize = strlen(textFuelText->text);
        textFuelText->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
        textFuelText->textPosition = glm::vec3(x, y, z);
        textFuelText->scale = 0.003f;

        fontRenderer->loadCharacters(textFuelText);
        fuelPoints.push_back(textFuelText);
    }
}

void Speedometer::initializeVertexShader(void)
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
            }
        }
    }
}

void Speedometer::initializeFragmentShader()
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
            }
        }
    }
}

void Speedometer::initializeShaderProgram(void)
{
    shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);

    // Bind the position attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_SPEEDOMETER_ATTRIBUTE_VERTEX_POSITION, "vertexPosition");

    // Bind the texture attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_SPEEDOMETER_ATTRIBUTE_TEXTURE0, "vertexTextureCoordinate0");

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

void Speedometer::initializeCircleBuffer(GLuint *vao, GLuint *vboPosition, GLuint *vboTexture, GLfloat radius)
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
    glVertexAttribPointer(CG_SPEEDOMETER_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_SPEEDOMETER_ATTRIBUTE_VERTEX_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, vboTexture);
    glBindBuffer(GL_ARRAY_BUFFER, *vboTexture);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circleTextureCoordinates.size(), circleTextureCoordinates.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(CG_SPEEDOMETER_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_SPEEDOMETER_ATTRIBUTE_TEXTURE0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Speedometer::initializeSpeedArrowBuffer(void)
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
    glVertexAttribPointer(CG_SPEEDOMETER_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_SPEEDOMETER_ATTRIBUTE_VERTEX_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Speedometer::initializeBuffers(void)
{
    initializeCircleBuffer(&vaoMainCircle, &vboMainCirclePosition, &vboMainCircleTexture, MAIN_CIRCLE_RADIUS);
    initializeCircleBuffer(&vaoLeftCircle, &vboLeftCirclePosition, &vboLeftCircleTexture, LEFT_CIRCLE_RADIUS);
    initializeSpeedArrowBuffer();
}

void Speedometer::generateCircleVertices(GLfloat radius, std::vector<GLfloat> *vertices)
{
    for(int pointCounter = 0; pointCounter <= numberOfCirclePoints; ++pointCounter)
    {
        GLfloat angle = (GLfloat)(2.0f * M_PI * pointCounter / numberOfCirclePoints);
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

void Speedometer::generateCircleTextureCoordinates(std::vector<GLfloat> *textureCoordinates)
{
    for(int pointCounter = 0; pointCounter <= numberOfCirclePoints; ++pointCounter)
    {
        GLfloat angle = (GLfloat)(2.0f * M_PI * pointCounter / numberOfCirclePoints);
        GLfloat xCos = cosf(angle);
        GLfloat ySin = sinf(angle);
        textureCoordinates->push_back((xCos + 1.0f) * 0.5f);
        textureCoordinates->push_back((ySin + 1.0f) * 0.5f);
    }
}

void Speedometer::setSpeed(float speed)
{
    float maxSpeed = SPEED_JUMP * NUMBER_OF_SPEED_POINTS;
    this->speedAngle = MAX_SPEED_ANGLE / maxSpeed * speed;

    if(this->speedAngle > MAX_SPEED_ANGLE)
    {
        this->speedAngle = MAX_SPEED_ANGLE;
    }
    else if(this->speedAngle < 0.0f)
    {
        this->speedAngle = 0.0f;
    }
}

void Speedometer::setFuelPercentage(float fuelPercentage)
{
    if(fuelPercentage > 100.0f)
    {
         fuelPercentage = 100.0f;
    }
    else if(fuelPercentage < 0.0f)
    {
        fuelPercentage = 0.0f;
    }

    this->fuelAngle = (MAX_FUEL_ANGLE - MIN_FUEL_ANGLE) * fuelPercentage / 100.0f;
}

void Speedometer::update(void)
{
    static std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

    color[0] = fabs(cosf(time));
    color[1] = fabs(sinf(time));
    color[2] = fabs(sinf(time));
}

void Speedometer::display(void)
{
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    glUseProgram(shaderProgramObject);

    glm::mat4x4 viewMatrix = glm::mat4x4();
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjectionMatrix));

    drawCircle(vaoMainCircle, glm::vec3(MAIN_CIRCLE_X_TRANSLATION, MAIN_CIRCLE_Y_TRANSLATION, Z_TRANSLATION), color);
    drawCircle(vaoLeftCircle, glm::vec3(LEFT_CIRCLE_X_TRANSLATION, LEFT_CIRCLE_Y_TRANSLATION, Z_TRANSLATION), color);

    drawSpeedArrow(glm::vec3(MAIN_CIRCLE_X_TRANSLATION, 0.0f, Z_TRANSLATION), glm::vec3(1.0f, 1.0f, 1.0f), -this->speedAngle, glm::vec3(1.0f, 1.0f, 1.0f));
    drawSpeedArrow(glm::vec3(LEFT_CIRCLE_X_TRANSLATION, LEFT_CIRCLE_Y_TRANSLATION, Z_TRANSLATION), glm::vec3(0.5f, 0.5f, 0.5f), -this->fuelAngle, glm::vec3(1.0f, 1.0f, 1.0f));

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

    glViewport(0, 0, windowWidth, windowHeight);
}

void Speedometer::drawCircle(GLuint vao, glm::vec3 position, glm::vec3 color)
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

void Speedometer::drawSpeedArrow(glm::vec3 position, glm::vec3 scale, GLfloat angle, glm::vec3 color)
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

bool Speedometer::loadGLTextures(GLuint *texture, TCHAR resourceId[])
{
    bool textureLoaded = false;
    BITMAP bmp;
    HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), resourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if(hBitmap)
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

void Speedometer::resize(int width, int height)
{
    if(height == 0)
    {
        height = 1;
    }

    windowWidth = width;
    windowHeight = height;
    viewportX = width - viewportWidth;
    perspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)viewportWidth / (GLfloat)viewportHeight, 1.0f, 1000.0f);
}

void Speedometer::cleanUp(void)
{
    for(int counter = 0; counter < speedPoints.size(); ++counter)
    {
        if(speedPoints[counter] != NULL)
        {
            free(speedPoints[counter]->text);
            free(speedPoints[counter]);
            speedPoints[counter] = NULL;
        }
    }

    speedPoints.clear();

    for(int counter = 0; counter < fuelPoints.size(); ++counter)
    {
        if(fuelPoints[counter] != NULL)
        {
            free(fuelPoints[counter]->text);
            free(fuelPoints[counter]);
            fuelPoints[counter] = NULL;
        }
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
}

Speedometer::~Speedometer()
{
    cleanUp();
}
