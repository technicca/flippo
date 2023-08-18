#include <iostream>
#include <algorithm>
#include <sstream>
#include "ascii.hpp"
#include "flip.hpp"

std::map<std::string, std::string> colorMap = {
    {"black", "\033[30m"},
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"white", "\033[37m"}
};

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command;
        std::vector<std::string> gradient;
        std::string input;
        int start = 1;
        if (argv[1][0] == '-') {
            command = argv[1];
            start = 2;
        }
        if (argc > 2 && argv[2][0] == '-') {
            std::string gradientCommand = argv[2];
            if (gradientCommand.substr(0, 10) == "--gradient=") {
                std::string gradientColors = gradientCommand.substr(10);
                std::istringstream ss(gradientColors);
                std::string color;
                while (std::getline(ss, color, ',')) {
                    color.erase(color.begin(), std::find_if(color.begin(), color.end(), [](int ch) {
                        return !std::isspace(ch);
                    }));
                    if (colorMap.count(color) > 0) {
                        gradient.push_back(colorMap[color]);
                    }
                }
            }
            start = 3;
        }
        for (int i = start; i < argc; ++i) {
            if (i > start) input += " ";
            input += argv[i];
        }

        if (command == "-ascii") {
            if (!gradient.empty()) {
                generate_ascii_art(input, gradient);
            } else {
                generate_ascii_art(input, {});
            }
        } else {
            std::reverse(input.begin(), input.end());
            for (char &c : input) {
                if (flipMap.count(c) > 0) {
                    std::cout << flipMap[c];
                } else {
                    std::cout << c;
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}