
#include "draw.h"
#include "func_limits.h"

double func(double x) {
    return x * x;
}

int main() {
    double f[N_POINTS];
    double step = (X_END - X_START) / (N_POINTS - 1), x = X_START;

    for (size_t i = 0; i < N_POINTS; i++) {
        f[i] = func(x);
        x += step;
    }

    draw(f, X_START, step);

    return 0;
}
