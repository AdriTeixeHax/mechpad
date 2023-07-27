#ifndef _RENDERING__H_
#define _RENDERING__H_

// OpenGL Libraries
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using Window = GLFWwindow;

inline void OnRender(Window* window)
{
    glBegin(GL_TRIANGLES);
    {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.5f, 0.5f);
    }
    glEnd();
}

#endif