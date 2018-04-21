#include <iostream>
#include <vector>

using std::vector;

void bubbleSort(vector<int> & nums)
{
	for (int i = 0; i < nums.size(); ++i)
		for (int j = 0; j < nums.size() - i; ++j)
			if (nums[j] > nums[j +1])
				std::swap(nums[j], nums[j + 1]);
}


int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	bubbleSort(nums);
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
