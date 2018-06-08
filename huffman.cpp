#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
	int val;
	int weight;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int v = 0, int w = 0, TreeNode *l = nullptr, TreeNode *r = nullptr)
		: val(v), weight(w), left(l), right(r) { }
	~TreeNode()
	{
		delete left;
		delete right;
	}

	bool isLeaf()
	{
		return !left && !right;
	}
};

class comparator 
{
public:
	bool operator()(TreeNode *t1, TreeNode *t2)
	{
		return t1->weight > t2->weight;
	}

};

TreeNode *build(int dict[256])
{
	priority_queue<TreeNode*, vector<TreeNode*>, comparator> pq;
	for (int i = 0; i < 256; ++i)
		if (dict[i])
			pq.push(new TreeNode(i, dict[i]));

	while (pq.size() > 1)
	{
		TreeNode *p = pq.top();
		pq.pop();
		TreeNode *q = pq.top();
		pq.pop();
		TreeNode *x = new TreeNode(0, p->weight + q->weight, p, q);
		pq.push(x);
	}
	TreeNode *ans = pq.top();
	pq.pop();
	return ans;
}

void encode(TreeNode *root, string& cur, vector<pair<char, string>>& ans)
{
	if (root->isLeaf())
	{
		ans.push_back(make_pair(root->val, cur));
		return;
	}
	cur.push_back('0');
	encode(root->left, cur, ans);
	cur.back() = '1';
	encode(root->right, cur, ans);
	cur.pop_back();
}


int main()
{
	string str = "this is the string which would be encoded!";

	int dict[256];
	fill_n(dict, 256, 0);
	for (char c : str)
		++dict[c];
	for (int i = 0; i < 256; ++i)
		if (dict[i])
			cout << static_cast<char>(i) << " " << dict[i] << endl;
	TreeNode *root = build(dict);
	string cur;
	vector<pair<char, string>> ans;
	encode(root, cur, ans);
	for (auto p : ans)
		cout << p.first << " " << p.second << endl;
	return 0;
}
