#include "classes/engine/engine.h"

int main (int argc, char** argv) {
    Engine engine;
    string input;
    while (input != "quit") {
        getline(cin, input);
        engine.parseExpr(input);
    }
    return 0;
}