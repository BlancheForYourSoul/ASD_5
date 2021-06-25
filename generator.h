#include <stdio.h>
#include <stdlib.h>
#define n1 0
#define n2 3
#define n3 0
#define n4 4
#define n5 5


int rand_int(int min, int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int* create_array(int size){
    int *A = (int *)calloc(size, sizeof(int));
    return A;
}

int** create_2Darray(int size){
    int **A = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++){
        A[i] = (int *)calloc(size, sizeof(int));
    }
    return A;
}

int** create_xy_array(int size1, int size2){
    int **A = (int **)malloc(size1 * sizeof(int *));
    for(int i = 0; i < size1; i++){
        A[i] = (int *)calloc(size2, sizeof(int));
    }
    return A;
}

void print_array(int* A, int size){
    for (int i = 0; i < size; i++){
        printf("%d ", A[i]);
    }
}

void print_2Darray(int** A, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int** get_matrix(int size, double k){
    int **A = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            A[i][j] = k * rand_int(0, 2);
            if (A[i][j] < 1.0){
                A[i][j] = 0;
            } else {
                A[i][j] = 1;
            }
        }
    }
    return A;
}

int** get_simetric_matrix(int size, double k){
    int **A = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            A[i][j] = k * rand_int(0, 2);
            if (A[i][j] >= 1.0){
                A[i][j] = 1;
                A[j][i] = 1;
            } else {
                A[i][j] = 0;
                A[j][i] = 0;
            }
        }
    }
    return A;
}

int** get_not_oriented_matrix(int**A, int size){
    int **res = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (A[i][j] == A[j][i]){
                res[j][i] = 1;
            }
        }
    }
    return res;
}

int** multiply_matrix(int** A, int** B, int size){
    int **res = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            res[i][j] = 0;
            for (int k = 0; k < size; k++){
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return res;
}

int** sum_matrix(int** A, int** B, int size){
    int **res = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            res[i][j] = A[i][j] + B[i][j];
        }
    }
    return res;
}

int** transpone_matrix(int** A, int size1, int size2){
    int **res = create_xy_array(size2, size1);
    for (int i = 0; i < size1; i++){
        for (int j = 0; j < size2; j++){
            res[i][j] = A[j][i];
        }
    }
    return res;
}

int* get_not_oriented_degree(int** A, int size){
    int *res = create_array(size);
    for (int i = 0; i < size; i++){
        res[i] = 0;
        for (int j = 0; j < size; j++){
            if (A[i][j] != 0){
                res[i]++;
            }
        }
    }
    return res;
}

int** get_oriented_degree(int** A, int size){
    int **res = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++){
        res[i] = create_array(size);
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (A[i][j] != 0){
                res[0][i]++;
            }
            if (A[j][i] != 0){
                res[1][i]++;
            }
        }
    }
    return res;
}

void get_hanged_isolated(int** A, int size){
    int **a = get_oriented_degree(A, size);
    int *hanged = create_array(size), *isolated = create_array(size), h_count = 0, i_count = 0;
    for (int i = 0; i < size; i++){
        if(a[0][i] == a[1][i]){
            if (a[0][i] == 1){
                h_count++;
                hanged[h_count-1] = i;
            } else if (a[0][i] == 0){
                i_count++;
                isolated[i_count-1] = i;
            }
        }
    }
    if (h_count > 0){
        printf("\nHanged: ");
        print_array(hanged, h_count);
    } else {
        printf("\nThere's no hanged");
    }
    if (i_count > 0){
        printf("\nIsolated: ");
        print_array(isolated, i_count);
    } else {
        printf("\nThere's no isolated");
    }
}

int is_regular(int** A, int size){
    int *a = get_not_oriented_degree(A, size);
    for (int i = 0; i < size-1; i++){
        if(a[i] != a[i+1]){
            printf("\nThe graph is irregular");
            return -1;
        }
    }
    printf("\nThe graph is regular, degree of it: %d", a[0]);
    return a[0];
}

int** accessibility(int** A, int size){
    int **res = create_2Darray(size);
    int **tmp = create_2Darray(size);
    res = sum_matrix(res, A, size);
    for (int i = 0; i < size-2; i++){
        tmp = multiply_matrix(res, A, size);
        res = sum_matrix(res, tmp, size);
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (res[i][j] != 0){
                res[i][j] = 1;
            }
        }
    }
    return res;
}

int** get_strong_connection(int** A, int size){
    int **tmp = accessibility(A, size);
    int **res = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            res[i][j] = tmp[i][j] * tmp[j][i];
        }
    }
    return res;
}

int** get_edge_matrix(int** A, int size){
    int **res = create_xy_array(size, 1);
    printf("created res\n");
    for (int i = 0; i < size; i++){
        int tmp = 1;
        printf("created res[%d]\n", i);
        for (int j = 0; j < size; j++){
            if ((i != j) && (A[i][j] == 1)){
                tmp++;
                res[i][0] = tmp-1;
                realloc(res[i], tmp);
                res[i][tmp-1] = j;
            }
        }
        for(int k = 0; k < tmp; k++){
            printf("%d ", res[i][k]);
        }
        printf("\n");
    }
    return res;
}