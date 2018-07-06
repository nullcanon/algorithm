#include"sort.h"
void TestSort()
{
	//int arr[] = { 25, 49, 25, 16, 8, 21 };
	int arr[] = { 25, 49, 25, 16, 8, 21, 25, 49, 25, 16, 8, 2 };

	int sz = sizeof(arr) / sizeof(arr[0]);
	//InsertSort(arr, sz);
	//NiceInsertSort(arr, sz);
	//SelectSort(arr, sz);
	//HeapSort(arr, sz);
	//ShellSort(arr, sz);
	//QuickSort(arr,0,sz-1);
	//QuickSortNor(arr, 0, sz - 1);
	//MergeSort(arr, sz);
	MergeSortNor(arr, sz);
	//CountSort(arr, sz);
	//BaseSort(arr, sz);

	for (int i = 0; i < sz; ++i)
		cout << arr[i] << " ";
	cout << endl;
}

int main()
{
	TestSort();
	return 0;
}