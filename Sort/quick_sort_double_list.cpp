#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
	int val;
	ListNode *prev;
	ListNode *next;

	ListNode(int v, ListNode *p = nullptr,
		ListNode *n = nullptr) : val(v), prev(p), next(n) { }
};


ListNode *partation(ListNode *first, ListNode *last, int pivot)
{
	while (1)
	{
		while (first->val < pivot)
			first = first->next;
		last = last->prev;
		while (pivot < last->val)
			last = last->prev;
		
		if (!(first < last))
			return first;
		
		std::swap(first->val, last->val);
		first = first->next;
	}
}

void quickSort(ListNode *head, ListNode *tail)
{
	if (head == tail || head->next == tail)
		return;
	ListNode *cut = partation(head, tail, head->val);
	quickSort(head, cut);
	quickSort(cut->next, tail);
}

int main()
{
	vector<int> nums = { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	ListNode *head = new ListNode(2);
	ListNode *p = head;
	for (int num : nums)
	{
		p->next = new ListNode(num, p);
		p = p->next;
	}
	p->next = new ListNode(-1, p);
	p = p->next;
	quickSort(head, p);
	while (head != p)
	{
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
	return 0;
}
