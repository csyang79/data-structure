#include <functional>
#include <iostream>
#include <vector>
using std::less;
using std::vector;

void insertionSort(vector<int> & nums);
void insertionSort(vector<int> & nums, int i, int j);

template <typename Iterator, typename Comperator>
void insertionSort(const Iterator& begin, const Iterator& end, \
					Comperator lessThan);
template <typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end);

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

template <typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end)
{
	insertionSort(begin, end, less<decltype(*begin)>{});
}

template <typename Iterator, typename Comperator>
void insertionSort(const Iterator& begin, const Iterator& end, \
					Comperator lessThan)
{
	if (begin == end)
		return;
	Iterator j;
	for (Iterator p = begin + 1; p != end; ++p)
	{
		auto tmp = std::move(*p);
		for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
			*j = std::move(*(j - 1));
		*j = std::move(tmp);
	}
}


int main()
{
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 8 };
	insertionSort(nums.begin(), nums.end());
	for (int num : nums)
		std::cout << num << std::endl;
	return 0;
}
