#include "../Lexer/Lexer.h"
#include "VirtualMachine.h"

void VM_Initialize(VM* VirtualMachine, TokenArray* TokenStream) {
    VirtualMachine -> Registers.A = 0;
    VirtualMachine -> Registers.B = 0;

    VirtualMachine -> IP = 0;
    VirtualMachine -> Tokens = TokenStream;
}

void VM_ExecuteToken(VM* VirtualMachine, Token* _Token) {
    switch (_Token -> Type) {
        case TOKEN_INCREMENT:
            VirtualMachine -> Registers.A++;

            break;
        
        case TOKEN_DECREMENT:
            VirtualMachine -> Registers.A--;

            break;
        
        case TOKEN_RESET:
            VirtualMachine -> Registers.A = 0;

            break;
        
        case TOKEN_FLIP:
            VirtualMachine -> Registers.A = ~VirtualMachine -> Registers.A;

            break;
        
        case TOKEN_SWAP:
            unsigned char Temp = VirtualMachine -> Registers.A;

            VirtualMachine -> Registers.A = VirtualMachine -> Registers.B;
            VirtualMachine -> Registers.B = Temp;

            break;
        
        case TOKEN_CR:
            VirtualMachine -> Registers.A = VirtualMachine -> Registers.A + VirtualMachine -> Registers.B;

            break;
        
        case TOKEN_SUB:
            VirtualMachine -> Registers.A = VirtualMachine -> Registers.A - VirtualMachine -> Registers.B;

            break;
        
        case TOKEN_LOOP_START:
            if (VirtualMachine -> Registers.A == 0)
                VirtualMachine -> IP = _Token -> Jump;

            break;
        
        case TOKEN_LOOP_END:
            if (VirtualMachine -> Registers.A != 0)
                VirtualMachine -> IP = _Token -> Jump;

            break;
        
        case TOKEN_STALL:
            break;
        
        case TOKEN_SKIP:
            VirtualMachine -> IP++;

            break;
        
        case TOKEN_INPUT:
            size_t _IP = VirtualMachine -> IP + 1;

            while (_IP < VirtualMachine -> Tokens -> Count) {
                Token *_Token = &VirtualMachine -> Tokens -> Tokens[_IP];

                if (_Token -> Type == TOKEN_INCREMENT)
                    VirtualMachine -> Registers.A++;
                else if (_Token -> Type == TOKEN_DECREMENT)
                    VirtualMachine -> Registers.A--;
                else if (_Token -> Type == TOKEN_RESET)
                    VirtualMachine -> Registers.A = 0;
                else
                    break;

                _IP++;
            }

            VirtualMachine -> IP = _IP - 1;
            
            break;
        
        case TOKEN_OUTPUT:
            printf("%c", (char) VirtualMachine -> Registers.A);
            
            break;
        
        
        case TOKEN_NUM_OUTPUT:
            printf("%u", VirtualMachine -> Registers.A);
            
            break;
        
        
        //case TOKEN_NUM_B_OUTPUT: B REGISTER DEBUGGER
        //    printf("%u", VirtualMachine -> Registers.B);
            
        //    break;
        
        case TOKEN_EOF:
            break;

        default:
            fprintf(stderr, "Unknown Token in Virtual Machine: %d\n", _Token -> Type);

            break;
    }
}

void VM_Run(VM* VirtualMachine) {
    while (VirtualMachine -> IP < VirtualMachine -> Tokens -> Count) {
         Token* _Token = &VirtualMachine -> Tokens -> Tokens[VirtualMachine -> IP];
        if (_Token -> Type == TOKEN_EOF) break;

        VM_ExecuteToken(VirtualMachine, _Token);
        VirtualMachine->IP++;
    }
}
