#pragma once

#include <vector>
#include <gl/glew.h>
#include <gl/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef enum
{
	GEOMETRY_ATTRIBUTE_VERTEX_POSITION = 0,
	GEOMETRY_ATTRIBUTE_COLOR = 1,
	GEOMETRY_ATTRIBUTE_NORMAL = 2,
	GEOMETRY_ATTRIBUTE_TEXTURE0 = 3
} GEOMETRY_ATTRIBUTES;

struct ShaderProgramBindAttributes
{
	char *vertexPosition = NULL;
	char *normal = NULL;
	char *color = NULL;
	char *texture0 = NULL;
};

class Geometry
{
public:
	Geometry();
	~Geometry();

	GLint initialize(const GLchar *vertexShaderCode, const char*fragmentShaderCode, ShaderProgramBindAttributes bindAttributes, char **error);
	void cleanUp();

	void setVertexPosition(std::vector<GLfloat> vertices);
	void setTextureCoordinates(std::vector<GLfloat> textureCoordinates);
	void setNormals(std::vector<GLfloat> normals);
	void setColor();

	void setModelMatrix(glm::mat4 modelMatrix);
	void setViewMatrix(glm::mat4 viewMatrix);
	void setProjectionMatrix(glm::mat4 projectionMatrix);

	void translate(glm::vec3 translate);
	void rotate(GLfloat angle, glm::vec3 rotate);
	void scale(glm::vec3 scale);

	GLuint getUniformLocation(const char* uniform);
	void setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void setUniform1i(GLint location, GLint value);
	void setUniform1f(GLint location, GLfloat value);
	void setUniform3fv(GLint location, GLsizei count, const GLfloat *value);
	void setUniform4fv(GLint location, GLsizei count, const GLfloat *value);

	virtual void update() = 0;
	virtual void startRendering(void);
	virtual void render(GLsizei numberOfTriangles) = 0;
	virtual void stopRendering(void);
	virtual void resize(int width, int height) = 0;


protected:
	GLuint vertexShaderObject = 0;
    GLuint fragmentShaderObject = 0;
    GLuint shaderProgramObject = 0;
	GLuint vao = 0;
	GLuint vboPosition = 0;
	GLuint vboNormals = 0;
	GLuint vboTexture = 0;
	GLuint vboElement = 0;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	GLint initializeVertexShader(const GLchar *vertexShaderCode, char **error);
	GLint initializeFragmentShader(const GLchar *fragmentShaderCode, char **error);
	GLint initializeShaderProgram(const ShaderProgramBindAttributes bindAttributes, char **error);
};
