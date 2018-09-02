#include "pyramid.h"
#include "logger.h"

Pyramid::Pyramid() : Geometry()
{

}

Pyramid::~Pyramid()
{
    this->cleanUp();
}

void Pyramid::update()
{

}

void Pyramid::render(GLsizei numberOfTriangles)
{
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

void Pyramid::resize(int width, int height)
{

}

void Pyramid::cleanUp()
{
    Geometry::cleanUp();
}
