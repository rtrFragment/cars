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
    creditRollTranslation = glm::vec3(0.0f, creditRollStartPosition, 0.0f);

    loadGLTextures(&texturePreview, MAKEINTRESOURCE(LAST_SCENE_BMP));
    loadGLTextures(&textureNewspaper, MAKEINTRESOURCE(NEWSPAPER_BMP));
    loadCreditRollTitle();
    loadCreditRoll();
    loadGroupMembers();
}

void CreditRoll::initializefontRenderer(void)
{
    fontRenderer = new FontRenderer("resources/fonts/times.ttf", 78);
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
        "uniform float fadeInOutColor;" \
        "\n" \
        "out vec4 fragmentColor;" \
        "\n" \
        "uniform sampler2D textureSampler0;"
        "\n" \
        "void main(void)" \
        "{" \
        "   fragmentColor = texture(textureSampler0, outVertexTextureCoordinate0) * vec4(fadeInOutColor, fadeInOutColor, fadeInOutColor, fadeInOutColor);" \
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
    fadeInOutColorUniform = glGetUniformLocation(shaderProgramObject, "fadeInOutColor");
}

void CreditRoll::initializePreviewRectBuffer()
{
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

    glBufferData(GL_ARRAY_BUFFER, sizeof(previewRectVertices), NULL, GL_DYNAMIC_DRAW);
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

void CreditRoll::initializeNewspapertBuffer()
{
    const GLfloat newspaperVertices[] = {
        6.0f, 6.0f, 0.0f,
        -6.0f, 6.0f, 0.0f,
        -6.0f, -6.0f, 0.0f,
        6.0f, -6.0f, 0.0f
    };

    const GLfloat newspaperTextureCoordinates[] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &vaoNewspaper);
    glBindVertexArray(vaoNewspaper);

    glGenBuffers(1, &vboNewspaperPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vboNewspaperPosition);

    glBufferData(GL_ARRAY_BUFFER, sizeof(newspaperVertices), newspaperVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(CG_CREDITROLL_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_CREDITROLL_ATTRIBUTE_VERTEX_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vboNewspaperTexture);
    glBindBuffer(GL_ARRAY_BUFFER, vboNewspaperTexture);

    glBufferData(GL_ARRAY_BUFFER, sizeof(newspaperTextureCoordinates), newspaperTextureCoordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(CG_CREDITROLL_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_CREDITROLL_ATTRIBUTE_TEXTURE0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void CreditRoll::initializeBuffers(void)
{
    initializePreviewRectBuffer();
    initializeNewspapertBuffer();
}

void CreditRoll::loadCreditRoll()
{
    loadTextDataFromFile("creditRollData.txt", glm::vec3(0.0f, 0.0f, -6.0f), creditRollTextData);
}

void CreditRoll::loadCreditRollTitle()
{
    creditRollTitleTextData = generateTextData("REAL TIME RENDERING", glm::vec3(-4.5f, 2.5f, -6.0f));
    creditRollTitleTextData->scale = 0.01f;
    fontRenderer->loadCharacters(creditRollTitleTextData);

    creditRollTitleDividerTextData = generateTextData("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", glm::vec3(-6.1f, 2.35f, -6.0f));
    creditRollTitleTextData->scale = 0.01f;
    fontRenderer->loadCharacters(creditRollTitleDividerTextData);

    creditRollDateTextData = generateTextData("30th September, 2018", glm::vec3(-1.15f, 2.2f, -6.0f));
    fontRenderer->loadCharacters(creditRollDateTextData);
}

void CreditRoll::loadGroupMembers()
{
    glm::vec3 textPosition = glm::vec3(-5.75f, previewRectFinalBottomY - 0.5f, -6.0f);
    loadTextDataFromFile("groupMembersColumn1.txt", textPosition, groupMembersTextData);

    textPosition = glm::vec3(-2.75f, previewRectFinalBottomY - 0.5f, -6.0f);
    loadTextDataFromFile("groupMembersColumn2.txt", textPosition, groupMembersTextData);
}

void CreditRoll::loadTextDataFromFile(char * fileName, glm::vec3 textPosition, std::vector<TextData *> &textDataList)
{
    char *data = NULL;
    char *context = NULL;
    char *nextLine = NULL;
    char *sep = "\n";
    int dataLength = readFile(fileName, &data);
    int column = 0;

    if(dataLength > 0)
    {
        nextLine = strtok_s(data, sep, &context);

        if(nextLine != NULL)
        {
            TextData *nextLineText = NULL;

            if(strlen(nextLine) > 0)
            {
                nextLineText = generateTextData(nextLine, textPosition);
                fontRenderer->loadCharacters(nextLineText);
                textDataList.push_back(nextLineText);
                textPosition[1] -= (2.0f * nextLineText->rectSize.height);
            }

            while((nextLine = strtok_s(NULL, "\n", &context)) != NULL)
            {
                if(strcmp(paragraphSeparator, nextLine) == 0 && strlen(nextLine) > 0)
                {
                    textPosition[1] -= (2.0f * nextLineText->rectSize.height);
                }
                else if(strlen(nextLine) > 0)
                {
                    nextLineText  = generateTextData(nextLine, textPosition);
                    fontRenderer->loadCharacters(nextLineText);
                    textDataList.push_back(nextLineText);
                    textPosition[1] -= (2.0f * nextLineText->rectSize.height);
                }
            }
        }
    }

    if(data != NULL)
    {
        free(data);
        data = NULL;
    }
}

TextData* CreditRoll::generateTextData(char *line, glm::vec3 position)
{
    int lineSize = strlen(line);

    TextData *nextLineText = (TextData *)malloc(sizeof(TextData));
    memset(nextLineText, 0, sizeof(TextData));

    nextLineText->text = (char *)malloc(sizeof(char *) * lineSize);
    strcpy(nextLineText->text, line);

    nextLineText->textSize = lineSize;
    nextLineText->textColor = glm::vec3(0.0f, 0.0f, 0.0f);
    nextLineText->textPosition = position;
    nextLineText->scale = 0.003f;

    return nextLineText;
}

void CreditRoll::update(void)
{
    if(previewRectTransalateDone == false)
    {
        if(previewRectVertices[0] > previewRectFinalRightX)
        {
            previewRectVertices[0] -= 0.01;
            previewRectVertices[9] -= 0.01;
        }
        else
        {
            previewRectTransalateRightXDone = true;
        }

        if(previewRectVertices[1] > previewRectFinalTopY)
        {
            previewRectVertices[1] -= 0.0021;
            previewRectVertices[4] -= 0.0021;
        }
        else
        {
            previewRectTransalateTopYDone = true;
        }

        if(previewRectVertices[7] < previewRectFinalBottomY)
        {
            previewRectVertices[7] += 0.0048;
            previewRectVertices[10] += 0.0048;
        }
        else
        {
            previewRectTransalateBottomYDone = true;
        }

        if(previewRectVertices[3] < previewRectFinalLeftX)
        {
            previewRectVertices[3] += 0.0005;
            previewRectVertices[6] += 0.0005;
        }
        else
        {
            previewRectTransalateLeftXDone = true;
        }

        previewRectTransalateDone = (
            previewRectTransalateRightXDone &&
            previewRectTransalateTopYDone &&
            previewRectTransalateBottomYDone &&
            previewRectTransalateLeftXDone
        );
    }

    if(previewRectTransalateDone == true)
    {
        if(fadeInOutColor <= 1.0f && fadeInFlag == false)
        {
            fadeIn();
        }
        else
        {
            fadeInFlag = true;
            creditRollTranslation[1] += creditRollTranslationFactor;

            TextData *lastCreditTextData = creditRollTextData[creditRollTextData.size() - 1];
            GLfloat lastCreditTextDataPosition = lastCreditTextData->textPosition[1] + creditRollTranslation[1];

            if((lastCreditTextDataPosition > creditRollEndPosition) && fadeInOutColor >= 0.0f)
            {
                fadeOut();
            }
        }
    }
}

void CreditRoll::fadeIn()
{
    fadeInOutColor += 0.002f;
}

void CreditRoll::fadeOut()
{
    fadeInOutColor -= 0.002f;
    previewTextureFadeOutColor -= 0.002f;
}

void CreditRoll::display(void)
{
    if(previewRectTransalateDone == true)
    {
        drawNewspaper();
        drawCreditRollTitle();
        drawCreditRoll();
        drawGroupMembers();
    }

    drawPreview();
}

void CreditRoll::drawPreview()
{
    glUseProgram(shaderProgramObject);

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -6.0f));

    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjectionMatrix));
    glUniform1f(fadeInOutColorUniform, previewTextureFadeOutColor);

    glBindVertexArray(vaoPreviewRect);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePreview);
    glUniform1i(textureSamplerUniform, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboPreviewRectPosition);
    glBufferData(GL_ARRAY_BUFFER, sizeof(previewRectVertices), previewRectVertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);
}

