// Randomized Quicksort
// Arzum Aydın - 22.11.2021

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
#include <time.h>


void swap(int* a, int* b) //swap handling function
{
    int temp = *a; 
    *a = *b;
    *b = temp;
}

int partition(int* arr, int l, int r)
{
    int x = rand() % (r - l) + l;   //generate random number, choose random element as pivot between higher index and lower index
    swap(arr+r, arr+x);   // take pivot to end of array by swapping with last element
    int pivot = arr[r]; 

    int i = l - 1; // i holds the place where pivot should be

    for(int j = l; j < r; j++) // iterate through array until pivot is reached
    {
        if(arr[j] <= pivot) // if there is a smaller value than pivot, swap arr[i] and arr[j]
        {                   // no swap necessary for the first element so i starts from (l-1)

            i++; //increment i to next position
            swap(arr+i, arr+j); // swap left and right elements with respect to pivot
        }
    }

    i++;
    swap(arr+i, arr+r); // assign pivot to its correct place
    return i; // return pivot index
}

void quickSort(int* arr, int l, int r)
{
    if(l < r)
    {
        // do partition by dividing elements into two groups as smaller than pivot and bigger than pivot
        int pivot_index = partition(arr, l, r);  // find pivot index by partitioning the array
        quickSort(arr, l, pivot_index - 1); // quicksort subarray on the left of pivot
        quickSort(arr, pivot_index + 1, r); // quicksort subarray on the right of pivot
    }
}

int main()
{
    srand(time(NULL));
    int size = 10;
    int* arr = (int *)malloc(sizeof(int) * size) ;
    int left, right;

	printf("Enter elements of the array: ");
	for(int i = 0; i < size; i++)
	{
        int input;
		scanf("%d", &input);
        arr[i] = input;
	}

    left = 0;
    right = size - 1;

    quickSort(arr, left, right);
    
    printf("Sorted array: \n");

    for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
    printf("\n");

    free(arr);
    return 0;
}