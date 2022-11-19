#pragma once
#include <iostream>

#include "plotter.hpp"

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>


#define FONT_SIZE 22.f
#define ROUNDING 5.f
#define BORDER 1.5f


class Interface
{
public:
    Interface();

    Plotter plot;
    bool is_polynom_regression_changed = true;

    void polynomial_regression(sf::RenderWindow &window, sf::View &view);
};