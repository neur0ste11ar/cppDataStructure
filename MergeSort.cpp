#include <iostream>
#include <vector>

template <typename T>
void merge(std::vector<T>& arr, int l, int m, int r)
{
    std::vector<T> temp;
	int i = l, j = m + 1;
	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j])
		{
			temp.push_back(arr[i]);
			i++;
		}
		else
		{
			temp.push_back(arr[j]);
			j++;
		}
	}
	while (i <= m)
	{
		temp.push_back(arr[i]);
		i++;
	}
	while (j <= r)
	{
		temp.push_back(arr[j]);
		j++;
	}
	for (int i = 0; i < temp.size(); i++)
	{
		arr[l + i] = temp[i];
	}
}

template <typename T>
void mergeSort(std::vector<T>& arr, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

int main()
{
	return 0;
};