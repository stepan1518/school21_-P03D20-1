#include "calculation.h"

double addition(double x, double y) { return x + y; }
double subtraction(double x, double y) { return x - y; }
double multiplication(double x, double y) { return x * y; }
double division(double x, double y) { return (fabs(y) > EPS) ? x / y : NAN; }
double ctg(double x) { return tan(M_PI / 2.0 - x); }
// Function calculates value in a single point
double calculate_point(double x, int n_tokens, struct token *tokens_array) {
    struct stack *tokens = init(2 * n_tokens);

    Function functions[] = {
        {ADDITION, addition, 1},
        {SUBTRACTION, subtraction, 1},
        {MULTIPLICATION, multiplication, 1},
        {DIVISION, division, 1},
        {SIN, sin, 0},
        {COS, cos, 0},
        {TAN, tan, 0},
        {CTG, ctg, 0},
        {SQRT, sqrt, 0},
        {LN, log, 0},
    };

    for (int i = 0; i < n_tokens; i++) {
        if (tokens_array[i].tag == NUMBER)
            push(tokens, tokens_array[i]);
        else if (tokens_array[i].id == X)
            push(tokens, (struct token){NUMBER, {.value = x}});
        else {
            for (size_t j = 0; j < sizeof(functions) / sizeof(functions[0]); j++) {
                if (functions[j].id == tokens_array[i].id) {
                    if (functions[j].is_binary) {
                        BinaryFunction bin_func = (BinaryFunction)functions[j].func;
                        push(tokens, (struct token){
                                         NUMBER, {.value = bin_func(pop(tokens).value, pop(tokens).value)}});
                    } else {
                        UnaryFunction un_func = (UnaryFunction)functions[j].func;
                        push(tokens, (struct token){NUMBER, {.value = un_func(pop(tokens).value)}});
                    }
                }
            }
        }
    }
    double result = pop(tokens).value;
    destroy(tokens);
    return result;
}

// Function calculates values according to output stack
void calculate_values(double *values, struct stack *output_stack) {
    for (int j = 0; j < MMAX; j++) {
        double x = X_MIN + X_INT * (double)j;
        values[j] = calculate_point(x, output_stack->top + 1, output_stack->tokens);
    }
}

// Function calculates graph values for drawing the graph
void calculate_graph(int graph[NMAX][MMAX], const double *values) {
    if (graph && values)
        for (int i = 0; i < NMAX; i++)
            for (int j = 0; j < MMAX; j++)
                if (values[j] >= Y_MIN + Y_INT * (double)i && values[j] < Y_MIN + Y_INT * (double)(i + 1))
                    graph[i][j]++;
}