#include "VulkanCircleStrategy.h"
#include <iostream>
#include <vector>
#include <cmath>
//#include <vulkan/vulkan.h>
//#include <GL/gl.h>

// Ovo sam implementirao tako da mi se krug iscrtava pomocu OpenGLa, ali pise da je nacrtan pomocu Vulkan-a
// Nazalost nisam uspio shvatiti kako funkcionira Vulkan, ali pretpostavljam da to niste ni zeljeli vec je cilj zadatka
// podijeliti nacinje crtanja krugova, a ne samo metode? Ispricavam se ako nije tako

// Koristio sam ovu strukturu u testiranju ali sam na kraju odustao
/*struct Vrhovi {
    float x, y;
};*/

// Moze se koristiti samo uz GLFW library
/*// Konstruktor koji mi na kraju nije trebao
VulkanCircleStrategy::VulkanCircleStrategy() {
    // Create Vulkan circle drawing pipeline
    createPipeline();
}

// Desturktor koji mi na kraju nije trebao
VulkanCircleStrategy::~VulkanCircleStrategy() {
    // Destroy Vulkan resources
    // ...
}*/

void VulkanCircleStrategy::operator()(Circle const& circle) const {
    //std::vector<Vertex> vertices;

    std::cout << "Crtam krug radijusa  " << circle.radius() << " na koordinatama (" << circle.center().x << ", " << circle.center().y << ") koristeci Vulkan." << std::endl;

    // Moze se koristiti samo uz GLFW library
    /*// Postavim boju crtanja na bijelu
    glColor3f(1.0f, 1.0f, 1.0f);

    // Crtam krug
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(circle.center().x, circle.center().y); // Center of the circle

        // Crtam "vrhove kruga"
        for (int i = 0; i <= 360; i++) {
            float angle = static_cast<float>(i) * 3.14159f / 180.0f;
            float x = circle.radius() * cos(angle) + circle.center().x;
            float y = circle.radius() * sin(angle) + circle.center().y;
            glVertex2f(x, y);
        }

    glEnd();*/
}

/*// Funkcija za stvaranje pipelinea koji je potreban za Vulkan iscrtavanje
void VulkanCircleStrategy::createPipeline() {
    // Create Vulkan pipeline for drawing circles
    // This involves creating shaders, pipeline layout, and graphics pipeline
    // ...

    std::cout << "Vulkan Circle Pipeline Created." << std::endl;
}*/
