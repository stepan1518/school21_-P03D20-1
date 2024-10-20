#include "stack.h"

// Function initialize stack. If memory allocated successfully return pointer to
// the stack, otherwise NULL
struct stack *init(size_t size) {
    // Allocate memory for stack
    struct stack *token_stack = (struct stack *)malloc(sizeof(struct token) * size);

    // If memory for stack allocated successfully, then initialize stack
    if (token_stack != NULL) {
        token_stack->size = size;
        token_stack->top = -1;
        token_stack->tokens = (struct token *)malloc(token_stack->size * sizeof(struct token));

        // If memory for tokens array allocated unsuccessfully, then destroy stack
        if (token_stack->tokens == NULL) {
            free(token_stack);
            token_stack = NULL;
        }
    }
    return token_stack;
}
// Function checks whether stack is full or not
int is_full(struct stack *token_stack) { return (token_stack->top == (int)(token_stack->size) - 1) ? 1 : 0; }
// Function checks whether stack is empty or not
int is_empty(struct stack *token_stack) { return (token_stack->top == -1) ? 1 : 0; }
// Function pushes token to the top of the stack
void push(struct stack *token_stack, struct token new_token) {
    if (!is_full(token_stack)) token_stack->tokens[++token_stack->top] = new_token;
}
// Function pops token from the top of the stack
struct token pop(struct stack *token_stack) {
    return (is_empty(token_stack)) ? (struct token){UNDEFINED, {.value = NAN}}
                                   : token_stack->tokens[(token_stack->top)--];
}
// Function peeks top of the stack
struct token peek(struct stack *token_stack) {
    return (is_empty(token_stack)) ? (struct token){UNDEFINED, {.value = NAN}}
                                   : token_stack->tokens[(token_stack->top)];
}
// Function destroys stack and frees memory
void destroy(struct stack *token_stack) {
    if (token_stack != NULL) {
        free(token_stack->tokens);
        free(token_stack);
    }
}