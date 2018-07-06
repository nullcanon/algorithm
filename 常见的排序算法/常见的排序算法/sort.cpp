#include"sort.h"
/**************************************/
//void InsertSort(int* arr, int sz)
//{
//	if (arr == NULL || sz <= 0)
//		return;
//	int i = 0, j = 1;
//	while (j < sz)
//	{
//		int tmp = arr[j];
//		int n = 0;
//		while (i>=0 && arr[i] > tmp)
//		{		
//			arr[j-n] = arr[i];
//			++n;
//			--i;
//		}
//		arr[i + 1] = tmp;
//		i = j;
//		++j;
//	}
//}

void InsertSort(int* arr, int sz)
{
	if (arr == NULL || sz <= 0)
		return;

	//i控制有序组和无序组的分界
	int i = 1, j = 0, tmp = 0;
	for (; i < sz; ++i)
	{
		tmp = arr[i];
		for (j = i; j>0 && arr[j-1] > tmp; --j)
			arr[j] = arr[j - 1];
		arr[j] = tmp;
	}
}

//优化插入排序，在查找部分运用二分查找
void NiceInsertSort(int* arr, int sz)
{
	if (arr == NULL || sz <= 0)
		return;

	int i = 1, tmp = 0;
	for (; i < sz; ++i)
	{
		tmp = arr[i];
		int left = 0, right = i - 1;
		int mid = 0, k = 0;
		while (left <= right)
		{
			mid = right + ((left - right) >> 1);
			if (arr[mid] > tmp)
			{
				right = mid - 1;
				k = mid;
			}
			else
			{
				left = mid + 1;
				k = mid + 1;
			}
		}
		for (int j = i; j > k; j--)
			arr[j] = arr[j - 1];
		arr[k] = tmp;
	}
}

/**************************************/
//可优化为在遍历的时候即找最大的又找最小的
void SelectSort(int* arr, int sz)
{
	if (arr == NULL || sz <= 0)
		return;

	for (int j = 0; j < sz-1; ++j)
	{
		int min = arr[j];
		int n = -1;
		for (int i = j+1; i < sz; ++i)
		{
			if (arr[i] < min)
			{
				min = arr[i];
				n = i;
			}
		}
		if (n>-1)
		{
			arr[n] = arr[j];
			arr[j] = min;
		}
	}
}
/**************************************/

static void Adjust(int* arr,int sz,int root)
{
	int parent = root;
	int child = (parent << 1) + 1;
	while (child < sz)
	{
		//默认左孩子是最大的
		if (child+1 < sz && arr[child] < arr[child + 1])
			child++;
		if (arr[parent] < arr[child])
		{
			swap(arr[parent], arr[child]);
			parent = child;
			child = (parent << 1) + 1;
		}
		else
			break;
	}

}
void HeapSort(int* arr, int sz)
{
	if (arr == NULL || sz <= 0)
		return;
	int root = ((sz - 2) >> 1);
	for (int i = root; i >= 0; --i)
		Adjust(arr,sz,i);

	for (int j = sz-1; j >0; --j)
	{
		swap(arr[0], arr[j]);
		Adjust(arr,j,0);
	}
}


/**************************************/

void ShellSort(int* arr, int sz)
{
	if (arr == NULL || sz <= 0)
		return;

	int gap = sz;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		int i = gap, j = 0, tmp = 0;
		for (; i < sz; ++i)
		{
			tmp = arr[i];
			for (j = i - gap; j>=0 && arr[j] > tmp; j -= gap)
				arr[j + gap] = arr[j];
			arr[j + gap] = tmp;
		}
	}
}

/**************************************/

//交换法
static int partition(int* arr, int left, int right)
{
	int begin = left, end = right;
	
	int k = arr[end];
	
	while (begin < end)
	{
		while (begin<end && arr[begin] <= k)
			begin++;
		while (begin<end && arr[end] >= k)
			end--;
		if (begin<end)
			swap(arr[begin], arr[end]);
	
	}
	if (begin!=right)
		swap(arr[begin], arr[right]);
	return begin;
}

//填坑法
static int partition1(int* arr, int begin, int end)
{
	int left = begin, right = end;
	int k = arr[end];
	while (left<right)
	{
		while (left < right && arr[left] <= k)
			left++;
		if (left < right)
			arr[right--] = arr[left];
		while (left < right && arr[right] >= k)
			right--;
		if (left < right)
			arr[left++] = arr[right];
	}
	arr[left] = k;
	return left;
}

