// Implement BFS & DFS traversal for graphs.
// You need to make use of an adjacency matrix for representing the graph
// The structure below should allow you to handle both directed and undirected graphs.
// For traversals, the respective function should accept starting node for traversal and perform traversal (BFS/ DFS).

#include "queue.c"

GraphRep *init_graph(int num_vertices, bool is_directed) {
    GraphRep *graph = (GraphRep *)malloc(sizeof(GraphRep));
    if (!graph) {
        printf("Memory allocation failed for graph.\n");
        exit(EXIT_FAILURE);
    }

    graph->nV = num_vertices;
    graph->nE = 0;
    graph->is_directed = is_directed;
    graph->type = BFS; // Initialize the traversal type (you can change it as needed)
    graph->source = -1; // Initialize the source

    // Initialize the adjacency matrix and other arrays
    graph->edges = (bool **)malloc(num_vertices * sizeof(bool *));
    graph->predecessor = (Vertex *)malloc(num_vertices * sizeof(Vertex));
    graph->color = (Color *)malloc(num_vertices * sizeof(Color));
    graph->distance = (int *)malloc(num_vertices * sizeof(int));
    graph->finish = (int *)malloc(num_vertices * sizeof(int));

    if (!graph->edges || !graph->predecessor || !graph->color || !graph->distance || !graph->finish) {
        printf("Memory allocation failed for graph arrays.\n");
        exit(EXIT_FAILURE);
    }

    for (Vertex i = 0; i < num_vertices; i++) {
        graph->edges[i] = (bool *)malloc(num_vertices * sizeof(bool));
        if (!graph->edges[i]) {
            printf("Memory allocation failed for edges array.\n");
            exit(EXIT_FAILURE);
        }
        for (Vertex j = 0; j < num_vertices; j++) {
            graph->edges[i][j] = false; // Initialize edges to false
        }

        graph->predecessor[i] = -1; // Initialize predecessor to -1
        graph->color[i] = WHITE; // Initialize color to WHITE
        graph->distance[i] = -1; // Initialize distance to -1
        graph->finish[i] = -1; // Initialize finish to -1
    }

    return graph;
}

void insert_edge(GraphRep *graph, Edge e) {
    if (e.u < 0 || e.u >= graph->nV || e.v < 0 || e.v >= graph->nV) {
        printf("Invalid edge vertices.\n");
        return;
    }

    graph->edges[e.u][e.v] = true;
    if (!graph->is_directed) {
        // If it's an undirected graph, add the reverse edge
        graph->edges[e.v][e.u] = true;
    }

    graph->nE++;
}


void remove_edge(GraphRep *graph, Edge e) {
    if (e.u < 0 || e.u >= graph->nV || e.v < 0 || e.v >= graph->nV) {
        printf("Invalid edge vertices.\n");
        return;
    }

    graph->edges[e.u][e.v] = false;
    if (!graph->is_directed) {
        // If it's an undirected graph, remove the reverse edge
        graph->edges[e.v][e.u] = false;
    }

    graph->nE--;
}


// NOTE: During both DFS and BFS traversals, when at a vertex that is connected with multiple vertices, always pick the connecting vertex which has the lowest value first
// Both traversals will always update the following attributes of the Graph:
// 1. source -> stores the value of the starting vertex for the traversal
// 2. type -> stores the traversal type (BFS or DFS)
// 3. color --> indicates if all vertices have been visited or not. Post traversal, all vertices should be BLACK
// 4. predecessor --> this array would hold the predecessor for a given vertex (indicated by the array index). 

// NOTE: BFS Traversal should additionally update the following in the graph:
// 1. distance --> this array would hold the number of hops it takes to reach a given vertex (indicated by the array index) from the source. 

