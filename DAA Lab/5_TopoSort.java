import java.util.ArrayList;
import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Number of tasks and dependency edges
Process: DFS traversal and push after visiting neighbors
Algorithm Used: Topological Sort (DFS based)
Technique: Decrease and Conquer
Output: Valid task execution order
Key Idea: A node is placed after all its dependencies
*/
class P5_TopoSort {
    static ArrayList<Integer>[] adj;
    static boolean[] visited;
    static int[] stack;
    static int top = -1;

    static void dfs(int v) {
        visited[v] = true; // Mark visited

        // Visit all neighbors
        for (int i = 0; i < adj[v].size(); i++) {
            int next = adj[v].get(i);
            if (!visited[next]) {
                dfs(next);
            }
        }

        stack[++top] = v; // Push after visiting neighbors
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of tasks (vertices): ");
        int n = sc.nextInt();

        System.out.print("Enter number of dependencies (edges): ");
        int e = sc.nextInt();

        adj = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<Integer>();
        }

        System.out.println("Enter edges as: from to");
        for (int i = 0; i < e; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            adj[u].add(v);
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
