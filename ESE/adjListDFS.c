#include<stdio.h>
#include<stdlib.h>

// Node structure to represent a node in the adjacency list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Graph structure with an array of adjacency lists
typedef struct Graph {
    int vertices;
    Node** adjList;
} Graph;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    
    // Create an array of adjacency lists, one for each vertex
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; ++i)
        graph->adjList[i] = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Depth-First Search (DFS) function
void DFS(Graph* graph, int vertex, int* visited) {
    // Mark the current vertex as visited
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Traverse all adjacent vertices
    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->data;
        if (!visited[adjVertex]) {
            // Recursive call for unvisited adjacent vertex
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

int main() {
    // Example: Representing a graph and performing DFS
    int vertices = 5;
    Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);

    printf("Depth-First Traversal (Starting from vertex 0):\n");
    
    // Array to keep track of visited vertices
    int* visited = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; ++i)
        visited[i] = 0;

    // Perform DFS starting from vertex 0
    DFS(graph, 0, visited);

    // Free allocated memory
    free(visited);
    free(graph->adjList);
    free(graph);

    return 0;
}
