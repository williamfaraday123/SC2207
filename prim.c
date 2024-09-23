/* 
1) Initialize keys of all vertices as infinite and 
   parent of every vertex as -1.
2) Create an empty priority_queue pq.  Every item
   of pq is a pair (weight, vertex). Weight (or 
   key) is used  as first item  of pair
   as first item is by default used to compare
   two pairs.
3) Initialize all vertices as not part of MST yet.
   We use boolean array inMST[] for this purpose.
   This array is required to make sure that an already
   considered vertex is not included in pq again. This
   is where Prim's implementation differs from Dijkstra.
   In Dijkstra's algorithm, we didn't need this array as
   distances always increase. We require this array here 
   because key value of a processed vertex may decrease
   if not checked.
4) Insert source vertex into pq and make its key as 0.
5) While either pq doesn't become empty 
    a) Extract minimum key vertex from pq. 
       Let the extracted vertex be u.
    b) Include u in MST using inMST[u] = true.
    c) Loop through all adjacent of u and do 
       following for every vertex v.
           // If weight of edge (u,v) is smaller than
           // key of v and v is not already in MST
           If inMST[v] = false && key[v] > weight(u, v)
               (i) Update key of v, i.e., do
                     key[v] = weight(u, v)
               (ii) Insert v into the pq 
               (iv) parent[v] = u
               
6) Print MST edges using parent array.
 */

#include <limits.h>
#include <stdbool.h>

struct vertex {
   int vertexNum;
   bool inMst; //whether node is already included in minimum spanning tree
   int parent; //predecessor of node
   int weight; //weight of path from parent to node
};
void swap(struct vertex* v1, struct vertex* v2) {
   struct vertex temp = *v1;
   *v1 = *v2;
   *v2 = temp;
}
void heapifyUp(struct vertex* minHeap, int v) {
   while(v > 0 && minHeap[v].weight < minHeap[(v - 1) / 2].weight) {
      swap(&minHeap[v], &minHeap[(v - 1) / 2]);
      v = (v - 1) / 2;
   }
}
void heapifyDown(struct vertex* minHeap, int heapSize, int root) {
   int smallest = root;
   int leftChildIndex = 2 * root + 1;
   int rightChildIndex = 2 * root + 2;

   if (leftChildIndex < heapSize && minHeap[leftChildIndex].weight < minHeap[smallest].weight) {
      smallest = leftChildIndex;
   }
   if (rightChildIndex < heapSize && minHeap[rightChildIndex].weight < minHeap[smallest].weight) {
      smallest = rightChildIndex;
   }

   if (smallest != root) {
      swap(&minHeap[root], &minHeap[smallest]);
      heapifyDown(minHeap, heapSize, smallest);
   }
}
void heapDeleteRoot(struct vertex* minHeap, int* heapSize) {
   swap(minHeap[0], minHeap[*heapSize-1]);
   (*heapSize)--;
   heapifyDown(minHeap, heapSize, 0);
}
void prim(int graph[V][V], int src) {
   struct vertex* minHeap = malloc(V * sizeof(struct vertex));
   
   //initialise all vertices in minHeap
   for (int v = 0; v < V; v++) {
      minHeap[v].vertexNum = v;
      minHeap[v].inMst = false;
      minHeap[v].parent = -1;
      minHeap[v].weight = INT_MAX;
   }

   //initialise values for src vertex
   //distance from src vertex to src vertex = 0
   minHeap[src].weight = 0;

   //place src node at root of minheap as src node has the min weight
   swap(&minHeap[src], &minHeap[0]);

   int heapSize = V;
   while (heapSize > 0) {
      //get min distance node (root of minheap)
      struct vertex u = minHeap[0];

      //add to mst
      minHeap[0].inMst = true;
      heapDeleteRoot(minHeap, &heapSize);

      //check distances of adjacent vertices not in mst
      for (int v = 0; v < heapSize; v++) {
         //if edge exists from u to v,
         //v is not in mst,
         //and edge weight from u to v < edge weight from v's parent to v
         if (graph[u.vertexNum][minHeap[v].vertexNum] && !minHeap[v].inMst && graph[u.vertexNum][minHeap[v].vertexNum] < minHeap[v].weight) {
            //update edge weight to v and change v's parent
            minHeap[v].weight = graph[u.vertexNum][minHeap[v].vertexNum];
            minHeap[v].parent = u.vertexNum;

            //after update, heapifyUp
            heapifyUp(minHeap, v);
         }
      }
   }
}
