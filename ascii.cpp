// ascii.cpp
// ascii.cpp defines how ascii art is generated based on the provided user input
#include <iostream>
#include "ascii.hpp"
#include <algorithm>

unsigned gradientIndex = 0; // This should be global or a class member

void generate_ascii_art(const std::string& text, const std::vector<std::string>& colors) {
    unsigned height = 0;
    std::string lower_text = text;
    std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(), ::tolower);
    for(char ch : lower_text) {
        auto it = letters.find(ch);
        if(it != letters.end()) {
            auto w = it->second.height();
            if(w > height) height = w;
        }
    }
    for(unsigned i = 0; i < height; ++i) {
        for(char ch : lower_text) {
            auto it = letters.find(ch);
            if(it != letters.end()) {
                const Letter& l = it->second;
                std::cout << colors[gradientIndex++ % colors.size()] << l(i);
            } else {
                std::cout << colors[gradientIndex++ % colors.size()] << std::string(letters.begin()->second.width(), ' ');
            }
        }
        std::cout << '\n';
    }
}
