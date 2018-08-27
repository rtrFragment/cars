#ifndef __MYGEOMETRY_H__
#define __MYGEOMETRY_H__


#include "Header.h"
#include <string>
#include "Pyramid.h"
#include "Cube.h"
#include "Obj_Loader.h"

#include<vector>

//Cube , Pyramid , Triangle, Square, Sphere
class MyGeometry
{
public:
	GLuint VAO;
	GLuint VBO_Position;
	GLuint VBO_Normal;
	GLuint VBO_Texture;
	GLuint VBO_Element;

	BOOL isSphere;
	
	GLfloat gAngle;
	
	glm::vec3 translateVector;
	glm::vec3 scaleVector;
	glm::vec3 rotateVector;
	GLfloat rotateX;
	GLfloat rotateY;
	GLfloat rotateZ;


	glm::mat4 modelMatrix, viewMatrix, rotationMatrix, scaleMatrix;
	glm::mat4 gPerspectiveProjectionMatrix;
	std::vector<float> gv_vertices, gv_textures, gv_normals;
	

	unsigned short sphere_elements[2280];

	void Myinit();
	void Uninitialize();
	void SetMVP(GLuint& modelMatrixUniform, GLuint& viewMatrixUniform, GLuint& projectionMatrixUniform, glm::vec3& translatexyz , glm::vec3& rotatexyz , glm::vec3& scalexyz);
	void Translate(glm::vec3 translatexyz);
	void Ratate(glm::vec3 rotatexyz);
	void RatateX(float value);
	void Scale(glm::vec3 scaleValue);
	void Resize(int width, int height);
	void Update();
	MyGeometry();
	//MyGeometry(float arr[], float arr1[], float arr2[]);
};

void MyGeometry::Update()
{
	gAngle += 0.1f;
	if (gAngle > 360.0)
		gAngle = 0.0f;

	rotateX += 0.1f;
	if (rotateX > 360.0)
		rotateX = 0.0f;

	rotateY += 0.1f;
	if (rotateY > 360.0)
		rotateY = 0.0f;

	rotateZ += 0.1f;
	if (rotateZ > 360.0)
		rotateZ = 0.0f;

}
void MyGeometry::Resize(int width, int height)
{
	gPerspectiveProjectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height,
		0.1f, 100.0f);
}
MyGeometry::MyGeometry()
{
//	gAngle = 0.0f;
	rotateX = 0.0f;
	rotateY = 0.0f;
	rotateZ = 0.0f;

	//rotateVector(rotateX, rotateY, rotateZ);
}

void MyGeometry::Myinit()
{
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	
	fprintf(gpFile, "Sizeof Vertices : %d, Normals : %d, Textures : %d\n", gv_vertices.size(), gv_normals.size(), gv_textures.size());
	//position
	glGenBuffers(1, &this->VBO_Position);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Position);
	glBufferData(GL_ARRAY_BUFFER, gv_vertices.size() * sizeof(float), &gv_vertices[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//normal
	glGenBuffers(1, &this->VBO_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Normal);
	glBufferData(GL_ARRAY_BUFFER, gv_normals.size() * sizeof(float), &gv_normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//texture
	glGenBuffers(1, &this->VBO_Texture);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texture);
	glBufferData(GL_ARRAY_BUFFER, gv_textures.size() * sizeof(float), &gv_textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	if (isSphere)
	{
		glGenBuffers(1, &this->VBO_Element);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Element);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(0);

	//gPerspectiveProjectionMatrix = mat4::identity();
}

void MyGeometry::SetMVP(GLuint& modelMatrixUniform, GLuint& viewMatrixUniform, GLuint& projectionMatrixUniform, glm::vec3& translatexyz, glm::vec3& rotatexyz, glm::vec3& scalexyz)
{
	//modelMatrix = glm::mat4::identity();
	//viewMatrix = glm::mat4::identity();
	//rotationMatrix = glm::mat4::identity();
//	if(glm::length(translatexyz))
	Translate(translatexyz);

	//if (glm::length(scalexyz))
		//Scale(scalexyz);

	//if(glm::length(rotatexyz))
	//Ratate(glm::vec3(rotateX, rotateY, rotateZ));
	//viewMatrix = lookat(vec3(4, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));

	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, &viewMatrix[0][0]);

	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, &gPerspectiveProjectionMatrix[0][0]);

}

