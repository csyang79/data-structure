#include <iostream>
#include <vector>
#include <queue>
using std::queue;
using std::vector;
template <typename T>
class SkewHeap
{
public:
	SkewHeap():root(nullptr) { }
	SkewHeap(const SkewHeap & rhs);
	~SkewHeap()
	{
		makeEmpty();
	} 
	
	bool empty() const
	{
		return root == nullptr;
	}	
	void printPre() const;
	void printLevel() const;
	const T& findMin() const;
	
	void insert(const T& x);
	void deleteMin();
	void makeEmpty();
	void merge(SkewHeap & rhs);

private:
	struct SkewNode
	{
		T element;
		SkewNode * left;
		SkewNode * right;
		SkewNode(const T& e, SkewNode * l = nullptr, SkewNode * r = nullptr) :\
			element(e), left(l), right(r) { } 
	};
	void printPre(SkewNode *) const;
	void printLevel(SkewNode *) const;
	SkewNode * root;
	SkewNode * merge(SkewNode * h1, SkewNode * h2);
	SkewNode * merge1(SkewNode * h1, SkewNode * h2);
	SkewNode * clone(SkewNode * rhs) const;
};

template <typename T>
const T& SkewHeap<T>::findMin() const
{
	return root == nullptr ? T() : root->element;
}
template <typename T>
void SkewHeap<T>::merge(SkewHeap & rhs)
{
	if (this == &rhs)
		return;
	root = merge(root, rhs.root);
}
template <typename T>
auto SkewHeap<T>::merge(SkewNode * h1, SkewNode * h2)->SkewNode *
{
	if (h1 == nullptr)
		return h2;
	if (h2 == nullptr)
		return h1;
	if (h1->element < h2->element)
		return merge1(h1, h2);
	else
		return merge1(h2, h1);	
}

template <typename T>
auto SkewHeap<T>::merge1(SkewNode * h1, SkewNode * h2)->SkewNode *
{
	if (h1->left == nullptr)
		h1->left = h2;
	else
	{
		h1->right = merge(h1->right, h2);
		std::swap(h1->left, h1->right);
	}		
	return h1;
}

template <typename T>
void SkewHeap<T>::makeEmpty()
{
	while (root)
		deleteMin();
}
template <typename T>
void SkewHeap<T>::insert(const T& e)
{
	root = merge(root, new SkewNode(e));
}

template <typename T>
void SkewHeap<T>::deleteMin()
{
	if (root)
	{
		SkewNode * oldRoot = root;
		root = merge(root->left, root->right);
		delete oldRoot;
	}
}

template <typename T>
void SkewHeap<T>::printPre() const
{
	printPre(root);
}

template <typename T>
void SkewHeap<T>::printPre(SkewNode * t) const 
{
	if (!t)
		std::cout << "#";
	else
	{
		std::cout << t->element;
		printPre(t->left);
		printPre(t->right);
	}
}
template <typename T>
void SkewHeap<T>::printLevel() const
{
	printLevel(root);
}

template <typename T>
void SkewHeap<T>::printLevel(SkewNode *t) const
{
	queue<SkewNode*> q;
	q.push(t);
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		if (t)
		{
			q.push(t->left);
			q.push(t->right);
			std::cout << t->element;
		}
		else
			std::cout << "#";
	}
}
int main()
{
	vector<int> nums{2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
	class SkewHeap<int> heap;
	for (int num : nums)
		heap.insert(num);
	heap.printPre();
	std::cout << std::endl;
	heap.printLevel();	
	std::cout << std::endl;
	return 0;
}
