#include <iostream>
#include <fstream>

#define EUTF_MAIN
#include "EUTF.hpp"

EUTF_TEST_SUITE(u8"te$t") 
{
	EUTF_NEW_TEST(u8"hello")
	{
		EUTF_CHECK(2 == 1);
		EUTF_EXPECT(3 == 3);
		EUTF_EXPECT(3 == 2);
	}
	
	EUTF_NEW_TEST(u8"hey")
	{
		EUTF_CHECK(2 == 2);
		EUTF_EXPECT(2 == 2);
		EUTF_EXPECT(2 == 2);
		EUTF_EXPECT(2 == 2);
	}

} 
EUTF_END_TEST_SUITE();

EUTF_NEW_TEST(u8"new_test")
{
	EUTF_MESSAGE(u8"olla");
}

int main(int, char*[])
{
	EUTF_RUN_ALL_TESTS();
	return 0;
}
