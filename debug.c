#include "debug.h"

#include <stdio.h>

void disassembleChunk(Chunk* chunk, const char* name){
    printf(" == %s == \n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int unknownOpCode(int offset) {
    printf("Couldn't understand instruction no. %d\n", offset);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset){
    uint16_t constant = chunk->code[offset + 1];
    printf("%s, no. %d: ", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("\n");
    
    return offset + 2;
}

int disassembleInstruction(Chunk* chunk, int offset){
    printf("%d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("    |");
    } else {
        printf("%d, ", chunk->lines[offset]);
    }

    uint16_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_RETURN: return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT: return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_NEGATE: return simpleInstruction("OP_NEGATE", offset);
        case OP_ADD: return simpleInstruction("OP_ADD", offset);
        case OP_MUL: return simpleInstruction("OP_MUL", offset);
        case OP_DIV: return simpleInstruction("OP_DIV", offset);
        case OP_SUB: return simpleInstruction("OP_SUB", offset);
        default: return unknownOpCode(offset);
    }
}