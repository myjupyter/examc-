#ifndef PROJECT_TEXT_H_
#define PROJECT_TEXT_H_

#include <vector>
#include <string>

typedef unsigned int uint;

class Text {
    public:
        Text();
        Text(const Text&) = delete;
        Text(Text&&) = delete;
        Text& operator=(const Text&) = delete;
        Text& operator=(Text&&) = delete;
        ~Text();

        void push_back(std::string& line);
        void insert(std::string& field, std::pair<uint, uint> index);
        void update(std::string& field, std::pair<uint, uint> index);
        void del(std::pair<uint, uint> index);

        friend std::ostream& operator<<(std::ostream& out, const Text& text);
        friend std::istream& operator>>(std::istream& in, Text& text);

    private:
        std::ostream& print_line(std::ostream& out, uint index) const;

        std::vector<std::vector<std::string>> _text;
};

#endif  // PROJECT_TEXT_H_
