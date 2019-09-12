#include <bits/stdc++.h>
using namespace std;

class TreeNode {
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int v = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(v), left(l), right(r) {}
};

TreeNode *createTree(const vector<string>& nums) {
	vector<TreeNode*> tmp = vector<TreeNode*>(nums.size(), nullptr);
	for (int i = 0; i < nums.size(); ++i) {
		if (!nums[i].empty()) {
			tmp[i] = new TreeNode(std::stoi(nums[i]));
			if (i != 0) {
				if (i & 1) {
					tmp[(i - 1) / 2]->left = tmp[i];
				} else {
					tmp[(i - 1) / 2]->right = tmp[i];
				}
			}
		}
	}
	return tmp[0];
}

void preorderTraversal(TreeNode *root) {
	if (root == nullptr)
		return;
	cout << root->val << endl;
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void levelOrderTraversal(TreeNode *root) {
	if (root == nullptr)
		return;
	queue<TreeNode*> q;
	q.push(root);
	TreeNode *t;
	while (!q.empty()) {
		t = q.front();
		q.pop();
		if (t->left != nullptr)
			q.push(t->left);
		if (t->right != nullptr)
			q.push(t->right);
		cout << t->val << endl;
	}
}
int main() {
	vector<string> vec = { "1", "2", "3", "4", "", "5", "" };
	TreeNode *root = createTree(vec);
	levelOrderTraversal(root);
	preorderTraversal(root);

}
