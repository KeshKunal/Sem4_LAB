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

    static void compute(int numItems, int capacity, int[] weights, int[] profits) {
        int[][] dpTable = new int[numItems + 1][capacity + 1];

        // Build DP table
        for (int item = 1; item <= numItems; item++) {
            for (int cap = 1; cap <= capacity; cap++) {
                if (weights[item] <= cap) {
                    dpTable[item][cap] = Math.max(
                        dpTable[item - 1][cap],
                        profits[item] + dpTable[item - 1][cap - weights[item]]
                    );
                } else {
                    dpTable[item][cap] = dpTable[item - 1][cap];
                }
            }
        }

        // Backtrack to find selected items
        int item = numItems;
        int remainingCap = capacity;
        System.out.println("Selected Objects:");
        while (item > 0 && remainingCap > 0) {
            if (dpTable[item][remainingCap] != dpTable[item - 1][remainingCap]) {
                System.out.println("Object: " + item);
                remainingCap = remainingCap - weights[item];
                item--;
            } else {
                item--;
            }
        }

        System.out.println("Optimal Profit is: " + dpTable[numItems][capacity]);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter no. of objects and Capacity of Knapsack: ");
        int numItems = sc.nextInt();
        int capacity = sc.nextInt();

        int[] weights = new int[numItems + 1];
        int[] profits = new int[numItems + 1];

        System.out.println("Enter weight and profit of each object:");
        for (int item = 1; item <= numItems; item++) {
            System.out.print("Object " + item + ": ");
            weights[item] = sc.nextInt();
            profits[item] = sc.nextInt();
        }

        compute(numItems, capacity, weights, profits);

        sc.close();
    }
}
