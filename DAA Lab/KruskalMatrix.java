import java.util.*;

public class KruskalMatrix {

    // 1. FIND function: Finds the root of a vertex (with Path Compression)
    // To remember: "If I'm not my own parent, keep looking up."
    static int find(int parent[], int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent, parent[i]); 
    }

    // 2. UNION function: Connects two sets
    // To remember: "Make the root of one the parent of the other."
    static void union(int parent[], int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        parent[rootX] = rootY;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // --- INPUT SECTION ---
        System.out.print("Enter number of vertices: ");
        int n = sc.nextInt();

        int[][] graph = new int[n][n];
        System.out.println("Enter adjacency matrix (0 for self, 999 for no edge):");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = sc.nextInt();
            }
        }

        // --- INITIALIZATION ---
        // Every node starts as its own parent (its own set)
        int[] parent = new int[n];
        for (int i = 0; i < n; i++) parent[i] = i;

        int edgesCount = 0; // Tracks edges added to MST (target is n-1)
        int totalCost = 0;  // Sum of weights in MST

        System.out.println("\nEdges in the Minimum Spanning Tree:");

        // --- CORE LOGIC: GREEDY SEARCH ---
        // Keep looking for edges until we have n-1 edges
        while (edgesCount < n - 1) {
            int min = 999; // Represents Infinity
            int u = -1, v = -1;

            // Nested loops to find the absolute minimum weight edge currently available
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // Check if edge exists and is smaller than current min
                    if (graph[i][j] != 0 && graph[i][j] < min) {
                        // CYCLE CHECK: Are these two nodes already connected?
                        if (find(parent, i) != find(parent, j)) {
                            min = graph[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            // If we found a valid minimum edge that doesn't form a cycle
            if (u != -1) {
                System.out.println("Edge " + u + " - " + v + " : " + min);
                totalCost += min;
                union(parent, u, v); // Merge the two sets
                edgesCount++;        // Increment edge counter
            } else {
                // If no edge was found but edgesCount < n-1, graph is disconnected
                break;
            }
        }

        // --- FINAL OUTPUT ---
        if (edgesCount == n - 1) {
            System.out.println("Total Cost of MST: " + totalCost);
        } else {
            System.out.println("No Spanning Tree possible (Graph is disconnected).");
        }

        sc.close();
    }
}