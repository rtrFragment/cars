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
    const GLfloat creditRollStartPosition = -3.75f;
    const GLfloat creditRollEndPosition = 1.9f;
    const GLfloat creditRollTranslationFactor = 0.01f;
    const GLfloat previewRectFinalTopY = creditRollEndPosition + 0.2f;
    const GLfloat previewRectFinalBottomY = -0.5f;
    const GLfloat previewRectFinalRightX = -0.25;
    const GLfloat previewRectFinalLeftX = -5.75;
    const GLfloat previewRectInitialLeftX = -6.0f;
    const GLfloat previewRectInitialRightX = 6.0f;
    const GLfloat previewRectInitialTopY = 3.4f;
    const GLfloat previewRectInitialBottomY = -3.5f;

    GLfloat fadeInOutColor = 0.0f;
    GLfloat previewTextureFadeOutColor = 1.0f;

    GLfloat previewRectVertices[12] = {
        previewRectInitialRightX, previewRectInitialTopY, 0.0f,
        previewRectInitialLeftX, previewRectInitialTopY, 0.0f,
        previewRectInitialLeftX, previewRectInitialBottomY, 0.0f,
        previewRectInitialRightX, previewRectInitialBottomY, 0.0f
    };

    bool fadeInFlag = false;
    bool fadeOutFlag = false;
    bool previewRectTransalateTopYDone = false;
    bool previewRectTransalateLeftXDone = false;
    bool previewRectTransalateRightXDone = false;
    bool previewRectTransalateBottomYDone = false;
    bool previewRectTransalateDone = false;

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
    GLuint fadeInOutColorUniform = 0;

    glm::mat4 perspectiveProjectionMatrix;
    glm::vec3 creditRollTranslation;

    FontRenderer *fontRenderer = NULL;
    TextData *creditRollTitleTextData = NULL;
    TextData *creditRollTitleDividerTextData = NULL;
    TextData *creditRollDateTextData = NULL;
    std::vector<TextData *> creditRollTextData;
    std::vector<TextData *> groupMembersTextData;

    void initializefontRenderer(void);
    void initializeVertexShader(void);
    void initializeFragmentShader(void);
    void initializeShaderProgram(void);
    void initializeBuffers(void);
    void initializePreviewRectBuffer(void);
    void initializeNewspapertBuffer();
    void loadCreditRoll();
    void loadCreditRollTitle();
    void loadGroupMembers();
    void loadTextDataFromFile(char * fileName, glm::vec3 textPosition, std::vector<TextData *> &textDataList);
    TextData* generateTextData(char *line, glm::vec3 position);
    void fadeIn();
    void fadeOut();
    void drawNewspaper();
    void drawPreview();
    void drawCreditRollTitle();
    void drawCreditRoll();
    void drawGroupMembers();
    bool loadGLTextures(GLuint *texture, TCHAR resourceId[]);
    int readFile(const char* fileName, char **data);
    void cleanUp(void);
};
