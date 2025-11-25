//https://leetcode.com/problems/restore-ip-addresses/submissions/1839373342/?envType=problem-list-v2&envId=backtracking
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void backtrack(const string& str, int start, int part, string path, vector<string>& result)
{
	//if the last part is up, and we are at the end of the str
	if (part == 4 && start == str.size())
	{
		result.push_back(path);
		return;
	}

	
	if (part == 4 || start == str.size())
		return;

	int num = 0;
	for (int len = 1; len <= 3 && start + len <= str.size(); len++)
	{
		string segment = str.substr(start, len); // radelq na chasti
		
		if (segment[0] == '0' && segment.size() > 1)
			break;

		num = stoi(segment);

		if (num > 255)
			break;

		backtrack(str, start + len, part + 1, (part == 0 ? segment : path + "." + segment), result);

	}

}
vector<string> restoreIPAddresses(const string& str)
{
	vector<string> result;
	if (str.size() < 4 || str.size() > 12) 
		return result;

	backtrack(str, 0, 0, "", result);
	return result;
}


int main()
{

	string str = "25525511135";
	string curr;
	vector<string> ips = restoreIPAddresses(str);

	for (auto& ip : ips) {
		cout << ip << "\n";
	}
}
