#include "compiler.h"
#include "common.h"
#include "scanner.h"
#include "chunk.h"
#include "tokenDebug.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG_PRINT_CODE
    #include "debug.h"
#endif

typedef struct {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

Parser parser;

Chunk* compilingChunk;

static void factor();
static void term();
static void expression();

static Chunk* currentChunk(){
    return compilingChunk;
}

static void errorAt(Token* token, const char* message) {
    if (parser.panicMode) return;
    parser.panicMode = true;
    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
        // Nothing.
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }

    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}

static void error(const char* message) {
    errorAt(&parser.previous, message);
}

static void errorAtCurrent(const char* message) {
    errorAt(&parser.current, message);
}

int total_tok = 0;

static void advance() {
    parser.previous = parser.current;

    for (;;) {
        parser.current = scanToken();

        //printToken("current token:", parser.current.type);

        total_tok++;
        if (parser.current.type != TOKEN_ERROR) break;

        errorAtCurrent(parser.current.start);
    }
}

static void consume(TokenType type, const char* message){
    if (parser.current.type == type){
        advance();
        return;
    }

    errorAtCurrent(message);
}

static bool match(TokenType type){
    return parser.current.type == type;
}

static bool match_a(TokenType type){
    if (!match(type)){
        return false;
    }
    advance();
    return true;
}

static void emitByte(uint16_t byte){
    writeChunk(currentChunk(), byte, parser.previous.line);
}

static void emitBytes(uint16_t byte1, uint16_t byte2){
    emitByte(byte1);
    emitByte(byte2);
}

static void emitReturn(){
    emitByte(OP_RETURN);
}

static uint16_t makeConstant(Value value){
    int constant = addConstant(currentChunk(), value);
    if (constant > UINT16_MAX){
        error("constant exceed max constant capacity in the current chunk");
    }
    return (uint16_t)constant;
}

static void emitConstant(Value value){
    emitBytes(OP_CONSTANT, makeConstant(value));
}

static void endCompiler(){
    emitReturn();

    #ifdef DEBUG_PRINT_CODE
        if (!parser.hadError){
            disassembleChunk(currentChunk(), "op codes");
        }
    #endif
}

static void number(){
    double num = strtod(parser.previous.start, NULL);
    emitConstant(num);
}

static void group_paren(){
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expected ')' to close '('");
}

static void factor(){
    if (match_a(TOKEN_NUMBER)){
        number();
    } else if (match_a(TOKEN_LEFT_PAREN)){
        group_paren();
    } else if (match_a(TOKEN_MINUS)){
        factor(); // The number
        emitByte(OP_NEGATE);
    }
}

static void term(){
    factor();
    while (match_a(TOKEN_MUL)||match_a(TOKEN_DIV)){
        OpCode operator_tok = parser.previous.type==TOKEN_MUL?OP_MUL:OP_DIV;
        factor();
        emitByte(operator_tok);
    }
}

static void expression(){
    term();
    while (match_a(TOKEN_PLUS)||match_a(TOKEN_MINUS)){
        OpCode operator_tok = parser.previous.type==TOKEN_PLUS?OP_ADD:OP_SUB;
        term();
        emitByte(operator_tok);
    }
}

bool compile(const char* source, Chunk* chunk){
    initScanner(source);
    compilingChunk = chunk;

    parser.panicMode = parser.hadError = false;
    //printf("panic: %s, error: %s\n", parser.panicMode?"true":"false", parser.hadError?"true":"false");
    
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");

    //printf("Total tokens received: %d\n", total_tok);

    endCompiler();
    total_tok = 0;
    return !parser.hadError;
}
