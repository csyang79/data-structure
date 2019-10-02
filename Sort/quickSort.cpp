#include <iostream>
#include <vector>
using std::vector;

void quickSort(vector<int>& nums, int left, int right);
void quickSort(vector<int>& nums);
int partation(vector<int>& nums, int left, int right);


int partation(vector<int>& nums, int left, int right)
{
	int t = nums[right], k = left;
	for (int i = left; i < right; ++i)
		if (nums[i] < t)
			std::swap(nums[i], nums[k++]);
	std::swap(nums[k], nums[right]);
	return k;
}

void quickSort(vector<int>& nums, int left, int right)
{
	if (left < right)
	{
		int pivot = partation(nums, left, right);
		quickSort(nums, left, pivot - 1);
		quickSort(nums, pivot + 1, right);
	}
}
void quickSort(vector<int>& nums)
{
	quickSort(nums, 0, nums.size() - 1);
}

int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	quickSort(nums);
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