void CreditRoll::drawNewspaper()
{
    glUseProgram(shaderProgramObject);

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -6.0f));

    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjectionMatrix));
    glUniform1f(fadeInOutColorUniform, fadeInOutColor);

    glBindVertexArray(vaoNewspaper);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureNewspaper);
    glUniform1i(textureSamplerUniform, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);
}

void CreditRoll::drawCreditRollTitle()
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    fontRenderer->renderText(creditRollTitleTextData, modelMatrix, viewMatrix, perspectiveProjectionMatrix);
    fontRenderer->renderText(creditRollTitleDividerTextData, modelMatrix, viewMatrix, perspectiveProjectionMatrix);
    fontRenderer->renderText(creditRollDateTextData, modelMatrix, viewMatrix, perspectiveProjectionMatrix);
}

void CreditRoll::drawCreditRoll()
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, creditRollTranslation);

    for(int counter = 0; counter < creditRollTextData.size(); ++counter)
    {
        TextData *nextTextData = creditRollTextData[counter];
        GLfloat currentPosition = nextTextData->textPosition[1] + creditRollTranslation[1];

        if(currentPosition < creditRollEndPosition)
        {
            fontRenderer->renderText(nextTextData, modelMatrix, viewMatrix, perspectiveProjectionMatrix);
        }
    }
}

