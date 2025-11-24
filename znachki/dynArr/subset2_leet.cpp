//https://leetcode.com/problems/subsets-ii/description/?envType=problem-list-v2&envId=backtracking
#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;

void backtrack(int i, vector<int>& nums, vector<int>& subset, vector<vector<int>>& res)
{
	if (i == nums.size())
	{
		res.push_back(subset);
		return;
	}

	subset.push_back(nums[i]);
	backtrack(i + 1, nums, subset, res);
	subset.pop_back();

	while (i + 1 < nums.size() && nums[i] == nums[i + 1])
	{
		i++;
	}
	backtrack(i + 1, nums, subset, res);

}

int main()
{
	vector<int> nums = { 1,2,1 };

	vector<vector<int>> res;
	vector<int> subset;
	sort(nums.begin(), nums.end());

	backtrack(0, nums, subset, res);

	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[i].size(); j++)
		{
			cout << res[i][j] << " ";
		}
		cout << endl;
	}

}
