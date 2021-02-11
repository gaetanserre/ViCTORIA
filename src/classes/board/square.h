#pragma once
#include <string>

class Square {
    public:
        Square(char rank, int file) {
            this->rank = rank;
            this->file = file;
        }

        Square (std::string square) {
            this->rank = square[0];
            this->file = square[1] - '0';
        }

        Square() {
            this->rank = -1;
            this->file = -1;
        }

        std::string toString() {
            std::string res = std::string(1, this->rank) + std::to_string(this->file);
            return res;
        }

        void print() {
            std::cout << this->rank << this->file;
        }

        bool operator==(Square s) {
            return this->rank == s.rank && this->file == s.file;
        }

        bool operator==(std::string str) {
            return this->rank == str[0] && this->file == str[1] - '0';
        }

        bool operator!=(Square s) {
            return !(*this == s);
        }

        bool operator!=(std::string str) {
            return !(*this == str);
        }

        char rank;
        int file;
};