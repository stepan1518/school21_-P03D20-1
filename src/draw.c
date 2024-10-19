#include "draw.h"

void draw(double* f, size_t size) {
    for (size_t i = 0; i < size; i++)
        printf("%lf", f[i]);
}