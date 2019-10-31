#pragma once
using namespace std;

//ok so like T can be anything
//it can be int or string or unsigned int
template<typename T>
void heapSort(T* arr, int n);
template<typename T>
void mergeSort(T* arr, int n);
template<typename T>
void shellSort(T* arr, int n);
template<typename T>
void bubbleSort(T* arr, int n);

//helper functions
template<typename T>
void heapify(T* arr, int index, int n);
template<typename T>
void merge(T* arr, unsigned int left, unsigned int middle, unsigned int right);
template<typename T>
void mergeSortHelper(T* arr, unsigned int left, unsigned int right);

//referenced implementation on Geeks for Geeks
//https://www.geeksforgeeks.org/heap-sort/
template<typename T>
void heapSort(T* arr, unsigned int n)
{
	if (!n)
		return;
	//build heap
	for (int i = n/2 - 1; i >= 0; i--)
		heapify(arr, i, n);
	//create max heap
	//switch first and last elements and call heapify on the new root
	while (n)
	{
		n--;
		swap(arr[0], arr[n]);
		heapify(arr, 0, n);
	}
}

template<typename T>
void heapify(T* arr, int index, unsigned int n)
{
	//find the largest out of the value at index, its left child, and its right child
	unsigned int max_index = index;
	unsigned int left = 2 * index + 1;
	unsigned int right = 2 * index + 2;

	if (left < n && arr[left] > arr[max_index])
		max_index = left;

	if (right < n && arr[right] > arr[max_index])
		max_index = right;

	//if max_index is not root
	if (max_index != index)
	{
		swap(arr[index], arr[max_index]);
		//recursively heapify the affected sub-tree
		heapify(arr, max_index, n);
	}
}

template<typename T>
void mergeSort(T* arr, int n)
{
	mergeSortHelper(arr, 0, n);
}

//referenced implementation on Geeks for Geeks
//https://www.geeksforgeeks.org/merge-sort/
//left and right are for the leftmost and rightmost 
//indices of thesubarray to be sorted
template<typename T>
void mergeSortHelper(T* arr, unsigned int left, unsigned int right)
{
	if (left < right)
	{
		unsigned int middle = (right + left) / 2;
		//Sort first then second halves
		mergeSortHelper(arr, left, middle);
		mergeSortHelper(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}

//i'm sorry for using so much unsigned. it made debuggy mode easy.
//also i'm not mixing types so it's ok.
template<typename T>
void merge(T* arr, unsigned int left, unsigned int middle, unsigned int right)
{
	unsigned int sizeL = middle - left + 1;
	unsigned int sizeR = right - middle;
	T* leftArr = new T[sizeL];
	T* rightArr = new T[sizeR];

	//create the subarrays by copying from arr
	unsigned int i;
	for (i = 0; i < sizeL; i++)
		leftArr[i] = arr[left+i];
	for (i = 0; i < sizeR; i++)
		rightArr[i] = arr[middle+1+i];

	//Merge the temp arrays back into arr

	//indices of leftArr, rightArr, and arr
	unsigned int indexL = 0, indexR = 0, indexM = left; // Initial index of merged subarray
	while (indexL < sizeL && indexR < sizeR)
	{
		if (leftArr[indexL] <= rightArr[indexR])
			arr[indexM] = leftArr[indexL++];
		else
			arr[indexM] = rightArr[indexR++];
		indexM++;
	}

	//if leftArr has any remaining values, copy them into arr
	while (indexL < sizeL)
		arr[indexM++] = leftArr[indexL++];

	//if rightArr has any remaining values, copy them into arr
	while (indexR < sizeR)
		arr[indexM++] = rightArr[indexR++];
	delete[] leftArr;
	delete[] rightArr;
}

template<typename T>
void shellSort(T* arr, int n)
{
	unsigned int gap = n/2;
	while (gap > 0)
	{
		//Insert this element where it belongs in its subarray.
		for (unsigned int i = gap; i < n; i++)
		{
			unsigned int temp = arr[i];
			unsigned int j;
			for (j = i; j >= gap && arr[j-gap] > temp; j-=gap)
				arr[j] = arr[j-gap];
			arr[j] = temp;
		}
		if (gap == 2)
			gap = 1;
		else
			gap /= 2.2;
	}
}
//https://www.geeksforgeeks.org/bubble-sort/
template<typename T>
void bubbleSort(T* arr, int n)  
{
	for (int i = 0; i < n-1; i++)
		//Last i elements are already in place
		for (int j = 0; j < n-i-1; j++)
			if (arr[j] > arr[j+1])
				swap(arr[j], arr[j+1]);
}

//https://www.geeksforgeeks.org/quick-sort/
//The main function that implements QuickSort  
//arr[] --> Array to be sorted,  
//low --> Starting index,  
//high --> Ending index */
template<typename T>
void quickSort(T* arr, int low, int high)  
{
    if (low < high)  
    {
        //pi is partitioning index,
        //arr[p] is now at right place
        int pi = partition(arr, low, high);
  
        //Separately sort elements before  
        //partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }
}

template<typename T>
int partition (T* arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element
  
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}