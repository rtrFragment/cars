#pragma once

#include <gl/glew.h>
#include <gl/gl.h>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

struct TextData
{
    // The text to render.
    GLchar *text;

    // The number of characters in 'text'.
    GLsizeiptr textSize;

    // The position where text will be rendered.
    glm::vec3 textPosition;

    // The text color.
    glm::vec3 textColor;
};

class FontRenderer
{
public:
    FontRenderer(char *fontFile, int fontSize);
    ~FontRenderer();

    FT_Error initialize();

    void loadCharacters(char *charactersToLoad, int numberOfCharacters);
    void renderText(TextData *text, glm::mat4x4 modelMatrix, glm::mat4x4 viewMatrix, glm::mat4x4 perspectiveProjectionMatrix, float scale);

private:
    struct TextCharacter
    {
        // The character.
        GLchar textChar;

        // The texture of character.
        GLuint textureId;

        // The size of character
        glm::ivec2 size;

        // Offset of character from base line to left and top.
        glm::ivec2 bearing;

        // X and Y offset of next character from this character.
        glm::ivec2 advance;
    };

    FT_Library freeType = NULL;
    FT_Face fontFace = NULL;

    char *fontFile;
    int fontSize;

    std::map<GLchar, TextCharacter*> characters;

    GLuint vertexShaderObject = 0;
    GLuint fragmentShaderObject = 0;
    GLuint shaderProgramObject = 0;

    GLuint vao = 0;
    GLuint vboPosition = 0;
    GLuint vboTexture = 0;
    GLuint modelMatrixUniform = 0;
    GLuint viewMatrixUniform = 0;
    GLuint projectionMatrixUniform = 0;
    GLuint textureSamplerUniform = 0;
    GLuint textColorUniform = 0;

    void initializeVertexShader(void);
    void initializeFragmentShader(void);
    void initializeShaderProgram(void);
    void initializeTextBuffers(void);
    void cleanUp(void);
};
