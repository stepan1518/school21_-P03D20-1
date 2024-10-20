#include "stack.h"

struct stack* init(size_t size) {
    // Allocate memory for stack
    struct stack* token_stack = (struct stack*)malloc(sizeof(struct token) * size);

    // If memory for stack allocated successfully, then initialize stack
    if (token_stack != NULL) {
        token_stack->size = size;
        token_stack->top = -1;
        token_stack->tokens = (struct token*)malloc(token_stack->size * sizeof(struct token));

        // If memory for tokens allocated unsuccessfully, then destroy stack
        if (token_stack->tokens == NULL) {
            free(token_stack);
            token_stack = NULL;
        }
    }

    return token_stack;
}
struct stack* resize(struct stack* token_stack, size_t new_size) {
    struct token* new_tokens = (struct token*)realloc(token_stack->tokens, new_size);

    // If realloc succeeds, the memory that was previously allocated to tokens will be freed. 
    // However, if the call fails, new_tokens will be NULL, but toknes will still point to its original memory
    if (new_tokens) {
        token_stack->size = new_size;
        token_stack->tokens = new_tokens;
    }
    
    return token_stack;
}
int is_full(struct stack* token_stack) {
    return (token_stack->top == (int)(token_stack->size) - 1) ? 1 : 0;
}
int is_empty(struct stack* token_stack) {
    return (token_stack->top == -1) ? 1 : 0;
}
void push(struct stack* token_stack, struct token new_token) {
    if (!is_full(token_stack))
        token_stack->tokens[++token_stack->top] = new_token;
}
struct token pop(struct stack* token_stack) {
    return (is_empty(token_stack)) ? (struct token){UNDEFINED, {.value = NAN}} : token_stack->tokens[(token_stack->top)--];
}
struct token peek(struct stack* token_stack) {
    return (is_empty(token_stack)) ? (struct token){UNDEFINED, {.value = NAN}} : token_stack->tokens[(token_stack->top)];
}
void destroy(struct stack* token_stack) {
    free(token_stack->tokens);
    free(token_stack);
}