#include <iostream>
#include <numeric>
#include <map>
#include <list>

int main()
{
	int value = 0;
	int answer = 0;
	int window = 0;
	std::list<int> lastvalues;
	std::map<int, int> measurements;
	while (std::cin >> value)
	{
		lastvalues.push_front(value);
		if (lastvalues.size() == 3)
		{
			measurements[window] = std::accumulate(lastvalues.begin(), lastvalues.end(), 0);
			std::cerr << window << ": " << measurements[window] << " ";
			if (window > 0)
			{
				if (measurements[window] > measurements[window - 1]){
					answer++;
					std::cerr << "(increased) ";
				}
				else
					std::cerr << "(decreased) ";
			}
			std::cerr << "{";
			for (auto i : lastvalues)
				std::cerr << i << ",";
			std::cerr << "\b}" << "\n";
			window++;
			lastvalues.pop_back();
		}
	}
	std::cout << "Answer: " << answer << std::endl;
	return (0);
}