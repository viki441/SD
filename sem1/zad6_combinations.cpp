#include <iostream>
#include <cmath>
#include <vector>

void generateVariations(std::vector<int>& elements,
	std::vector<int>& current, int start, int k)
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

	for (int i = start; i < (int)elements.size(); ++i) {
		

		current.push_back(elements[i]);
		generateVariations(elements, current, i + 1, k);
		current.pop_back(); 
		
	}
}


int main()
{ 
	std::vector<int> elements = { 1,2,3,4,5 };
	int k = 3;
	std::vector<int> current;

	generateVariations(elements, current, 0, k);

  
}

