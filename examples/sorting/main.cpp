#include <algorithm>
#include <random>

#define EUTF_MAIN
#include "EUTF.hpp"

#include "quicksort.hpp"

void Shuffle(std::vector<int>& values)
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(values.begin(), values.end(), g);
}

EUTF_TEST_SUITE(u8"quicksort")
{
	EUTF_NEW_TEST(u8"unique values")
	{
		static std::vector<int> sorted_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static std::vector<int> copied_values{ sorted_values };
	
		Shuffle(copied_values);
		sort::QuickSort(copied_values);

		EUTF_EXPECT(copied_values == sorted_values);
	}

	EUTF_NEW_TEST(u8"non unique values")
	{
		static std::vector<int> sorted_values{ 1, 2, 2, 4, 5, 5, 5, 8, 9, 9 };
		static std::vector<int> copied_values{ sorted_values };

		Shuffle(copied_values);
		sort::QuickSort(copied_values);

		EUTF_EXPECT(copied_values == sorted_values);
	}

	EUTF_NEW_TEST(u8"reversed")
	{
		static std::vector<int> sorted_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static std::vector<int> copied_values{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

		sort::QuickSort(copied_values);

		EUTF_EXPECT(copied_values == sorted_values);
	}

	EUTF_NEW_TEST(u8"almost sorted")
	{
		static std::vector<int> sorted_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static std::vector<int> copied_values{ 1, 3, 2, 4, 5, 7, 6, 8, 9, 10 };

		sort::QuickSort(copied_values);

		EUTF_EXPECT(copied_values == sorted_values);
	}	
}

int main(int, char*[])
{
	EUTF_RUN_ALL_TESTS();
	return 0;
}

