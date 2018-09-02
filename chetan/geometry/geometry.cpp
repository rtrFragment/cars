
#include <string>

#include "geometry.h"
#include "logger.h"

Geometry::Geometry() {}

GLint Geometry::initialize(const GLchar *vertexShaderCode, const char*fragmentShaderCode, ShaderProgramBindAttributes bindAttributes, char **error)
{
	GLint shaderCompileStatus = initializeVertexShader(vertexShaderCode, error);

	if(shaderCompileStatus == GL_FALSE)
	{
		return shaderCompileStatus;
	}

	shaderCompileStatus = GL_TRUE;
	shaderCompileStatus = initializeFragmentShader(fragmentShaderCode, error);

	if(shaderCompileStatus == GL_FALSE)
	{
		return shaderCompileStatus;
	}

	shaderCompileStatus = GL_TRUE;
	shaderCompileStatus = initializeShaderProgram(bindAttributes, error);

	if(shaderCompileStatus == GL_FALSE)
	{
		return shaderCompileStatus;
	}

	glGenVertexArrays(1, &this->vao);

	return shaderCompileStatus;
}

GLint Geometry::initializeVertexShader(const GLchar *vertexShaderCode, char **error)
{
    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, (const char**)&vertexShaderCode, NULL);
    glCompileShader(vertexShaderObject);

    GLint infoLogLength = 0;
    GLint shaderCompileStatus = 0;

    glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &shaderCompileStatus);

    if(shaderCompileStatus == GL_FALSE)
    {
        glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if(infoLogLength > 0)
        {
            *error = (char *)malloc(infoLogLength);

            if(error != NULL)
            {
                GLsizei written = 0;
                glGetShaderInfoLog(vertexShaderObject, infoLogLength, &written, *error);
            }
        }
    }

	return shaderCompileStatus;
}

GLint Geometry::initializeFragmentShader(const GLchar *fragmentShaderCode, char **error)
{
    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObject, 1, (const char**)&fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderObject);

    GLint infoLogLength = 0;
    GLint shaderCompileStatus = 0;

    glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &shaderCompileStatus);

    if(shaderCompileStatus == GL_FALSE)
    {
        glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if(infoLogLength > 0)
        {
            *error = (char *)malloc(infoLogLength);

            if(error != NULL)
            {
                GLsizei written = 0;
                glGetShaderInfoLog(fragmentShaderObject, infoLogLength, &written, *error);
            }
        }
    }

	return shaderCompileStatus;
}

GLint Geometry::initializeShaderProgram(const ShaderProgramBindAttributes bindAttributes, char **error)
{
	shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);

    // Bind the position attribute location before linking.
	if(bindAttributes.vertexPosition != NULL)
	{
    	glBindAttribLocation(shaderProgramObject, GEOMETRY_ATTRIBUTE_VERTEX_POSITION, bindAttributes.vertexPosition);
	}

    // Bind the normal attribute location before linking.
	if(bindAttributes.normal != NULL)
	{
		glBindAttribLocation(shaderProgramObject, GEOMETRY_ATTRIBUTE_NORMAL, bindAttributes.normal);
	}

	// Bind the color attribute location before linking.
	if(bindAttributes.color != NULL)
	{
		glBindAttribLocation(shaderProgramObject, GEOMETRY_ATTRIBUTE_NORMAL, bindAttributes.color);
	}

	// Bind the texture0 attribute location before linking.
	if(bindAttributes.texture0 != NULL)
	{
		glBindAttribLocation(shaderProgramObject, GEOMETRY_ATTRIBUTE_NORMAL, bindAttributes.texture0);
	}

    // Now link and check for error.
    glLinkProgram(shaderProgramObject);

    GLint infoLogLength = 0;
    GLint shaderProgramLinkStatus = 0;

    glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &shaderProgramLinkStatus);

    if(shaderProgramLinkStatus == GL_FALSE)
    {
        glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if(infoLogLength > 0)
        {
            *error = (char *)malloc(infoLogLength);

            if(*error != NULL)
            {
                GLsizei written = 0;
                glGetProgramInfoLog(shaderProgramObject, infoLogLength, &written, *error);
            }
        }
    }

	return shaderProgramLinkStatus;
}

