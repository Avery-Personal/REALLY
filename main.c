#include <stdio.h>

#include "src/Lexer/Lexer.h"

int main() {
    // Increments the A registers to 3; Output A register.
    const char *File = 
        "^^^"
        "\"";

    TokenArray *Tokens = Tokenize(File);
    PrintTokens(Tokens);
}
