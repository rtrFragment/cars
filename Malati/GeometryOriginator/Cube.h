#ifndef __CUBE_H__
#define __CUBE_H__

const float cubeVertices[] =
{
	//top
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	//bottom
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	//front
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	//back
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	//right
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	//left
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f


};

const float cubeColors[] =
{
	//		1.0f, 0.0f, 0.0f, //top
	//	0.0f, 1.0f, 0.0f, //bottom
	//0.0f, 0.0f, 1.0f, //front
	//0.0f, 1.0f, 1.0f, //back
	//1.0f, 0.0f, 1.0f, //right
	//1.0f, 1.0f, 0.0f //left

	1.0f, 0.0f, 0.0f, //top
	0.0f, 1.0f, 0.0f, //bottom
	0.0f, 0.0f, 1.0f, //front
	0.0f, 1.0f, 1.0f, //back

	0.0f, 1.0f, 0.0f, //bottom
	0.0f, 0.0f, 1.0f, //front
	0.0f, 1.0f, 1.0f, //back
	1.0f, 0.0f, 1.0f, //right

	0.0f, 0.0f, 1.0f, //front
	0.0f, 1.0f, 1.0f, //back
	1.0f, 0.0f, 1.0f, //right
	1.0f, 1.0f, 0.0f, //left

	0.0f, 1.0f, 1.0f, //back
	1.0f, 0.0f, 1.0f, //right
	1.0f, 1.0f, 0.0f, //left
	1.0f, 0.0f, 0.0f, //top

	1.0f, 0.0f, 1.0f, //right
	1.0f, 1.0f, 0.0f, //left
	1.0f, 0.0f, 0.0f, //top
	0.0f, 1.0f, 0.0f, //bottom

	1.0f, 1.0f, 0.0f, //left
	1.0f, 0.0f, 0.0f, //top
	0.0f, 1.0f, 0.0f, //bottom
	0.0f, 0.0f, 1.0f //front

};

const float cubeNormals[] =
{
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f

};

const float cubeTexcoords[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,


	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	//left

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};


#endif // !__CUBE_H

