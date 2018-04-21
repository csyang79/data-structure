#include <iostream>
#include <vector>
//note : don't call non-const member function in const member function(eg: if size() is non-const,
// error occured in printHeap) 
using std::vector;
template <typename T>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100) : array(capacity), currentSize(0) { } 
	explicit BinaryHeap(const vector<T>& items);
	
	int size() const
	{
		return currentSize;
	}
	bool empty() const
	{ return size() == 0; }
	const T& findMin() const
	{ return empty() ? -2147483648 : array[1]; }
	void insert(const T& x);
	void deleteMin();
	void deleteMin(T& minItem);
	void makeEmpty()
	{ currentSize = 0; }
	void printHeap() const;
private:
	int currentSize;
	vector<T> array;
	void buildHeap();
	void percolateDown(int hole);
};
template <typename T>
void BinaryHeap<T>::insert(const T& x)
{
	if (currentSize == array.size() - 1)
		array.resize(array.size() * 2);
	int hole = ++currentSize;
	T copy = x;
	array[0] = std::move(copy);
	for (; x < array[hole / 2]; hole /= 2)
		array[hole] = std::move(array[hole / 2]);
	array[hole] = std::move(array[0]);
}
template <typename T>
void BinaryHeap<T>::deleteMin()
{
	if (empty())
		return;
	array[1] = std::move(array[currentSize--]);
	//note: for buildin type, argument dependent lookup(ADL) is not performed
	BinaryHeap<T>::percolateDown(1);
	//percolateDown(1);
}
template <typename T>
void BinaryHeap<T>::deleteMin(T& minItem)
{
	if (empty())
		return;
	minItem = std::move(array[1]);
	array[1] = std::move(array[currentSize--]);
	percolateDown(1);
}
template <typename T>
void BinaryHeap<T>::percolateDown(int hole)
{
	int child;
	T tmp = std::move(array[hole]);
	for (child = hole * 2; hole * 2 <= currentSize; hole = child, child = 2 * hole)
	{
		if (child != currentSize && array[child + 1] < array[child])	
			++child;
		if (array[child] < tmp)
			array[hole] = std::move(array[child]);
		else
			break;
	}
	array[hole] = std::move(tmp);
}
template <typename T>
BinaryHeap<T>::BinaryHeap(const vector<T>& items) : array(items.size() + 10), \
	currentSize(items.size())
{
	for (int i = 0; i < items.size(); ++i)
		array[i + 1] = items[i];
	buildHeap();
}
template <typename T>
void BinaryHeap<T>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; --i)
		BinaryHeap<T>::percolateDown(i);
}
template <typename T>
void BinaryHeap<T>::printHeap() const
{
	for (int i = 1; i <= size(); ++i)
		std::cout << array[i] << std::endl;
}
int main()
{
	vector<int> nums{ 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	class BinaryHeap<int> heap(nums);
	heap.deleteMin();
	heap.printHeap();
	return 0;
}
