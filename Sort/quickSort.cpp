#include <iostream>
#include <vector>
using std::vector;

int median3(vector<int> & nums, int start, int end);
void insertionSort(vector<int>& nums, int left, int right);
void quickSort(vector<int> & nums);
void quickSort(vector<int> & nums, int start, int end);
void quickSort(vector<int> & nums)
{
	quickSort(nums, 0, nums.size() - 1);
}


void quickSort(vector<int> & nums, int left, int right)
{
	if (left + 10 < right)
	{
		int pivot = median3(nums, left, right);
		int i = left, j = right - 1;
		while (1)
		{
			while (nums[++i] < pivot);
			while (nums[--j] > pivot);
			if (i < j)
				std::swap(nums[i], nums[j]);
		}
		std::swap(nums[right - 1], nums[i]);
		quickSort(nums, left, i - 1);
		quickSort(nums, i + 1, right); 
	}
	else
	{
		insertionSort(nums, left, right);
	}
}
void insertionSort(vector<int>& nums, int left, int right)
{
	for (int i = left + 1; i <= right; ++i)
	{
		int t = std::move(nums[i]);
		int j;
		for (j = i - 1; j >= 0 && nums[j] > t; --j)
			nums[j + 1] = std::move(nums[j]);
		nums[j + 1] = std::move(t);	
	}
}

int median3(vector<int> & nums, int start, int end)
{
	int mid = start + (end - start) >> 1;
	if (nums[start] > nums[mid])
		std::swap(nums[start], nums[mid]);
	if (nums[mid] > nums[end])
		std::swap(nums[mid], nums[end]);
	if (nums[start] > nums[mid])
		std::swap(nums[start], nums[mid]);
	std::swap(nums[mid], nums[end - 1]);
	return nums[end - 1];
}
int main()
{
	vector<int> nums{2, 1, 4, 7 ,4, 8, 3, 6, 4, 8};
	std::cout << nums.size() << std::endl;
	quickSort(nums);
//	insertionSort(nums, 0, nums.size() - 1);
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
