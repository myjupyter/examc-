#include <iostream>
#include <sstream>
#include <utility>

#include "text.h"

const std::string ERR_MSG("Wrong index");

Text::Text(){};

Text::~Text(){};

void Text::push_back(std::string& line) {
    std::stringstream ss(std::move(line));
    std::string field;
    std::vector<std::string> splited_line;
    while (std::getline(ss, field, '\t')) {
        if (field.empty()) {
            continue;
        }
        splited_line.push_back(std::move(field));
    }
    _text.push_back(std::move(splited_line));
}

void Text::insert(std::string& field, std::pair<uint, uint> index) {
    if (index.first == _text.size() && index.second == 0) {
        _text.push_back(std::vector<std::string>());
        _text[_text.size() - 1].push_back(std::move(field));
            
        print_line(std::cout, index.first);
        std::cout << std::endl;
        return;
    }
    if (index.first < _text.size() &&
        index.second == _text[index.first].size()) { 
        _text[index.first].push_back(std::move(field));
        print_line(std::cout, index.first);
        std::cout << std::endl;
        return;
    }

    if (index.first >= _text.size() ||
        index.second > _text[index.first].size()) {
        throw std::out_of_range(ERR_MSG);
    }

    auto it = _text[index.first].begin();
    _text[index.first].insert(it + index.second, std::move(field));

    print_line(std::cout, index.first);
    std::cout << std::endl;
}

void Text::update(std::string& field, std::pair<uint, uint> index) {
    if (index.first >= _text.size() ||
        index.second >= _text[index.first].size()) {
        throw std::out_of_range(ERR_MSG);
    }
    _text[index.first][index.second] = std::move(field);

    print_line(std::cout, index.first);
    std::cout << std::endl;
}

void Text::del(std::pair<uint, uint> index) {
    if (_text.empty()) {
        return;
    }

    if (index.first > _text.size() ||
        index.second > _text[index.first].size()) {
        throw std::out_of_range(ERR_MSG);
    }

    auto it = _text[index.first].begin();
    _text[index.first].erase(it + index.second);
    
    if (_text[index.first].empty()) {
        auto it = _text.begin();
        _text.erase(it + index.first);
    } else {
        print_line(std::cout, index.first);
        std::cout << std::endl;
    }
}

std::ostream& Text::print_line(std::ostream& out, uint index) const {
    uint j = 0;
    out << index << ". ";
    for (std::string field : _text[index]) {
        out << "(" << j++ << ")" << field << '\t';
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Text& text) {
    unsigned int i = 0;
    for (std::vector<std::string> line : text._text) {
        text.print_line(out, i++);
        out << std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Text& text) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) break;
        text.push_back(line);
    }
    return in;
}
