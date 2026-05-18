import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Men and women preference tables
Process: Men propose in order, women keep best proposal
Algorithm Used: Gale-Shapley Stable Matching
Technique: Greedy Technique
Output: Stable pairs (woman -> man)
Key Idea: Each free man proposes to next preferred woman

PSEUDO CODE
-----------
GALE_SHAPLEY(menPref, womenPref, n):
    SET all men as free, all women as unmatched
    WHILE there exists a free man m DO
        w = next woman on m's preference list
        IF w is unmatched THEN
            MATCH(m, w)
        ELSE IF w prefers m over current partner m' THEN
            UNMATCH(m')
            MATCH(m, w)
    RETURN stable matching
*/
class P2_GaleShapley {
    static int getFreeMan(boolean[] free) {
        for (int i = 0; i < free.length; i++) {
            if (free[i]) {
                return i;
            }
        }
        return -1;
    }

    static boolean prefersNewMan(int[][] womenPref, int woman, int newMan, int currentMan) {
        // Check order in woman's list
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

        int[] womanPartner = new int[n];   // wpartner[w] = m means Woman 'w' is paired with Man 'm'
        boolean[] manFree = new boolean[n];  // menFree[m] = true if Man 'm' is free
        int[] nextProposal = new int[n];   // For Man 'm', the index of the next woman to propose to in his mpref list

        // Initialize all women as free and all men as free
        for (int i = 0; i < n; i++) {
            womanPartner[i] = -1;
            manFree[i] = true;
            nextProposal[i] = 0;
        }

        int freeCount = n;

        // Gale-Shapley main loop
        while (freeCount > 0) {
            int m = getFreeMan(manFree); // Pick any free man
            int w = menPref[m][nextProposal[m]]; // Next woman to propose
            nextProposal[m]++;

            if (womanPartner[w] == -1) {
                // Woman is free
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
