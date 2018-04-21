#include <iostream>
#include <vector>
using std::vector;

void selectSort(vector<int> & nums)
{
	for (int i = nums.size(), idx; i > 0; --i)
	{
		idx = 0;
		for (int j = 1; j < i; ++j)
			if (nums[j] > nums[idx])
				idx = j;
		std::swap(nums[i - 1], nums[idx]);
	}
}

int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	selectSort(nums);
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
