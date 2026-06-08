
/*
MEMORY MAP
----------

Input: Number of cities and cost matrix
Process: Try all routes with pruning using current best cost
Algorithm Used: Travelling Salesperson Problem (Branch and Bound)
Technique: Branch and Bound
Output: Minimum cost tour and path
Key Idea: Prune any partial path whose cost exceeds best

PSEUDO CODE
-----------
Algorithm TSP(level, currentCity, currentCost)

Input:
    Cost matrix cost[n][n]
Output:
    Minimum tour cost and optimal path

1. IF currentCost ≥ minCost THEN
       RETURN            // Prune this branch

2. IF level = n THEN
       totalCost ← currentCost + cost[currentCity][0]

       IF totalCost < minCost THEN
            minCost ← totalCost
            Store current path as best path
       END IF

       RETURN
   END IF

3. FOR each city next from 0 to n-1 DO

       IF next is not visited AND
          cost[currentCity][next] ≠ 0 THEN

            visited[next] = true
            Add next to current path
            TSP(level + 1,
                next,
                currentCost + cost[currentCity][next])

            visited[next] = false      // Backtrack

       END IF

   END FOR

End Algorithm

Time Complexity  : O(n!)
Space Complexity : O(n)
*/

import java.util.Scanner;

public class TSP_BranchAndBound {

    static int n;  // no. of cities 
    static int[][] cost; // cost matrix
    static boolean[] visited;  // keeps track of visited cities
    static int[] path; // current tour
    static int[] bestPath; // best route found
    static int minCost = Integer.MAX_VALUE; // best min tour cost

    static void tsp(int level, int currentCity, int currentCost) {

        // Bound (Pruning)
        if (currentCost >= minCost)
            return;

        // All cities visited
        if (level == n) {
            int totalCost = currentCost + cost[currentCity][0];

            if (totalCost < minCost) {
                minCost = totalCost;

                for (int i = 0; i < n; i++)
                    bestPath[i] = path[i];
            }
            return;
        }

        // Branch
        for (int next = 0; next < n; next++) {

            if (!visited[next] && cost[currentCity][next] != 0) {

                visited[next] = true;
                path[level] = next;

                tsp(level + 1,
                    next,
                    currentCost + cost[currentCity][next]);

                visited[next] = false; // Backtrack
            }
        }
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of cities: ");
        n = sc.nextInt();

        cost = new int[n][n];
        visited = new boolean[n];
        path = new int[n];
        bestPath = new int[n];

        System.out.println("Enter cost matrix:");

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cost[i][j] = sc.nextInt();
            }
        }

        visited[0] = true;
        path[0] = 0;
        // level : how many cities have been included in the current path so far.
        tsp(1, 0, 0);

        System.out.println("\nMinimum Cost = " + minCost);

        System.out.print("Optimal Path = ");
        for (int i = 0; i < n; i++) {
            System.out.print((bestPath[i] + 1) + " -> ");
        }
        System.out.println("1");

        sc.close();
    }
}