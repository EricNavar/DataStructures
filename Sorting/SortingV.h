#pragma once
#include <vector>
using namespace std;

//ok so like T can be anything
//it can be int or string or unsigned int
template<typename T>
void heapSort(vector<T>& v);
template<typename T>
void mergeSort(vector<T>& v);
template<typename T>
void shellSort(vector<T>& v);
template<typename T>
void bubbleSort(vector<T>& v);

//helper functions
template<typename T>
void heapify(vector<T>& v, int index, int n);
template<typename T>
void merge(vector<T>& v, unsigned int left, unsigned int middle, unsigned int right);
template<typename T>
void mergeSortHelper(vector<T>& v, unsigned int left, unsigned int right);

//referenced implementation on Geeks for Geeks
//https://www.geeksforgeeks.org/heap-sort/
template<typename T>
void heapSort(vector<T>& v)
{
	unsigned int n = v.size();
	if (!n)
		return;
	//build heap
	for (int i = n/2 - 1; i >= 0; i--)
		heapify(v, i, n);
	//create max heap
	//switch first and last elements and call heapify on the new root
	do
	{
		n--;
		swap(v[0], v[n]);
		heapify(v, 0, n);
	}
	while (n)
}

template<typename T>
void heapify(vector<T>& v, int index, unsigned int n)
{
	//find the largest out of the value at index, its left child, and its right child
	unsigned int max_index = index;
	unsigned int left = 2 * index + 1;
	unsigned int right = 2 * index + 2;

	if (left < n && v[left] > v[max_index])
		max_index = left;

	if (right < n && v[right] > v[max_index])
		max_index = right;

	//if max_index is not root
	if (max_index != index)
	{
		swap(v[index], v[max_index]);
		//recursively heapify the affected sub-tree
		heapify(v, max_index, n);
	}
}

template<typename T>
void mergeSort(vector<T>& v)
{
	mergeSortHelper(v, 0, v.size() - 1);
}

//referenced implementation on Geeks for Geeks
//https://www.geeksforgeeks.org/merge-sort/
//left and right are for the leftmost and rightmost 
//indices of thesubarray to be sorted
template<typename T>
void mergeSortHelper(vector<T> & v, unsigned int left, unsigned int right)
{
	if (left < right)
	{
		unsigned int middle = (right + left) / 2;
		//Sort first then second halves
		mergeSortHelper(v, left, middle);
		mergeSortHelper(v, middle + 1, right);
		merge(v, left, middle, right);
	}
}

//i'm sorry for using so much unsigned. it made debuggy mode easy.
//also i'm not mixing types so it's ok.
template<typename T>
void merge(vector<T>& v, unsigned int left, unsigned int middle, unsigned int right)
{
	unsigned int sizeL = middle - left + 1;
	unsigned int sizeR = right - middle;
	vector<T> leftV(sizeL);
	vector<T> rightV(sizeR);

	//create the subarrays by copying from v
	unsigned int i;
	for (i = 0; i < sizeL; i++)
		leftV[i] = v[left+i];
	for (i = 0; i < sizeR; i++)
		rightV[i] = v[middle+1+i];

	//Merge the temp arrays back into v

	//indices of leftV, rightV, and v
	unsigned int indexL = 0, indexR = 0, indexM = left; // Initial index of merged subarray
	while (indexL < sizeL && indexR < sizeR)
	{
		if (leftV[indexL] <= rightV[indexR])
			v[indexM] = leftV[indexL++];
		else
			v[indexM] = rightV[indexR++];
		indexM++;
	}

	//if leftV has any remaining values, copy them into v
	while (indexL < sizeL)
		v[indexM++] = leftV[indexL++];

	//if rightV has any remaining values, copy them into v
	while (indexR < sizeR)
		v[indexM++] = rightV[indexR++];
}

template<typename T>
void shellSort(vector<T>& v)
{
	unsigned int n = v.size();
	unsigned int gap = n/2;
	while (gap > 0)
	{
		//Insert this element where it belongs in its subarray.
		for (unsigned int i = gap; i < n; i++)
		{
			unsigned int temp = v[i];
			unsigned int j;
			for (j = i; j >= gap && v[j-gap] > temp; j-=gap)
				v[j] = v[j-gap];
			v[j] = temp;
		}
		if (gap == 2)
			gap = 1;
		else
			gap /= 2.2;
	}
}

//https://www.geeksforgeeks.org/bubble-sort/
template<typename T>
void bubbleSort(vector<T>& v)  
{
    int n = v.size();
	for (int i = 0; i < n-1; i++)
		//Last i elements are already in place
		for (int j = 0; j < n-i-1; j++)
			if (v[j] > v[j+1])
				swap(v[j], v[j+1]);
}

//https://www.geeksforgeeks.org/quick-sort/
//The main function that implements QuickSort  
//v[] --> Vector to be sorted,  
//low --> Starting index,  
//high --> Ending index */
template<typename T>
void quickSort(vector<T>& v, int low, int high)  
{
    if (low < high)  
    {
        //pi is partitioning index,
        //v[p] is now at right place
        int pi = partition(v, low, high);
  
        //Separately sort elements before  
        //partition and after partition  
        quickSort(v, low, pi - 1);  
        quickSort(v, pi + 1, high);  
    }
}


template<typename T>
int partition (vector<T>& v, int low, int high)
{
    int pivot = v[high]; // pivot
    int i = (low - 1); // Index of smaller element
  
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (v[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}