#include <limits.h>

#define V 9

int findMinDistanceUnvisitedNode(int dist[V], bool visited[V]) {
    int min = INT_MAX, minIndex = -1;
    for(int v = 0; v < V; v++){
        if(!visited[v] && dist[v] < min){
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(int graph[V][V], int src) {

    //array to store distance of each vertex from src vertex
    int* dist = malloc(V*sizeof(int));

    //array to store whether each vertex is already included in shortest path tree
    bool* visited = malloc(V*sizeof(bool));

    //array to store predecessor of each vertex
    int* predecessor = malloc(V*sizeof(int));

    //initialisation
    for(int i = 0; i < V; i++){
        dist[i] = INT_MAX; visited[i] = false; predecessor[i] = -1;
    }

    //set values for src vertex
    dist[src] = 0;

    for(int i = 0; i < V - 1; i++){
        int u = findMinDistanceUnvisitedNode(dist, visited);

        //mark the current vertex as visited
        visited[u] = true;

        //find distances of neighbouring vertices
        for(int v = 0; v < V; v++){
            //update dist value of v only if there is an edge from u to v,
            //unvisited,
            //and total weight of path from src to v through u < current distance from src to v
            if(graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                predecessor[v] = u;
            }
        }
    }
}

/*
Complexity Analysis
Time Complexity: The time complexity of Dijkstra’s algorithm is O(V^2).
This is because the algorithm uses two nested loops to traverse the graph and find the shortest path from the source node to all other nodes.

Space Complexity: The space complexity of Dijkstra’s algorithm is O(V).
This is because the algorithm uses an array of size V to store the distances from the source node to all other nodes.
*/