void traverse_bfs(GraphRep *graph, Vertex source) {
    // Initialize the queue for BFS
    Queue *queue = initialize_queue(graph->nV);

    graph->source = source;
    graph->type = BFS;

    // Initialize distances and colors
    for (Vertex v = 0; v < graph->nV; v++) {
        graph->color[v] = WHITE;
        graph->distance[v] = -1;
    }

    // Start BFS from the source
    graph->color[source] = GRAY;
    graph->distance[source] = 0;

    enqueue(queue, source);

    while (!isEmpty(queue)) {
        Vertex u = dequeue(queue);

        for (Vertex v = 0; v < graph->nV; v++) {
            if (graph->edges[u][v] && graph->color[v] == WHITE) {
                graph->color[v] = GRAY;
                graph->distance[v] = graph->distance[u] + 1;
                graph->predecessor[v] = u;
                enqueue(queue, v);
            }
        }

        graph->color[u] = BLACK;
    }

    // Cleanup
    free(queue);
}


// NOTE: DFS Traversal should additionally update the following in the graph:
// 1. distance --> Assuming 1 hop to equal 1 time unit, this array would hold the time of discovery a given vertex (indicated by the array index) from the source. 
// 2. finish --> Assuming 1 hop to equal 1 time unit, this array would hold the time at which exploration concludes for a given vertex (indicated by the array index). 
void dfs_visit(GraphRep *graph, Vertex u, int *time) {
    graph->color[u] = GRAY;
    graph->distance[u] = ++(*time);

    for (Vertex v = 0; v < graph->nV; v++) {
        if (graph->edges[u][v] && graph->color[v] == WHITE) {
            graph->predecessor[v] = u;
            dfs_visit(graph, v, time);
        }
    }

    graph->color[u] = BLACK;
    graph->finish[u] = ++(*time);
}

void traverse_dfs(GraphRep *graph, Vertex source) {
    graph->source = source;
    graph->type = DFS;

    int time = 0;

    // Initialize distances and colors
    for (Vertex v = 0; v < graph->nV; v++) {
        graph->color[v] = WHITE;
        graph->distance[v] = -1;
    }

    for (Vertex v = 0; v < graph->nV; v++) {
        if (graph->color[v] == WHITE) {
            dfs_visit(graph, v, &time);
        }
    }
}

// displays the path from the current 'source' in graph to the provided 'destination'. 
// The graph holds the value of the traversal type, so the function should let the caller know what kind of traversal was done on the graph and from which vertex, along with the path.
void display_path(GraphRep *graph, Vertex destination) {
    if (graph->type == BFS) {
        printf("Breadth-First Search from vertex %d to vertex %d:\n", graph->source, destination);
    } else if (graph->type == DFS) {
        printf("Depth-First Search from vertex %d to vertex %d:\n", graph->source, destination);
    } else {
        printf("Unknown traversal type.\n");
        return;
    }

    printf("Path: ");

    Vertex v = destination;
    while (v != -1) {
        printf("%d ", v);
        v = graph->predecessor[v];
    }

    printf("\n");
}

// display the graph in the matrix form
void display_graph(GraphRep *graph) {
    printf("Adjacency Matrix:\n");
    for (Vertex u = 0; u < graph->nV; u++) {
        for (Vertex v = 0; v < graph->nV; v++) {
            printf("%d ", graph->edges[u][v]);
        }
        printf("\n");
    }
}

// int main() {
//     int num_vertices = 6;
//     GraphRep *graph = init_graph(num_vertices, false); // Create an undirected graph

//     // Insert edges to create a sample graph
//     insert_edge(graph, (Edge){0, 1});
//     insert_edge(graph, (Edge){0, 2});
//     insert_edge(graph, (Edge){1, 3});
//     insert_edge(graph, (Edge){2, 4});
//     insert_edge(graph, (Edge){3, 5});
//     insert_edge(graph, (Edge){4, 5});

//     printf("Graph:\n");
//     display_graph(graph);

//     // Perform BFS traversal from vertex 0
//     traverse_bfs(graph, 0);

//     // Display the path from vertex 0 to vertex 5
//     display_path(graph, 5);

//     // Reset the graph for DFS traversal
//     for (int v = 0; v < num_vertices; v++) {
//         graph->color[v] = WHITE;
//         graph->distance[v] = -1;
//         graph->predecessor[v] = -1;
//         graph->finish[v] = -1;
//     }

//     // Perform DFS traversal from vertex 0
//     traverse_dfs(graph, 0);

//     // Display the path from vertex 0 to vertex 5
//     display_path(graph, 5);

//     // Clean up and free resources
//     free(graph);

//     return 0;
// }
