#include <iostream>
#include <vector>
#include <climits>


using namespace std;

struct ListNode {
	int val;
	ListNode *next;

	ListNode(int v) : val(v), next(nullptr) { }
};

ListNode *merge(ListNode *head1, ListNode *head2);

ListNode *mergeSort(ListNode *head)
{
	if (!head || !head->next)
		return head;
	
	ListNode *p = head;
	ListNode *q = head;
	while (p->next && p->next->next)
	{
		p = p->next->next;
		q = q->next;
	}
	p = q->next;
	q->next = nullptr;
	q = head;

	q = mergeSort(q);
	p = mergeSort(p);
	return merge(p, q);
}

ListNode *merge(ListNode *head1, ListNode *head2)
{
	if (!head2)
		return head1;
	if (!head1)
		return head2;
	ListNode *p = head1;
	ListNode *q = head2;
	ListNode dummy(INT_MIN);
	ListNode *pre = &dummy;
	while (p && q)
	{
		if (p->val < q->val)
		{
			pre->next = p;
			p = p->next;
		}
		else
		{
			pre->next = q;
			q = q->next;
		}
		pre = pre->next;
	}
	if (p)
		pre->next = p;
	else
		pre->next = q;
	return dummy.next;
}


int main()
{
	ListNode *head1 = new ListNode(2);
	ListNode *p = head1;
	vector<int> nums = { 1, 4, 7 , 4, 3, 8, 6, 4, 7};
	for (int num : nums)
	{
		p->next = new ListNode(num);
		p = p->next;
	}
	p = mergeSort(head1);

	while (p)
	{
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
	return 0;
}
