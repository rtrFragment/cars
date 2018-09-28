#pragma once

#define _USE_MATH_DEFINES

#include "creditRoll.h"
#include "resources/resource.h"
#include "lib/logger/logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <chrono>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/glew.h>
#include <gl/gl.h>

CreditRoll::CreditRoll()
{
    logInfo("CreditRoll created.\n");
}

void CreditRoll::initialize(void)
{
    initializefontRenderer();
    initializeVertexShader();
    initializeFragmentShader();
    initializeShaderProgram();
    initializeBuffers();

    perspectiveProjectionMatrix = glm::mat4(1.0f);

    loadGLTextures(&texturePreview, MAKEINTRESOURCE(LAST_SCENE_BMP));
    loadCreditRoll();
}

void CreditRoll::initializefontRenderer(void)
{
    fontRenderer = new FontRenderer("resources/fonts/ubuntuMono.ttf", 48);
    FT_Error error = fontRenderer->initialize();

    if(error != 0)
    {
        logError("Not able to initialize FreeType, error code: %d\n", error);
    }
}

void CreditRoll::initializeVertexShader()
{
    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

    const GLchar *vertexShaderCode = "#version 450 core" \
        "\n" \
        "in vec4 vertexPosition;" \
        "in vec2 vertexTextureCoordinate0;" \
        "\n" \
        "out vec2 outVertexTextureCoordinate0;" \
        "\n" \
        "uniform mat4 modelMatrix;" \
        "uniform mat4 viewMatrix;" \
        "uniform mat4 projectionMatrix;" \
        "\n" \
        "void main(void)" \
        "{" \
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix  * vertexPosition;" \
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
                logError("CG: Vertex shader compilation log: %s\n", infoLog);
                free(infoLog);
                cleanUp();
                exit(EXIT_FAILURE);
            }
        }
    }
}

void CreditRoll::initializeFragmentShader()
{
    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar *fragmentShaderCode = "#version 450 core" \
        "\n" \
        "in vec2 outVertexTextureCoordinate0;" \
        "\n" \
        "out vec4 fragmentColor;" \
        "\n" \
        "uniform sampler2D textureSampler0;"
        "\n" \
        "void main(void)" \
        "{" \
        "   fragmentColor = texture(textureSampler0, outVertexTextureCoordinate0);" \
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
                logError("CG: Fragment shader compilation log: %s\n", infoLog);
                free(infoLog);
                cleanUp();
                exit(EXIT_FAILURE);
            }
        }
    }
}

void CreditRoll::initializeShaderProgram()
{
    shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);

    // Bind the position attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_CREDITROLL_ATTRIBUTE_VERTEX_POSITION, "vertexPosition");

    // Bind the texture attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_CREDITROLL_ATTRIBUTE_TEXTURE0, "vertexTextureCoordinate0");

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
                logError("CG: Shader program link log: %s\n", infoLog);
                free(infoLog);
                cleanUp();
                exit(EXIT_FAILURE);
            }
        }
    }

    modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "modelMatrix");
    viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "viewMatrix");
    projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "projectionMatrix");
    textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "textureSampler0");
}

void CreditRoll::initializePreviewRectBuffer()
{
    const GLfloat previewRectVertices[] = {
        -0.25f, 3.0f, 0.0f,
        -5.75f, 3.0f, 0.0f,
        -5.75f, 0.25f, 0.0f,
        -0.25f, 0.25f, 0.0f
    };

    const GLfloat previewRectTextureCoordinates[] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &vaoPreviewRect);
    glBindVertexArray(vaoPreviewRect);

    glGenBuffers(1, &vboPreviewRectPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vboPreviewRectPosition);

    glBufferData(GL_ARRAY_BUFFER, sizeof(previewRectVertices), previewRectVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(CG_CREDITROLL_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_CREDITROLL_ATTRIBUTE_VERTEX_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vboPreviewRectTexture);
    glBindBuffer(GL_ARRAY_BUFFER, vboPreviewRectTexture);

    glBufferData(GL_ARRAY_BUFFER, sizeof(previewRectTextureCoordinates), previewRectTextureCoordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(CG_CREDITROLL_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_CREDITROLL_ATTRIBUTE_TEXTURE0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void CreditRoll::initializeBuffers(void)
{
    initializePreviewRectBuffer();
}

void CreditRoll::loadCreditRoll()
{
    char *data = NULL;
    char *context = NULL;
    char *nextLine = NULL;
    char *sep = "\n";
    int dataLength = readFile("creditRollData.txt", &data);

    if(dataLength > 0)
    {
        nextLine = strtok_s(data, sep, &context);

        if(nextLine != NULL)
        {
            logInfo("Line: %s\n", nextLine);

            while((nextLine = strtok_s(NULL, "\n", &context)) != NULL)
            {
                logInfo("Line: %s\n", nextLine);
            }
        }
    }
}

void CreditRoll::update(void)
{
    // static std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();
    // std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::high_resolution_clock::now();
    // float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

    // color[0] = fabs(cosf(time));
    // color[1] = fabs(sinf(time));
    // color[2] = fabs(sinf(time));
}

void CreditRoll::display(void)
{
    glUseProgram(shaderProgramObject);

    drawPreview();

    glUseProgram(0);
}

void CreditRoll::drawPreview()
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -6.0f));

    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjectionMatrix));

    glBindVertexArray(vaoPreviewRect);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePreview);
    glUniform1i(textureSamplerUniform, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

bool CreditRoll::loadGLTextures(GLuint *texture, TCHAR resourceId[])
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

void CreditRoll::resize(int width, int height)
{
    if(height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    perspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
}

int CreditRoll::readFile(const char* fileName, char **data)
{
	FILE *dataFile = NULL;
    char *textData = NULL;
	fopen_s(&dataFile, fileName, "r");

	if(dataFile == NULL)
	{
		logError("Not able to load data from file '%s'\n", fileName);
		return 0;
	}

	fseek(dataFile, 0, SEEK_END);
	long dataLength = ftell(dataFile);
	fseek(dataFile, 0, SEEK_SET);
	textData = (char *)malloc(dataLength + 1);

	if (textData != NULL)
	{
		fread(textData, sizeof(char *), dataLength, dataFile);
		textData[dataLength] = '\0';
	}

	fclose(dataFile);

    *data = textData;

	return dataLength + 1;
}

void CreditRoll::cleanUp(void)
{
    // for(int counter = 0; counter < speedPoints.size(); ++counter)
    // {
    //     if(speedPoints[counter] != NULL)
    //     {
    //         free(speedPoints[counter]->text);
    //         free(speedPoints[counter]);
    //         speedPoints[counter] = NULL;
    //     }
    // }

    // speedPoints.clear();

    if(fontRenderer != NULL)
    {
        delete fontRenderer;
        fontRenderer = NULL;
    }

    if(vaoPreviewRect != 0)
    {
        glDeleteVertexArrays(1, &vaoPreviewRect);
        vaoPreviewRect = 0;
    }

    if(vboPreviewRectPosition != 0)
    {
        glDeleteBuffers(1, &vboPreviewRectPosition);
        vboPreviewRectPosition = 0;
    }

    if(vboPreviewRectTexture != 0)
    {
        glDeleteBuffers(1, &vboPreviewRectTexture);
        vboPreviewRectTexture = 0;
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

    if(texturePreview != 0)
    {
        glDeleteTextures(1, &texturePreview);
        texturePreview = 0;
    }
}

CreditRoll::~CreditRoll()
{
    cleanUp();
}
