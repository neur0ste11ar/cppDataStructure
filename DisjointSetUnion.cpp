#include <iostream>
#include <vector>

class DSB
{
private:
	std::vector<int> parent;
	std::vector<int> count;

public:
	DSB(int n)
	{
		parent.resize(n);
		count.resize(n, 0);
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
		}
	}

	int find(int x)
	{
		if (parent[x] != x)
		{
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void unite(int x, int y)
	{
		int rX = find(x);
		int rY = find(y);
		if (rX != rY)
		{
			if (count[rX] < count[rY])
			{
				parent[rX] = rY;
				count[rY] += count[rX];
			}
			else
			{
				parent[rY] = rX;
				count[rX] += count[rY];
			}
		}
	}

	void setCount(int x, int c)
	{
		count[find(x)] = c;
	}

	int getCount(int x)
	{
		return count[find(x)];
	}
};

int main()
{
	return 0;
}