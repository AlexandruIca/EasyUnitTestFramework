#include "EUTF.hpp"

//
// * no more than one test per line
//
EUTF_TEST_SUITE(whatever) { EUTF_NEW_TEST(Test1){ EUTF_CHECK(2 == 3); }  }EUTF_END_TEST_SUITE(); EUTF_RUN_ALL_TESTS();

int main(int, char*[])
{
	return 0;
}

