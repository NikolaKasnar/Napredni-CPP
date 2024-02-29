#pragma once
#include "shape.h"
#include <utility>
#include <functional>

class Square : public Shape {
public:
    using DrawStrategy = std::function<void(Square const&)>;

    // Konstruktor kvadrata
    Square(float sideLength, Point position, DrawStrategy drawer) :
        sideLength_{ sideLength }, position_{ position }, drawer_{ std::move(drawer) } {}

    // Povratne funkcije za duljinu stranice, centar i metodu crtanja
    float sideLength() const { return sideLength_; }
    Point position() const { return position_; }
    virtual void draw() const override { drawer_(*this); }

private:
    float sideLength_;
    Point position_;
    DrawStrategy drawer_;
};
