import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Weighted graph (adjacency matrix) and source vertex
Process: Repeatedly pick nearest unvisited vertex and relax edges
Algorithm Used: Dijkstra's Algorithm
Technique: Greedy Technique
Output: Shortest distance and path from source to all vertices
Key Idea: Once a vertex is finalized, its shortest distance is fixed

PSEUDO CODE
-----------
DIJKSTRA(graph, src, n):
    dist[] = {INF}, dist[src] = 0
    visited[] = {false}
    parent[] = {-1}
    FOR count = 0 to n-2 DO
        u = vertex with minimum dist[] among unvisited
        IF u == -1 THEN BREAK
        visited[u] = true
        FOR each vertex v = 0 to n-1 DO
            IF NOT visited[v] AND graph[u][v] > 0 THEN
                IF dist[u] + graph[u][v] < dist[v] THEN
                    dist[v] = dist[u] + graph[u][v]
                    parent[v] = u
    PRINT dist[] and reconstruct paths using parent[]
*/
class P4_Dijkstra {
    static final int INF = 9999;

    static int minDistance(int[] dist, boolean[] visited) {
        int min = INF;
        int index = -1;

        // Find the unvisited vertex with smallest distance
        for (int i = 0; i < dist.length; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                index = i;
            }
        }
        return index;
    }

    static void printPath(int v, int[] parent) {
        if (v == -1) {
            return;
        }
        printPath(parent[v], parent);
        System.out.print(v + " ");
    }

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
        boolean[] visited = new boolean[n];
        int[] parent = new int[n];

        // Initialize distances and parents
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            parent[i] = -1;
        }
        dist[src] = 0;

        long start = System.nanoTime();

        // Dijkstra core loop
        for (int count = 0; count < n - 1; count++) {
            int u = minDistance(dist, visited);
            if (u == -1) {
                break;
            }
            visited[u] = true; // Finalize this vertex

            // Relax edges from u
            for (int v = 0; v < n; v++) {
                if (!visited[v] && graph[u][v] > 0) {
                    if (dist[u] + graph[u][v] < dist[v]) {
                        dist[v] = dist[u] + graph[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        long end = System.nanoTime();

        // Print distances
        System.out.println("Shortest distances from source " + src + ":");
        for (int i = 0; i < n; i++) {
            System.out.println(i + " -> " + dist[i]);
        }

        // Print paths
        System.out.println("\nPaths from source " + src + ":");
        for (int i = 0; i < n; i++) {
            System.out.print("Path to " + i + ": ");
            printPath(i, parent);
            System.out.println();
        }

        System.out.println("Execution time (ns): " + (end - start));

        sc.close();
    }
}
