/* 
Heapsort is based on binary heap data structure.
The heap sort algorithm consists of two phases. 
1. In the first phase, the array is converted into a max heap.
2. In the second phase, the highest element is removed (i.e., the one at the tree root) and the remaining elements are used to create a new max heap
 */

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int N, int i) {
    if (i < N) {
        //find the largest amongst root i, left child 2*i+1, and right child 2*i+2
        int largest = i;
        int leftChildIndex = 2*i + 1;
        int rightChildIndex = 2*i + 2;

        if (leftChildIndex < N && arr[leftChildIndex] > arr[largest]) { //left child
            largest = leftChildIndex;
        }
        if (rightChildIndex < N && arr[rightChildIndex] > largest) { //right child
            largest = rightChildIndex;
        }

        //if root is not largest, swap and continue heapifying
        if (largest != i) {
            swap(&arr[i], &arr[largest]);
            heapify(arr, N, largest);
        }
    }
}
void heapsort(int arr[], int N) {
    //construct max heap
    for (int i = N / 2 - 1; i >= 0; i--) {
        heapify(arr, N, i);
    }

    //loop until heap consists of only 1 element
    for (int lastIndex = N - 1; lastIndex > 0; lastIndex--) {
        //swap root with last element of heap
        swap(&arr[0], &arr[lastIndex]);

        //heapify remaining elements of heap
        //excluding last element which is already the max
        heapify(arr, lastIndex, 0);
    }
}

/*
Complexity Analysis
Time Complexity: The time complexity of Heap Sort is O(n log n).
The log n factor comes from the height of the binary heap, so heapify takes O(log n) time.
No. of times heapify() is calle is proprtional to n due to for loop
*/