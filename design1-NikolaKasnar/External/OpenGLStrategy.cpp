#include "OpenGLStrategy.h"
#include <iostream>
//#include <GL/gl.h>
#include <cmath>

void OpenGLStrategy::operator()(Circle const &circle) const {
    std::cout << "Crtam krug sa radijusom " << circle.radius() << " na koordinatama ("
              << circle.center().x << ", " << circle.center().y << ") koristeci OpenGL." << std::endl;

    // Moze se koristiti samo uz GLFW library
    /*// Postavim boju crtanja na bijelu
    glColor3f(1.0f, 1.0f, 1.0f);

    // Pocetak crtanja kruga kruga
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circle.center().x, circle.center().y); // Center kruga

    // Crtam krug sa OpenGL metodom
    for (int i = 0; i <= 360; i++) {
        float angle = static_cast<float>(i) * 3.14159f / 180.0f;
        float x = circle.radius() * cos(angle) + circle.center().x;
        float y = circle.radius() * sin(angle) + circle.center().y;
        glVertex2f(x, y);
    }

    glEnd();*/
}

void OpenGLStrategy::operator()(Square const &square) const {
    std::cout << "Crtam kvadrat sa duljinom stranice " << square.side() << " na koordinatama ("
              << square.position().x << ", " << square.position().y << ") koristeci OpenGL." << std::endl;

    // Moze se koristiti samo uz GLFW library
    /*// Postavim boju crtanja na bijelu
    glColor3f(1.0f, 1.0f, 1.0f);

    // Crtam kvadrat sa OpenGL metodom
    glBegin(GL_QUADS);
        glVertex2f(square.position().x, square.position().y);
        glVertex2f(square.position().x + square.side(), square.position().y);
        glVertex2f(square.position().x + square.side(), square.position().y + square.side());
        glVertex2f(square.position().x, square.position().y + square.side());
    glEnd();*/
}

