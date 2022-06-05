#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_RETURN,
	OP_NEGATE,
	OP_ADD,
	OP_MUL,
	OP_DIV,
	OP_SUB,
} OpCode;

typedef struct {
	int count;
	int capacity;
	uint16_t* code;
	ValueArray constants;
	int* lines;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint16_t byte, int line);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);

#endif