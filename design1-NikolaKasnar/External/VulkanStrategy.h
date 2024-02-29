#pragma once
#include "circle.h"
#include "square.h"

class VulkanStrategy {
public:

    // Funkcija za crtanje kruga
    void operator()(Circle const &circle) const;

    // Funkcija za crtanje kvadrata
    void operator()(Square const &square) const;
};
