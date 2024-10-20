#include "graph.h"

// Function draw graph according to calculated graph values
void draw_graph(int graph[NMAX][MMAX]) {
    if (graph)
        for (int i = 0; i < NMAX; i++) {
            for (int j = 0; j < MMAX; j++) {
                printf("%c", (graph[i][j]) ? '*' : '.');
                // Skip whitespace at the end of the row
                if (j < MMAX - 1) printf(" ");
            }
            // Skip newline character after the last column
            if (i < NMAX - 1) printf("\n");
        }
}