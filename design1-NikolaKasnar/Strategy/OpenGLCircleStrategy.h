#pragma once
#include "circle.h"
#include <iostream>
//#include <GL/gl.h>
#include <cmath>

class OpenGLCircleStrategy{
    public:
        void operator()(Circle const& circle) const;
};
