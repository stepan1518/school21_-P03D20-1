#include "draw.h"

void draw(double* f, double start, double step) {
    double max_y = -1e9, min_y = 1e9, x = start;
    char res[Y_POINTS][N_POINTS + 1];

    for (int i = 0; i < Y_POINTS; i++) {
        for (int j = 0; j < N_POINTS; j++) {
            res[i][j] = '.';
        }
    }

    for (int i = 0; i < N_POINTS; i++) {
        double cur_y = f[i];
        if (cur_y > max_y) {
            max_y = cur_y;
        }
        if (cur_y < min_y) {
            min_y = cur_y;
        }
    }

    x = start;
    for (int i = 0; i < N_POINTS; i++) {
        double cur_y = f[i];

        double proc = (cur_y - min_y) / (max_y - min_y);
        double pos_y = proc * (Y_POINTS - 1);

        res[(int)round(pos_y)][i] = '*';
        x += step;
    }

    for (int i = Y_POINTS - 1; i >= 0; i--) {
        res[i][N_POINTS] = '\0';
        printf("%s\n", res[i]);
    }

    printf("\n\n");
}