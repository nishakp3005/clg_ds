#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for an adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent a graph
struct Graph {
    int V;              // Number of vertices
    struct Node** adjList;  // Array of adjacency lists
};

// Function to create a new graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));

    for (int i = 0; i < V; ++i)
        graph->adjList[i] = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform Breadth-First Search on the graph
void BFS(struct Graph* graph, int startVertex) {
    // Create an array to keep track of visited vertices
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; ++i)
        visited[i] = false;

    // Create a queue for BFS
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    // Mark the current vertex as visited and enqueue it
    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("Breadth-First Search starting from vertex %d:\n", startVertex);

    while (front != rear) {
        // Dequeue a vertex and print it
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Explore adjacent vertices
        struct Node* temp = graph->adjList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    printf("\n");

    // Free allocated memory
    free(visited);
    free(queue);
}

// Function to display the adjacency list representation of the graph
void displayGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; ++i) {
        printf("Adjacency list of vertex %d:\n", i);
        struct Node* temp = graph->adjList[i];
        while (temp != NULL) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    // Create a graph with 5 vertices
    struct Graph* graph = createGraph(5);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);

    // Display the adjacency list representation of the graph
    displayGraph(graph);

    // Perform BFS starting from vertex 0
    BFS(graph, 0);

    // Free allocated memory
    free(graph->adjList);
    free(graph);

    return 0;
}
