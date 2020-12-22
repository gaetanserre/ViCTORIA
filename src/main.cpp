#include "classes/board.h"

int main (int argc, char** argv) {
    Board b;

    if (argc == 2) {
        string temp(argv[1]);
        b.init(temp);
    } else {
        b.init();
    }

    b.print_pieces();
    cout << endl;
    b.print_move("");

    return 0;
}