## Coding style
Rectify any inconsistency within the code. Also need to add a doxyfile to test if the doxygen documentation is actually correct. clang-format/tidy should also be added to the project to stay consistent with one coding style(for eg. the code should follow the 80 column rule).

## Test, test, test
Asynchronous tests, console, xml and json output, command line arguments are features that need a lot of testing to see if they work correctly. 

## Mocking capability
Having a mocking utility in the would be really nice. Something that looks like google mock/boost.turtle would be pretty good(while also being capable of mocking c functions).

## Test shuffling
Add the option to shuffle tests(both in code and through command line arguments).

## Don't overengineer
For version 1.4 the features that should be ready are: test fixtures, asynchronous tests, complete cosole, xml and json default output, custom output capability, command line options(for setting the tab size, the filter to ignore certain tests, the name of the output file if needed, whether the tests should be shuffled) and having the ability to set a custom logic for ignoring tests. 

## Future features
* Test fixtures
* Parameterized tests
* Toml, csv, html generators provided out of the box
* all_of, any_of logic for ignoring tests provided out of the box
* Utility for floating point comparison approximation
* A workaround for not showing the results of a failed expression inside an assertion macro like catch does(probably something like: TRY_EXPECT(2 == i, "i was: " << i))
* Macros for use outside unit tests declared with eutf(possible approach: same macros but with '_' appended to them. eg.:
 ```c++
 int my_test(int a, int b) { EXPECT_(a == b); }
 ```
 These macros should be thread safe and have a seperate output from the other macros. The output should be generated with the same generator for the normal macros)
* Macros for checking whether an expression/function throws(possible approach: EXPECT_THROWS([](){}()) and EXPECT_THROWS_AS(const std::exception&, [](){}()) )

## Improve documentation

