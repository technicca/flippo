#include "gradient.hpp"
#include <cstdlib>
#include <iostream>

std::tuple<int, int, int> hex_to_rgb(std::string_view hex) {
  if(hex[0]=='#') hex.remove_prefix(1);
  
  int r = std::stoi(std::string(hex.substr(0,2)), nullptr, 16);
  int g = std::stoi(std::string(hex.substr(2,2)), nullptr, 16);
  int b = std::stoi(std::string(hex.substr(4,2)), nullptr, 16);
  
  return std::make_tuple(r, g, b);
}


std::tuple<int, int, int> interpolate(std::tuple<int, int, int> color1, std::tuple<int, int, int> color2, double fraction) {
    int r = std::get<0>(color1) + fraction * (std::get<0>(color2) - std::get<0>(color1)),
        g = std::get<1>(color1) + fraction * (std::get<1>(color2) - std::get<1>(color1)),
        b = std::get<2>(color1) + fraction * (std::get<2>(color2) - std::get<2>(color1));
        
    return std::make_tuple(r, g, b);
}

std::string rgb_to_termcolor(std::tuple<int, int, int> rgb) {
  int r = std::get<0>(rgb);
  int g = std::get<1>(rgb);
  int b = std::get<2>(rgb);
  
  return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::vector<std::string> generate_gradient(std::vector<std::string> colors) {
    std::vector<std::string> gradient;
    std::vector<std::tuple<int, int, int>> rgbValues;

    if (colors.size() < 2) {
        return gradient;
    }

    for (const auto& color : colors) {
        if (color[0] == '#') {
            // Convert hex color to RGB and then to terminal color code
            std::tuple<int, int, int> rgb = hex_to_rgb(color);
            rgbValues.push_back(rgb);
            std::cout << "RGB values: " << std::get<0>(rgb) << ", " << std::get<1>(rgb) << ", " << std::get<2>(rgb) << std::endl;
        }
    }

    // Generate the color gradient
    for (std::size_t i = 0; i < rgbValues.size() - 1; ++i) {
        for (int n = 0; n < 100; ++n) {
            double fraction = n / 100.0;
            std::tuple<int, int, int> interpolatedColor = interpolate(rgbValues[i], rgbValues[i+1], fraction);
            std::string termColor = rgb_to_termcolor(interpolatedColor);
            std::cout << "Generated color: " << termColor << std::endl;
            gradient.push_back(termColor);
            std::cout << "Gradient color: " << termColor << std::endl;
        }
    }

    return gradient;
}
