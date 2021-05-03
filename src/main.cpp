#include "classes/engine/engine.h"

int main (int argc, char** argv) {
    Evaluator evaluator;
    Engine engine (argv[0], evaluator);

    string input;
    while (input != "quit") {
        getline(cin, input);
        engine.parseExpr(input);
    }
    return 0;
}