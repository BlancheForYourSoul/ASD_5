// DFS algorithm in C

#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

struct node {
    int vertex;
    struct node* next;
};

struct node* createNode(int v);

struct Graph {
    int numVertices;
    int* visited;

    // We need int** to store a two dimensional array.
    // Similary, we need struct node** to store an array of Linked lists
    struct node** adjLists;
};

// DFS algo
int** DFS(struct Graph* graph, int vertex) {
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;

    int **routes = create_xy_array(2, 1000);
    int size = 1;

    graph->visited[vertex] = 1;
    printf("\nVisited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        routes[0][0]++;
        routes[1][0]++;
        routes[0][size] = vertex;
        routes[1][size] = connectedVertex;
        printf("%d->%d\n", vertex, connectedVertex);
        size++;


        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
    return routes;
}

// Create a node
struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

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
    int **Routes = DFS(graph, 0);

    return 0;
}