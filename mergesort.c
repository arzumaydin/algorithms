#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* arr, int p, int q, int r){ 
    // p is the most left position, q is the mid position and r is the most right position
  
    //divide the array into two and create two new arrays
    int n1 = q - p + 1;
    int n2 = r - q;
    int left[n1];
    int right[n2];
    
    // loop throught the left array and copy the elements of the input array to it
    for (int i = 0; i < n1; i++)
        left[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[q + 1 + j];

    // Handle the current index of subarrays and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Select the smaller one of L[i] or M[j],
    // until the end of one of these 2 subarrays
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Start filling elements from the subarray
    // whose elements are still left
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
    
}

void mergeSort(int* arr, int l, int r){
  // PLACE YOUR CODE HERE.
    int m;
    if(l < r)
    {
        m = floor((l + r) / 2);
        mergeSort(arr, l, m); // sort left array
        mergeSort(arr, m+1, r); // sort right array
        merge(arr, l, m, r); // merge two arrays
    }
}

int main()
{
    int size = 10;
    int* arr = malloc(sizeof(int) * size);

	printf("Enter elements of the array: ");
	for(int i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}

    mergeSort(arr, 0, size - 1);

    printf("Sorted array: ");

    for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
    printf("\n");

    return 0;
}