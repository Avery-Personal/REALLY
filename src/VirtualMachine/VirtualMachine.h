#define MAX_REGISTER_DATA 1028

typedef struct {
    unsigned char A; // Primary register
    unsigned char B; // Secondary register
} ABRegisters;

typedef struct {
    TokenArray* Tokens;
    ABRegisters Registers;

    size_t IP;
} VM;

void VM_Initialize(VM* VirtualMachine, TokenArray* Tokens);
void VM_ExecuteToken(VM* VirtualMachine, Token* _Token);
void VM_Run(VM* VirtualMachine);
