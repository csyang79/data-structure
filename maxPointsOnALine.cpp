#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>
using std::string;
using std::pair;
using std::unordered_map;
using std::vector;

int gcd(int x, int y);
int maxPointsOnALine(vector<pair<int, int>>& points)
{
	unordered_map<string, int> ump;
	int n = points.size();
	for (int i = 0; i < n; ++i)
	{
		pair<int, int> p1 = points[i];
		for (int j = i + 1; j < n; ++j)
		{
			pair<int, int> p2 = points[j];	
			int x = p2.first - p1.first;
			int y = p2.second - p1.second;
			if (x == 0 && y != 0)
			{
				++ump["vertical"]; 
				continue;	
			}
			int g = gcd(y, x);
			string cur = std::to_string(y / g) + "/" + std::to_string(x / g);
			std::cout << cur << std::endl;
			++ump[cur];
		}
	} 
	int res = 0;
	for (auto it = ump.begin(); it != ump.end(); ++it)
		res = res > it->second ? res : it->second;
	return res;
}

int gcd(int x, int y)
{
	return y == 0 ? x : gcd( y, x % y );
}

int main()
{
	vector<pair<int, int>> points { { 2, 3 }, { 4, 7 }, { 3, 5 }, { 4, 0 }, { 8, 5 } };
	std::sort(points.begin(), points.end());
	std::cout << maxPointsOnALine(points) << std::endl;
	return 0;
}
