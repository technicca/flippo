// main.cpp
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cxxopts.hpp>
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
    cxxopts::Options options(argv[0], " - command line options");
    options
        .allow_unrecognised_options()
        .add_options()
        ("a,ascii", "Generate ASCII art")
        ("f,flip", "Flip the input text")
        ("g,gradient", "Apply a color gradient", cxxopts::value<std::vector<std::string>>())
        ("input", "Input text", cxxopts::value<std::string>())
        ("help", "Print help")
    ;

    options.parse_positional({"input"});
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    std::string input = result["input"].as<std::string>();

    std::vector<std::string> gradient;
    if (result.count("gradient")) {
        auto colors = result["gradient"].as<std::vector<std::string>>();
        for (const auto& color : colors) {
            if (colorMap.count(color) > 0) {
                gradient.push_back(colorMap[color]);
            }
        }
    }

    if (result.count("ascii")) {
        generate_ascii_art(input, gradient);
    } else if (result.count("flip")) {
        std::reverse(input.begin(), input.end());
        for (char &c : input) {
            if (flipMap.count(c) > 0) {
                std::cout << gradient[gradientIndex++ % gradient.size()] << flipMap[c];
            } else {
                std::cout << gradient[gradientIndex++ % gradient.size()] << c;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
