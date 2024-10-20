#include "calculation/calculation.h"
#include "graph/graph.h"
#include "parser/parser.h"
#include "stack/stack.h"
#define BUFFER_SIZE 32768

int main(void) {
    struct stack *output_stack;
    char buffer[BUFFER_SIZE];
    // token_templates must be precedence sorted in descending order
    const char *token_templates[] = {"(",   ")",   "+",   "-",    "*",  "/", "sin",
                                     "cos", "tan", "ctg", "sqrt", "ln", "x"};
    fgets(buffer, BUFFER_SIZE, stdin);
    output_stack = ShuntingYard(tokenize(buffer, token_templates), token_templates);

    if (output_stack) {
        double values[MMAX] = {0};
        int graph[NMAX][MMAX] = {0};

        calculate_values(values, output_stack);
        calculate_graph(graph, values);
        draw_graph(graph);
    } else
        printf("n/a");

    destroy(output_stack);
    return 0;
}