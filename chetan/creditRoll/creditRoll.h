#include <windows.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "fontRenderer.h"

class CreditRoll
{
public:
    CreditRoll();
    ~CreditRoll();

    void initialize(void);
    void update(void);
    void display(void);
    void resize(int width, int height);
    void setSpeed(float speed);
    void setFuelPercentage(float fuelPercentage);

private:
    enum
    {
        CG_CREDITROLL_ATTRIBUTE_VERTEX_POSITION = 0,
        CG_CREDITROLL_ATTRIBUTE_COLOR,
        CG_CREDITROLL_ATTRIBUTE_NORMAL,
        CG_CREDITROLL_ATTRIBUTE_TEXTURE0,
    };

    GLuint vertexShaderObject = 0;
    GLuint fragmentShaderObject = 0;
    GLuint shaderProgramObject = 0;

    GLuint vaoPreviewRect = 0;
    GLuint vboPreviewRectPosition = 0;
    GLuint vboPreviewRectTexture = 0;

    GLuint texturePreview = 0;
    GLuint textureSamplerUniform = 0;
    GLuint modelMatrixUniform = 0;
    GLuint viewMatrixUniform = 0;
    GLuint projectionMatrixUniform = 0;

    glm::mat4x4 perspectiveProjectionMatrix;

    FontRenderer *fontRenderer = NULL;
    std::vector<TextData *> creditRollTextData;

    void initializefontRenderer(void);
    void initializeVertexShader(void);
    void initializeFragmentShader(void);
    void initializeShaderProgram(void);
    void initializeBuffers(void);
    void initializePreviewRectBuffer(void);
    void loadCreditRoll();
    void drawPreview();
    void drawCreditRoll();
    bool loadGLTextures(GLuint *texture, TCHAR resourceId[]);
    int readFile(const char* fileName, char **data);
    void cleanUp(void);
};
