#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer/Lexer.h"
#include "VirtualMachine/VirtualMachine.h"

char *ReadFile(const char *Filename) {
    FILE *File = fopen(Filename, "r");
    if (!File) {
        perror("Error opening file");

        return NULL;
    }

    fseek(File, 0, SEEK_END);
    size_t Size = ftell(File);
    fseek(File, 0, SEEK_SET);

    char *Buffer = malloc(Size + 1);
    if (!Buffer) {
        perror("Memory allocation failed");
        fclose(File);
        
        return NULL;
    }

    fread(Buffer, 1, Size, File);
    fclose(File);

    Buffer[Size] = '\0';

    return Buffer;
}

char *ReadSource(void) {
    size_t Capacity = 1024;
    size_t len = 0;

    char *Buffer = malloc(Capacity);
    if (!Buffer) return NULL;

    int Character;

    while ((Character = getchar()) != EOF) {
        if (len + 1 >= Capacity) {
            Capacity *= 2;
            Buffer = realloc(Buffer, Capacity);

            if (!Buffer) return NULL;
        }

        Buffer[len++] = (char) Character;
    }

    Buffer[len] = '\0';

    return Buffer;
}

void PrintUsage(const char *Program) {
    printf("Usage: %s [options] <file or ->\n", Program);
    printf("Options:\n");
    printf("  -v       Verbose output\n");
    printf("  -h       Help\n");
    printf("Use '-' as filename to read from stdin.\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        PrintUsage(argv[0]);

        return 1;
    }

    int Verbose = 0;
    const char *Filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0)
            Verbose = 1;
        else if (strcmp(argv[i], "-h") == 0) {
            PrintUsage(argv[0]);

            return 0;
        } else
            Filename = argv[i];
    }

    char *Source = NULL;

    if (!Filename) {
        if (Verbose) printf("Reading source from stdin (Ctrl+D to finish)...\n");

        Source = ReadSource();
    } else if (strcmp(Filename, "-") == 0) {
        if (Verbose) printf("Reading source from stdin (Ctrl+D to finish)...\n");

        Source = ReadSource();
    } else {
        Source = ReadFile(Filename);
    }

    if (!Source)
        return 1;

    if (Verbose)
        printf("Read %zu bytes from %s\n", strlen(Source), Filename);

    TokenArray *Tokens = Tokenize(Source);
    if (!Tokens) {
        fprintf(stderr, "Tokenization failed\n");
        free(Source);

        return 1;
    }

    if (Verbose)
        printf("Tokenized %zu Tokens\n", Tokens -> Count);

    VM VirtualMachine;
    VM_Initialize(&VirtualMachine, Tokens);

    if (Verbose)
        printf("Running VM...\n");

    VM_Run(&VirtualMachine);

    if (Verbose)
        printf("\nExecution finished.\n");

    free(Source);
    free(Tokens -> Tokens);
    free(Tokens);

    return 0;
}