//前后指针法，可改进为链表排序
static int partition2(int* arr, int begin, int end)
{
	int pre = begin-1, cur = begin;
	int k = arr[end];
	while (cur<end)
	{
		if (arr[cur] < k)
		{
			pre++;

			if (pre != cur)
				swap(arr[pre], arr[cur]);
		}
		cur++;
	}
	swap(arr[pre+1], arr[cur]);
	return pre+1;
}

void QuickSort(int* arr, int begin,int end)
{
	if (begin<end)
	{
		int mid = partition2(arr,begin,end);
		QuickSort(arr, begin, mid-1);
		QuickSort(arr ,mid+1,end);
	}
}

#include<stack>
void QuickSortNor(int*arr, int begin, int end)
{
	stack<int> s;
	s.push(end);
	s.push(0);
	while (!s.empty())
	{
		begin = s.top();
		s.pop();
		end = s.top();
		s.pop();
		
		if (begin<end)
		{
			int mid = partition(arr, begin, end);
			s.push(end);
			s.push(mid+1);
			s.push(mid - 1);
			s.push(begin);
		}
	}
}

/**************************************/
static void MergeArr(int* arr,int begin,int mid,int end,int* tmp)
{
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] <= arr[begin2])
			tmp[i++] = arr[begin1++];
		else
			tmp[i++] = arr[begin2++];
	}
	while (begin1 <= end1)
		tmp[i++] = arr[begin1++];
	while (begin2 <= end2)
		tmp[i++] = arr[begin2++];
	while (begin <= end)
		arr[begin] = tmp[begin++];
}

static void MergeSort(int* arr,int begin,int end,int* tmp)
{
	if (begin < end)
	{
		int mid = begin + ((end - begin) >> 1);
		MergeSort(arr, begin, mid, tmp);
		MergeSort(arr, mid + 1, end, tmp);
		MergeArr(arr, begin, mid, end, tmp);	
	}
}

void MergeSort(int* arr, int sz)
{
	int* tmp = new int[sz];
	MergeSort(arr, 0, sz - 1, tmp);
	
	delete[] tmp;
}

//归并排序非递归
//按照递归程序执行的思路来
//void MergeSortNor(int*arr ,int sz)
//{
//	int* tmp = new int[sz];
//	int gap = 1;
//	while (1)
//	{
//		for (int i = 0; i < sz; i+=(gap<<1))
//		{
//			int mid = i + ((i+gap - i) >> 1);
//
//			int n = i+gap*2-1;	
//
//			if (n >= sz)
//			{
//				mid = i-1;
//				n = sz - 1;
//				MergeArr(arr, 0, mid, n, tmp);
//				return;
//			}		
//			MergeArr(arr, i, mid, n, tmp);
//		}
//		gap <<= 1;
//	
//	}
//	delete[] tmp;
//}

/**************************************/

void CountSort(int* arr, int sz)
{
	//找最大值和最小值
	int min = arr[0], max = arr[0];
	for (int i = 0; i < sz; ++i)
	{
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}

	//统计
	int tmpSize = max - min + 1;
	int* tmp = new int[tmpSize];
	memset(tmp, 0, sizeof(int)*tmpSize);
	for (int i = 0; i < sz; ++i)	
	{
		tmp[arr[i]-min]++;
	}

	//回收
	int idx = 0;
	for (int i = 0; i < tmpSize; ++i)
	{
		while (tmp[i]--)
			arr[idx++] = i + min;
	}
	delete[] tmp;
}

/**************************************/
//统计最大数量级
static int CountDigit(int* arr, int sz)
{
	int digit = 1;
	int base = 10;
	for (int i = 0; i < sz; ++i)
	{
		while (arr[i] >= base)
		{
			digit++;
			base *= 10;
		}
	}
	return digit;
}

void BaseSort(int* arr, int sz)
{
	int digit = CountDigit(arr, sz);
	int base = 1;
	int* tmp = new int[sz];
	while (digit--)
	{
		//把个（十...）位相同的数放到一个桶中
		int count[10] = { 0 };
		for (int i = 0; i < sz; ++i)
			count[arr[i] / base % 10]++;
		
		//根据个..位排序
		//	1.统计个..位数相同的在arr中的起始位置
		int start[10] = { 0 };
		for (int i = 1; i < 10; ++i)
			start[i] = start[i - 1] + count[i - 1];
		memset(tmp, 0, sizeof(int)*sz);
		
		//	2.按个..位顺序放到tmp数组中
		for (int i = 0; i < sz; ++i)
			tmp[start[arr[i] / base % 10]++] = arr[i];
		base *= 10;

		//拷回arr
		for (int i = 0; i < sz; ++i)
			arr[i] = tmp[i];
	}
	delete[] tmp;
}