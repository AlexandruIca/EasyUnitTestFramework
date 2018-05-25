#include <iostream>
#include <fstream>

#include "EUTF.hpp"

EUTF_TEST_SUITE($) 
{
	EUTF_NEW_TEST(hello)
	{
		EUTF_CHECK(2 == 1);
		EUTF_EXPECT(3 == 3);
		EUTF_EXPECT(3 == 2);
	}
	
	EUTF_NEW_TEST(hey)
	{
		EUTF_CHECK(2 == 2);
		EUTF_EXPECT(2 == 2);
		EUTF_EXPECT(2 == 2);
		EUTF_EXPECT(2 == 2);
	}

} 
EUTF_END_TEST_SUITE();

EUTF_NEW_TEST(new_test)
{
	EUTF_MESSAGE("olla");
}

int main(int, char*[])
{
	EUTF_RUN_ALL_TESTS();
	return 0;
}
