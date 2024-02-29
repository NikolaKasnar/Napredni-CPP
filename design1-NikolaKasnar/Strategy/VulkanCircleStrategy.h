#pragma once

#include "circle.h"

class VulkanCircleStrategy {
public:

    // Konstruktor i destruktor koji mi na kraju nisu trebali
    /*VulkanCircleStrategy();
    ~VulkanCircleStrategy();*/

    // Nacrtam krug koristeci Vulkan strategiju
    void operator()(Circle const& circle) const;

private:
    // Stvori Vulkan pipeline za crtanje
    //void createPipeline();
};
