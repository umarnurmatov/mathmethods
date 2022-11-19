#include "interface.hpp"
#include <fstream>
#include <algorithm>
#include <cmath>

std::string filepath(std::string path)
{
    return std::string(PROJECT_SOURCE_DIR) + std::string(path);
}

void check_file(std::ifstream& file)
{
	if (!file)
	{
		std::cerr << "Failed opening file for reading!" << std::endl;
		exit(1);
	}
}

Interface::Interface()
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(filepath(std::string("/resourses/CascadiaMono-Regular.ttf")).c_str(), FONT_SIZE);
    ImGui::SFML::UpdateFontTexture();

    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowRounding = ROUNDING;
    style->FrameRounding = ROUNDING;
    style->PopupRounding = ROUNDING;
    style->WindowBorderSize = BORDER;
    style->FrameBorderSize = BORDER;
    //ImGui::StyleColorsLight();
}

void Interface::polynomial_regression(sf::RenderWindow &window, sf::View &d_view)
{
    if(is_polynom_regression_changed)
    {
        std::ifstream input(filepath("/resourses/input.txt").c_str());
	    check_file(input);

        std::string inp;
        input >> inp;
        int N = stoi(inp);
        std::vector<float> p_x;
        std::vector<float> p_y;
        for(int i = 0; i < N; i++)
        {
            input >> inp;
            p_x.push_back(std::stof(inp));
            input >> inp;
            p_y.push_back(std::stof(inp));
        }
        input.close();

        plot.setup_plot(d_view.getSize());
        plot.add_dataset(&p_x ,&p_y);
        plot.add_polynomial_regression();
        plot.setup_axis();
        plot.setup_grid();
        is_polynom_regression_changed = false;
    }
    plot.draw(window);
}