class Solution {
	public:
		void sortColors(vector<int>& nums) {
			int zero = 0, two = nums.size();
			for (int i = 0; i < two; ++i)
			{
				if (nums[i] == 0)
					std::swap(nums[zero++], nums[i]);
				if (nums[i] == 2)
					std::swap(nums[--two], nums[i--]);
			}
		}
};
