#define EUTF_MAIN
#include "EUTF/EUTF.hpp"

//
// A workaround for the lack of expression templates:
//     EUTF_TRY(
//          fact(i) == n, 
//          fact(i) << " is not " << n);
//

NEW_TEST("First one", "Original")
{
    EXPECT(6 == 7);
    ASSERT(1 == 3);
}

NEW_TEST("Basic Test", "One Tag", "Two tags", "THRee tags")
{
    MESSAGE("Hello there: " << 2);
    ASSERT(2 == 2);
    CHECK(1 == 2);

    SECTION("Hey", "There") {
        MESSAGE("Message" << " inside " << "section");
        CHECK(2.3f > 4.5f);

        EXPECT(2 == 2);

        EXPECT(2 == 3);
        REQUIRE(5 == 6);

        SECTION("Does this run??????????") {
            MESSAGE("Shouldn't run but who knows...");
        }
    }
}

int main()
{ eutf::run_all_tests(eutf::xml_generator, eutf::default_logic, nullptr); }

