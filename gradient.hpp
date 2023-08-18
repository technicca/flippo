#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>
#include <vector>
#include <tuple>

std::tuple<int, int, int> hex_to_rgb(std::string_view hex);
std::tuple<int, int, int> interpolate(std::tuple<int, int, int> color1, std::tuple<int, int, int> color2, double fraction);
std::string rgb_to_termcolor(std::tuple<int, int, int> rgb);
std::vector<std::string> generate_gradient(std::vector<std::string> colors);

#endif
