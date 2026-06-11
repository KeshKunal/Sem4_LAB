import java.util.*;

public class dijkstra {
	private static final int INF = 1000;

	private static void printPath(int v, int[] parent) {
		if (v == -1) {
			return;
		}
		printPath(parent[v], parent);
		System.out.print(v + " ");
	}

	private static int minDistance(int[] dist, boolean[] visited) {
		int min = INF;
		int minIndex = -1;
		for (int i = 0; i < dist.length; i++) {
			if (!visited[i] && dist[i] < min) {
				min = dist[i];
				minIndex = i;
			}
		}
		return minIndex;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		System.out.print("Enter number of vertices: ");
		int n = sc.nextInt();
		int[][] graph = new int[n][n];

		System.out.println("Enter adjacency matrix (0 or negative for no edge):");
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
		Arrays.fill(dist, INF);
		Arrays.fill(parent, -1);
		dist[src] = 0;

		for (int count = 0; count < n - 1; count++) {
			int u = minDistance(dist, visited);
			if (u == -1) {
				break;
			}
			visited[u] = true;

			for (int v = 0; v < n; v++) {
				int weight = graph[u][v];
				if (!visited[v] && weight > 0 && dist[u] != INF && dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
					parent[v] = u;
				}
			}
		}

		System.out.println("Shortest distances from source " + src + ":");
		for (int i = 0; i < n; i++) {
			if (dist[i] == INF) {
				System.out.println(i + " -> INF");
			} else {
				System.out.println(i + " -> " + dist[i]);
			}
		}

		System.out.println("\nPath and total weight from source " + src + ":");
		for (int i = 0; i < n; i++) {
			if (dist[i] == INF) {
				System.out.println(i + " -> INF (no path)");
			} else {
				System.out.print(i + " -> " + dist[i] + " | path: ");
				printPath(i, parent);
				System.out.println();
			}
		}

		sc.close();
	}
}
