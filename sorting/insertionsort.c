void insertionSort(int arr[], int start, int end) {
    for (int startOfUnsortedSection = start + 1; startOfUnsortedSection <= end; startOfUnsortedSection++) {
        int current = arr[startOfUnsortedSection];

        //find a slot to insert current element
        //iterate through sorted section
        int j = startOfUnsortedSection - 1;
        while (j >= start && arr[j] > current) {
            //if any element in sorted section is greater than current element, shift it to the right
            arr[j + 1] = arr[j];
            j--;
        }

        //break out of while loop when index j is out of bound || element j <= current element
        //insert current element into the hole j + 1
        arr[j + 1] = current;
    }
}

/* 
Time Complexity:
- Best case: O(n) , If the list is already sorted, where n is the number of elements in the list.
- Average case: O(n^2) , If the list is randomly ordered
- Worst case: O(n^2) , If the list is in reverse order
Space Complexity:
- O(1), in-place sorting algorithm
 */