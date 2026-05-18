import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Weighted graph (adjacency matrix) and source vertex
Process: Repeatedly pick nearest unvisited vertex and relax edges
Algorithm Used: Dijkstra's Algorithm
Technique: Greedy
Output: Shortest distance and path from source to all vertices
Key Idea: Once a vertex is finalized, its shortest distance is fixed
*/
class P6_Dijkstra {
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

        sc.close();
    }
}
