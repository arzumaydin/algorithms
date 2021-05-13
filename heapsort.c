#include <stdio.h>
#include <stdlib.h>

// recursive function to heapify array - e.g: [4, 3, 10, 5, 1]
void heapify(int arr[], int size, int index) 
{
    int largest_index = index; // largest number's index
    int left_index = 2 * index + 1; // left child of root
    int right_index = 2 * index + 2; // right child of root

    if(left_index < size && arr[left_index] > arr[largest_index]) // set left child as root
    {
        largest_index = left_index;
    }
    if(right_index < size && arr[right_index] > arr[largest_index])
    {
        largest_index = right_index;
    }
    if(largest_index != index)
    {
        int temp = arr[index];
        arr[index] = arr[largest_index];
        arr[largest_index] = temp;

        heapify(arr, size, largest_index);
    }
}

void heapSort(int arr[], int size)
{
    for(int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }
    
    for(int i = size - 1; i > 0; i--)
    {
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;

        heapify(arr, i, 0);
    }
}

int main()
{
    int size = 20;
    int arr[size];

	printf("Enter elements of the array: ");
	for(int i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}

    heapSort(arr, size);
    printf("Sorted array: ");

    for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
    printf("\n");

    return EXIT_SUCCESS;
}