#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define size 10

int main()
{
	int arr[size];

	printf("Enter elements of the array: ");
	for(int i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}
	int type = 0;
	printf("Enter 1 for ascending or 2 for descending: ");
	scanf("%d", &type);

	int count = size;
	int x = 0;

	while(x != count)
	{
		for(int i = 0; i < count - 1; i++)
		{
			if(type == 1 && arr[i] > arr[i + 1])
			{
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
			else if(type == 2 && arr[i] < arr[i + 1])
			{
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
		count--;
	}

	printf("Sorted array: ");

	for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return EXIT_SUCCESS;
}