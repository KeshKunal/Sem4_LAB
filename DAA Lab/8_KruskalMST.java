import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Weighted graph (adjacency matrix)
Process: Pick smallest edges that do not form a cycle
Algorithm Used: Kruskal's Algorithm (Matrix based)
Technique: Greedy
Output: Edges of MST and total cost
Key Idea: Use union-find to avoid cycles
*/
class P8_KruskalMST {
    static int find(int[] parent, int i) {
        if (parent[i] == i) {
            return i;
        }
        parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    static void union(int[] parent, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        parent[rootX] = rootY;
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

        int[] parent = new int[n];

        // Initialize each vertex as its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        int edgesCount = 0;
        int totalCost = 0;

        System.out.println("Edges in MST:");

        // Pick edges until we get n-1 edges
        while (edgesCount < n - 1) {
            int min = 9999;
            int u = -1;
            int v = -1;

            // Find the smallest edge that does not form a cycle
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (graph[i][j] != 0 && graph[i][j] < min) {
                        if (find(parent, i) != find(parent, j)) {
                            min = graph[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            if (u != -1) {
                System.out.println(u + " - " + v + " = " + min);
                totalCost += min;
                union(parent, u, v);
                edgesCount++;
            } else {
                break;
            }
        }

        System.out.println("Total Cost: " + totalCost);
        sc.close();
    }
}
