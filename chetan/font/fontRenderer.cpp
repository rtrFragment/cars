#include "fontRenderer.h"

enum
{
    CG_FONT_ATTRIBUTE_VERTEX_POSITION = 0,
	CG_FONT_ATTRIBUTE_COLOR,
	CG_FONT_ATTRIBUTE_NORMAL,
	CG_FONT_ATTRIBUTE_TEXTURE0,
};

FontRenderer::FontRenderer(char *fontFile, int fontSize)
{
    if (fopen_s(&logFile, "font_renderer_debug.log", "w") != 0)
	{
		printf("Unable to open font renderer log file.\n");
	}

    log("---------- FontRenderer | Debug Logs Starts ----------\n");

    this->fontFile = fontFile;
    this->fontSize = fontSize;
}

void FontRenderer::log(const char* message, ...)
{
    if(logFile != NULL)
    {
        va_list args;
        va_start(args, message );
        vfprintf(logFile, message, args );
        va_end( args );

        fflush(logFile);
    }
}

FT_Error FontRenderer::initialize()
{
    FT_Error error = FT_Init_FreeType(&freeType);

    if(error != 0)
    {
        log("[Error] | Not able to initialize FreeType, error code %d\n", error);
        return error;
    }

    error = FT_New_Face(freeType, fontFile, 0, &fontFace);

    if(error != 0)
    {
        log("[Error] | Not able to load font face, error code %d\n", error);
        return error;
    }

    // Font's width and height parameters, setting the width to 0 lets the face dynamically calculate the width
    // based on the given height.
    error = FT_Set_Pixel_Sizes(fontFace, 0, fontSize);

    if(error != 0)
    {
        log("[Error] | Not able to set font size, error code %d\n", error);
        return error;
    }

    initializeVertexShader();
    initializeFragmentShader();
    initializeShaderProgram();
    initializeTextBuffers();

    return 0;
}

void FontRenderer::loadCharacters(char *charactersToLoad, int numberOfCharacters)
{
    for(int counter = 0; counter < numberOfCharacters; ++counter)
    {
        GLchar characterToLoad = charactersToLoad[counter];

        if(characters.find(characterToLoad) != characters.end())
        {
            // We have already loaded character data, move to next one.
            continue;
        }

        // Load character glyph.
        FT_Error error = FT_Load_Char(fontFace, characterToLoad, FT_LOAD_RENDER);

        if(error != 0)
        {
            log("[Error] | Cannot load character '%c', error code: %d\n", characterToLoad, error);
            continue;
        }

        GLuint textureId = 0;
        glGenTextures(1, &textureId);
        // For programmable pipeline set 1 instead of 4 for better performation.
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // Generate the mipmapped texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Unbind the texture.
        glBindTexture(GL_TEXTURE_2D, 0);

        TextCharacter *nextChar = (TextCharacter *)malloc(sizeof(TextCharacter));
        memset(nextChar, 0, sizeof(TextCharacter));

        nextChar->textChar = characterToLoad;
        nextChar->textureId = textureId;
        nextChar->size = vmath::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows);
        nextChar->bearing = vmath::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top);
        nextChar->advance = vmath::ivec2(fontFace->glyph->advance.x, fontFace->glyph->advance.y);

        characters[characterToLoad] = nextChar;
    }
}

void FontRenderer::initializeVertexShader(void)
{
    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

    const GLchar *vertexShaderCode = "#version 450 core" \
        "\n" \
        "in vec3 vertexPosition;" \
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
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);" \
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
                log("[Error] | Vertex shader compilation log: %s\n", infoLog);
                free(infoLog);
            }
        }
    }
}

void FontRenderer::initializeFragmentShader(void)
{
    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar *fragmentShaderCode = "#version 450 core" \
    "\n" \
    "in vec2 outVertexTextureCoordinate0;" \
    "\n" \
    "out vec4 fragmentColor;" \
    "\n" \
    "uniform sampler2D textureSampler0;"
    "uniform vec3 textColor;"
    "\n" \
    "void main(void)" \
    "{" \
    "    vec4 sampled = vec4(1.0,1.0,1.0,texture(textureSampler0, outVertexTextureCoordinate0).r);" \
    "    fragmentColor = vec4(textColor, 1.0) * sampled;" \
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
                log("[Error] | Fragment shader compilation log: %s\n", infoLog);
            }
        }
    }
}

