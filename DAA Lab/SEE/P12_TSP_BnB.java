import java.util.Scanner;

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
TSP(level, currentCity, currentCost):
    IF currentCost >= bestCost THEN RETURN       // Prune
    IF level == n THEN
        totalCost = currentCost + cost[currentCity][0]
        IF totalCost < bestCost THEN
            bestCost = totalCost
            bestPath = path
        RETURN
    FOR each unvisited city next DO
        IF cost[currentCity][next] != 0 THEN
            visited[next] = true
            path[level] = next
            TSP(level + 1, next, currentCost + cost[currentCity][next])
            visited[next] = false                // Backtrack
*/
class P12_TSP_BnB {
    static final int INF = 9999;
    static int n;
    static int[][] cost;
    static boolean[] visited;
    static int[] path;
    static int[] bestPath;
    static int bestCost = INF;

    static void tsp(int level, int currentCity, int currentCost) {
        // Prune if cost already exceeds best
        if (currentCost >= bestCost) {
            return;
        }

        // If all cities are visited, check returning to start
        if (level == n) {
            if (cost[currentCity][0] != 0) {
                int totalCost = currentCost + cost[currentCity][0];
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    for (int i = 0; i < n; i++) {
                        bestPath[i] = path[i];
                    }
                }
            }
            return;
        }

        // Try next city
        for (int next = 0; next < n; next++) {
            if (!visited[next] && cost[currentCity][next] != 0) {
                visited[next] = true;
                path[level] = next;
                tsp(level + 1, next, currentCost + cost[currentCity][next]);
                visited[next] = false;
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of cities: ");
        n = sc.nextInt();

        cost = new int[n][n];
        System.out.println("Enter cost matrix (0 for no edge):");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cost[i][j] = sc.nextInt();
            }
        }

        visited = new boolean[n];
        path = new int[n];
        bestPath = new int[n];

        visited[0] = true; // Start from city 0
        path[0] = 0;

        tsp(1, 0, 0);

        if (bestCost == INF) {
            System.out.println("No possible tour");
        } else {
            System.out.println("Minimum tour cost: " + bestCost);
            System.out.print("Tour path: ");
            for (int i = 0; i < n; i++) {
                System.out.print(bestPath[i] + " -> ");
            }
            System.out.println("0");
        }

        sc.close();
    }
}
