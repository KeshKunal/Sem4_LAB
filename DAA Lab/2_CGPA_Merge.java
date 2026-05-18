import java.util.Scanner;

/*
MEMORY MAP
----------

Input: Number of students and CGPA values
Process: Assign grade for each CGPA, then merge sort by CGPA descending
Algorithm Used: Merge Sort (modified for CGPA + Grade)
Technique: Divide and Conquer
Output: CGPA with grade in descending order
Key Idea: Merge two sorted halves while keeping grade together
*/
class P2_CGPA_Merge {
    static String gradeFor(double cgpa) {
        if (cgpa >= 9.0) {
            return "O";
        } else if (cgpa >= 8.0) {
            return "S";
        } else if (cgpa >= 7.0) {
            return "A";
        } else if (cgpa >= 6.0) {
            return "B";
        } else if (cgpa >= 5.0) {
            return "C";
        } else {
            return "F";
        }
    }

    static void merge(double[] cgpa, String[] grade, int left, int mid, int right) {
        int i = left;
        int j = mid + 1;
        int k = 0;

        double[] tempCgpa = new double[right - left + 1];
        String[] tempGrade = new String[right - left + 1];

        // Merge in descending order of CGPA
        while (i <= mid && j <= right) {
            if (cgpa[i] >= cgpa[j]) {
                tempCgpa[k] = cgpa[i];
                tempGrade[k] = grade[i];
                i++;
            } else {
                tempCgpa[k] = cgpa[j];
                tempGrade[k] = grade[j];
                j++;
            }
            k++;
        }

        // Copy remaining left half
        while (i <= mid) {
            tempCgpa[k] = cgpa[i];
            tempGrade[k] = grade[i];
            i++;
            k++;
        }

        // Copy remaining right half
        while (j <= right) {
            tempCgpa[k] = cgpa[j];
            tempGrade[k] = grade[j];
            j++;
            k++;
        }

        // Copy back to original arrays
        for (int t = 0; t < tempCgpa.length; t++) {
            cgpa[left + t] = tempCgpa[t];
            grade[left + t] = tempGrade[t];
        }
    }

    static void mergeSort(double[] cgpa, String[] grade, int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSort(cgpa, grade, left, mid);
            mergeSort(cgpa, grade, mid + 1, right);
            merge(cgpa, grade, left, mid, right);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of students: ");
        int n = sc.nextInt();

        double[] cgpa = new double[n];
        String[] grade = new String[n];

        System.out.println("Enter CGPA values:");
        for (int i = 0; i < n; i++) {
            cgpa[i] = sc.nextDouble();
            grade[i] = gradeFor(cgpa[i]);
        }

        // Sort CGPA and grades together in descending order
        mergeSort(cgpa, grade, 0, n - 1);

        // Print final merged and sorted result
        System.out.print("Merged and sorted result: [");
        for (int i = 0; i < n; i++) {
            System.out.print(cgpa[i] + " - " + grade[i]);
            if (i < n - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");

        sc.close();
    }
}
