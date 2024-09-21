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
}

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