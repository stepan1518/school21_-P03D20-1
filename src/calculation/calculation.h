#ifndef CALCULATION_H
#define CALCULATION_H

#include "../graph/graph.h"
#include "../stack/stack.h"

#define EPS 1E-12
#define X_MIN 0.0
#define X_MAX 4 * M_PI
#define Y_MIN -1.0
#define Y_MAX 1.0
#define X_INT (X_MAX - X_MIN) / (double)(MMAX - 1)
#define Y_INT (Y_MAX - Y_MIN) / (double)(NMAX - 1)

// Define types for unary and binary functions
typedef double (*UnaryFunction)(double);
typedef double (*BinaryFunction)(double, double);

typedef struct {
    enum TokegId id;
    void *func;
    int is_binary;
} Function;

double addition(double, double);
double subtraction(double, double);
double multiplication(double, double);
double division(double, double);
double ctg(double);
double calculate_point(double, int, struct token *);
void calculate_values(double *, struct stack *);
void calculate_graph(int[NMAX][MMAX], const double *);

#endif  // CALCULATION_H