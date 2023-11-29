#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <queue.c>

#define MAX_VERTICES 100

// Graph structure
typedef struct {
    int vertices;
    int edges;
    int matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Queue structure for BFS
typedef struct {
    int *array;
    int front;
    int rear;
    int size;
} Queue;

// Function to initialize a graph
Graph* initGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->edges = 0;

    // Initialize matrix with zeros (no edges initially)
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            graph->matrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int from, int to) {
    if (from >= 0 && from < graph->vertices && to >= 0 && to < graph->vertices) {
        graph->matrix[from][to] = 1;
        graph->edges++;
    } else {
        printf("Invalid edge: (%d, %d)\n", from, to);
    }
}

// Function to print the adjacency matrix
void printMatrix(Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; ++i) {
        for (int j = 0; j < graph->vertices; ++j) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to initialize a queue for BFS
Queue* initQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->array = (int*)malloc(sizeof(int) * size);
    queue->front = queue->rear = -1;
    queue->size = size;
    return queue;
}

//
