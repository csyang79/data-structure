#include <iostream>
#include <vector>
#include <climits>
#include <cstddef>
using std::vector;
template <typename T>
class RedBlackTree
{
public:
	explicit RedBlackTree(const T& negInf = INT_MIN);
	//RedBlackTree(const RedBlackTree& rhs);
	~RedBlackTree()
	{
		makeEmpty();
	}

	const T& findMin() const;
	const T& findMax() const;
	bool contains(const T& x) const;
	bool isEmpty() const
	{
		return header->right == nullNode;
	}
	void printTree() const
	{
		if (header->right == nullNode)
			std::cout << "Empty tree" << std::endl;
		else
			printTree(header->right);
	}

	void makeEmpty()
	{
		while (header->right != nullNode)
			erase(header->right->element);
	}
	void insert(const T& x);
	void erase(const T& x);
	void remove(const T& x);
	enum { RED, BLACK };
	//RedBlackTree & operator=(const RedBlackTree & rhs);

private:
	struct RedBlackNode
	{
		T element;
		RedBlackNode * left;
		RedBlackNode * right;
		int color;
		RedBlackNode(const T& theElement = T{}, RedBlackNode *lt = nullptr, RedBlackNode * rt = nullptr, int c = BLACK) :
			element(theElement), left(lt), right(rt), color(c) { }
		RedBlackNode *& child(int t)
		{
			return t == 0 ? left : right;
		}
	};
	RedBlackNode *header;	//头结点
	RedBlackNode *nullNode;	//叶子

	//用于insert例程
	RedBlackNode *current;
	RedBlackNode *parent;
	RedBlackNode *grand;
	RedBlackNode *great;
	RedBlackNode *sibling;
	
	void reclainMemory(RedBlackNode *t);
	void printTree(RedBlackNode *t) const
	{
		if (t != t->left)
		{
			printTree(t->left);
			std::cout << t->element << std::endl;
			printTree(t->right);
		}
	}
	bool isRed(RedBlackNode* node)
	{
		return node->color == RED;
	}
	//RedBlackNode *clone(RedBlackNode *t) const;

	void handleDoubleRed(const T& item);
	RedBlackNode *rotate(const T& item, RedBlackNode *theParent);
	RedBlackNode* rotateWithLeftChild(RedBlackNode *& k2);
	RedBlackNode* rotateWithRightChild(RedBlackNode *& k1);

	RedBlackNode* doubleRotate(RedBlackNode *& r, bool LR, bool recolor);
	RedBlackNode* singleRotate(RedBlackNode *& r, bool LR, bool recolor);
};
template <typename T>
RedBlackTree<T>::RedBlackTree(const T& negInf)
{
	nullNode = new RedBlackNode;
	nullNode->left = nullNode->right = nullNode;

	header = new RedBlackNode(negInf);
	header->left = header->right = nullNode;
}

template <typename T>
auto RedBlackTree<T>::rotate(const T& item, RedBlackNode *theParent)->RedBlackNode*
{
	if (item < theParent->element)
	{
		item < theParent->left->element ? rotateWithLeftChild(theParent->left) : rotateWithRightChild(theParent->left);
		return theParent->left;
	}
	else
	{
		item < theParent->right->element ? rotateWithLeftChild(theParent->right) : rotateWithRightChild(theParent->right);
		return theParent->right;
	}
}

template <typename T>
auto RedBlackTree<T>::rotateWithLeftChild(RedBlackNode *& r)->RedBlackNode*
{
	RedBlackNode* q = r->left;
	r->left = q->right;
	q->right = r;
	q = r;
	return q;
}
template <typename T>
auto RedBlackTree<T>::rotateWithRightChild(RedBlackNode *& r)->RedBlackNode*
{
	RedBlackNode* q = r->right;
	r->right = q->left;
	q->left = r;
	q = r;
	return q;
}
template <typename T>
void RedBlackTree<T>::handleDoubleRed(const T& item)
{
	current->color = RED;
	current->left->color = BLACK;
	current->right->color = BLACK;
	if (parent->color == RED)
	{
		grand->color = RED;
		if (item < grand->element != item < parent->element)
			parent = rotate(item, grand);
		current = rotate(item, great);
		current->color = BLACK;
	}
	header->right->color = BLACK;
}

