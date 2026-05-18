import java.util.Scanner;

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
class P11_SubsetSum {
    static void subset(int[] arr, int index, int sum, String result) {
        // If subset found
        if (sum == 0) {
            System.out.println("Subset: " + result);
            return;
        }

        // Stop condition
        if (index == arr.length || sum < 0) {
            return;
        }

        // Include current element
        subset(arr, index + 1, sum - arr[index], result + arr[index] + " ");

        // Exclude current element
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
        subset(arr, 0, sum, "");

        sc.close();
    }
}
