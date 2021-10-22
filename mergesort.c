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
    int* left = malloc(sizeof(int) * n1);
    int* right = malloc(sizeof(int) * n2);
    
    // loop throught the left array and copy the elements of the input array to it
    for(int i = 0; i < n1; i++)
    {
        *(left + i) = *(arr + (p+i));
    }

    // loop throught the right array and copy the elements of the input array to it
    for(int j = 0; j < n2; j++)
    {
        *(right + j) = *(arr + q + j + 1);
    }
    
    int i = 0; int j = 0;
    int k = p; // starting from the most left element
    for(; k < r; k++) // iterate until the most right element
    {
        if(*(left+i) <= *(right+j)) // if left array's element is smaller than right array's element
        {
            *(arr+k) = *(left+i); // copy the smaller value to the input array
            i++; // increase whichever array's element is copied into the input array
        }
        else
        {
            *(arr+k) = *(right+j); // similar operation for the other condition
            j++;
        }
    }
    
    // if one of the arrays' values are copied entirely but the other one is not 
    // we copy rest of the values to the input array
    // e.g left array is {1,2,4} and right array is {5,7,8}
    // left array will be copied while right is not therefore, we must copy the right array after all the comparisons
    while (i < n1) { // copy left array to input array
        *(arr+k) = *(left+i);
        i++;
        k++;
    }

    while (j < n2) { // copy right array to input array
        *(arr+k) = *(right+j);
        j++;
        k++;
    }
    
}

void mergeSort(int* arr, int l, int r){
  // PLACE YOUR CODE HERE.
    int m;
    if(l < r)
    {
        m = floor((l + r) / 2); // find a mid point
        mergeSort(arr, l, m); // sort left array
        mergeSort(arr, m+1, r); // sort right array
        merge(arr, l, m, r); // merge two arrays
    }
}

int main()
{
    int size = 7;
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