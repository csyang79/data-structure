//dfs,注意各种剪枝，以及传入引用可大幅度减少创建局部vector时间，回溯法记得先标记后取消
class Solution {
	public:
		bool exist(vector<vector<char>>& board, string word) {
			bool ans = false;
			vector<vector<char>> visited(board.size(), vector<char>(board[0].size(), 0));
			for (int i = 0; i < board.size(); ++i)
				for (int j = 0; j < board[0].size(); ++j)
				{
					if (board[i][j] == word[0])
					{
						vector<vector<char>> m = visited;
						if (dfs(board, i, j, word, 0, m))
							return true;
					}
				}
			return ans;
		}
		bool dfs(vector<vector<char>>& board, int i, int j, string word, int idx, vector<vector<char>>& visited)
		{
			if (visited[i][j] == 1)
				return false;
			if (board[i][j] != word[idx])
				return false;
			if (++idx == word.size())
				return true;
			visited[i][j] = 1;            
			if (i + 1 < board.size() && dfs(board, i + 1, j, word, idx, visited) ||
					i > 0 && dfs(board, i - 1, j, word, idx, visited) ||
					j + 1 < board[0].size() && dfs(board, i, j + 1, word, idx, visited) ||
					j > 0 && dfs(board, i, j - 1, word, idx, visited))
				return true;
			visited[i][j] = 0;
			return false;
		}
};
