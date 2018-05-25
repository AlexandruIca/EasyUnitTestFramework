#include "EUTF.hpp"

size_t strlength(const char* s)
{
	size_t k = 0;
	
	while(s[k] != '\0') {
	    	++k;
	}

	return k;
}

EUTF_NEW_TEST(strlength-test)
{
	EUTF_EXPECT(strlength("abc") == 3);
	EUTF_CHECK(strlength("def") == 2);
}

int main(int, char*[])
{
	EUTF_RUN_ALL_TESTS();
	return 0;
}

