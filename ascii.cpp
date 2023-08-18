#include <iostream>
#include "ascii.hpp"
#include <algorithm>

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
                std::cout << colors[i % colors.size()] << l(i);
            } else {
                std::cout << std::string(letters.begin()->second.width(), ' ');
            }
        }
        std::cout << '\n';
    }
}
