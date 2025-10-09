#include <iostream>
#include <cmath>
#include <vector>

void generateVariations(std::vector<int>& elements,
	std::vector<int>& current, std::vector<bool>& used, int k)
{
	if ((int)current.size() == k)
	{
		std::cout << "{ ";
		for (int i = 0; i < k; ++i)
		{
			std::cout << current[i];
			if (i < k - 1)  std::cout << ", ";
		}
		std::cout << " }\n";
		return;
	}

	for (int i = 0; i < (int)elements.size(); ++i) {
		if (!used[i]) {
			used[i] = true;
			current.push_back(elements[i]);

			generateVariations(elements, current, used, k);

			current.pop_back(); 
			used[i] = false;
		}
	}
}


int main()
{ 
	std::vector<int> elements = { 1,2,3,4,5 };
	int k = 3;

	std::vector<int> current;
	std::vector<bool> used(elements.size(), false);

	generateVariations(elements, current, used, k);

  
}

