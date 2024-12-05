#include <iostream>
#include <vector>
#include <queue>

struct compare
{
	bool operator()(std::pair<int, int> a, std::pair<int, int> b)
	{
		return a.second < b.second;
	}
};

int main()
{
	std::vector<std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare>> v;
}