import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Number of vertices and adjacency matrix
Process: Update all-pairs shortest paths using intermediate vertices
Algorithm Used: Floyd-Warshall
Technique: Dynamic Programming
Output: Shortest path matrix
Key Idea: Try each vertex as an intermediate stop

PSEUDO CODE
-----------
FLOYD_WARSHALL(graph, n):
    dist[][] = graph[][] (with 0 -> INF for non-edges, 0 for diagonal)
    FOR k = 0 to n-1 DO
        FOR i = 0 to n-1 DO
            FOR j = 0 to n-1 DO
                IF dist[i][k] + dist[k][j] < dist[i][j] THEN
                    dist[i][j] = dist[i][k] + dist[k][j]
    PRINT dist[][]
*/
class P7_FloydWarshall {
    static final int INF = 9999;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of vertices: ");
        int n = sc.nextInt();

        int[][] dist = new int[n][n];

        System.out.println("Enter adjacency matrix (0 for no edge):");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val = sc.nextInt();
                if (i == j) {
                    dist[i][j] = 0; // Distance to self is 0
                } else if (val == 0) {
                    dist[i][j] = INF; // No edge
                } else {
                    dist[i][j] = val; // Given edge weight
                }
            }
        }

        // Floyd-Warshall core logic
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        System.out.println("All-pairs shortest path matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF) {
                    System.out.print("INF ");
                } else {
                    System.out.print(dist[i][j] + " ");
                }
            }
            System.out.println();
        }

        sc.close();
    }
}
