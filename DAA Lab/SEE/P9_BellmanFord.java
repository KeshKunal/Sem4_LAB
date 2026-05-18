import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Weighted graph (adjacency matrix) and source vertex
Process: Relax all edges V-1 times and check for negative cycle
Algorithm Used: Bellman-Ford
Technique: Dynamic Programming
Output: Shortest distances or negative cycle message
Key Idea: Repeated edge relaxation

PSEUDO CODE
-----------
BELLMAN_FORD(graph, src, n):
    dist[] = {INF}, dist[src] = 0
    FOR count = 0 to n-2 DO
        FOR each edge (u, v) with weight w DO
            IF dist[u] != INF AND dist[u] + w < dist[v] THEN
                dist[v] = dist[u] + w

    // Negative cycle detection
    FOR each edge (u, v) with weight w DO
        IF dist[u] != INF AND dist[u] + w < dist[v] THEN
            PRINT "Negative cycle exists"
            RETURN
    PRINT dist[]
*/
class P9_BellmanFord {
    static final int INF = 9999;

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

        System.out.print("Enter source vertex (0 to " + (n - 1) + "): ");
        int src = sc.nextInt();

        int[] dist = new int[n];
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
        }
        dist[src] = 0;

        // Relax all edges V-1 times
        for (int count = 0; count < n - 1; count++) {
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    int w = graph[u][v];
                    if (w != 0 && dist[u] != INF && dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }

        // Check for negative cycles
        boolean hasNegativeCycle = false;
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int w = graph[u][v];
                if (w != 0 && dist[u] != INF && dist[u] + w < dist[v]) {
                    hasNegativeCycle = true;
                }
            }
        }

        if (hasNegativeCycle) {
            System.out.println("Graph contains a negative weight cycle");
        } else {
            System.out.println("Shortest distances from source " + src + ":");
            for (int i = 0; i < n; i++) {
                if (dist[i] == INF) {
                    System.out.println(i + " -> INF");
                } else {
                    System.out.println(i + " -> " + dist[i]);
                }
            }
        }

        sc.close();
    }
}
