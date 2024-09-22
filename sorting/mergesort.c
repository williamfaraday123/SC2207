/* 
Mergesort is based on Divide and Conquer
1. Divide: Divide the list or array recursively into two halves until it can no more be divided.
2. Merge: The sorted subarrays are merged back together in sorted order. The process continues until all elements from both subarrays have been merged.
 */

//In-place merge
void merge(int arr[], int start, int end) {
    int mid = (start + end) / 2;
    int leftArrayIndex = start;
    int rightArrayIndex = mid + 1;

    while(leftArrayIndex <= mid && rightArrayIndex <= end){

        //compare element in left array and element in right array
        if(arr[leftArrayIndex] <= arr[rightArrayIndex]){
            //move to next element in left array
            leftArrayIndex++;
        }else{

            //save the current right array element
            int rightArrayElement = arr[rightArrayIndex];

            //shift all elements after the left array element (included) and before the right array element to the right
            for(int i=rightArrayIndex; i>leftArrayIndex; i--){
                arr[i] = arr[i-1];
            }

            //insert the saved right array element at the leftArrayIndex
            //increment left array index so that left array index will point to the current left array element instead of the inserted right element
            arr[leftArrayIndex++] = rightArrayElement;

            //increase the ending point of the left array
            mid++;

            //move to next element in right array
            rightArrayIndex++;
        }
    }
}


/*
Time complexity:
- The outer while loop runs while there are elements in both the left and right halves, and each time, either the left or right index is incremented. This means that, in the worst case, it iterates over all the elements between start and end, giving a total of O(n) iterations where n = end - start + 1.
- Inside the else condition, there's a for loop that shifts elements when the right half element is smaller than the left half element. This loop runs a number of times proportional to the number of shifts needed, which in the worst case could be O(n) times in total across the whole merge. Thus, the worst-case time complexity of this shifting operation is O(n).
- Hence, the worst-case time complexity is O(n^2)
Space complexity:
- no additional arrays are used in merge in-place
- Space complexity is O(1)
 */

//Merge with temporary subarrays
void merge(int arr[], int start, int end) {
    int mid = (start + end) / 2;

    int leftArraySize = mid - start + 1, rightArraySize = end - mid;

    //create temporary subarrays
    int* leftArray = malloc(leftArraySize * sizeof(int));
    int* rightArray = malloc(rightArraySize * sizeof(int));
    
    //copy data to temporary subarrays
    for (int i = 0; i < leftArraySize; i++) {
        leftArray[i] = arr[start + i];
    }
    for (int i = 0; i < rightArraySize; i++) {
        rightArray[i] = arr[mid + 1 + i];
    }

    //merge the subarrays back into arr
    int leftArrayIndex = 0, rightArrayIndex = 0, i = 0;

    while (leftArrayIndex < leftArraySize && rightArrayIndex < rightArraySize) {
        if (leftArray[leftArrayIndex] <= rightArray[rightArrayIndex]) {
            arr[i++] = leftArray[leftArrayIndex++];
        } else {
            arr[i++] = rightArray[rightArrayIndex++];
        }
    }

    //copy the remaining elements of the subarrays
    while (leftArrayIndex < leftArraySize) {
        arr[i++] = leftArray[leftArrayIndex++];
    }

    while (rightArrayIndex < rightArraySize) {
        arr[i++] = rightArray[rightArrayIndex++];
    }

    free(leftArray);
    free(rightArray);
}

/* 
Time complexity:
- The algorithm first compares elements in both subarrays, with each comparison taking constant time. The number of comparisons is bounded by the total number of elements in the two subarrays, which is n = leftArrSize + rightArrSize. Hence, the comparison step takes O(n) time.
- After one of the arrays is exhausted, the remaining elements from the other array are copied over. This takes linear time in the size of the remaining elements, which is at most O(n).
- Thus, the time complexity of this merge is O(n).
Space complexity:
- The algorithm uses two temporary arrays, leftArr and rightArr, each of size equal to their respective halves. In the worst case, these arrays combined will have a size of n = leftArrSize + rightArrSize. Thus, the extra space required is proportional to the size of the input array.
- Hence, the space complexity is O(n) due to the additional memory required for the temporary arrays.
 */

void mergesort(int arr[], int start, int end) {
    if (start >= end) {
        return;
    }

    //divide the array to 2 halves, recursive call on each half to divide further
    int mid = (start + end) / 2;
    mergesort(arr, start, mid); //recursive call on left half of array
    mergesort(arr, mid + 1, end); //recursive call on right half of array
    merge(arr, start, end);
}

/* 
if in-place merge is used:

total time taken T(n) = O(1) if n = 1
                      = 2 * T(n / 2) + O(n^2) if n > 1
- T(n) Represents the total time time taken by the algorithm to sort an array of size n.
- 2T(n/2) represents time taken by the algorithm to recursively sort the two halves of the array. Since each half has n/2 elements, we have two recursive calls with input size as (n/2).
- O(n^2) represents the time taken to merge the two sorted halves (if in-place merge is used)

Time complexity = O(n^2 * log n)
Space complexity = O(1)


if merge with temporary subarrays is used:

total time taken T(n) = O(1) if n = 1
                      = 2 * T(n / 2) + O(n) if n > 1
- T(n) Represents the total time time taken by the algorithm to sort an array of size n.
- 2T(n/2) represents time taken by the algorithm to recursively sort the two halves of the array. Since each half has n/2 elements, we have two recursive calls with input size as (n/2).
- O(n) represents the time taken to merge the two sorted halves (if merge with temporary subarrays is used)

Time complexity = O(n log n)
Space complexity = O(n)
 */