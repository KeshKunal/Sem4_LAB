/*
MEMORY MAP
----------

Input: Number of parcels and their weights
Process: Partition using Hoare scheme, then quick sort both parts
Algorithm Used: Quick Sort (Hoare Partition)
Technique: Divide and Conquer
Output: Sorted parcel weights and execution time
Key Idea: Use two pointers that move inward around a pivot

PSEUDO CODE
-----------
QUICKSORT(arr, low, high):
    IF low < high THEN
        p = HOARE_PARTITION(arr, low, high)
        QUICKSORT(arr, low, p)
        QUICKSORT(arr, p + 1, high)

HOARE_PARTITION(arr, low, high):
    pivot = arr[low]
    i = low - 1
    j = high + 1
    WHILE TRUE DO
        DO i = i + 1 WHILE arr[i] < pivot
        DO j = j - 1 WHILE arr[j] > pivot
        IF i >= j THEN RETURN j
        SWAP(arr[i], arr[j])
*/

import java.util.Scanner;
class P1_QuickSortHoare {
    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static int hoarePartition(int[] arr, int low, int high) {
        int pivot = arr[low]; // Choose first element as pivot
        int i = low - 1;      // Left pointer (starts before range)
        int j = high + 1;     // Right pointer

        while (true) {
            // Move i to the right until element >= pivot
            do {
                i++;
            } while (arr[i] < pivot);

            // Move j to the left until element <= pivot
            do {
                j--;
            } while (arr[j] > pivot);

            // If pointers cross, return partition index
            if (i >= j) {
                return j;
            }

            // Swap out-of-place elements
            swap(arr, i, j);
        }
    }

    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int p = hoarePartition(arr, low, high); // Partition index
            quickSort(arr, low, p);                 // Sort left part
            quickSort(arr, p + 1, high);            // Sort right part
        }
    }

    static void printArray(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of parcels: ");
        int n = sc.nextInt();
        int[] weights = new int[n];

        System.out.println("Enter parcel weights:");
        for (int i = 0; i < n; i++) {
            weights[i] = sc.nextInt();
        }

        System.out.print("Before sorting: ");
        printArray(weights);

        long start = System.nanoTime();
        quickSort(weights, 0, weights.length - 1);
        long end = System.nanoTime();

        System.out.print("After sorting: ");
        printArray(weights);
        System.out.println("Execution time (ns): " + (end - start));

        sc.close();
    }
}
