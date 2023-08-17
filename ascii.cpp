#include <iostream>
#include "ascii.hpp"

void generate_ascii_art(const std::string& text) {
    unsigned height = 0;
    for(char ch : text) {
        auto it = letters.find(ch);
        if(it != letters.end()) {
            auto w = it->second.height();
            if(w > height) height = w;
        }
    }
    for(unsigned i = 0; i < height; ++i) {
        for(char ch : text) {
            auto it = letters.find(ch);
            if(it != letters.end()) {
                const Letter& l = it->second;
                std::cout << l(i);
            } else {
                std::cout << std::string(letters.begin()->second.width(), ' ');
            }
        }
        std::cout << '\n';
    }
}