void CreditRoll::drawGroupMembers()
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    for(int counter = 0; counter < groupMembersTextData.size(); ++counter)
    {
        TextData *nextTextData = groupMembersTextData[counter];
        fontRenderer->renderText(groupMembersTextData[counter], modelMatrix, viewMatrix, perspectiveProjectionMatrix);
    }
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
    long dataLength = 0;

    fopen_s(&dataFile, fileName, "r");

    if(dataFile == NULL)
    {
        logError("Not able to load data from file '%s'\n", fileName);
        return 0;
    }

    fseek(dataFile, 0L, SEEK_END);
    dataLength = ftell(dataFile);
    fseek(dataFile, 0L, SEEK_SET);

    textData = (char*)calloc(dataLength + 1, sizeof(char));

    if(textData != NULL)
    {
        fread(textData, sizeof(char), dataLength, dataFile);
    }
    else
    {
        logError("Not able to allocate memory.");
        fclose(dataFile);
        return 0;
    }

    fclose(dataFile);

    *data = textData;

    return dataLength + 1;
}

void CreditRoll::cleanUp(void)
{
    creditRollTitleTextData->vertices.clear();
    free(creditRollTitleTextData->text);
    free(creditRollTitleTextData);
    creditRollTitleTextData = NULL;

    creditRollTitleDividerTextData->vertices.clear();
    free(creditRollTitleDividerTextData->text);
    free(creditRollTitleDividerTextData);
    creditRollTitleDividerTextData = NULL;

    creditRollDateTextData->vertices.clear();
    free(creditRollDateTextData->text);
    free(creditRollDateTextData);
    creditRollDateTextData = NULL;

    for(int counter = 0; counter < creditRollTextData.size(); ++counter)
    {
        if(creditRollTextData[counter] != NULL)
        {
            creditRollTextData[counter]->vertices.clear();
            free(creditRollTextData[counter]->text);
            free(creditRollTextData[counter]);
            creditRollTextData[counter] = NULL;
        }
    }

    creditRollTextData.clear();

    for(int counter = 0; counter < groupMembersTextData.size(); ++counter)
    {
        if(groupMembersTextData[counter] != NULL)
        {
            groupMembersTextData[counter]->vertices.clear();
            free(groupMembersTextData[counter]->text);
            free(groupMembersTextData[counter]);
            groupMembersTextData[counter] = NULL;
        }
    }

    groupMembersTextData.clear();

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

    if(vaoNewspaper != 0)
    {
        glDeleteVertexArrays(1, &vaoNewspaper);
        vaoNewspaper = 0;
    }

    if(vboNewspaperPosition != 0)
    {
        glDeleteBuffers(1, &vboNewspaperPosition);
        vboNewspaperPosition = 0;
    }

    if(vboNewspaperTexture != 0)
    {
        glDeleteBuffers(1, &vboNewspaperTexture);
        vboNewspaperTexture = 0;
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
