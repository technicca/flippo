I'm making a c++ terminal program that takes an input as text and either flips the text upside down or turns it into ascii art if the -ascii option is specified. I'm planning to extend functionality to support multiple ascii art "fonts" for the text, multiple colors, gradient colors, line separation with |, etc. I also plan to add the ability to turn images, gifs, videos to ascii art in the terminal and write them as a file. For now, I want you to add the ability to specify color of the ascii output when the user inputs text. I'm gonna give you my project files:

ascii.cpp:

#include <iostream>
#include "ascii.hpp"
#include <algorithm>

void generate_ascii_art(const std::string& text) {
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
                std::cout << l(i);
            } else {
                std::cout << std::string(letters.begin()->second.width(), ' ');
            }
        }
        std::cout << '\n';
    }
}


Ascii.hpp:

#ifndef ASCII_H
#define ASCII_H

#include <map>
#include <vector>
#include <string_view>
#include <string>

class Letter {
public:
    Letter(std::string_view l) : width_(0) {
        auto b = l.begin();
        for(auto it = b; it != l.end(); ++it) {
            if(*it == '\n') {
                auto w = it - b;
                if(w > width_) width_ = w;
                svs.emplace_back(b, w);
                b = it + 1;
            }
        }
        auto w = l.end() - b;
        if(w > width_) width_ = w;
        svs.emplace_back(b, w);
    }

    unsigned width() const { return width_; }
    unsigned height() const { return svs.size(); }

    std::string operator()(unsigned line) const {
        if(line >= svs.size()) return std::string(width_, ' ');
        return std::string(svs[line]) + std::string(width_ - svs[line].size(), ' ');
    }

private:
    std::vector<std::string_view> svs;
    unsigned width_;
};


void generate_ascii_art(const std::string& text);


inline std::map<char, Letter> letters = {
    {'a', Letter(R"(
░█████╗░
██╔══██╗
███████║
██╔══██║
██║░░██║
╚═╝░░╚═╝
)")},
    {'b', Letter(R"(
██████╗░
██╔══██╗
██████╦╝
██╔══██╗
██████╦╝
╚═════╝░
)")},
    {'c', Letter(R"(
░█████╗░
██╔══██╗
██║░░╚═╝
██║░░██╗
╚█████╔╝
░╚════╝░
)")},
etc.... for all supported characters (letters a-z, numbers, + some other ascii characters)

};


#endif // ASCII_H

main.cpp:
#include <iostream>
#include <algorithm>
#include "ascii.hpp"
#include "flip.hpp"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command;
        std::string input;
        int start = 1;
        if (argv[1][0] == '-') {
            command = argv[1];
            start = 2;
        }
        for (int i = start; i < argc; ++i) {
            if (i > start) input += " ";
            input += argv[i];
        }

        if (command == "-ascii") {
            generate_ascii_art(input);
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

flip.hpp:
#ifndef FLIP_H
#define FLIP_H

#include <map>
#include <string>

inline std::map<char, std::string> flipMap = {
    {'a', "\u0250"}, {'b', "q"}, {'c', "\u0254"}, {'d', "p"}, {'e', "\u01DD"},
    {'f', "\u025F"}, {'g', "\u0183"}, {'h', "\u0265"}, {'i', "\u0131"}, {'j', "\u0638"},
    {'k', "\u029E"}, {'l', "l"}, {'m', "\u026F"}, {'n', "u"}, {'o', "o"},
    {'p', "d"}, {'q', "b"}, {'r', "\u0279"}, {'s', "s"}, {'t', "\u0287"},
    {'u', "n"}, {'v', "\u028C"}, {'w', "\u028D"}, {'x', "x"}, {'y', "\u028E"},
    {'z', "z"}, {'0', "0"}, {'1', "\u0196"}, {'2', "\u1105"}, {'3', "\u0190"},
    {'4', "\u3123"}, {'5', "\u03DB"}, {'6', "9"}, {'7', "\u3125"}, {'8', "8"},
    {'9', "6"}, {' ', " "}
};

#endif


Modify my code to support printing ascii art output from text in user specified color. If they use -ascii -color=*name of color*, its RGB value, or hext -> print the text in their specified color