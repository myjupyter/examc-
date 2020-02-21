#include <iostream>
#include <cctype>
#include <algorithm>

#include "text.h"

#define INSERT 1
#define UPDATE 2
#define DELETE 3
#define OUTPUT 4
#define EXIT_  5

const std::string MENU(
    "1. Insert field;\n"
    "2. Update field;\n"
    "3. Delete field;\n"
    "4. Print all text;\n"
    "5. Exit.\n");

const std::string clean("\x1B[2J\x1B[H");

int main() {
    Text the_text;
    
    std::string str_index;
    std::pair<uint, uint> index;

    std::string field;

    std::cout << clean << "Enter the text(to complete entering press 2xEnter): " << std::endl;
    std::cin >> the_text;
    std::cout << clean;
    
    std::string command("1");
    int command_num = std::stoi(command);
    while (command_num) {
        std::cout << MENU;
        std::cout << "Print command: ";
        std::cin >> command;
        try {
            command_num = std::stoi(command);
            if (command_num > 0 && command_num < 4) {
                std::cout << "Line index: ";
                std::cin >> str_index;
                index.first = std::stoi(str_index);
                
                std::cout << "Field index: ";
                std::cin >> str_index;
                index.second = std::stoi(str_index);
                
                if (command_num < 3) {
                    std::cout << "New field: ";
                    std::cin >> field;
                }
            }
        } catch(std::invalid_argument& err) {
            std::cout << clean << "Invalid command" << std::endl << "Try again" << std::endl;
            std::cout << std::endl;
            continue;
        }
        std::cout << clean;
        std::cout << "Result: " << std::endl;
        try {
            switch (command_num) {
                case INSERT:
                    the_text.insert(field, index);
                    break;
                case UPDATE:
                    the_text.update(field, index);
                    break;
                case DELETE:
                    the_text.del(index);
                    break;
                case OUTPUT:
                    std::cout << the_text;
                    break;
                case EXIT_:
                    command_num = 0;
                    continue;
                    break;
                default:
                    command_num = 1;
                    std::cout << clean << "Invalid command" << std::endl << "Try again" << std::endl;
                    std::cout << std::endl;
                    continue;
            }
        } catch (std::out_of_range& err) {
            std::cout << "Wrong index" << std::endl << "Try again" << std::endl;
            std::cout << std::endl;
            continue;
        }
        std::cout << std::endl;
    }
    std::cout << clean << "Bye!" << std::endl;
    return 0;
}