/*void MyGeometry::SetTransformationMatrix(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale)
{

}*/
void MyGeometry::Translate(glm::vec3 translatexyz)
{
	modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, translatexyz);
}

void MyGeometry::Ratate(glm::vec3 rotatexyz)
{
	rotationMatrix = glm::mat4();
	rotateVector = rotatexyz;
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(60.0f), rotateVector);
		//glm::rotate(rotationMatrix, glm::radians(60.0f), gAngle, gAngle, gAngle);

	modelMatrix = modelMatrix * rotationMatrix; //imp
}

/*void MyGeometry::RatateX(float value)
{
	glm::vec3 rotatex(value, 0.0f, 0.0f);
	rotateVector = rotateVector & rotatex;	
}*/

void MyGeometry::Scale(glm::vec3 scaleValue)
{
	scaleMatrix = glm::mat4();
	scaleMatrix = glm::scale(scaleMatrix, scaleValue);
	modelMatrix = modelMatrix * scaleMatrix;
}

void MyGeometry::Uninitialize()
{
	if (VAO)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	if (VBO_Position)
	{
		glDeleteBuffers(1, &VBO_Position);
		VBO_Position = 0;
	}
	if (VBO_Normal)
	{
		glDeleteBuffers(1, &VBO_Normal);
		VBO_Normal = 0;
	}
	if (VBO_Texture)
	{
		glDeleteBuffers(1, &VBO_Texture);
		VBO_Texture = 0;
	}
}



//////////////////////////////////////////////////////////////////////////////////////////
class MySphere : public MyGeometry
{
public:
	GLuint gNumVertices;
	GLuint gNumElements;
	float vertices1[2000];
	float normals1[2000];
	float textures1[2000];
	MySphere();

};

MySphere::MySphere()
{
	getSphereVertexData(vertices1, normals1, textures1, sphere_elements);
	this->gNumVertices = getNumberOfSphereVertices();
	this->gNumElements = getNumberOfSphereElements();
	isSphere = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
class MyPyramid : public MyGeometry
{
public:
	MyPyramid();
	void DrawPyramid();
	void LoadPyramidData(std::vector<float> &vertices, std::vector<float> &textures, std::vector<float> &normals);
};

MyPyramid::MyPyramid()
{
	LoadPyramidData(gv_vertices, gv_textures, gv_normals);
	isSphere = false;
}

void MyPyramid::LoadPyramidData(std::vector<float> &vertices, std::vector<float> &textures, std::vector<float> &normals)
{
	for (int i = 0; i != 36; i++)
	{
		vertices.push_back(pyramidVertices[i]);
	}
	for (int i = 0; i != 24; i++)
	{
		textures.push_back(pyramidTexcoords[i]);
	}
	for (int i = 0; i != 36; i++)
	{
		normals.push_back(pyramidNormal[i]);
	}
}

void MyPyramid::DrawPyramid()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);
}

////////////////////////////////////cube/////////////////////////
class MyCube : public MyGeometry
{
public:
	MyCube();
	void DrawCube();
	void LoadCubeData(std::vector<float> &vertices, std::vector<float> &textures, std::vector<float> &normals);
};

MyCube::MyCube()
{
	LoadCubeData(gv_vertices, gv_textures, gv_normals);
	isSphere = false;
}

void MyCube::LoadCubeData(std::vector<float> &vertices, std::vector<float> &textures, std::vector<float> &normals)
{
	for (int i = 0; i != 72; i++)
	{
		vertices.push_back(cubeVertices[i]);
	}
	for (int i = 0; i != 48; i++)
	{
		textures.push_back(cubeTexcoords[i]);
	}
	for (int i = 0; i != 72; i++)
	{
		normals.push_back(cubeNormals[i]);
	}
}

void MyCube::DrawCube()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
	glBindVertexArray(0);
}

class Mesh : public MyGeometry
{
public:
	//Mesh();
	int count_of_vertices;
	void DrawMesh();
	void LoadData();
	//int LoadMeshData(char *filename, std::vector<float> &vertices, std::vector<float> &textures, std::vector<float> &normals);
};

void Mesh::LoadData()
{
	count_of_vertices = LoadMeshData("resources/SmallBushTree.obj", gv_vertices, gv_textures, gv_normals);
}

void Mesh::DrawMesh()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, count_of_vertices);


	glBindVertexArray(0);
}
#endif