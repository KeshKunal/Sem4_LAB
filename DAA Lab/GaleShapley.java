import java.util.*;

class Matching {
    int n;
    int[][] mpref;         // Men's preferences
    int[][] wpref;         // Women's preferences

    int[] wpartner;        // wpartner[w] = m means Woman 'w' is paired with Man 'm'
    boolean[] menFree;     // menFree[m] = true if Man 'm' is free
    int[] nextProposal;    // For Man 'm', the index of the next woman to propose to in his mpref list

    Matching(int n, int[][] mpref, int[][] wpref) {
        this.n = n;
        this.mpref = mpref;
        this.wpref = wpref;

        wpartner = new int[n];
        menFree = new boolean[n];
        nextProposal = new int[n];

        // Initially, all women are single, all men are free, and each man will start by
        // proposing to the first woman on his list (index 0).
        for (int i = 0; i < n; i++) {
            wpartner[i] = -1;     // -1 signifies a woman is free
            menFree[i] = true;      // All men start as free
            nextProposal[i] = 0;    // Each man starts by proposing to the woman at index 0 of his preference list
        }

        stableMatch(); // Kick off the main algorithm
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
    
    boolean prefersNewMan(int woman, int newMan, int currentMan) {
        // This function iterates through the specified woman's preference list.
        for (int i = 0; i < n; i++) {
            // If we find the newMan first, it means he has a higher rank (lower index).
            if (wpref[woman][i] == newMan)
                return true;
            // If we find the currentMan first, it means he has a higher rank.
            if (wpref[woman][i] == currentMan)
                return false;
        }
        return false; // Should not be reached in a valid setup.
    }

    // --- Lines 78-84: Printing the final result ---
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