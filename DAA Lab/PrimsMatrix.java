import java.util.*;

public class PrimsMatrix {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of vertices: ");
        int V = sc.nextInt();
        int[][] graph = new int[V][V];

        System.out.println("Enter adjacency matrix (0 for self, 999 for no edge):");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                graph[i][j] = sc.nextInt();
            }
        }

        // --- INITIALIZATION ---
        boolean[] inMST = new boolean[V];
        inMST[0] = true; // Start the "fire" from vertex 0

        int edgesCount = 0;
        int totalCost = 0;

        System.out.println("\nEdges in MST:");

        // --- CORE LOGIC ---
        while (edgesCount < V - 1) {
            int min = 999;
            int u = -1, v = -1;

            // Search the matrix for the smallest edge
            for (int i = 0; i < V; i++) {
                if (inMST[i]) { // RULE: 'i' must ALREADY be in our tree
                    for (int j = 0; j < V; j++) {
                        // RULE: 'j' must NOT be in our tree yet
                        if (!inMST[j] && graph[i][j] != 0 && graph[i][j] < min) {
                            min = graph[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            // If a valid edge was found
            if (u != -1) {
                System.out.println(u + " - " + v + " = " + min);
                totalCost += min;
                inMST[v] = true; // Add the new vertex to our tree
                edgesCount++;
            } else {
                break;
            }
        }

        System.out.println("Total Cost: " + totalCost);
        sc.close();
    }
}