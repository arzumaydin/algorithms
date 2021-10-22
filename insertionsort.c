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

void insertionSort(int* arr, int size)
{
    int key = 0, j = 0; 
    for(int i = 1; i < size; i++) // divide array to two as sorted and unsorted
    {
        j = i - 1;
        key = *(arr + i); // choose an index as a key value
        while(j >= 0 && *(arr + j) > key) // if value on the left hand side of key is bigger than key, enter the loop
        {
            *(arr + j + 1) = *(arr + j); // swap elements
            j--; // iterate through all the values on the left of the key value
        }
        *(arr + j + 1) = key; // after swap operations change the key as the next number on the unsorted array
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

    insertionSort(arr, size); // call function

    printf("Sorted array: ");

    for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
    printf("\n");

    return 0;
}