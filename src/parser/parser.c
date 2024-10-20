#include "stack/stack.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 32768
#define N_TOKENS 13

void remove_spaces(char* str) {
    char* temp = str;
    do {
        while (*temp == ' ') {
            ++temp;
        }
    } while ((*str++ = *temp++));
}
char* tokenize(char *str, const char *token_templates[]) {
    char* tokenized = NULL;

    if (str && token_templates) {
        remove_spaces(str);
        char* tokenized_temp = (char*)malloc(sizeof(char) * 2 * strlen(str));
        tokenized = tokenized_temp;

        while (*str && *str != '\n') {            
            int token_len = 1;

            if (*str >= '0' && *str <= '9') {
                char *endptr;
                strtold(str, &endptr);
                token_len = endptr - str;
            } else {
                for (int i = 0; i < N_TOKENS; i++) {
                    int str_len = strlen(token_templates[i]); 
                    if (!strncmp(str, token_templates[i], str_len))
                        token_len = str_len;
                }
            }
            
            while (token_len--) {
                *(tokenized_temp++) = *(str++);
            }
            *(tokenized_temp++) = ' ';
        }
    }

    return tokenized;
}
struct token parse_token(const char *str, const char *token_templates[]) {
    struct token new_token = {UNDEFINED, {.value = NAN}};

    if (str) {
        if (*str >= '0' && *str <= '9') {
            new_token.tag = NUMBER;
            new_token.value = strtold(str, NULL);
        }
        else {
            for (int i = 0; i < N_TOKENS; i++) {
                if (!strncmp(str, token_templates[i], strlen(token_templates[i]))) {
                    new_token.tag = OPERATOR;
                    new_token.id = i;
                }
            }
        }
    }

    return new_token;
}

struct stack* ShuntingYard(char* str, const char *token_templates[]) {
    int error = 0;
    struct stack* output_stack = NULL;
    struct stack* operator_stack = NULL;

    if (str) {
        output_stack = init(strlen(str));
        operator_stack = init(strlen(str));

        char *token_string = strtok(tokenize(str, token_templates), " ");
        while (!error && token_string) {
            struct token token = parse_token(token_string, token_templates);
            if (token.tag == UNDEFINED) {
                error++;
            }
            else if (token.tag == NUMBER) {
                push(output_stack, token);
            }
            else if (token.id >= SIN && token.id <= X) {
                push(operator_stack, token);
            }
            else if (token.id >= ADDITION && token.id <= DIVISION) {
                while (!is_empty(operator_stack) && peek(operator_stack).id != LPARENTHESIS && (peek(operator_stack).id >= token.id)) {
                    push(output_stack, pop(operator_stack));
                }
                push(operator_stack, token);
            } else if (token.id == LPARENTHESIS)
                push(operator_stack, token);
            else if (token.id == RPARENTHESIS) {
                while (!error && peek(operator_stack).id != LPARENTHESIS) {
                    if (is_empty(operator_stack))
                        error++;
                    else
                        push(output_stack, pop(operator_stack));
                };

                if (peek(operator_stack).id != LPARENTHESIS)
                    error++;
                else
                    pop(operator_stack);
                
                if (peek(operator_stack).id >= SIN && peek(operator_stack).id <= X)
                    push(output_stack, pop(operator_stack));
            }

            token_string = strtok(NULL, " ");
        };

        while (!error && !is_empty(operator_stack)) {
            if (peek(operator_stack).id == LPARENTHESIS)
                error++;

            push(output_stack, pop(operator_stack));
        }
    } else
        error++;

    free(operator_stack);
    if (error) {
        free(output_stack);
        output_stack = NULL;
    }

    return output_stack;
}
double evaluate(double x, int n_tokens, struct token* tokens_array) {
    struct stack* tokens = init(n_tokens);
    
    for (int i = 0; i < n_tokens; i++) {
        if (tokens_array[i].tag == NUMBER)
            push(tokens, tokens_array[i]);
        else if (tokens_array[i].id == X)
            push(tokens, (struct token){NUMBER, {.value = x}});
        else if (tokens_array[i].id == ADDITION)
            push(tokens, (struct token){NUMBER, {.value = pop(tokens).value + pop(tokens).value}});
        else if (tokens_array[i].id == SUBTRACTION)
            push(tokens, (struct token){NUMBER, {.value = pop(tokens).value - pop(tokens).value}});
        else if (tokens_array[i].id == MULTIPLICATION)
            push(tokens, (struct token){NUMBER, {.value = pop(tokens).value * pop(tokens).value}});
        else if (tokens_array[i].id == DIVISION)
            push(tokens, (struct token){NUMBER, {.value = (1.0 / pop(tokens).value) * pop(tokens).value}});
        else if (tokens_array[i].id == SIN)
            push(tokens, (struct token){NUMBER, {.value = sin(pop(tokens).value)}});
        else if (tokens_array[i].id == COS)
            push(tokens, (struct token){NUMBER, {.value = cos(pop(tokens).value)}});
        else if (tokens_array[i].id == TAN)
            push(tokens, (struct token){NUMBER, {.value = tan(pop(tokens).value)}});
        else if (tokens_array[i].id == CTG)
            push(tokens, (struct token){NUMBER, {.value = tan(M_PI / 2.0 - pop(tokens).value)}});
        else if (tokens_array[i].id == SQRT)
            push(tokens, (struct token){NUMBER, {.value = sqrt(pop(tokens).value)}});
        else if (tokens_array[i].id == LN)
            push(tokens, (struct token){NUMBER, {.value = log(pop(tokens).value)}});            
    }

    double result = pop(tokens).value;

    return (is_empty(tokens)) ? result : NAN;
}
int main(void) {
    char buffer[BUFFER_SIZE];

    // token_templates must be precedence sorted in descending order
    const char *token_templates[] = {"(", ")", "+", "-", "*", "/", "sin", "cos", "tan", "ctg", "sqrt", "ln", "x"};
    fgets(buffer, BUFFER_SIZE, stdin);

    struct stack* output_stack = ShuntingYard(tokenize(buffer, token_templates), token_templates);

    if (output_stack) {
        double res = evaluate(1, output_stack->top + 1, output_stack->tokens);

        if (isfinite(res))
            printf("%lf", res);
        else
            printf("n/a");
    }
    else
        printf("n/a");
    
    return 0;
}
