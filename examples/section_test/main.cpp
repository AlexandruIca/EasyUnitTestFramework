#define EUTF_MAIN
#include "EUTF.hpp"

EUTF_TEST_SUITE(u8"suite")
{
	EUTF_NEW_TEST(u8"test")
	{
		EUTF_SECTION(u8"whatever", u8"tag")
		{
			EUTF_REQUIRE(2 == 2);
			EUTF_REQUIRE(2 == 3); 
		}

		EUTF_SECTION(u8"another section", u8"another tag")
		{
			EUTF_EXPECT(2 == 3);
			
			// will run
			EUTF_SECTION(u8"nested section", u8"tag")
			{
				EUTF_REQUIRE(2 == 3);
				// won't run
				EUTF_SECTION(u8"one more")
				{
					EUTF_CHECK(2 == 3);
					EUTF_MESSAGE(u8"Did you get this far?");
				}
			}
		}
	}
}
EUTF_END_TEST_SUITE();

int main(int, char*[])
{
	EUTF_RUN_ALL_TESTS();
	return 0;
}

