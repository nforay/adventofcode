#include <iostream>
#include <vector>
#include <bitset>

int main()
{
	std::string					line;
	std::vector<int>			oxygen;
	std::vector<int>			carbon;
	int							count;
	bool						filter;

	while (std::cin >> line)
		oxygen.push_back(std::bitset<12>(line).to_ulong());
	carbon = oxygen;
	for (auto i : {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}) 
	{
		if (oxygen.size() > 1) {
			count = std::count_if(oxygen.begin(), oxygen.end(), [&i](int line) { return line & (1 << i); });
			std::cerr << "Oxygen: Keeping only the " << std::max(count, (int)oxygen.size()-count) << " values with a " << ((double)count > (double)(oxygen.size()/2)) << " at position " << 12-i << "\n";
			filter = (count == (oxygen.size()-count) ? 1 : (count > (oxygen.size()-count)));
			oxygen.erase(std::remove_if(oxygen.begin(), oxygen.end(), [&filter, i](int line) { return !(line & (1 << i)) == filter; }), oxygen.end());
		}
		if (carbon.size() > 1) {
			count = std::count_if(carbon.begin(), carbon.end(), [&i](int line) { return line & (1 << i); });
			std::cerr << "Carbon: Keeping only the " << std::min(count, (int)carbon.size()-count) << " values with a " << !((double)count > (double)(carbon.size()/2)) << " at position " << 12-i << "\n";
			filter = (count == (carbon.size()-count) ? 0 : !(count > (carbon.size()-count)));
			carbon.erase(std::remove_if(carbon.begin(), carbon.end(), [&filter, i](int line) { return !(line & (1 << i)) == filter; }), carbon.end());
		}
	}
	std::cerr << "Oxygen:\t" << oxygen[0] << "\t" << std::bitset<12>(oxygen[0]) << std::endl;
	std::cerr << "Carbon:\t" << carbon[0] << "\t" << std::bitset<12>(carbon[0]) << std::endl;
	std::cout << "Answer: " << oxygen[0] * carbon[0] << std::endl;
	return (0);
}