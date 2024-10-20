#include "parser.h"

// Function skip all spaces in the string
void remove_spaces(char *str) {
    char *temp = str;
    do {
        while (*temp == ' ') ++temp;
    } while ((*str++ = *temp++));
}
// Function prepares string for token parsing. Returns tokenized string
char *tokenize(char *str, const char *token_templates[]) {
    char *tokenized = NULL;

    if (str && token_templates) {
        remove_spaces(str);

        // In worst case scenario tokenized string has 2 times more length of the
        // original string
        char *tokenized_temp = (char *)malloc(sizeof(char) * 2 * strlen(str));
        tokenized = tokenized_temp;

        while (*str && *str != '\n') {
            // Smallest token length equals 1
            int token_len = 1;

            // Try to parse real number
            if (*str >= '0' && *str <= '9') {
                char *endptr = NULL;
                strtold(str, &endptr);
                token_len = endptr - str;
                free(endptr);
                // Try to parse other token templates
            } else {
                for (int i = 0; i < N_TOKENS; i++) {
                    int token_str_len = strlen(token_templates[i]);
                    if (!strncmp(str, token_templates[i], token_str_len)) token_len = token_str_len;
                }
            }

            // Copy token into tokenized string
            while (token_len--) {
                *(tokenized_temp++) = *(str++);
            }
            // Add whitespace as a delimiter for future token parsing
            *(tokenized_temp++) = ' ';
        }
    }

    return tokenized;
}
// Function parse token string and returns struct token
struct token parse_token(const char *str, const char *token_templates[]) {
    struct token new_token = {UNDEFINED, {.value = NAN}};  // Create default token

    if (str) {
        // Try to parse real number
        if (*str >= '0' && *str <= '9') {
            new_token.tag = NUMBER;
            new_token.value = strtold(str, NULL);
            // Try to parse other token templates
        } else {
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
struct stack *ShuntingYard(char *str, const char *token_templates[]) {
    struct stack *output_stack = NULL;  // Create two stacks according to Shunting Yard Algorithm
    struct stack *operator_stack = NULL;
    int error = 0;

    if (str) {
        output_stack = init(strlen(str));
        operator_stack = init(strlen(str));

        if (!output_stack || !operator_stack) error++;
        char *token_string = strtok(tokenize(str, token_templates), " ");  // Get next token
        while (!error && token_string) {
            struct token token = parse_token(token_string, token_templates);  // Parse token from token string
            if (token.tag == UNDEFINED)                                       // If token parsed incorrectly
                error++;
            else if (token.tag == NUMBER)
                push(output_stack, token);  // Put number into the output queue
            else if (token.id >= SIN && token.id <= X)
                push(operator_stack, token);  // Put function onto the operator stack
            else if (token.id >= ADDITION && token.id <= DIVISION) {
                // There is an operator o2 at the top of the operator stack which is not
                // a left parenthesis with greater or same precedence
                while (!is_empty(operator_stack) && peek(operator_stack).id != LPARENTHESIS &&
                       (peek(operator_stack).id >= token.id))
                    push(output_stack, pop(operator_stack));
                push(operator_stack, token);  // Push operator onto the operator stack
            } else if (token.id == LPARENTHESIS)
                push(operator_stack,
                     token);  // Push left parenthesis onto the operator stack
            else if (token.id == RPARENTHESIS) {
                // While the operator at the top of the operator stack is not a left
                // parenthesis
                while (!error && peek(operator_stack).id != LPARENTHESIS)
                    (is_empty(operator_stack)) ? error++ : push(output_stack, pop(operator_stack));
                // There is no left parenthesis at the top of the operator stack
                if (peek(operator_stack).id != LPARENTHESIS)
                    error++;
                else
                    pop(operator_stack);
                // If there is a function token at the top of the operator stack
                if (peek(operator_stack).id >= SIN && peek(operator_stack).id <= X)
                    push(output_stack, pop(operator_stack));
            }
            // Get next token
            free(token_string);
            token_string = strtok(NULL, " ");
        };
        // While there are tokens on the operator stack
        while (!error && !is_empty(operator_stack)) {
            if (peek(operator_stack).id == LPARENTHESIS) error++;
            push(output_stack, pop(operator_stack));
        }
    } else
        error++;

    free(str);
    destroy(operator_stack);
    if (error) destroy(output_stack);
    return (error) ? NULL : output_stack;
}