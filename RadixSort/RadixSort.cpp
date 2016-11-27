// RadixSort.cpp : Defines the entry point for the console application.
//

//
// C++ Program To Implement Radix Sort
//

#include "stdafx.h"
#include<iostream>
#include <cstdlib>
using namespace std;

// A utility function to print an array
void print(int arr[], int n)
{
	printf("{ ");
	for (int i = 0; i < n; i++)
		printf("%03d, ", arr[i]);
	printf(" }\n");
}

//get maximum value in arr[]
int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}
 
//count sort of arr[]
void countSort(int arr[], int n, int exp)
{
	int output[11] = { 0 };
	int i, count[10] = { 0 };
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	printf("counting value mod %04d ", exp);
	print(count, 10);

	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;		
	}
	for (i = 0; i < n; i++)
	{
		arr[i] = output[i];
		printf("Step %02d: ", i+1);
		print(arr, n);
	}
}

// sorts arr[] of size n using Radix Sort
void radixsort(int arr[], int n)
{
	int m = getMax(arr, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		countSort(arr, n, exp);
		printf("Sorted:  ");
		print(arr, n);
		printf("\n");
	}
}

/*
* Main
*/
int main()
{
	printf("Hello World!\n");
	int arr[] = { 783, 99, 472, 182, 264, 543, 356, 295, 692, 491, 94 };
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Before sorting: ");
	print(arr, n);
	printf("\n------------------------------------------------------------------------\n\n");

	radixsort(arr, n);

	printf("\n\n------------------------------------------------------------------------\n");
	printf("After sorting: ");
	print(arr, n);

	printf("\n\nHit any key to terminate.");
	getchar();
	return 0;
}