#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include "func_limits.h"

void draw(double* f, size_t size);

int main() {
    double f[3] = {1, 2, 3};
    draw(f, 3);

    return 0;
}

#endif