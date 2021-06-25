#include <stdio.h>
#include <stdlib.h>

struct node {
    int vertex;
    struct node* next;
};

struct node* createNode(int v);

struct Graph {
    int numVertices;
    int* visited;
    struct node** adjLists;
};

int c = 0;
// dfs algo
int** dfs(struct Graph* graph, int vertex) {
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
            dfs(graph, connectedVertex);
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
