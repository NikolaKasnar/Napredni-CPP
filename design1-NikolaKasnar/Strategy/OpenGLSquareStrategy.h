#pragma once
#include "square.h"
#include <iostream>
//#include <GL/gl.h>

class OpenGLSquareStrategy {
public:
    void operator()(Square const& square) const;

private:
    // Moze se koristiti samo uz GLFW library
    // Nije potrebno odijeliti funkciju, prvotno sam napravio ovako pa sam ostavio
    //void drawSquare(const Square& square) const;
};
