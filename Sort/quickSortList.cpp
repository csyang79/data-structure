#include <bits/stdc++.h>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int v = 0, ListNode *n = nullptr) : val(v), next(n) {}
};

ListNode *partation(ListNode *head, ListNode *tail) {
	int t = head->val;
	ListNode *cur = head;
	while (head != tail) {
		if (head->val < t) {
			std::swap(head->val, cur->val);
			cur = cur->next;
		}
		head = head->next;
	}
	std::swap(cur->val, t);
	return cur;
}

void quickSortList(ListNode *head, ListNode *tail) {
	if (head == tail || head->next == tail)
		return;
	ListNode *k = partation(head, tail);
	quickSortList(head, k);
	quickSortList(k->next, tail);
}

int main() {
	ListNode *head = new ListNode(2);
	ListNode *cur = head;
	int arr[] = { 1, 4, 7, 4, 8, 3, 6, 4, 7 };
	for (int i : arr) {
		cur->next = new ListNode(i);
		cur = cur->next;
	}
	quickSortList(head, nullptr);
	while (head != nullptr) {
		cout << head->val << endl;
		head = head->next;
	}
}
