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
    
    string input;
    while (true) {
        cout << "Type move :" << endl;
        cin >> input;
        if (input == "exit") break;
        const char* move = input.c_str();
        if (b.play_move(move)) b.print_pieces();
        else cout << "Illegal move." << endl;
    }
    return 0;
}