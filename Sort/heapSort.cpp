#include <iostream>
#include <vector>
using std::vector;

void heapSort(vector<int>& nums);
void percolateDown(vector<int>& nums, int i, int n);

void heapSort(vector<int>& nums)
{
	for (int i = (nums.size() - 1) / 2 - 1; i >= 0; --i)
		percolateDown(nums, i, nums.size());
	for (int j = nums.size() - 1; j > 0; --j)
	{
		std::swap(nums[0], nums[j]);
		percolateDown(nums, 0, j);
	}
}

void percolateDown(vector<int>& nums, int i, int n)
{
	int t = std::move(nums[i]);
	int child;
	for (; (child = i * 2 + 1) < n; i = child)
	{
		if (child != n - 1 && nums[child + 1] > nums[child])
			++child;
		if (nums[child] > t)
			nums[i] = std::move(nums[child]);
		else
			break;
	}
	nums[i] = std::move(t);
}

int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 8 };
	heapSort(nums);
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
