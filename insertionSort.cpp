#include <iostream>
#include <vector>
using std::vector;

void insertionSort(vector<int> & nums);
void insertionSort(vector<int> & nums, int i, int j);

void insertionSort(vector<int> & nums)
{
	insertionSort(nums, 0, nums.size());
}

void insertionSort(vector<int> & nums, int lo, int hi)
{
	for (int i = lo + 1; i != hi; ++i)
	{
		int t = std::move(nums[i]);
		int j;
		for (j = i; j > 0 && nums[j - 1] > t; --j)
			nums[j] = std::move(nums[j - 1]);
		nums[j] = std::move(t);
	}
}

int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 8 };
	insertionSort(nums);
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
