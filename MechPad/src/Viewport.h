#ifndef _VIEWPORT__H_
#define _VIEWPORT__H_

// STL libraries
#include <iostream>
#include <vector>

// OpenGL Libraries
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Own headers
#include "Polygon.hpp"

class Viewport
{
private:
	std::vector<uint*>	  _buffers;
	std::vector<Polygon*> _polygons;

public:
	// Constructor
	Viewport(void) : _buffers(), _polygons() {}
	// Destructor
	~Viewport(void) {}

	void addArrayBuffer(uint* buffer, uint numberOfBuffers, uint size, const void* data, GLenum usage)
	{
		glGenBuffers(numberOfBuffers, buffer);
		glBindBuffer(GL_ARRAY_BUFFER, *buffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		_buffers.push_back(buffer);
	}

	void addPolygon(Polygon* polygon) { _polygons.push_back(polygon); }
};

#endif