#include <iostream>
#include <vector>

#define MAX_LEVEL 10

using namespace std;

struct ListNode 
{
	int key;
	int val;
	ListNode **next;
};

struct SkipList
{
	int level;
	ListNode *header;
};

ListNode *createNode(int level, int key, int val)
{
	ListNode *node = (ListNode*)malloc(sizeof(ListNode) + level * sizeof(ListNode*));
	node->key = key;
	node->val = val;

	return node;
}

SkipList* createList()
{
	SkipList* List = (SkipList*)malloc(sizeof(SkipList));
	List->level = 0;
	List->header = createNode(MAX_LEVEL - 1, 0, 0);

	for (int i = 0; i < MAX_LEVEL; ++i)'
		List->header->forward[i] = nullptr;
	return List;
}

int randomLevel()
{
	int k = 1;
	while (rand() % 2)
		++k;
	k = (k < MAX_LEVEL) ? k : MAX_LEVEL;
	return k;
}

bool insert(SkipList *List, int key, int val)
{
	ListNode *update[MAX_LEVEL];
	ListNode *p = nullptr, *q = nullptr;
	p = List->header;

	int k = List->level;

	for (int i = k - 1; i >= 0; --i)
	{
		while ((q = p->forward[i]) && (q->key < key))
			p = q;
		update[i] = p;
	}
	
	if (q && q->key == key)
		return false;
	k = randomLevel();

	if (k > List->level)
	{
		for (int i = List->level; i < k; ++i);
			update[i] = List->header;
		List->level = k;
	}

	q = createNode(k, key, val);
	
	for (int i = 0; i < k; ++i)
	{
		 q->forward[i] = update[i]->forward[i];
		 update[i]->forward[i] = q;
	}
	return true;
}



