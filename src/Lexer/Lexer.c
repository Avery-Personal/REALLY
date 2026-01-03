#include "Lexer.h"

const char* TokenName(TokenType Type) {
    switch (Type) {
        case TOKEN_INCREMENT: return "INCREMENT";
        case TOKEN_DECREMENT: return "DECREMENT";
        case TOKEN_RESET: return "RESET";
        case TOKEN_FLIP: return "FLIP";
        case TOKEN_SWAP: return "SWAP";
        case TOKEN_CR: return "CR";
        case TOKEN_SUB: return "SUB";
        case TOKEN_LOOP_START: return "LOOP_START";
        case TOKEN_LOOP_END: return "LOOP_END";
        case TOKEN_STALL: return "STALL";
        case TOKEN_SKIP: return "SKIP";
        case TOKEN_INPUT: return "INPUT";
        case TOKEN_OUTPUT: return "OUTPUT";
        case TOKEN_EOF:return "EOF";
        
        default:                return "UNKNOWN";
    }
}

TokenArray *CreateTokens(size_t Initialize) {
    TokenArray *TempArray = malloc(sizeof(TokenArray));
    if (!TempArray)
        return NULL;
    
    if (Initialize == 0)
        Initialize = 1;

    TempArray -> Tokens = (Token*) malloc(Initialize * sizeof(Token));
    if (!TempArray -> Tokens) {
        free(TempArray);
        
        return NULL;
    }

    TempArray -> Count = 0;
    TempArray -> Capacity = Initialize;
    
    return TempArray;
}

void AddToken(TokenArray *TokenStream, TokenType Type, int Jump) {
    if (TokenStream -> Count >= TokenStream -> Capacity) {
        TokenStream -> Capacity *= 2;
        Token *NewMemory = realloc(TokenStream -> Tokens, TokenStream -> Capacity * sizeof(Token));

        if (!NewMemory) {
            fprintf(stderr, "Out of memory\n");

            exit(1);
        }
        
        TokenStream -> Tokens = NewMemory;
    }

    TokenStream -> Tokens[TokenStream -> Count++] = (Token){ Type, Jump };
}

TokenArray *Tokenize(const char *Program) {
    size_t CODE = strlen(Program);
    TokenArray *TokenStream = CreateTokens(CODE);
    if (!TokenStream) {
        fprintf(stderr, "Couldn't create token array");
    
        return NULL;
    }

    int LoopStack[MAX_LOOP_DEPTH];
    int LoopDepth = 0;
    
    for (size_t i=0; i < CODE; ++i) {
        char Character = Program[i];

        switch (Character) {
            case '^':
                AddToken(TokenStream, TOKEN_INCREMENT, -1);

                break;
                
            case 'v':
                AddToken(TokenStream, TOKEN_DECREMENT, -1);

                break;
                
            case '0':
                AddToken(TokenStream, TOKEN_RESET, -1);

                break;
                
            case '&':
                AddToken(TokenStream, TOKEN_FLIP, -1);

                break;
                
            case '~':
                AddToken(TokenStream, TOKEN_SWAP, -1);

                break;
                
            case '@':
                AddToken(TokenStream, TOKEN_CR, -1);

                break;
                
            case '#':
                AddToken(TokenStream, TOKEN_SUB, -1);

                break;
                
            case '(':
                if (LoopDepth >= MAX_LOOP_DEPTH) {
                    fprintf(stderr, "ERROR: Too many nested loops\n");

                    return NULL;
                }

                AddToken(TokenStream, TOKEN_LOOP_START, -1);
                LoopStack[LoopDepth++] = TokenStream -> Count - 1;

                break;
                
            case ')': {
                    if (LoopDepth <= 0) {
                        fprintf(stderr, "ERROR: Unmatched ')'\n");

                        return NULL;
                    }

                    int StartIndex = LoopStack[--LoopDepth];
                    
                    AddToken(TokenStream, TOKEN_LOOP_END, StartIndex);
                    TokenStream -> Tokens[StartIndex].Jump = TokenStream -> Count -1;

                    break;
                }

            case ':':
                AddToken(TokenStream, TOKEN_STALL, -1);

                break;
                
            case ';':
                AddToken(TokenStream, TOKEN_SKIP, -1);

                break;
                
            case '\'':
                AddToken(TokenStream, TOKEN_INPUT, -1);

                break;
                
            case '"':
                AddToken(TokenStream, TOKEN_OUTPUT, -1);

                break;
            
            default:
                fprintf(stderr, "Unknown character: %c\n", Character);

                break;
        }
    }

    if (LoopDepth != 0) {
        fprintf(stderr, "ERROR: Unmatched '('\n");

        return NULL;
    }

    AddToken(TokenStream, TOKEN_EOF, -1);

    return TokenStream;
}

void PrintTokens(TokenArray* Tokens) {
    printf("Token Count: %i\n\n", Tokens -> Count);

    for (size_t i=0; i < Tokens -> Count; ++i) {
        Token _Token = Tokens -> Tokens[i];

        if (_Token.Type == TOKEN_LOOP_START || _Token.Type == TOKEN_LOOP_END) {
            printf("%s (Jump: %d)\n", TokenName(_Token.Type), _Token.Jump);
        } else {
            printf("%s\n", TokenName(_Token.Type));
        }
    }
}
