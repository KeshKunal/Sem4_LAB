import java.util.*;

class Matching {

    int n;
    int[][] mpref;
    int[][] wpref;

    int[] wpartner;        // woman -> man
    boolean[] menFree;     // free men
    int[] nextProposal;    // next woman index to propose

    Matching(int n,int[][] mpref, int[][] wpref) {
        this.n = n;
        this.mpref = mpref;
        this.wpref = wpref;

        wpartner = new int[n];
        menFree = new boolean[n];
        nextProposal = new int[n];

        // initialization
        for (int i = 0; i < n; i++) {
            wpartner[i] = -1;
            menFree[i] = true;
            nextProposal[i] = 0;
        }

        stableMatch();
    }

    // Gale-Shapley Algorithm
    void stableMatch() {

        int freeCount = n;

        while (freeCount > 0) {

            int m;
            for (m = 0; m < n; m++)
                if (menFree[m])
                    break;

            int w = mpref[m][nextProposal[m]];
            nextProposal[m]++;

            // woman is free
            if (wpartner[w] == -1) {
                wpartner[w] = m;
                menFree[m] = false;
                freeCount--;
            }
            else {
                int currentMan = wpartner[w];

                if (prefersNewMan(w, m, currentMan)) {
                    wpartner[w] = m;
                    menFree[m] = false;
                    menFree[currentMan] = true;
                }
            }
        }

        printResult();
    }

    // check woman's preference
    boolean prefersNewMan(int woman, int newMan, int currentMan) {
        for (int i = 0; i < n; i++) {
            if (wpref[woman][i] == newMan)
                return true;
            if (wpref[woman][i] == currentMan)
                return false;
        }
        return false;
    }

    void printResult() {
        System.out.println("\nFinal Couples:");
        for (int w = 0; w < n; w++) {
            System.out.println("Woman " + w + " - Man " + wpartner[w]);
        }
    }
}

public class GaleShapley {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of pairs: ");
        int n = sc.nextInt();

        int[][] mpref = new int[n][n];
        int[][] wpref = new int[n][n];

        System.out.println("Enter men's preferences (values 0-4):");
        for (int i = 0; i < n; i++) {
            System.out.print("Man " + i + ": ");
            for (int j = 0; j < n; j++) {
                mpref[i][j] = sc.nextInt();
            }
        }

        System.out.println("\nEnter women's preferences (values 0-4):");
        for (int i = 0; i < n; i++) {
            System.out.print("Woman " + i + ": ");
            for (int j = 0; j < n; j++) {
                wpref[i][j] = sc.nextInt();
            }
        }

        new Matching(n,mpref, wpref);

        sc.close();
    }
}