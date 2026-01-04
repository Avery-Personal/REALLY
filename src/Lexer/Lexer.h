#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 1024
#define MAX_LOOP_DEPTH 256

typedef enum {
    TOKEN_INCREMENT, // ^
    TOKEN_DECREMENT, // v
    TOKEN_RESET, // 0
    TOKEN_FLIP, // &
    TOKEN_SWAP, // ~
    TOKEN_CR, // @
    TOKEN_SUB, // #
    TOKEN_LOOP_START, // (
    TOKEN_LOOP_END, // )
    TOKEN_STALL, // :
    TOKEN_SKIP, // ;
    TOKEN_INPUT, // '
    TOKEN_OUTPUT, // "
    TOKEN_NUM_OUTPUT, // %
    //TOKEN_NUM_B_OUTPUT, // ! B REGISTER DEBUGGER

    TOKEN_EOF, // End of File
} TokenType;

typedef struct {
  TokenType Type;
  int Jump;
} Token;

typedef struct {
    Token *Tokens;
    
    size_t Count;
    size_t Capacity;
} TokenArray;

TokenArray *CreateTokens(size_t Initialize);
void AddToken(TokenArray *TokenArray, TokenType Type, int Jump);
TokenArray *Tokenize(const char *Program);
void PrintTokens(TokenArray* Tokens);
