#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Function prototypes
void addEdge(int graph[MAX_VERTICES][MAX_VERTICES], int vertex1, int vertex2);
void printAdjacencyMatrix(int graph[MAX_VERTICES][MAX_VERTICES], int vertices);
void dfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertex, int visited[MAX_VERTICES], int vertices);

int main() {
    int vertices, edges;
    
    // Input the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    int graph[MAX_VERTICES][MAX_VERTICES] = {0}; // Initializing the adjacency matrix with zeros
    int visited[MAX_VERTICES] = {0}; // Array to track visited vertices

    // Input the edges
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (vertex1 vertex2):\n");
    for (int i = 0; i < edges; ++i) {
        int vertex1, vertex2;
        scanf("%d %d", &vertex1, &vertex2);
        addEdge(graph, vertex1, vertex2);
    }

    // Print the adjacency matrix
    printf("\nAdjacency Matrix:\n");
    printAdjacencyMatrix(graph, vertices);

    // Perform DFS
    printf("\nDFS starting from vertex 0:\n");
    dfs(graph, 0, visited, vertices);

    return 0;
}

// Function to add an edge to the graph
void addEdge(int graph[MAX_VERTICES][MAX_VERTICES], int vertex1, int vertex2) {
    // Assuming an undirected graph
    graph[vertex1][vertex2] = 1;
    graph[vertex2][vertex1] = 1;
}

// Function to print the adjacency matrix
void printAdjacencyMatrix(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Function to perform Depth-First Search
void dfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertex, int visited[MAX_VERTICES], int vertices) {
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (int i = 0; i < vertices; ++i) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            dfs(graph, i, visited, vertices);
        }
    }
}
