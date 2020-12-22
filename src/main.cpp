#include "classes/board.h"

int main (int argc, char** argv) {
    Board *b = (Board*) malloc(sizeof(Board));
    if (argc == 2) {
        string temp(argv[1]);
        Board b2(temp);
        *b = b2;
    } else {
        *b = Board();
    }
    (*b).print_pieces();
    return 0;
}