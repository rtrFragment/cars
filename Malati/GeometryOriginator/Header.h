#ifndef __HEADER_H__
#define __HEADER_H__
#include <gl\glew.h>
#include <gl/GL.h>

#include <windows.h>
#include <stdio.h> // for FILE I/O
#include <iostream>

FILE *gpFile = NULL;

//use it before other GL.h


//#include "vmath.h"
#include "Sphere.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "MySphere.h"
//#include "Sphere1.h"
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"Sphere.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//using namespace vmath;

typedef enum
{
	MALATI_ATTRIBUTE_VERTEX = 0,
	MALATI_ATTRIBUTE_COLOR,
	MALATI_ATTRIBUTE_NORMAL,
	MALATI_ATTRIBUTE_TEXTURE
}MyEnum;

#endif