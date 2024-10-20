#include "stack.h"
#include <stdio.h>

int main(void) {
    //struct stack* token_stack;
    struct token token1 = {OPERATOR, {.id = 10}};
    struct token token2 = {NUMBER, {.value = 1}};
    
    printf("%d %d\n", token1.tag, token1.id);
    printf("%d %lf\n", token2.tag, token2.value);

    return 0;
}