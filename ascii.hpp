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
// other characters here
};

void generate_ascii_art(const std::string& text);

#endif // ASCII_H

