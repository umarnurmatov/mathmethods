#include "plotter.hpp"

void Plotter::setup_plot(sf::Vector2f _w_size)
{
    w_size = _w_size;
    zero = sf::Vector2f(w_size.x / 2, w_size.y / 2);
}
void Plotter::setup_grid()
{
    int grid_step_x = fabs(p_x_min - p_x_max) / 10;
    int grid_step_y = fabs(p_y_min - p_y_max) / 10;

    // сетка
    std::vector<int> transf = {1, -1};
    for(int i = 0; i < w_size.x / 2; i += grid_step_x)
    {
        for(int t : transf)
        {
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0] = sf::Vertex(sf::Vector2f(zero.x + t * i * kx, w_size.y), sf::Color::Black); 
            line[1] = sf::Vertex(sf::Vector2f(zero.x + t * i * kx, 0), sf::Color::Black); 
            grid_x.push_back(line);
        }
    }
    for(int i = 0; i < w_size.y / 2; i += grid_step_y)
    {
        for(int t : transf)
        {
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0] = sf::Vertex(sf::Vector2f(w_size.x, zero.y + t * i * ky), sf::Color::Black); 
            line[1] = sf::Vertex(sf::Vector2f(0, zero.y + t * i * ky), sf::Color::Black); 
            grid_x.push_back(line);
        }
    }
}

void Plotter::setup_axis()
{
    // оси
    x_axis.setSize(sf::Vector2f(w_size.x, AXIS_THICKNESS_PIXELS));
    y_axis.setSize(sf::Vector2f(AXIS_THICKNESS_PIXELS, w_size.y));
    x_axis.setPosition(sf::Vector2f(0, zero.y - AXIS_THICKNESS_PIXELS / 2));
    y_axis.setPosition(sf::Vector2f(zero.x - AXIS_THICKNESS_PIXELS / 2, 0));
    x_axis.setFillColor(sf::Color::Black);
    y_axis.setFillColor(sf::Color::Black);
}

void Plotter::add_dataset(std::vector<float> *_p_x, std::vector<float> *_p_y)
{
    p_x = *_p_x;
    p_y = *_p_y;
    p_x_min = p_x[0];
    p_x_max = p_x[p_x.size() - 1];
    p_y_min = *std::min_element(p_y.begin(), p_y.end());
    p_y_max = *std::max_element(p_y.begin(), p_y.end());
    kx = w_size.x / (fabs(p_x_min - p_x_max) * 2);
    ky = w_size.y / (fabs(p_y_min - p_y_max) * 2);

    // исходные данные
    sf::CircleShape point(POINT_RADIUS_PIXELS);
    point.setOrigin(POINT_RADIUS_PIXELS / 2, POINT_RADIUS_PIXELS / 2);
    point.setFillColor(sf::Color::Blue);
    for(int i = 0; i < p_x.size(); i++)
    {
        point.setPosition(sf::Vector2f(zero.x + p_x[i] * kx, w_size.y - zero.y - p_y[i] * ky));
        points.push_back(point);
    }
}

void Plotter::add_polynomial_regression()
{
    // полином
    Polynomial_regression p(&p_x, &p_y, 10);
    std::vector<float> coeffs;
    p.get_coeffs(&coeffs);

    for(float x = p_x[0]; x <= p_x[p_x.size() - 1]; x+=0.1f)
    {
        float y = 0;
        for(int i = 0; i < coeffs.size(); i++) y += pow(x, i) * coeffs[i];
        polynom.push_back(sf::Vertex(sf::Vector2f(zero.x + x * kx, w_size.y - zero.y - y * ky), sf::Color::Red));
    }
}

void Plotter::draw(sf::RenderWindow &window)
{

    // сетка
    for(sf::VertexArray g : grid_x) window.draw(g);
    for(sf::VertexArray g : grid_y) window.draw(g);

    // оси
    window.draw(x_axis);
    window.draw(y_axis);

    // данные
    for(sf::CircleShape p : points) window.draw(p);

    //полином
    window.draw(&polynom[0], polynom.size(), sf::LinesStrip);
}