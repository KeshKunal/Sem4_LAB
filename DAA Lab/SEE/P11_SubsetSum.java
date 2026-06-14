
/*
MEMORY MAP
----------

Input: Array of numbers and target sum
Process: Include/exclude each element using recursion
Algorithm Used: Subset Sum
Technique: Backtracking
Output: All subsets that match the target sum
Key Idea: Try both choices for each element

PSEUDO CODE
-----------
SUBSET(arr, index, sum, result):
    IF sum == 0 THEN
        PRINT result
        RETURN
    IF index == length(arr) OR sum < 0 THEN
        RETURN
    // Include current element
    SUBSET(arr, index + 1, sum - arr[index], result + arr[index])
    // Exclude current element
    SUBSET(arr, index + 1, sum, result)
*/

import java.util.Scanner;
class P11_SubsetSum {
    // Backtracking: choose to include or exclude each element to reach target sum.
    static void subset(int[] arr, int index, int sum, String result) {
        // Base case: target achieved, print current subset path.
        if (sum == 0) {
            System.out.println("Subset: " + result);
            return;
        }

        // Stop exploring if no elements remain or sum becomes negative.
        if (index == arr.length || sum < 0) {
            return;
        }

        // Include current element and reduce remaining sum.
        subset(arr, index + 1, sum - arr[index], result + arr[index] + " ");

        // Exclude current element and keep sum unchanged.
        subset(arr, index + 1, sum, result);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.print("Enter target sum: ");
        int sum = sc.nextInt();

        System.out.println("Possible Subsets:");
        // Start from index 0 with empty subset.
        subset(arr, 0, sum, "");

        sc.close();
    }
}

/*
Applications:
Partition problems
Target sum problems
Resource allocation
*/

/*
Complexity Analysis (Based on this specific implementation):
------------------------------------------------------------
Time Complexity:
  - Best Case:    O(2^n) (since we need to find all subsets that match the target sum, we explore the subset tree)
  - Average Case: O(2^n)
  - Worst Case:   O(2^n)
Space Complexity:
  - Auxiliary Space: O(n) representing the maximum recursion depth
  - Total Space:     O(n) to store the elements array
*/