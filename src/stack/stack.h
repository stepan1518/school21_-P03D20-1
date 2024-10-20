#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <math.h>

enum TokenTag {NUMBER, OPERATOR, UNDEFINED};
enum TokegId {LPARENTHESIS, RPARENTHESIS, ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, SIN, COS, TAN, CTG, SQRT, LN, X};

// Token is tagged union structure
struct token {
    enum TokenTag tag;
    union {
        long long id;
        double value;
    };
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
struct token peek(struct stack*);
void destroy(struct stack*);

#endif // STACK_H