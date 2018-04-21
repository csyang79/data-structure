#include <iostream>
#include <vector>
using std::vector;

void mergeSort(vector<int>& nums);
void mergeSort(vector<int>& nums, int start, int end, vector<int>& tmp);
void merge(vector<int>& nums, int start, int mid, int end, vector<int>& tmp);

void mergeSort(vector<int>& nums)
{
	vector<int> tmp(nums.size());
	mergeSort(nums, 0, nums.size() - 1, tmp);
}

void mergeSort(vector<int>& nums, int start, int end, vector<int>& tmp)
{
	if (start < end)
	{
		int mid = start + ((end - start) >> 1);
		mergeSort(nums, start, mid, tmp);
		mergeSort(nums, mid + 1, end, tmp);
		merge(nums, start, mid, end, tmp);
	}
}

void merge1(vector<int>& nums, int start, int mid, int end, vector<int>& tmp)
{
	int i = mid, j = end, k = end;
	while (i >= start || j > mid)
	{
		if (i < start || (j > mid && nums[i] < nums[j]))
			tmp[k--] = nums[j--];
		else
			tmp[k--] = nums[i--];
	}
	for (int i = start; i <= end; ++i)
		nums[i] = tmp[i];
}

void merge(vector<int>& nums, int start, int mid, int end, vector<int>& tmp)
{
	int i = start, j = mid + 1, k = start;
	while (i <= mid)
	{
		if (j <= end && nums[i] > nums[j])
			tmp[k++] = nums[j++];
		else
			tmp[k++] = nums[i++];
	}
	for (--k; k >= start; --k)
		nums[k] = tmp[k];
}
int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	mergeSort(nums);	
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
