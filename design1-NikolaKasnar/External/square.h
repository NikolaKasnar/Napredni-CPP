#pragma once
#include <utility>
#include "point.h"

class Square{
    public:

        // Konstruktor za kvadrat
        Square(float sideLenght, Point position) : sideLenght_{sideLenght}, position_{position}{}

        // Funkcije za vracanje radijusa, centra i metode crtanja
        float side() const { return sideLenght_; }
        Point position() const {return position_; }
    private:
        float sideLenght_;
        Point position_;
};
