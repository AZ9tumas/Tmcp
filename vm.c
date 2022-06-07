#include "vm.h"
#include "debug.h"
#include "compiler.h"

#include <stdio.h>

VM vm;

static void resetStack(){
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {

}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop(){
    vm.stackTop--;
    return *vm.stackTop;
}

void Binary_op(uint16_t instruction){
    double second_val = pop();
    double first_val = pop();

    printf("Binary operation: %s\n", instruction == OP_ADD?"Add":"nan");
    printf("Numbers: %f %f\n", first_val, second_val);
    printf("add: %f\n", first_val + second_val);

    push(first_val + second_val);
}

static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    
    #ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
    #endif
    #define BINARY_OP(op) \
        do { \
            double b = pop(); \
            double a = pop(); \
            push(a op b); \
        } while (false)

    for (;;) {
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;

            }
            case OP_NEGATE: {
                //Value constant = pop();
                //push(-constant);
                *(vm.stackTop-1) = -(*(vm.stackTop-1));
                break;
            }
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
            case OP_ADD: Binary_op(OP_ADD); break;
            case OP_DIV: BINARY_OP(/); break;
            case OP_MUL: BINARY_OP(*); break;
            case OP_SUB: BINARY_OP(-); break;
            default: printf("Cannot understand a specific instruction\n");
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(const char* source){
    Chunk chunk;
    initChunk(&chunk);

    if (!compile(source, &chunk)){
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();

    disassembleChunk(&chunk, "<repl>");
    
    freeChunk(&chunk);
    return result;
}
