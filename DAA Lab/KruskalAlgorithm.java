import java.util.*;

class KruskalAlgorithm {

    // 1. Edge class to represent a weighted edge in the graph
    static class Edge implements Comparable<Edge> {
        int src, dest, weight;

        public Edge(int src, int dest, int weight) {
            this.src = src;
            this.dest = dest;
            this.weight = weight;
        }

        // Compare edges based on their weight for sorting
        @Override
        public int compareTo(Edge other) {
            return Integer.compare(this.weight, other.weight);
        }
    }

    // 2. Union-Find (Disjoint Set) data structure
    static class UnionFind {
        int[] parent;
        int[] rank;

        public UnionFind(int n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }

        // Find the representative of the set containing x (with path compression)
        public int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]); // Path compression
            }
            return parent[x];
        }

        // Union of two sets (with union by rank)
        public void union(int a, int b) {
            int rootA = find(a);
            int rootB = find(b);

            if (rootA != rootB) {
                if (rank[rootA] < rank[rootB]) {
                    parent[rootA] = rootB;
                } else if (rank[rootA] > rank[rootB]) {
                    parent[rootB] = rootA;
                } else {
                    parent[rootB] = rootA;
                    rank[rootA]++;
                }
            }
        }
    }

    private final int vertices;
    private final List<Edge> edges;

    public KruskalAlgorithm(int vertices) {
        this.vertices = vertices;
        edges = new ArrayList<>();
    }

    public void addEdge(int src, int dest, int weight) {
        edges.add(new Edge(src, dest, weight));
    }

    public void findMST() {
        Collections.sort(edges);
        UnionFind uf = new UnionFind(vertices);
        List<Edge> result = new ArrayList<>();

        for (Edge edge : edges) {
            int root1 = uf.find(edge.src);
            int root2 = uf.find(edge.dest);

            if (root1 != root2) {
                result.add(edge);
                uf.union(root1, root2);
            }

            if (result.size() == vertices - 1)
                break;
        }

        System.out.println("Edges in the Minimum Spanning Tree");
        int totalWeight = 0;
        for (Edge e : result) {
            System.out.println(e.src + " - " + e.dest + " : " + e.weight);
            totalWeight += e.weight;
        }
        System.out.println("Total Weight " + totalWeight);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of vertices:");
        int vertices = sc.nextInt();
        System.out.println("Enter number of edges:");
        int edges = sc.nextInt();
        KruskalAlgorithm graph = new KruskalAlgorithm(vertices);
        System.out.println("Enter Edge(src, dest, wt) for " + edges + " edges:");
        for(int i=0; i<edges; i++)
        {
            graph.addEdge(sc.nextInt(), sc.nextInt(), sc.nextInt());
        }

        graph.findMST();
        sc.close();
    }
}
