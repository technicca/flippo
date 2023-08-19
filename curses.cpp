#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <getopt.h>
#include <sstream>
#include "cxxopts.hpp"
#include <ncurses.h>
#include "ascii.hpp"

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to convert a color name to an RGB color
std::vector<int> colorNameToRgb(const std::string& color) {
    if (color == "red") {
        return {255, 0, 0};
    } else if (color == "green") {
        return {0, 255, 0};
    } else if (color == "blue") {
        return {0, 0, 255};
    } else if (color == "white") {
        return {255, 255, 255};
    } else if (color == "black") {
        return {0, 0, 0};
    } else {
        std::cerr << "Invalid color: " << color << std::endl;
        exit(1);
    }
}

// Function to interpolate between two RGB colors
std::vector<int> interpolate(const std::vector<int>& color1, const std::vector<int>& color2, double t) {
    int r = color1[0] + t * (color2[0] - color1[0]);
    int g = color1[1] + t * (color2[1] - color1[1]);
    int b = color1[2] + t * (color2[2] - color1[2]);
    return {r, g, b};
}

// Function to convert a string to ASCII art
std::vector<std::string> convertToAsciiArt(const std::string& str, const std::map<char, Letter>& ascii_map) {
    std::vector<std::string> ascii_art;
    for (char c : str) {
        if (ascii_map.count(c) == 0) {
            std::cerr << "Invalid character: " << c << std::endl;
            exit(1);
        }
        for (unsigned i = 0; i < ascii_map.at(c).height(); ++i) {
            if (ascii_art.size() <= i) {
                ascii_art.push_back("");
            }
            ascii_art[i] += ascii_map.at(c)(i);
        }
    }
    return ascii_art;
}

int main(int argc, char** argv) {
    // Initialize ncurses
    initscr();
    start_color();
    use_default_colors();
    cbreak();
    noecho();

    // Define color pairs
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_BLUE, -1);

    // ...

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        endwin();
        std::cout << options.help() << std::endl;
        return 0;
    }
    std::string ascii_text = result["ascii"].as<std::string>();
    std::string gradient_colors = result["gradient"].as<std::string>();
    std::vector<std::vector<int>> colors;
    for (const std::string& color_str : split(gradient_colors, ',')) {
        colors.push_back(colorNameToRgb(color_str));
    }
    std::vector<std::string> ascii_art = convertToAsciiArt(ascii_text, letters);

    for (unsigned i = 0; i < ascii_art.size(); ++i) {
        int len = ascii_art[i].length();
        for (int j = 0; j < len; ++j) {
            double t = static_cast<double>(j) / (len - 1);
            int color_index = t * (colors.size() - 1);
            double t_local = t * (colors.size() - 1) - color_index;
            std::vector<int> color;
            if (color_index + 1 < colors.size()) {
                color = interpolate(colors[color_index], colors[color_index + 1], t_local);
            } else {
                color = colors[color_index];
            }

            // Use ncurses function to output the color
            attron(COLOR_PAIR(chooseColorPair(color)));
            addch(ascii_art[i][j]);
            attroff(COLOR_PAIR(chooseColorPair(color)));
        }
        addch('\n');
    }

    refresh();
    getch(); // Wait for user input

    endwin(); // End ncurses

    return 0;
}
