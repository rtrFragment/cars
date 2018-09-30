#pragma once

#include <windows.h>
#include <vector>
#include <GL/glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../fontRenderer/fontRenderer.h"

class Speedometer
{
public:
    Speedometer();
    ~Speedometer();

    void initialize(void);
    void update(void);
    void display(void);
    void resize(int width, int height);
    void setSpeed(float speed);
    void setFuelPercentage(float fuelPercentage);

private:
    enum
    {
        CG_SPEEDOMETER_ATTRIBUTE_VERTEX_POSITION = 0,
        CG_SPEEDOMETER_ATTRIBUTE_COLOR,
        CG_SPEEDOMETER_ATTRIBUTE_NORMAL,
        CG_SPEEDOMETER_ATTRIBUTE_TEXTURE0,
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

    const int numberOfCirclePoints = 10000;
    const GLsizei viewportWidth = 400;
	const GLsizei viewportHeight = 200;
    GLsizei viewportX = 0;
    GLsizei viewportY = 0;
    GLsizei windowWidth = 0;
    GLsizei windowHeight = 0;

    float speedAngle;
    float fuelAngle;

    FontRenderer *fontRenderer = NULL;
    std::vector<TextData *> speedPoints;
    std::vector<TextData *> fuelPoints;

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
    void drawCircle(GLuint vao, glm::vec3 position, glm::vec3 color);
    void drawSpeedArrow(glm::vec3 position, glm::vec3 scale, GLfloat angle, glm::vec3 color);
    bool loadGLTextures(GLuint *texture, TCHAR resourceId[]);
    void cleanUp(void);
};
