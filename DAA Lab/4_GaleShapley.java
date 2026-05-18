import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Men and women preference tables
Process: Men propose in order, women keep best proposal
Algorithm Used: Gale-Shapley Stable Marriage
Technique: Greedy
Output: Stable pairs
Key Idea: Each free man proposes to next preferred woman
*/
class P4_GaleShapley {
    static int getFreeMan(boolean[] free) {
        for (int i = 0; i < free.length; i++) {
            if (free[i]) {
                return i;
            }
        }
        return -1;
    }

    static boolean prefersNewMan(int[][] womenPref, int woman, int newMan, int currentMan) {
        // Check the order of preference in woman's list
        for (int i = 0; i < womenPref[woman].length; i++) {
            if (womenPref[woman][i] == newMan) {
                return true;
            }
            if (womenPref[woman][i] == currentMan) {
                return false;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of pairs: ");
        int n = sc.nextInt();

        int[][] menPref = new int[n][n];
        int[][] womenPref = new int[n][n];

        System.out.println("Enter men's preferences (0 to " + (n - 1) + "):");
        for (int i = 0; i < n; i++) {
            System.out.print("Man " + i + ": ");
            for (int j = 0; j < n; j++) {
                menPref[i][j] = sc.nextInt();
            }
        }

        System.out.println("Enter women's preferences (0 to " + (n - 1) + "):");
        for (int i = 0; i < n; i++) {
            System.out.print("Woman " + i + ": ");
            for (int j = 0; j < n; j++) {
                womenPref[i][j] = sc.nextInt();
            }
        }

        int[] womanPartner = new int[n];  // womanPartner[w] = man index
        boolean[] manFree = new boolean[n];
        int[] nextProposal = new int[n]; // Next woman index for each man

        // Initialize all women as free (-1) and all men as free (true)
        for (int i = 0; i < n; i++) {
            womanPartner[i] = -1;
            manFree[i] = true;
            nextProposal[i] = 0;
        }

        int freeCount = n;

        // Core Gale-Shapley loop
        while (freeCount > 0) {
            int m = getFreeMan(manFree); // Pick any free man
            int w = menPref[m][nextProposal[m]]; // Next woman to propose
            nextProposal[m]++;

            if (womanPartner[w] == -1) {
                // Woman is free, accept proposal
                womanPartner[w] = m;
                manFree[m] = false;
                freeCount--;
            } else {
                int currentMan = womanPartner[w];
                if (prefersNewMan(womenPref, w, m, currentMan)) {
                    // Woman prefers new man
                    womanPartner[w] = m;
                    manFree[m] = false;
                    manFree[currentMan] = true;
                }
            }
        }

        System.out.println("Final stable pairs:");
        for (int w = 0; w < n; w++) {
            System.out.println("Woman " + w + " - Man " + womanPartner[w]);
        }

        sc.close();
    }
}
