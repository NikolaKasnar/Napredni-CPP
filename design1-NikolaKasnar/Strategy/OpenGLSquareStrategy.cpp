#include "OpenGLSquareStrategy.h"
#include <iostream>

void OpenGLSquareStrategy::operator()(Square const& square) const {
    std::cout << "Crtam kvadtrat čije su stranice duljine " << square.sideLength() << " na koordinatama (" << square.position().x << ", " << square.position().y << ") koristeci OpenGL." << std::endl;

    //drawSquare(square);
}

// Moze se koristiti samo uz GLFW library
/*void OpenGLSquareStrategy::drawSquare(const Square& square) const {
    float halfSide = square.sideLength() / 2.0f;

    glBegin(GL_QUADS);

    glVertex2f(square.position().x - halfSide, square.position().y - halfSide); // Bottom-left
    glVertex2f(square.position().x + halfSide, square.position().y - halfSide); // Bottom-right
    glVertex2f(square.position().x + halfSide, square.position().y + halfSide); // Top-right
    glVertex2f(square.position().x - halfSide, square.position().y + halfSide); // Top-left

    glEnd();
}*/
