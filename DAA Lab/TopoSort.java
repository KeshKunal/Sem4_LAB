import java.util.*;

public class TopoSort {
    static ArrayList<Integer>[] adj;
    static boolean[] visited;
    static Stack<Integer> stack = new Stack<>();

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter number of vertices: ");
        int n = sc.nextInt();
        
        System.out.print("Enter number of edges: ");
        int e = sc.nextInt();

        // 1. Initialize Adjacency List
        adj = new ArrayList[n];
        for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();
        
        System.out.println("Enter the edges (source destination):");
        for (int i = 0; i < e; i++) {
            adj[sc.nextInt()].add(sc.nextInt());
        }

        // 2. Perform DFS for each node
        visited = new boolean[n];
        for (int i = 0; i < n; i++) {
            if (!visited[i]) dfs(i);
        }

        // 3. Print in Reverse (Pop from stack)
        System.out.print("Topological Sort: ");
        while (!stack.isEmpty()) {
            System.out.print(stack.pop() + " ");
        }
        
        sc.close();
    }

    static void dfs(int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) dfs(v);
        }
        stack.push(u); // Core logic: push after visiting neighbors
    }
}