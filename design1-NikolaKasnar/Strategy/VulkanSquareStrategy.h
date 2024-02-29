#pragma once

#include "square.h"
//#include <vulkan/vulkan.h>


// Slicno kao i za VulcanCircleStrategy.h
class VulkanSquareStrategy {
public:

    // Konstruktor i destruktor koji mi na kraju nisu trebali
    //VulkanSquareStrategy();
    //~VulkanSquareStrategy();

    // Funkcija za crtanje kvadrata
    void operator()(Square const& square) const;

private:
// Moze se koristiti samo uz GLFW library
    // Opet sam odijelio funkciju za crtanje posto sam tako napravio i za OpenGLStrategy
    /*void drawSquare(const Square& square) const;

    // Stvori Vulkan pipeline za crtanje
    void createPipeline();*/
};
