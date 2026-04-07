import java.util.*;
class QuickSort {

    static void quickSort(int[] a, int left, int right) {
        if (left < right) {
            int i = left;
            int j = right + 1;
            int pivot = a[left]; // Choosing the first element as the pivot

            do {
                // Increment i until an element >= pivot is found
                do {
                    i++;
                } while (a[i] < pivot);

                // Decrement j until an element <= pivot is found
                do {
                    j--;
                } while (a[j] > pivot);

                // If pointers haven't crossed, swap elements at i and j
                if (i < j) {
                    swap(a, i, j);
                }
            } while (i < j);

            // Swap the pivot (at index 'left') with the element at index 'j'
            swap(a, left, j);

            // Recursively sort the sub-arrays
            quickSort(a, left, j - 1);
            quickSort(a, j + 1, right);
        }
    }

    // Helper method to swap elements in the array
    static void swap(int[] a, int i, int j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        // Array from your handwritten example
        System.out.println("Enter the no. of elements:");
        int n = sc.nextInt();
        int[] data = new int[n];

        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            data[i] = sc.nextInt();
        }

        System.out.println("Original Array:");
        printArray(data);

        quickSort(data, 0, data.length - 1);

        System.out.println("\nSorted Array:");
        printArray(data);
    }

    private static void printArray(int[] arr) {
        for (int value : arr) {
            System.out.print(value + " ");
        }
        System.out.println();
    }
}