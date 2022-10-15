#pragma once

#include <cmath>
#include <vector>

#include "SFML/Graphics.hpp"

#include "polynomial_regression.hpp"

#define POINT_RADIUS_PIXELS 5.f

class Plotter
{
    std::vector<float> p_x;
    std::vector<float> p_y;

    sf::Vector2f w_size;
    sf::View d_view;
    sf::Vector2f zero;

    std::vector<sf::VertexArray> grid_x;
    std::vector<sf::VertexArray> grid_y;

    std::vector<sf::CircleShape> points;
    sf::Vertex x_axis[2];
    sf::Vertex y_axis[2];

    std::vector<sf::Vertex> polynom;

    float p_x_min, p_x_max;
    float p_y_min, p_y_max;
    float kx, ky;

public:
    void setup(sf::View d_view);
    void setup_grid_and_axis();
    void add_dataset(std::vector<float> *_p_x, std::vector<float> *_p_y);
    void draw(sf::RenderWindow &window);
    void add_fit_polynom();
};