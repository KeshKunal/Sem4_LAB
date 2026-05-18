import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Number of marks and the marks array
Process: Split array, sort each half, merge
Algorithm Used: Merge Sort
Technique: Divide and Conquer
Output: Sorted marks in ascending order
Key Idea: Merge two sorted halves
*/
class P1_MergeSort {
    static void merge(int[] arr, int left, int mid, int right) {
        int i = left;       // Pointer for left half
        int j = mid + 1;    // Pointer for right half
        int k = 0;          // Pointer for temp array
        int[] temp = new int[right - left + 1]; // Temp array

        // Compare and copy smaller values
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        // Copy remaining elements from left half
        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        // Copy remaining elements from right half
        while (j <= right) {
            temp[k++] = arr[j++];
        }

        // Copy temp back to original array
        for (int t = 0; t < temp.length; t++) {
            arr[left + t] = temp[t];
        }
    }

    static void mergeSort(int[] arr, int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2; // Find middle
            mergeSort(arr, left, mid);    // Sort left half
            mergeSort(arr, mid + 1, right); // Sort right half
            merge(arr, left, mid, right); // Merge halves
        }
    }

    static void printArray(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            if (i < arr.length - 1) {
                System.out.print(" ");
            }
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of marks: ");
        int n = sc.nextInt();
        int[] marks = new int[n];

        System.out.println("Enter the marks:");
        for (int i = 0; i < n; i++) {
            marks[i] = sc.nextInt();
        }

        System.out.print("Marks (given): ");
        printArray(marks);

        mergeSort(marks, 0, marks.length - 1); // Sort the marks

        System.out.print("Sorted marks: ");
        printArray(marks);

        sc.close();
    }
}
