#include "tokenDebug.h"
#include <stdio.h>

void printToken(const char* message, TokenType type){
    printf("%s",message);
    switch(type){
        case TOKEN_LEFT_PAREN:printf("TOKEN_LEFT_PAREN");break;
        case TOKEN_RIGHT_PAREN:printf("TOKEN_RIGHT_PAREN");break;
        case TOKEN_LEFT_BRACE:printf("TOKEN_LEFT_BRACE");break;
        case TOKEN_RIGHT_BRACE:printf("TOKEN_RIGHT_BRACE");break;
        case TOKEN_COMMA:printf("TOKEN_COMMA");break;
        case TOKEN_DOT:printf("TOKEN_DOT");break;
        case TOKEN_MINUS:printf("TOKEN_MINUS");break;
        case TOKEN_PLUS:printf("TOKEN_PLUS");break;
        case TOKEN_SEMICOLON:printf("TOKEN_SEMICOLON");break;
        case TOKEN_DIV:printf("TOKEN_DIV");break;
        case TOKEN_MUL:printf("TOKEN_MUL");break;
        case TOKEN_BANG:printf("TOKEN_BANG");break;
        case TOKEN_BANG_EQUAL:printf("TOKEN_BANG_EQUAL");break;
        case TOKEN_EQUAL:printf("TOKEN_EQUAL");break;
        case TOKEN_EQUAL_EQUAL:printf("TOKEN_EQUAL_EQUAL");break;
        case TOKEN_GREATER:printf("TOKEN_GREATER");break;
        case TOKEN_GREATER_EQUAL:printf("TOKEN_GREATER_EQUAL");break;
        case TOKEN_LESS:printf("TOKEN_LESS");break;
        case TOKEN_LESS_EQUAL:printf("TOKEN_LESS_EQUAL");break;
        case TOKEN_IDENTIFIER:printf("TOKEN_IDENTIFIER");break;
        case TOKEN_STRING:printf("TOKEN_STRING");break;
        case TOKEN_NUMBER:printf("TOKEN_NUMBER");break;
        case TOKEN_AND:printf("TOKEN_AND");break;
        case TOKEN_CLASS:printf("TOKEN_CLASS");break;
        case TOKEN_ELSE:printf(" OKEN_ELSE");break;
        case TOKEN_FALSE:printf("TOKEN_FALSE");break;
        case TOKEN_FOR:printf("TOKEN_FOR");break;
        case TOKEN_FUN:printf("TOKEN_FUN");break;
        case TOKEN_IF:printf("TOKEN_IF");break;
        case TOKEN_NIL:printf("TOKEN_NIL");break;
        case TOKEN_OR:printf("TOKEN_OR");break;
        case TOKEN_PRINT:printf("TOKEN_PRINT");break;
        case TOKEN_RETURN:printf("TOKEN_RETURN");break;
        case TOKEN_SUPER:printf("TOKEN_SUPER");break;
        case TOKEN_THIS:printf("TOKEN_THIS");break;
        case TOKEN_TRUE:printf("TOKEN_TRUE");break;
        case TOKEN_VAR:printf("TOKEN_VAR");break;
        case TOKEN_WHILE:printf(" TOKEN_WHILE");break;
        case TOKEN_ERROR:printf("TOKEN_ERROR");break;
        case TOKEN_EOF:printf("TOKEN_EOF");break;
        default:printf("Idk this token\n");
    }
    printf("\n");
}