void FontRenderer::initializeShaderProgram(void)
{
    shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);

    // Bind the position attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_FONT_ATTRIBUTE_VERTEX_POSITION, "vertexPosition");

    // Bind the texture attribute location before linking.
    glBindAttribLocation(shaderProgramObject, CG_FONT_ATTRIBUTE_TEXTURE0, "vertexTextureCoordinate0");

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
                log("[Error] | Shader program link log: %s\n", infoLog);
            }
        }
    }

    // After linking get the value of modelView and projection uniform location from the shader program.
    modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "modelMatrix");
    viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "viewMatrix");
    projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "projectionMatrix");
    textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "textureSampler0");
    textColorUniform = glGetUniformLocation(shaderProgramObject, "textColor");
}

void FontRenderer::initializeTextBuffers(void)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(CG_FONT_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_FONT_ATTRIBUTE_VERTEX_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vboTexture);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(CG_FONT_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(CG_FONT_ATTRIBUTE_TEXTURE0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void FontRenderer::renderText(TextData *textData, vmath::mat4 modelMatrix, vmath::mat4 viewMatrix, vmath::mat4 perspectiveProjectionMatrix, float scale)
{
    glUseProgram(shaderProgramObject);

    // Pass modelMatrix to vertex shader in 'modelMatrix' variable defined in shader.
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);

    // Pass viewMatrix to vertex shader in 'viewMatrix' variable defined in shader.
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);

    // Pass perspectiveProjectionMatrix to vertex shader in 'projectionMatrix' variable defined in shader.
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

    glUniform3fv(textColorUniform, 1, textData->textColor);

    // Now bind the VAO to which we want to use
    glBindVertexArray(vao);

    // Enable 0th texture
    glActiveTexture(GL_TEXTURE0);

    GLfloat xPosition = textData->textPosition[0];

    for(GLsizeiptr counter = 0; counter < textData->textSize; ++counter)
    {
        TextCharacter *nextChar = characters[textData->text[counter]];

        xPosition += nextChar->bearing[0] * scale;
        GLfloat yPosition = textData->textPosition[1] - (nextChar->size[1] - nextChar->bearing[1]) * scale;
        GLfloat width = nextChar->size[0] * scale;
        GLfloat height = nextChar->size[1] * scale;

        GLfloat vertices[18] = {
            xPosition        , yPosition + height, textData->textPosition[2],
            xPosition        , yPosition         , textData->textPosition[2],
            xPosition + width, yPosition         , textData->textPosition[2],
            xPosition        , yPosition + height, textData->textPosition[2],
            xPosition + width, yPosition         , textData->textPosition[2],
            xPosition + width, yPosition + height, textData->textPosition[2]
        };

        GLfloat textureCoordinates[12] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
        };

        glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindTexture(GL_TEXTURE_2D, nextChar->textureId);
        glUniform1i(textureSamplerUniform, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance the cursors for next glyph, advance is number of 1/64 pixels
        // So bitshift by 6 to get value in pixels (2^6 = 64)
        xPosition += (nextChar->advance[0] >> 6) * scale;
    }

    // unbind the vao
    glBindVertexArray(0);

    glUseProgram(0);
}

void FontRenderer::cleanUp(void)
{
    std::map<GLchar, TextCharacter*>::iterator  characterIterator;

    for (characterIterator = characters.begin(); characterIterator != characters.end(); ++characterIterator)
    {
        TextCharacter *nextChar = characterIterator->second;
        glDeleteBuffers(1, &(nextChar->textureId));
        free(nextChar);

        characterIterator->second = NULL;
    }

    characters.clear();

    FT_Done_Face(fontFace);
    FT_Done_FreeType(freeType);

    if(vao)
    {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    if(vboPosition)
    {
        glDeleteBuffers(1, &vboPosition);
        vboPosition = 0;
    }

    if(vboTexture)
    {
        glDeleteBuffers(1, &vboTexture);
        vboTexture = 0;
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

    if(logFile)
    {
        log("---------- FontRenderer | Debug Logs End ----------\n");
        fclose(logFile);
        logFile = NULL;
    }
}

FontRenderer::~FontRenderer()
{
    cleanUp();
}
