#include "classes/AI/engine.h"

int main (int argc, char** argv) {
    Engine engine;
    string input;
    while (input != "quit") {
        getline(cin, input);
        engine.parse_expr(input);
    }


    return 0;
}