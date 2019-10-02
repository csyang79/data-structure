#include <iostream>
using namespace std;
class   DisjointSet
{
	public:
		int *father;  //记录父节点 
		int *rank;  //记录秩
		DisjointSet(int size)
		{
			father = new int[size];
			rank = new int[size];
			for(int i = 0; i < size; i++)
			{
				father[i] = i; //初始化时每个父节点是自己本身
				rank[i] = 0; //初始化时每个结点的秩都为0 
			}
		} 
		~DisjointSet()
		{
			delete []father;
			delete []rank;
		}
		int find_set(int node)  //查找根结点
		{
			if(father[node] != node)
			{
				father[node] = find_set(father[node]);  //压缩路径优化 
			}
			return father[node];
		}
		bool merge(int node1, int node2) //合并操作
		{
			int ancestor1 = find_set(node1);
			int ancestor2 = find_set(node2);
			if(ancestor1 != ancestor2)
			{
				//比较两棵树之间秩的大小
				if(rank[ancestor1]>rank[ancestor2])
				{
					father[ancestor2] = ancestor1;  
				}
				else
				{
					father[ancestor1] = ancestor2;
					rank[ancestor2] = max(rank[ancestor2], rank[ancestor1]+1); //更新秩
				}
				return true;
			}
			return false;
		} 
};
int main()
{
	int n, m;   //n表示元素个数，m表示有关系的元素个数
	int count = 0;
	cin>>n>>m;
	DisjointSet dus(n);
	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin>>a>>b;
		dus.merge(a, b);
	}
	for(int i =0; i < n; i++)
	{
		if(dus.father[i] == i)  //输出集合的个数
		{
			count++;
		}
	}
	cout<<count<<endl;
	return 0;
}
