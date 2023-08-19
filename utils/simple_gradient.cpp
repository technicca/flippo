#include <iostream>
#include <string>

int main() {
    std::string text = "Hello world!";
    int len = text.length();
    for (int i = 0; i < len; ++i) {
        int red = 255 - (255 * i / len);
        int green = 255 * i / len;
        std::cout << "\033[38;2;" << red << ";" << green << ";0m" << text[i];
    }
    std::cout << "\033[0m" << std::endl;  // Reset to default color
    return 0;
}
