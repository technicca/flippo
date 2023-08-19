#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>
#include <sstream>
#include <map>

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

// Function to convert a hex color string to an RGB color string
std::vector<int> hexToRgb(const std::string& hex) {
    int r = std::stoi(hex.substr(0, 2), nullptr, 16);
    int g = std::stoi(hex.substr(2, 2), nullptr, 16);
    int b = std::stoi(hex.substr(4, 2), nullptr, 16);
    return {r, g, b};
}

// Function to interpolate between two RGB colors
std::vector<int> interpolate(const std::vector<int>& color1, const std::vector<int>& color2, double t) {
    int r = color1[0] + t * (color2[0] - color1[0]);
    int g = color1[1] + t * (color2[1] - color1[1]);
    int b = color1[2] + t * (color2[2] - color1[2]);
    return {r, g, b};
}

int main(int argc, char** argv) {
    // Map of predefined color names to RGB color strings
    std::map<std::string, std::vector<int>> colorMap = {
        {"red", {255, 0, 0}},
        {"green", {0, 255, 0}},
        {"blue", {0, 0, 255}},
        // Add more colors here...
    };

    std::vector<std::vector<int>> colors;
    std::string text;

    // Parse command line options
    int opt;
    while ((opt = getopt(argc, argv, "g:")) != -1) {
        switch (opt) {
        case 'g':
            for (const std::string& colorStr : split(optarg, ',')) {
                if (colorMap.count(colorStr)) {
                    colors.push_back(colorMap[colorStr]);
                } else if (colorStr.length() == 6 && colorStr.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos) {
                    colors.push_back(hexToRgb(colorStr));
                } else {
                    std::cerr << "Invalid color: " << colorStr << std::endl;
                    return 1;
                }
            }
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " -g color1,color2,color3 \"input text\"" << std::endl;
            return 1;
        }
    }

    // Get the input text
    if (optind < argc) {
        text = argv[optind];
    } else {
        std::cerr << "Usage: " << argv[0] << " -g color1,color2,color3 \"input text\"" << std::endl;
        return 1;
    }

    // Print the text with gradient colors
    int len = text.length();
    for (int i = 0; i < len; ++i) {
        double t = static_cast<double>(i) / (len - 1);
        int colorIndex = t * (colors.size() - 1);
        double tLocal = t * (colors.size() - 1) - colorIndex;
        std::vector<int> color;
        if (colorIndex + 1 < colors.size()) {
            color = interpolate(colors[colorIndex], colors[colorIndex + 1], tLocal);
        } else {
            color = colors[colorIndex];
        }
        std::cout << "\033[38;2;" << color[0] << ";" << color[1] << ";" << color[2] << "m" << text[i];
    }
    std::cout << "\033[0m" << std::endl;  // Reset to default color

    return 0;
}
