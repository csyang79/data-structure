//桶排序求第一个未出现的正数
class Solution {
	public:
		int firstMissingPositive(vector<int>& nums) {
			bucket_sort(nums);
			for (int i = 0; i < nums.size(); ++i)
				if (nums[i] != i + 1)
					return i + 1;
			return nums.size() + 1;
		}
		void bucket_sort(vector<int>& nums)
		{
			const int n = nums.size();
			for (int i = 0; i < nums.size(); ++i)
				while (nums[i] != i + 1)
				{
					if (nums[i] <= 0 || nums[i] > n || nums[i] == nums[nums[i] - 1])
						break;
					std::swap(nums[i], nums[nums[i] - 1]);
				}
		}
};
