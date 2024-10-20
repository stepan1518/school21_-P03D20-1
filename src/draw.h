#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <math.h>

#include "func_limits.h"
#include "parser.h"

#define N_POINTS 80
#define Y_POINTS 25

void draw(double* f, double start, double step);

#endif