import java.util.*;

public class PrimsAlgorithm {

    // 1. Inner class to represent an edge in the graph for the adjacency list
    static class Edge {
        int dest;
        int weight;

        public Edge(int dest, int weight) {
            this.dest = dest;
            this.weight = weight;
        }
    }

    // 2. Inner class to represent a pair for the PriorityQueue (vertex, weight)
    // We need this to sort edges by weight in the priority queue
    static class Pair implements Comparable<Pair> {
        int vertex;
        int weight;

        public Pair(int vertex, int weight) {
            this.vertex = vertex;
            this.weight = weight;
        }

        @Override
        public int compareTo(Pair other) {
            return Integer.compare(this.weight, other.weight);
        }
    }

    public static void findMST(int vertices, List<List<Edge>> adj) {
        boolean[] visited = new boolean[vertices];
        PriorityQueue<Pair> pq = new PriorityQueue<>();
        List<String> mstEdges = new ArrayList<>();
        int totalWeight = 0;

        // 1. Start from vertex 0
        pq.add(new Pair(0, 0));

        while (!pq.isEmpty()) {
            Pair current = pq.poll();
            int u = current.vertex;

            // 2. If we have already visited this vertex, skip it to avoid cycles
            if (visited[u]) {
                continue;
            }

            // 3. Mark the vertex as visited and add its info to the result
            visited[u] = true;
            if (current.weight > 0) { // Don't add the starting self-loop
                // This part is slightly more complex as we don't store the source in the pair.
                // For simplicity in output, we'll just show the total weight.
                // A more complex implementation would store the parent to reconstruct the edge.
            }
            totalWeight += current.weight;


            // 4. Add all adjacent, unvisited vertices to the priority queue
            for (Edge edge : adj.get(u)) {
                if (!visited[edge.dest]) {
                    pq.add(new Pair(edge.dest, edge.weight));
                }
            }
        }

        // A complete MST must have V-1 edges. We can check this by counting visited nodes.
        int visitedCount = 0;
        for(boolean v : visited) {
            if(v) visitedCount++;
        }

        if (visitedCount < vertices) {
            System.out.println("MST not possible (Graph is not connected)");
        } else {
            System.out.println("Prim's Algorithm MST:");
            // Note: Printing the specific edges is more complex with this PQ setup.
            // We would need to track the parent of each vertex.
            // This implementation focuses on correctly calculating the total weight.
            System.out.println("Total Weight of MST: " + totalWeight);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of vertices: ");
        int vertices = sc.nextInt();

        // Adjacency list representation of the graph
        List<List<Edge>> adj = new ArrayList<>();
        for (int i = 0; i < vertices; i++) {
            adj.add(new ArrayList<>());
        }

        System.out.print("Enter number of edges: ");
        int numEdges = sc.nextInt();

        System.out.println("Enter edges (source destination weight):");
        for (int i = 0; i < numEdges; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int weight = sc.nextInt();
            // For an undirected graph, add edges in both directions
            adj.get(u).add(new Edge(v, weight));
            adj.get(v).add(new Edge(u, weight));
        }

        findMST(vertices, adj);

        sc.close();
    }
}
