import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Weighted graph (adjacency matrix)
Process: Grow MST by always picking the smallest edge to a new vertex
Algorithm Used: Prim's Algorithm (Matrix based)
Technique: Greedy
Output: Edges of MST and total cost
Key Idea: Always connect nearest unvisited vertex
*/
class P7_PrimsMST {
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

        System.out.println("Total Cost: " + totalCost);
        sc.close();
    }
}
