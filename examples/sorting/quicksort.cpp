#include "quicksort.hpp"

#include <algorithm>

static void quickSort(int lo, int hi, std::vector<int>& v)
{
	int i = lo, j = hi, piv = v[lo + (hi - lo) / 2];

	while(i <= j) {
		while(v[i] < piv)
			++i;
		while(v[j] > piv)
			--j;

		if(i <= j) {
			std::swap(v[i], v[j]);

			++i, --j;
		}
	}

	if(j > lo) {
		quickSort(lo, j, v);
	}
	if(i < hi) {
		quickSort(i, hi, v);
	}
}

void sort::QuickSort(std::vector<int>& values)
{
	quickSort(0, values.size() - 1, values);
}

