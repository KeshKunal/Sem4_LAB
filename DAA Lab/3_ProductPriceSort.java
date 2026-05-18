import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Number of products and price array
Process: Quick sort and measure time
Algorithm Used: Quick Sort
Technique: Divide and Conquer
Output: Sorted prices and execution time
Key Idea: Partition around a pivot
*/
class P3_ProductPriceSort {
    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int p = partition(arr, low, high); // Get pivot index
            quickSort(arr, low, p - 1);        // Sort left part
            quickSort(arr, p + 1, high);       // Sort right part
        }
    }

    static int partition(int[] arr, int low, int high) {
        int pivot = arr[high]; // Choose last element as pivot
        int i = low - 1;       // Index of smaller element

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr, i, j); // Swap smaller element to left side
            }
        }
        swap(arr, i + 1, high); // Place pivot in correct position
        return i + 1;
    }

    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
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

        System.out.print("Enter number of products: ");
        int n = sc.nextInt();
        int[] prices = new int[n];

        System.out.println("Enter product prices:");
        for (int i = 0; i < n; i++) {
            prices[i] = sc.nextInt();
        }

        System.out.print("Original prices: ");
        printArray(prices);

        long start = System.nanoTime(); // Start time
        quickSort(prices, 0, prices.length - 1); // Sort prices
        long end = System.nanoTime(); // End time

        System.out.print("Sorted prices: ");
        printArray(prices);

        System.out.println("Execution time (ns): " + (end - start));

        sc.close();
    }
}
