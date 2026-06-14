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
import java.util.Scanner;

public class P3_TopoSortDFS {

    static int graph[][], stack[];
    static boolean visited[];
    static int top = -1, n;

    static void dfs(int v) {
        visited[v] = true;

        for (int i = 0; i < n; i++)
            if (graph[v][i] == 1 && !visited[i])
                dfs(i);

        stack[++top] = v;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of vertices: ");
        n = sc.nextInt();

        graph = new int[n][n];

        System.out.println("Enter adjacency matrix:");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = sc.nextInt();

        visited = new boolean[n];
        stack = new int[n];

        for (int i = 0; i < n; i++)
            if (!visited[i])
                dfs(i);

        System.out.print("Topological Order: ");

        while (top >= 0)
            System.out.print(stack[top--] + " ");

        sc.close();
    }
}

/*
Complexity Analysis (Based on this specific implementation):
------------------------------------------------------------
Time Complexity:
  - Best Case:    O(n^2) (due to traversing the full row of size n in adjacency matrix for every visited vertex)
  - Average Case: O(n^2)
  - Worst Case:   O(n^2)
Space Complexity:
  - Auxiliary Space: O(n) (for stack, visited, and recursion call stack)
  - Total Space:     O(n^2) to store the adjacency matrix of size n x n
*/