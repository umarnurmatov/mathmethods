#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "interface.hpp"

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode().getFullscreenModes()[0], "Mathmeth", sf::Style::Default, settings);
    ImGui::SFML::Init(window, false);

    // sf::Cursor c;
    // c.loadFromSystem(sf::Cursor::SizeAll);
    // window.setMouseCursor(c);
    

    Interface interface;
    
    sf::View defaultView = window.getDefaultView();
    sf::View view = defaultView;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized) {
                // resize view
                view = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
                window.setView(view);
            }
        }
        
        ImGui::SFML::Update(window, deltaClock.restart());


        window.clear(sf::Color::White);
        interface.polynomial_regression(window, defaultView);
        
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}