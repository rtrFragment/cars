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

    const char* paragraphSeparator = "-----";
    const float creditRollStartPosition = -3.75f;
    const float creditRollEndPosition = 2.0f;
    const float creditRollTranslationFactor = 0.01f;

    GLuint vertexShaderObject = 0;
    GLuint fragmentShaderObject = 0;
    GLuint shaderProgramObject = 0;

    GLuint vaoPreviewRect = 0;
    GLuint vboPreviewRectPosition = 0;
    GLuint vboPreviewRectTexture = 0;

    GLuint vaoNewspaper = 0;
    GLuint vboNewspaperPosition = 0;
    GLuint vboNewspaperTexture = 0;

    GLuint texturePreview = 0;
    GLuint textureNewspaper = 0;
    GLuint textureSamplerUniform = 0;
    GLuint modelMatrixUniform = 0;
    GLuint viewMatrixUniform = 0;
    GLuint projectionMatrixUniform = 0;

    glm::mat4 perspectiveProjectionMatrix;
    glm::vec3 creditRollTranslation;

    FontRenderer *fontRenderer = NULL;
    TextData *creditRollTitleTextData;
    std::vector<TextData *> creditRollTextData;

    void initializefontRenderer(void);
    void initializeVertexShader(void);
    void initializeFragmentShader(void);
    void initializeShaderProgram(void);
    void initializeBuffers(void);
    void initializePreviewRectBuffer(void);
    void initializeNewspapertBuffer();
    void loadCreditRoll();
    TextData* generateTextData(char *line, glm::vec3 position);
    void drawNewspaper();
    void drawPreview();
    void drawCreditRoll();
    bool loadGLTextures(GLuint *texture, TCHAR resourceId[]);
    int readFile(const char* fileName, char **data);
    void cleanUp(void);
};
