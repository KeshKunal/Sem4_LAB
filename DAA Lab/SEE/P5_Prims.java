import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Weighted graph (adjacency matrix)
Process: Grow MST by always picking the smallest edge to a new vertex
Algorithm Used: Prim's Algorithm (Matrix based)
Technique: Greedy Technique
Output: Edges of MST and total cost
Key Idea: Always connect nearest unvisited vertex

PSEUDO CODE
-----------
PRIMS(graph, n):
    inMST[] = {false}, inMST[0] = true
    edgesCount = 0, totalCost = 0
    WHILE edgesCount < n - 1 DO
        min = INF, u = -1, v = -1
        FOR each vertex i in MST DO
            FOR each vertex j NOT in MST DO
                IF graph[i][j] != 0 AND graph[i][j] < min THEN
                    min = graph[i][j], u = i, v = j
        IF u == -1 THEN BREAK
        ADD edge (u, v) to MST
        totalCost += min
        inMST[v] = true
        edgesCount++
    PRINT edges and totalCost
*/
class P5_Prims {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of vertices: ");
        int n = sc.nextInt();

        int[][] graph = new int[n][n];
        System.out.println("Enter adjacency matrix (0 for no edge):");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = sc.nextInt();
            }
        }

        boolean[] inMST = new boolean[n];
        inMST[0] = true; // Start from vertex 0

        int edgesCount = 0;
        int totalCost = 0;

        System.out.println("Edges in MST:");

        long start = System.nanoTime();

        // Repeat until we have n-1 edges
        while (edgesCount < n - 1) {
            int min = 9999;
            int u = -1;
            int v = -1;

            // Find smallest edge from visited to unvisited
            for (int i = 0; i < n; i++) {
                if (inMST[i]) {
                    for (int j = 0; j < n; j++) {
                        if (!inMST[j] && graph[i][j] != 0 && graph[i][j] < min) {
                            min = graph[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            // Add the selected edge
            if (u != -1) {
                System.out.println(u + " - " + v + " = " + min);
                totalCost += min;
                inMST[v] = true;
                edgesCount++;
            } else {
                break;
            }
        }

        long end = System.nanoTime();

        System.out.println("Total Cost: " + totalCost);
        System.out.println("Execution time (ns): " + (end - start));

        sc.close();
    }
}
