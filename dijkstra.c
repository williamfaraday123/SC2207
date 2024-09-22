#include <limits.h>
#include <stdbool.h>

#define V 9


//Dijkstra with Linear Search
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
Time Complexity: O(V^2)
Iteratively search for the unvisited node with the smallest distance using a loop (findMinDistanceUnvisitedNode) takes O(V) time
Outer for loop takes O(V) time

Space Complexity: O(V)
You store the distance array, visited array, and predecessor array, each of which takes O(V) space.
*/







//Dijkstra with min Heap
struct vertex {
    int vertexNum; //vertex 1 has vertexNum = 1
    int dist; //distance of each vertex from src vertex
    int predecessor; //predecessor of each vertex
};
void swap(struct vertex* v1, struct vertex* v2) {
    struct vertex temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}
void heapifyDown(struct vertex* minHeap, int heapSize, int root) {
    int smallest = root;
    int leftChildIndex = 2 * root + 1;
    int rightChildIndex = 2 * root + 2;
    if (leftChildIndex < heapSize && minHeap[leftChildIndex].dist < minHeap[smallest].dist) {
        smallest = leftChildIndex;
    }
    if (rightChildIndex < heapSize && minHeap[rightChildIndex].dist < minHeap[smallest].dist) {
        smallest = rightChildIndex;
    }

    if (smallest != root) {
        swap(&minHeap[root], &minHeap[smallest]);
        heapifyDown(minHeap, heapSize, smallest);
    }
}
void heapifyUp(struct vertex* minHeap, int heapSize, int v)  {
    int i = v;
    while (i > 0 && minHeap[(i - 1) / 2].dist > minHeap[i].dist) {
        swap(&minHeap[(i - 1) / 2], &minHeap[i]);
        i = (i - 1) / 2;
    }
}
void heapDeleteRoot(struct vertex* minHeap, int* heapSize) {
    swap(&minHeap[0], &minHeap[*heapSize - 1]);
    (*heapSize)--;
    heapifyDown(minHeap, *heapSize, 0);
}

void dijkstra(int graph[V][V], int src) {

    struct vertex* minHeap = malloc(V* sizeof(struct vertex));

    //initialisation
    for (int i = 0; i < V; i++) {
        minHeap[i].vertexNum = i;
        minHeap[i].dist = INT_MAX;
        minHeap[i].predecessor = -1;
    }

    //set values for src vertex
    minHeap[src].dist = 0;

    //src vertex has min dist, so insert src vertex at root of minHeap
    //other vertices have dist = INT_MAX
    swap(&minHeap[src], &minHeap[0]);

    int heapSize = V;
    while (heapSize > 0) {

        //root of minHeap is unvisited vertex with min distance
        struct vertex u = minHeap[0]; //extracting the root: O(1)

        //visit u, delete from heap
        heapDeleteRoot(minHeap, &heapSize); //last element in heap is moved to root position, followed by heapifyDown() starting from the root: O(log V) since height of heap is proportional to log V

        //find distances of unvisited neighbouring vertices
        for (int v = 0; v < heapSize; v++) {

            //if edge exists between u and v
            //v is unvisited (still in heap)
            //and total weight of path from src to v through u < current distance from src to v
            if (graph[u.vertexNum][minHeap[v].vertexNum] && u.dist + graph[u.vertexNum][minHeap[v].vertexNum] < minHeap[v].dist) {
                minHeap[v].dist = u.dist + graph[u.vertexNum][minHeap[v].vertexNum];
                minHeap[v].predecessor = u.vertexNum;

                //fix heap according to updated distance of vertex v
                //heapifyUp: check if vertex v is still smaller than children, then recursively check its parent
                heapifyUp(minHeap, heapSize, v); //O(log V)
            }
        }
    }
}

/* 
Time complexity: O((V + E) log V)
- Each vertex is extracted from the heap once, and extracting a node and heapifying down take O(log V).
- Each edge's distance is potentially updated, and for each update, a heapify up is done, taking O(log V).
Therefore, the overall time complexity of Dijkstra's algorithm using a min-heap is:
O((V + E) log V), where:
- V is the number of vertices.
- E is the number of edges.

Space complexity: O(V)
You also use a min-heap to keep track of the nodes, which takes O(V) space for all nodes.
 */