template <typename T>
auto RedBlackTree<T>::doubleRotate(RedBlackNode *& node, bool LR, bool recolor)->RedBlackNode*
{
	parent = node->child(!LR);
	current = parent->child(LR);
	node->child(!LR) = current->child(LR);
	parent->child(LR) = current->child(!LR);
	current->child(LR) = node;
	current->child(!LR) = parent;
	if (recolor)
	{
		node->color = RED;
		current->color = BLACK;
	}
	return current;
}

template <typename T>
auto RedBlackTree<T>::singleRotate(RedBlackNode *& node, bool LL, bool recolor)->RedBlackNode*
{
	current = node->child(!LL);
	node->child(!LL) = current->child(LL);
	current->child(LL) = node;

	if (recolor)
	{
		current->color = BLACK;
		node->color = RED;
	}
	return current;
}
template <typename T>
void RedBlackTree<T>::insert(const T& x)
{
	current = parent = grand = header;
	nullNode->element = x;
	while (current->element != x)
	{
		great = grand; grand = parent; parent = current;
		current = x < current->element ? current->left : current->right;
		if (current->left->color == RED && current->right->color == RED)
			handleDoubleRed(x);
	}
	if (current != nullNode)
		return;
	current = new RedBlackNode(x, nullNode, nullNode);
	if (x < parent->element)
		parent->left = current;
	else
		parent->right = current;
	handleDoubleRed(x);
}
template <typename T>
void RedBlackTree<T>::erase(const T& x)
{
	if (header->right == nullNode)
		return;
	current = parent = header;
	RedBlackNode* sibling = nullptr;
	RedBlackNode *find = nullptr;
	int dir = 1, last;
	if (!isRed(header->right->left) && !isRed(header->right->right))
		header->right->color = RED;
	while (current->child(dir) != nullNode)
	{
		last = dir;
		grand = parent; parent = current;
		current = current->child(dir);
		dir = current->element < x;
		if (current->element == x)
			find = current;
		if (!isRed(current) && !isRed(current->child(dir)))
		{
			if (isRed(current->child(!dir)))
			{
				parent = parent->child(last) = dir == 1 ? rotateWithLeftChild(current) : rotateWithRightChild(current);	
				parent->color = BLACK;
				current->color = RED;
			}
			else
			{
				sibling = parent->child(!last);
				if (sibling != nullNode)
				{
					if (!isRed(sibling->left) && !isRed(sibling->right))
					{
						parent->color = BLACK;
						current->color = RED;
						sibling->color = RED;
					}
					else
					{
						int dir2 = (parent == grand->child(1));
						if (isRed(sibling->child(last)))
							grand->child(dir2) = doubleRotate(parent, last, false);
						else if (isRed(sibling->child(!last)))
							grand->child(dir2) = singleRotate(parent, last, false);
						current->color = grand->child(dir2)->color = RED;
						grand->child(dir2)->child(0)->color = BLACK;
						grand->child(dir2)->child(1)->color = BLACK;
					}
					
				}
			}
		}
	}
	if (find != nullptr)
	{
		find->element = current->element;
		parent->child(current == parent->right) = nullNode;
		delete(current);
	}
	if (header->right != nullNode)
		header->right->color = BLACK;
}

int main()
{
	class RedBlackTree<int> rbTree;
	vector<int> a{ 30, 15, 70, 10, 20, 60, 85, 5, 50, 65, 80, 90, 40, 55 };
	for (int i = 0; i < a.size(); ++i)
		rbTree.insert(a[i]);
	rbTree.printTree();
	return 0;
}
