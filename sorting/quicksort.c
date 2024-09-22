/* 
Quicksort is based on Divide and Conquer
There are mainly three steps in the algorithm.
1. Choose a pivot
2. Partition the array around pivot. After partition, it is ensured that all elements are smaller than all right and we get index of the end point of smaller elements. The left and right may not be sorted individually.
3. Recursively call for the two partitioned left and right subarrays.
4. We stop recursion when there is only one element is left.
 */

int swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int start, int end) {
    int pivot = start; //choose the pivot as the start element
    int lastSmall = start;

    //Move all elements smaller than arr[pivot] to the left side with index <= lastSmall
    //elements from start + 1 to lastSmall (inclusive) are smaller than pivot after every iteration
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] < arr[pivot]) {
            swap(&arr[++lastSmall], &arr[i]);
        }
    }

    //swap pivot with lastSmall, so that pivot element will be at index = lastSmall and all elements before lastSmall are smaller than pivot
    swap(&arr[lastSmall], &arr[pivot]);
    return lastSmall;
}

void quicksort(int arr[], int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);

        //recursive call on the 2 partitioned subarrays
        quicksort(arr, start, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }
}

/* 
Time complexity:
- Best Case : Ω (N log (N))
The best-case scenario for quicksort occur when the pivot chosen at the each step divides the array into roughly equal halves.
In this case, the algorithm will make balanced partitions, leading to efficient Sorting.
- Average Case: θ ( N log (N))
Quicksort’s average-case performance is usually very good in practice, making it one of the fastest sorting Algorithm.
- Worst Case: O(N ^ 2)
The worst-case Scenario for Quicksort occur when the pivot at each step consistently results in highly unbalanced partitions. When the array is already sorted and the pivot is always chosen as the smallest or largest element. To mitigate the worst-case Scenario, various techniques are used such as choosing a good pivot (e.g., median of three) and using Randomized algorithm (Randomized Quicksort ) to shuffle the element before sorting.
Space complexity:
- O(1), if we don’t consider the recursive stack space. If we consider the recursive stack space then, in the worst case quicksort could make O ( N ).
 */