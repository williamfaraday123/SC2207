/* 
1) Sort edges in ascending order of their weight
2) Pick the smallest edge.
   Check if it forms a cycle with the spanning tree formed so far.
   If cycle is not formed, include this edge in MST. 
   Else, discard it
3) Repeat step 2 until there are V-1 edges in MST
 */

#include <vector>
using namespace std;

//QuickUnion data structure used for cycle detection
class QuickUnion {

public:
    int* id; //id[v] = parent node of vertex v in quickunion tree
    int* size; //size[v] = size of quickunion tree rooted at vertex v

    QuickUnion(int numVertices) {
        id = malloc(numVertices * sizeof(int));
        size = malloc(numVertices * sizeof(int));
        for(int i = 0; i < numVertices; i++) {
            id[i] = i; //initialise id of i = i since i has no parent
            size[i] = 1; //each vertex starts as a single node tree
        }
    }

    //find root of tree containing i in quickunion tree
    int find(int i) {
        while (id[i] != i) {
            id[i] = id[id[i]]; //path compression
            i = id[i];
        }
        return i;
    }

    //connect p and q in quickunion tree by connecting root of p to root of q or vice versa
    void unite(int p, int q) {
        //weighted quickunion to avoid tall trees
        //keep track of size of each tree using size[] array
        //balance by linking root of smaller tree to root of larger tree
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) { //already connected
            return;
        }
        if (size[pRoot] < size[qRoot]) {
            id[pRoot] = qRoot;
        } else if (size[qRoot] < size[pRoot]) {
            id[qRoot] = pRoot;
        } else {
            id[qRoot] = pRoot;

            //since size[pRoot] == size[qRoot], size[pRoot] would be incremented by 1, with pRoot is linked to qRoot
            size[pRoot] += 1;
        }
    }

    //check if nodes p and q are connected (if both nodes have the same root in quickunion tree)
    bool connected(int p, int q) {
        return find(p) == find(q);
    }
};

//minHeap used for selecting the shortest edge efficiently
class minHeap {
public:
    vector<vector<int>> arr;
    int size;

    minHeap(): size(0) {}

    void swap(vector<int>& e1, vector<int>& e2) {
        vector<int> temp = e1;
        e1 = e2;
        e2 = temp;
    }

    void heapifyUp(int e) {
        while (e > 0 && arr[e][2] < arr[(e - 1) / 2][2]) {
            swap(arr[e], arr[(e - 1) / 2]);
            e = (e - 1) / 2;
        }
    }

    void heapifyDown(int root) {
        int smallest = root;
        int leftChildIndex = 2 * root + 1;
        int rightChildIndex = 2 * root + 2;

        if (leftChildIndex < size && arr[leftChildIndex][2] < arr[smallest][2]) {
            smallest = leftChildIndex;
        }
        if (rightChildIndex < size && arr[rightChildIndex][2] < arr[smallest][2]) {
            smallest = rightChildIndex;
        }

        if (smallest != root) {
            swap(arr[root], arr[smallest]);
            heapifyDown(smallest);
        }
    }

    vector<int> heapDeleteRoot() {
        vector<int> root = arr[0];
        swap(arr[0], arr[size - 1]); // swap root with last element
        size--;
        heapifyDown(0);
        return root;
    }
};

//KruskalsMST using minHeap
class KruskalsMST {
public:
    vector<vector<int>> kruskals(int** graph, int V) {

        //use min heap to store edgelist, where edge with min length will be root of heap
        minHeap edgeList;

        vector<vector<int>> mst;

        //insert all edges to minHeap O(E log E)
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (graph[i][j]) {
                    edgeList.arr.push_back({ i, j, graph[i][j] });
                    edgeList.size++;
                    edgeList.heapifyUp(edgeList.size - 1);
                }
            }
        }

        QuickUnion quickUnion(V); //O(V)
        while (edgeList.size > 0 && mst.size() < V - 1) {
            //pick the shortest edge
            vector<int> shortestEdge = edgeList.heapDeleteRoot(); //O(E log E)
            int v1 = shortestEdge[0];
            int v2 = shortestEdge[1];
            if (!quickUnion.connected(v1, v2)) { //check if shortestEdge forms a cycle with mst O(E log V)
                //if no cycle, add edge to mst and unite the 2 vertices v1 and v2 in quickUnion
                quickUnion.unite(v1, v2); //O(V log V)
                mst.push_back(shortestEdge); //O(V)
            }
        }

        return mst;
    }
};

/* 
Time complexity: O(E log E)
- sorting of edges takes O(E log E) time
- After sorting we iterate through all edges and apply the find-union algorithm. The find and union operations can take O(log V) time. So this process takes O(E log V) time
- overall time complexity = O(E log E + E log V) = O(E log E)

Space complexity: O(V + E)
- size of mst = V - 1 => O(V)
- size of heap = E => O(E)
- size of quickUnion tree = V nodes => O(V)
 */