#include <iostream>
#include <fstream>

#define EUTF_MAIN
#include "EUTF.hpp"
#include "test_sample.hpp"

EUTF_TEST_SUITE(u8"wat") 
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
	//
	// * the vector class tests will run as well
	//
	EUTF_RUN_ALL_TESTS();
	return 0;
}
