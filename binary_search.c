#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define size 20

bool binary_search(int arr[], int lower, int upper, int data) //recursive
{
	int mid = (lower + upper) /2;
	while(lower < upper)
	{
		if(arr[mid] == data)
		{
			printf("Data found in database in spot %d.\n", mid+1);
			return true;
		}
		else if(data > arr[mid])
		{
			lower = mid + 1;
			mid = (lower + upper) / 2;
			return binary_search(arr, lower, upper, data);
		}
		else if(data < arr[mid])
		{
			upper = mid - 1;
			mid = (lower + upper) / 2;
			return binary_search(arr, lower, upper, data);
		}
	}

	printf("Data not found in database.\n");
	return false;
}

int main()
{
	srand(time(NULL));

	int arr[size] = {2,3,5,7,8,9,11,14,19,21,24,28,32,34,37,41,45,53,57,65};

	printf("Array: ");
	
	for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	int data = 0;
	printf("Enter number to be searched: ");
	scanf("%d", &data);

	binary_search(arr, 0, size - 1, data);

	return EXIT_SUCCESS;
}