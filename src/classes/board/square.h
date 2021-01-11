#pragma once
#include <string>

class Square {
    public:
        Square(char row, int line) {
            this->row = row;
            this->line = line;
        }

        Square (std::string square) {
            this->row = square[0];
            this->line = square[1] - '0';
        }

        Square() {
            this->row = -1;
            this->line = -1;
        }

        void print() {
            std::cout << this->row << this->line;
        }

        bool operator==(Square s) {
            return this->row == s.row && this->line == s.line;
        }

        bool operator==(std::string str) {
            return this->row == str[0] && this->line == str[1] - '0';
        }

        bool operator!=(Square s) {
            return !(*this == s);
        }

        bool operator!=(std::string str) {
            return !(*this == str);
        }

        char row;
        int line;
};