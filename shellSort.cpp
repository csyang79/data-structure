#include <iostream>
#include <vector>
using std::vector;

template <typename T>
void shellSort(vector<T> & nums)
{
	for (int gap = nums.size() >> 1; gap > 0; gap /= 2)
	{
		for (int i = gap; i < nums.size(); ++i)
		{
			T t = std::move(nums[i]);
			int j = i;
			for (; j >= gap && nums[j - gap] > t; j -= gap)
				nums[j] = nums[j - gap];
			nums[j] = std::move(t);
		}
	}
}

int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8 ,3 ,6, 4, 7 };
	shellSort(nums);
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
