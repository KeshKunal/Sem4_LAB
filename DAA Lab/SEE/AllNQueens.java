import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Size of board N
Process: Place queens row by row using backtracking
Algorithm Used: N-Queens
Technique: Backtracking
Output: All valid arrangements and count
Key Idea: Check column and diagonal safety

PSEUDO CODE
-----------
SOLVE(row):
    IF row == N THEN
        PRINT board
        solutionCount++
        RETURN
    FOR col = 0 to N-1 DO
        IF IS_SAFE(row, col) THEN
            board[row] = col
            SOLVE(row + 1)

IS_SAFE(row, col):
    FOR i = 0 to row-1 DO
        IF board[i] == col THEN RETURN false
        IF |i - row| == |board[i] - col| THEN RETURN false
    RETURN true
*/
import java.util.Scanner;

public class AllNQueens {
    // Declare N and board, but initialize them later in main
    static int N; 
    static int[] board; 
    static int solutionCount = 0;

    static void solve(int row) {
        if (row == N) {
            printBoard();
            solutionCount++;
            return;
        }

        for (int col = 0; col < N; col++) {
            if (isSafe(row, col)) {
                board[row] = col; // Place queen
                solve(row + 1);   // Recurse for next row
            }
        }
    }

    static boolean isSafe(int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i] == col || Math.abs(i - row) == Math.abs(board[i] - col)) {
                return false; // Same column or same diagonal
            }
        }
        return true;
    }

    static void printBoard() {
        System.out.println("Solution " + (solutionCount + 1) + ":");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i] == j) System.out.print("Q ");
                else System.out.print(". ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of queens (N): ");
        N = sc.nextInt();
        
        board = new int[N];
        
        System.out.println("\nFinding solutions for " + N + " Queens...\n");
        
        solve(0);
        System.out.println("Total solutions: " + solutionCount);
        
        sc.close();
    }
}