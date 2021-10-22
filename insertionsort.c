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
    for(int i = 1; i < size; i++)
    {
        j = i - 1;
        key = *(arr + i);
        while(j >= 0 && *(arr + j) > key)
        {
            *(arr + j + 1) = *(arr + j);
            j--;
        }
        *(arr + j + 1) = key;
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

    insertionSort(arr, size);

    printf("Sorted array: ");

    for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
    printf("\n");

    return 0;
}