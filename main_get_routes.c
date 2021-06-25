#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "dfs.h"

int main() {
    double k1 = 1.0 - n3*0.01 - n4*0.005 - 0.15;
    srand(0304);
    int **A = get_matrix(n, k1);
    struct Graph* graph = createGraph(n);
    //int **A1 = get_edge_matrix(A, n5);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i !=j && A[i][j] == 1 && A[j][i] == 1){
                A[j][i] = 0;
            }
        }
    }
    print_2Darray(A, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && A[i][j] == 1){
                addEdge(graph, i, j);
                printf("\nadded %d->%d", i, j);
            }
        }
    }

    printf("\n");
    int **Routes = dfs(graph, 0);

    return 0;
}
