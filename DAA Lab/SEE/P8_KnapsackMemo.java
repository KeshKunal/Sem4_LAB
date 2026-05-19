import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Number of items, weights, profits, and capacity
Process: Build DP table and backtrack to find selected items
Algorithm Used: 0/1 Knapsack (Memory Function)
Technique: Dynamic Programming
Output: Selected items and optimal profit
Key Idea: Best of include/exclude for each item

PSEUDO CODE
-----------
KNAPSACK(numItems, capacity, weights[], profits[]):
    dpTable[0..numItems][0..capacity] = 0
    FOR item = 1 to numItems DO
        FOR cap = 1 to capacity DO
            IF weights[item] <= cap THEN
                dpTable[item][cap] = MAX(dpTable[item-1][cap],
                    profits[item] + dpTable[item-1][cap - weights[item]])
            ELSE
                dpTable[item][cap] = dpTable[item-1][cap]

    // Backtrack to find selected items
    item = numItems, remainingCap = capacity
    WHILE item > 0 AND remainingCap > 0 DO
        IF dpTable[item][remainingCap] != dpTable[item-1][remainingCap] THEN
            PRINT item is selected
            remainingCap -= weights[item]
        item--
    PRINT dpTable[numItems][capacity] as optimal profit
*/
class P8_KnapsackMemo {

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of objects: ");
        int n = sc.nextInt();

        int w[] = new int[n + 1];
        int p[] = new int[n + 1];
        // FIXED: Start i at 1 so w[1] matches the first item in the DP table v[1][j]
        for (int i = 1; i <= n; i++) {
            System.out.print("Enter weight and profit for Item " + i + ": ");
            w[i] = sc.nextInt();
            p[i] = sc.nextInt();
        }

        System.out.print("Enter capacity: ");
        int m = sc.nextInt();
        int v[][] = new int[n + 1][m + 1];
        sc.close();

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (w[i] <= j) {
                    // Now w[i] and p[i] correctly point to the current item i
                    v[i][j] = Math.max(v[i - 1][j], v[i - 1][j - w[i]] + p[i]);
                } else {
                    v[i][j] = v[i - 1][j];
                }
            }
        }
        int i=n, j=m;
        System.out.println("Max Profit: " + v[n][m]);
        System.out.println("Selected Items:");
        while (i>0 && j>0) {
            if (v[i][j] != v[i - 1][j]) {
                System.out.println("Item " + i);
                j -= w[i];
                i--;
            }
            else
                i--;
        }
    }
}