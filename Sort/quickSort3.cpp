template <class RandomAccessIterator, class T>
void quickSort(RandomAccessIterator first,
		RandomAccessIterator last)
{
	if (first != last)
	{
		RandomAccessIterator cut = partation(first, last, *first);
		quickSort(first, cut);
		quickSort(cut, last);
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
		std::swap(first, last);
		++first;
	}
}
