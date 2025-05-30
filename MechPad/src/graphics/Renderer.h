#ifndef _RENDERER__H_
#define _RENDERER__H_

// OpenGL libraries
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "graphics/VertexArray.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"

#define glAssert(x) if (!(x)) __debugbreak(); // MSVC assertion

#define glCall(x) glClearError();\
    x;\
    glAssert(glLogCall(#x, __FILE__, __LINE__))

void glClearError(void);
bool glLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void clear(void) const { glCall(glClear(GL_COLOR_BUFFER_BIT)); }
};

#endif