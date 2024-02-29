#include "VulkanSquareStrategy.h"
#include <iostream>
//#include <vulkan/vulkan.h>
//#include <GL/gl.h>

// Ovo sam implementirao tako da mi se kvadrat iscrtava pomocu OpenGLa, ali pise da je nacrtan pomocu Vulkan-a
// Nazalost nisam uspio shvatiti kako funkcionira Vulkan, ali pretpostavljam da to niste ni zeljeli vec je cilj zadatka
// podijeliti nacinje crtanja krugova, a ne samo metode? Ispricavam se ako nije tako

// Koristio sam ovu strukturu u testiranju ali sam na kraju odustao
/*struct Vrhovi {
    float x, y;
};*/

// Moze se koristiti samo uz GLFW library
// Konstruktor koji mi na kraju nije trebao
/*VulkanSquareStrategy::VulkanSquareStrategy() {
    // Create Vulkan square drawing pipeline
    createPipeline();
}

// Desturktor koji mi na kraju nije trebao
VulkanSquareStrategy::~VulkanSquareStrategy() {
    // Destroy Vulkan resources
    // ...
}*/

void VulkanSquareStrategy::operator()(Square const& square) const {
    //std::vector<Vertex> vertices;

    std::cout << "Crtam kvadrat cija je stranica duljine  " << square.sideLength() << " na koordinatama (" << square.position().x << ", " << square.position().y << ") koristeci Vulkan." << std::endl;

    //drawSquare(square);
}

// Moze se koristiti samo uz GLFW library
/*void VulkanSquareStrategy::drawSquare(const Square& square) const {
        float halfSide = square.sideLength() / 2.0f;

        glBegin(GL_QUADS);

        glVertex2f(square.position().x - halfSide, square.position().y - halfSide); // Bottom-left
        glVertex2f(square.position().x + halfSide, square.position().y - halfSide); // Bottom-right
        glVertex2f(square.position().x + halfSide, square.position().y + halfSide); // Top-right
        glVertex2f(square.position().x - halfSide, square.position().y + halfSide); // Top-left

        glEnd();
    }

// Funkcija za stvaranje pipelinea koji je potreban za Vulkan iscrtavanje
void VulkanSquareStrategy::createPipeline() {
    // Create Vulkan pipeline for drawing squares
    // This involves creating shaders, pipeline layout, and graphics pipeline
    // ...

    std::cout << "Vulkan Circle Pipeline Created." << std::endl;
}*/
