#pragma once

#include "geometry.h"

class Pyramid: public Geometry
{
public:
	Pyramid();
	~Pyramid();

	void update();
	void render(GLsizei numberOfVertices);
	void resize(int width, int height);
	void cleanUp();
};
