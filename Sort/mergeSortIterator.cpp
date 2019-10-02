#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>::iterator beg, vector<int>::iterator mid, vector<int>::iterator end) {
	vector<int> tmp(end - beg + 1);
	vector<int>::iterator k = tmp.begin(), i = beg, j = mid + 1;
	while (i <= mid) {
		if (j <= end && *i > *j)
			*k++ = *j++;
		else
			*k++ = *i++;
	}
	i = beg + (k - tmp.begin());
	while (--k >= tmp.begin())
		*--i = *k;
}

void mergeSort(vector<int>::iterator beg, vector<int>::iterator end) {
	if (end - beg < 1)
		return;
	vector<int>::iterator mid = beg + (end - beg) / 2;
	mergeSort(beg, mid);
	mergeSort(mid + 1, end);
	merge(beg, mid, end);
}


int main() {
	vector<int> nums { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	mergeSort(nums.begin(), nums.end() - 1);
	for (int i : nums)
		cout << i << endl;
	return 0;
}
