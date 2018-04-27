#include <iostream>
#include <vector>
using std::vector;

int lower_bound(vector<int>& nums, int target)
{
	int left = 0, right = nums.size();
	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] >= target)
			right = mid;
		else
			left = mid + 1;
	}
	return left;
}

int main()
{
	vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 9, 9, 10};
	std::cout << lower_bound(nums, 9) << std::endl;
	return 0;
}

