import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Text and pattern strings
Process: Build shift table and compare from right to left
Algorithm Used: Horspool String Matching
Technique: Input Enhancement (Space-Time Tradeoff)
Output: Pattern found position or not found
Key Idea: Skip characters using shift values

PSEUDO CODE
-----------
BUILD_SHIFT_TABLE(pattern, m):
    shift[0..255] = m
    FOR i = 0 to m - 2 DO
        shift[pattern[i]] = m - 1 - i
    RETURN shift

HORSPOOL_SEARCH(text, pattern):
    n = length(text), m = length(pattern)
    shift = BUILD_SHIFT_TABLE(pattern, m)
    i = m - 1
    WHILE i < n DO
        k = 0
        WHILE k < m AND pattern[m-1-k] == text[i-k] DO
            k++
        IF k == m THEN RETURN i - m + 1
        ELSE i = i + shift[text[i]]
    RETURN -1
*/
class P6_Horspool {
    static int[] buildShiftTable(String pattern) {
        int[] shift = new int[256];
        int m = pattern.length();

        // Default shift is pattern length
        for (int i = 0; i < 256; i++) {
            shift[i] = m;
        }

        // For each character except last, set shift
        for (int i = 0; i < m - 1; i++) {
            shift[pattern.charAt(i)] = m - 1 - i;
        }

        return shift;
    }

    static int horspoolSearch(String text, String pattern) {
        int n = text.length();
        int m = pattern.length();

        int[] shift = buildShiftTable(pattern);

        int i = m - 1; // Index in text
        while (i < n) {
            int k = 0;

            // Compare from right to left
            while (k < m && pattern.charAt(m - 1 - k) == text.charAt(i - k)) {
                k++;
            }

            if (k == m) {
                return i - m + 1; // Match found
            } else {
                i = i + shift[text.charAt(i)]; // Shift by table value
            }
        }

        return -1; // Not found
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter text: ");
        String text = sc.nextLine();

        System.out.print("Enter pattern: ");
        String pattern = sc.nextLine();

        int index = horspoolSearch(text, pattern);

        if (index == -1) {
            System.out.println("Pattern not found");
        } else {
            System.out.println("Pattern found at index: " + index);
        }

        sc.close();
    }
}

/*
Complexity Analysis (Based on this specific implementation):
------------------------------------------------------------
Time Complexity:
  - Best Case:    O(n/m) (occurs when the pattern is not present and characters align to allow max shifts of size m)
  - Average Case: O(n)
  - Worst Case:   O(n * m) (occurs when text and pattern have repeating matching characters, leading to minimal shift of 1)
Space Complexity:
  - Auxiliary Space: O(1) (since the shift table size is constant, 256 for ASCII)
  - Total Space:     O(n + m) to store the text and pattern strings
*/
