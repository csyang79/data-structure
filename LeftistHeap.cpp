#include <iostream>
#include <vector>
#include <queue>
using std::queue;
using std::vector;
template <typename T>
class LeftistHeap
{
public:
	LeftistHeap() : root(nullptr) { }
	LeftistHeap(const LeftistHeap & rhs);
	
	~LeftistHeap();
	LeftistHeap & operator=(const LeftistHeap & rhs);

	bool empty() const;
	const T& findMin() const;
	void print() const;

	void insert(const T& x);
	void deleteMin();
	void deleteMin(T& minItem);
	void makeEmpty();
	void merge(LeftistHeap & rhs);
private:
	struct LeftistNode
	{
		T element;
		LeftistNode * left;
		LeftistNode * right;
		int npl;
		LeftistNode(const T& e, LeftistNode * lt = nullptr, LeftistNode * rt = nullptr,\
 int np = 0) : element(e), left(lt), right(rt), npl(np) { }
	};
	LeftistNode * root;
	LeftistNode * merge(LeftistNode * h1, LeftistNode * h2);
	LeftistNode * merge1(LeftistNode * h1, LeftistNode * h2);
	void swapChildren(LeftistNode * t);
	void reclaimMemory(LeftistNode * t);
	LeftistNode * clone(LeftistNode * t) const;
};

template <typename T>
void LeftistHeap<T>::print() const
{
	if (!root)
		return;
	queue<LeftistNode*> q;
	LeftistNode * x;
	q.push(root);
	while (!q.empty())
	{
		x = q.front();
		q.pop();
		std::cout << x->element;
		if (x->left)
			q.push(x->left);	
		if (x->right)
			q.push(x->right);
	}
}
template <typename T>
bool LeftistHeap<T>::empty() const 
{
	return root == nullptr;
}
template <typename T>
void LeftistHeap<T>::merge(LeftistHeap & rhs)
{
	if (this = &rhs)
		return;
	root = merge(root, rhs.root);
	rhs.root = nullptr;
}
template <typename T>
auto LeftistHeap<T>::merge(LeftistNode * h1, LeftistNode * h2)->LeftistNode *
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
LeftistHeap<T>::~LeftistHeap()
{	
	makeEmpty();
}
template <typename T>
auto LeftistHeap<T>::merge1(LeftistNode * h1, LeftistNode * h2)->LeftistNode *
{
	if (h1->left == nullptr)
		h1->left = h2;
	else
	{
		h1->right = merge(h1->right, h2);
		if (h1->left->npl < h1->right->npl)
			std::swap(h1->left, h1->right);
		h1->npl = h1->right->npl + 1;
	}
	return h1;
}
template <typename T>
void LeftistHeap<T>::insert(const T& x)
{
	root = merge(new LeftistNode(x), root);
}

template <typename T>
void LeftistHeap<T>::deleteMin()
{
	if (empty())
		return;
	LeftistNode * oldRoot = root;
	root = merge(root->left, root->right);
	delete oldRoot;
}

template <typename T>
void LeftistHeap<T>::deleteMin(T& minItem)
{
	minItem = findMin();
	deleteMin();
}

template <typename T>
const T& LeftistHeap<T>::findMin() const
{	
	return root ? root->element : T();	
}

template <typename T>
void LeftistHeap<T>::makeEmpty()
{
	while (root)
		deleteMin();
}
int main()
{
	vector<int> nums{2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
	class LeftistHeap<int> heap;
	for (int i = 0; i < nums.size(); ++i)
		heap.insert(nums[i]);
	heap.print();
	return 0;
}