void Geometry::setVertexPosition(std::vector<GLfloat> vertices)
{
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vboPosition);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboPosition);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(GEOMETRY_ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GEOMETRY_ATTRIBUTE_VERTEX_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	logInfo("vertices.size(): %d\n", vertices.size());
}

void Geometry::setTextureCoordinates(std::vector<GLfloat> textureCoordinates)
{
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vboTexture);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(GLfloat), textureCoordinates.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(GEOMETRY_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GEOMETRY_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Geometry::setNormals(std::vector<GLfloat> normals)
{
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboNormals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(GEOMETRY_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GEOMETRY_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Geometry::setColor()
{
	glBindVertexArray(this->vao);

	glBindVertexArray(0);
}

GLuint Geometry::getUniformLocation(const char* uniform)
{
	return glGetUniformLocation(shaderProgramObject, uniform);
}

void Geometry::setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix4fv(location, count, transpose, value);
}

void Geometry::setUniform1i(GLint location, GLint value)
{
	glUniform1i(location,value);
}

void Geometry::setUniform1f(GLint location, GLfloat value)
{
	glUniform1f(location, value);
}

void Geometry::setUniform3fv(GLint location, GLsizei count, const GLfloat *value)
{
	glUniform3fv(location, count, value);
}

void Geometry::setUniform4fv(GLint location, GLsizei count, const GLfloat *value)
{
	glUniform4fv(location, count, value);
}

void Geometry::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

void Geometry::setViewMatrix(glm::mat4 viewMatrix)
{
	this->viewMatrix = viewMatrix;
}

void Geometry::setProjectionMatrix(glm::mat4 projectionMatrix)
{
	this->projectionMatrix = projectionMatrix;
}

void Geometry::translate(glm::vec3 translate)
{
	this->modelMatrix = glm::translate(this->modelMatrix, translate);
}

void Geometry::rotate(GLfloat angle, glm::vec3 rotate)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), rotate);
}

void Geometry::scale(glm::vec3 scaleValue)
{
	this->modelMatrix = glm::scale(this->modelMatrix, scaleValue);
}

void Geometry::startRendering(void)
{
	glUseProgram(this->shaderProgramObject);
}

void Geometry::stopRendering(void)
{
	glUseProgram(0);
}

void Geometry::cleanUp()
{
	if (this->vao)
	{
		glDeleteVertexArrays(1, &this->vao);
		this->vao = 0;
	}

	if (this->vboPosition)
	{
		glDeleteBuffers(1, &this->vboPosition);
		this->vboPosition = 0;
	}

	if (this->vboNormals)
	{
		glDeleteBuffers(1, &this->vboNormals);
		this->vboNormals = 0;
	}

	if (this->vboTexture)
	{
		glDeleteBuffers(1, &this->vboTexture);
		this->vboTexture = 0;
	}

	if (this->vboElement)
	{
		glDeleteBuffers(1, &this->vboElement);
		this->vboElement = 0;
	}

	if(this->vertexShaderObject)
    {
        glDeleteShader(this->vertexShaderObject);
        this->vertexShaderObject = 0;
    }

    if(this->fragmentShaderObject)
    {
        glDeleteShader(this->fragmentShaderObject);
        this->fragmentShaderObject = 0;
    }

	if(this->shaderProgramObject)
    {
        if(this->vertexShaderObject)
        {
            glDetachShader(this->shaderProgramObject, this->vertexShaderObject);
        }

        if(this->fragmentShaderObject)
        {
            glDetachShader(this->shaderProgramObject, this->fragmentShaderObject);
        }
    }

    if(this->vertexShaderObject)
    {
        glDeleteShader(this->vertexShaderObject);
        this->vertexShaderObject = 0;
    }

    if(this->fragmentShaderObject)
    {
        glDeleteShader(this->fragmentShaderObject);
        this->fragmentShaderObject = 0;
    }

    if(this->shaderProgramObject)
    {
        glDeleteProgram(this->shaderProgramObject);
        this->shaderProgramObject = 0;
    }
}

Geometry::~Geometry()
{
	this->cleanUp();
}
