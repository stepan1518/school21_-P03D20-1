#ifndef PARSER_H
#define PARSER_H

#include <string.h>

#include "../stack/stack.h"

void remove_spaces(char *);
char *tokenize(char *, const char *[]);
struct token parse_token(const char *, const char *[]);
struct stack *ShuntingYard(char *, const char *[]);

#endif  // PARSER_H