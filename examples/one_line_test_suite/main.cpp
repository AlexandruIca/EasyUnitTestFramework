#define EUTF_MAIN
#include "EUTF.hpp"

//
// * no more than one test per line
//
EUTF_TEST_SUITE(u8"whatever") { EUTF_NEW_TEST(u8"Test1"){ EUTF_CHECK(2 == 3); }  }EUTF_END_TEST_SUITE(); EUTF_RUN_ALL_TESTS();

int main(int, char*[])
{
	return 0;
}

