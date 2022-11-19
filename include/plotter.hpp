#pragma once

#include <cmath>
#include <vector>

#include "SFML/Graphics.hpp"

#include "polynomial_regression.hpp"

#define POINT_RADIUS_PIXELS 5.f
#define AXIS_THICKNESS_PIXELS 3.f

class Plotter
{
    std::vector<float> p_x;
    std::vector<float> p_y;

    sf::Vector2f w_size;
    sf::View d_view;
    sf::Vector2f zero;

    std::vector<sf::VertexArray> grid_x;
    std::vector<sf::VertexArray> grid_y;

    sf::RectangleShape x_axis;
    sf::RectangleShape y_axis;

    std::vector<sf::CircleShape> points;
    

    std::vector<sf::Vertex> polynom;

    float p_x_min, p_x_max;
    float p_y_min, p_y_max;
    float kx, ky;

public:
    void setup_plot(sf::Vector2f _w_size);

    void setup_grid();
    void setup_axis();

    void add_dataset(std::vector<float> *_p_x, std::vector<float> *_p_y);
    void add_polynomial_regression();

    void draw(sf::RenderWindow &window);

};