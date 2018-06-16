#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;


template <class RandomAccessIterator, class T>
RandomAccessIterator partation(RandomAccessIterator first, \
			RandomAccessIterator last, \
			T pivot);
template <class RandomAccessIterator>

void quickSort(RandomAccessIterator first,
		RandomAccessIterator last)
{
	if (first + 1 < last)
	{
		RandomAccessIterator cut = partation(first, last, *first);
		quickSort(first, cut);
		quickSort(cut + 1, last);		//若为cut则栈溢出，最坏为元素全相同
	}
}

template <class RandomAccessIterator, class T>
RandomAccessIterator partation(RandomAccessIterator first,
			RandomAccessIterator last,
			T pivot)
{
	while (1)
	{
		while (*first < pivot)
			++first;
		--last;
		while (pivot < *last)
			--last;
		if (!(first < last))
			return first;
		std::swap(*first, *last);
		++first;
	}
}

int main()
{
	vector<int> nums = { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	quickSort(nums.begin(), nums.end());
	for (int num : nums)
		cout << num << " ";
	cout << endl;
	return 0;
}
