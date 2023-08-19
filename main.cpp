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

        if (command == "-ascii" || command == "-a") {
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