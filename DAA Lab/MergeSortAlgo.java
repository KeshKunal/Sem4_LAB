import java.util.Arrays;
import java.util.Scanner;

class MergeSortAlgo
{

	static void merge(int[] arr, int l, int mid, int r)
	{
        int i=l, j=mid+1, k=0;
        int[] temp = new int[r+1];
        while(i<=mid && j<=r)
        {
            if(arr[i]<arr[j])
                temp[k++]=arr[i++];
            else
                temp[k++]=arr[j++];
        }
        while(i<=mid)
            temp[k++]=arr[i++];
        while(j<=r)
            temp[k++]=arr[j++];

        for(int p=0; p<k; p++)
            arr[l++]=temp[p];
    }

    static void mergeSort(int[] arr, int l, int r) {
        if (l < r) {
            int mid = l + (r - l) / 2;
            mergeSort(arr, l, mid);
            mergeSort(arr, mid + 1, r);
            merge(arr, l, mid, r);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of elements: ");
        int n = scanner.nextInt();

        int[] arr = new int[n];

        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }

        System.out.println("Original array: " + Arrays.toString(arr));

        mergeSort(arr, 0, arr.length - 1);

        System.out.println("Sorted array: " + Arrays.toString(arr));
        
        scanner.close();
    }
}




