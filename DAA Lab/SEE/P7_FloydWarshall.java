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

    public static void compute(int[][] dist){
        int V = dist.length;
        for(int k=0; k<V; k++){
            for(int i=0; i<V ; i++){
                for(int j=0; j<V ; j++){
                    if((dist[i][k] + dist[k][j])<dist[i][j]){
                        dist[i][j] = dist[i][k]+dist[k][j];
                    }
                }
            }
        }
    }

    public static void main(String args[]){
        Scanner sc =  new Scanner(System.in);
        System.out.print("Enter number of nodes:");
        int n = sc.nextInt();
        int[][] graph = new int[n][n];
        System.out.println("Enter the adjacency matrix (999 for no edges, 0 for diagonal):");
        for(int i=0; i<n; i++){
            for(int j=0;j<n;j++){
                graph[i][j] = sc.nextInt();
            }
        }
        sc.close();

        compute(graph);

        System.out.println("Output distance matrix:");
        for(int[] row :graph){
            for(int val : row){
                System.out.print(val+" ");
            }
            System.out.println();
        }

    }
}

/*
Complexity Analysis (Based on this specific implementation):
------------------------------------------------------------
Time Complexity:
  - Best Case:    O(n^3) (always processes the three nested loops of size n)
  - Average Case: O(n^3)
  - Worst Case:   O(n^3)
Space Complexity:
  - Auxiliary Space: O(1) (updates the distance matrix in-place)
  - Total Space:     O(n^2) to store the adjacency matrix of size n x n
*/