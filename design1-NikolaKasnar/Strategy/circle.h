#pragma once
#include "shape.h"
#include <utility>
#include <functional>

class Circle : public Shape{
    public:
        using DrawStrategy = std::function<void(Circle const &)>;

        // Konstruktor za krug
        Circle(float r, Point center, DrawStrategy drawer) :
            radius_{r}, center_{center}, drawer_{std::move(drawer)} {}

        // Funkcije za vracanje radijusa, centra i metode crtanja
        float radius() const { return radius_; }
        Point center() const {return center_; }
        virtual void draw() const override{ drawer_(*this); }
    private:
        float radius_;
        Point  center_;
        DrawStrategy drawer_;
};
