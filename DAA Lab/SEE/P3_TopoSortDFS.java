import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Number of activities and adjacency matrix
Process: DFS traversal and push after visiting neighbors
Algorithm Used: Topological Sort using DFS
Technique: Decrease and Conquer
Output: Valid topological order
Key Idea: A node is placed after all its dependencies

PSEUDO CODE
-----------
TOPO_SORT(graph, n):
    visited[] = {false}
    stack = empty
    FOR each vertex v = 0 to n-1 DO
        IF NOT visited[v] THEN
            DFS(v)
    PRINT stack in reverse order

DFS(v):
    visited[v] = true
    FOR each neighbor u of v DO
        IF NOT visited[u] THEN
            DFS(u)
    PUSH v onto stack
*/
class P3_TopoSortDFS {
    static int[][] graph;
    static boolean[] visited;
    static int[] stack;
    static int top = -1;
    static int n;

    static void dfs(int v) {
        visited[v] = true; // Mark visited

        // Visit all neighbors
        for (int i = 0; i < n; i++) {
            if (graph[v][i] == 1 && !visited[i]) {  // there is an edge from v -> i and it is not visited
                dfs(i);
            }
        }

        stack[++top] = v; // Push after visiting neighbors
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of vertices: ");
        n = sc.nextInt();

        graph = new int[n][n];
        System.out.println("Enter adjacency matrix (0 or 1):");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = sc.nextInt();
            }
        }

        visited = new boolean[n];
        stack = new int[n];

        // Run DFS from each node
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        // Print topological order
        System.out.print("Topological order: ");
        for (int i = top; i >= 0; i--) {
            System.out.print(stack[i] + " ");
        }
        System.out.println();

        sc.close();
    }
}
