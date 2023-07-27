/* MechPad.cpp | Main file for the MechPad Project by AdriTeixeHax */

// IO
#include <iostream>

// Callbacks
#include "Input.h"
#include "Rendering.h"

int main(void)
{
    Window* window;

    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW." << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(1280, 720, "MechPad Project - by AdriTeixeHax", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }

    // Input callback registering
    glfwSetKeyCallback(window, OnKeyboard);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error initializing GLEW." << std::endl;
        return -1;
    }

    // Print out the OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl << std::endl;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Clear color buffer bit
        glClear(GL_COLOR_BUFFER_BIT);
        // Render the scene
        OnRender(window);
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}