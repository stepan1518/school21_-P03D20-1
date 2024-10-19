#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <math.h>

#define TOKEN_LEN 32

enum TokenTag {NUMBER, FUNCTION, PARENTHESIS, OPERATOR, WHITESPACE, UNDEFINED};

// Token is tagged union structure (either a number or an operator)
struct token {
    enum TokenTag tag;
    char* string;
};
struct stack {
    size_t size;
    int top;
    struct token* tokens;
};

struct stack* init(size_t);
struct stack* resize(struct stack*, size_t);
int is_full(struct stack*);
int is_empty(struct stack*);
void push(struct stack*, struct token);
struct token pop(struct stack*);
void destroy(struct stack*);

#endif // STACK_H