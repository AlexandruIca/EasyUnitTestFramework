# EasyUnitTestFramework
An easy to use unit testing framework for C++0x.
It's a very flexible framework, easy to setup and shouldn't increase compile times by too much.
# Setup
This framework uses CMake as its buildsystem. To link your project with this library should be fairly simple: clone this repository in your working directory and add the CMakeLists.txt of the library(check usage/).
If you don't use cmake it still shouldn't be too complicated, the framework only consists of one .cpp and one .hpp file.
# How to use
Tests should be created in .cpp files:
```c++
// ... whatever

// default place to print test results is the console
#include "EUTF.hpp"

EUTF_NEW_TEST(name of the test does not have to be a valid variable name)
{
	// test something
	EUTF_EXPECT(2 == 3); // will give an error
	EUTF_CHECK(2 == 3); // will give a warning
	EUTF_MESSAGE("this will be printed alongside the output that contains the results of the tests");
	EUTF_ASSERT(2 == 3); // this will give a fatal error, anything after ASSERT that fails won't get executed, it will exit from the test

	// everything else is skipped because EUTF_ASSERT failed
}

```
To run the test:
```c++
// you can call RUN_ALL_TESTS in the same file you've created the test, however I strongly recommend you call it in your main.cpp(or however it's called) file since you may have tests across multiple .cpp files 
// and there should be only ONE RUN_ALL_TESTS call in your entire project

// You could also call it in the global namespace:
/* EUTF_RUN_ALL_TESTS(); */

int main()
{
	EUTF_RUN_ALL_TESTS();
	return 0;
}
```
The output of that should be something like this:
```c++
path/to/your/file.cpp(line at which a fatal error/error/warning/message occured) name of the test does not have to be a valid variable name [FAILURE]: 2 == 3
path/to/your/file.cpp(line at which a fatal error/error/warning/message occured) name of the test does not have to be a valid variable name [WARNING]: 2 == 3
path/to/your/file.cpp(line at which a fatal error/error/warning/message occured) name of the test does not have to be a valid variable name [MESSAGE]: this will be printed alongside the output that contains the results of the tests
path/to/your/file.cpp(line at which a fatal error/error/warning/message occured) name of the test doesn'tt have to be a valid variable name [FATAL]: 2 == 3

Warnings: 1
Failures: 1
```
To save the results to a different file:
```c++
#include <fstream>

std::ofstream g{ "output.txt" };

#define EUTF_LOG g
#include "EUTF.hpp"

// your tests

```
You can also have test suites which are a way to organize tests:
```c++
#include "EUTF.hpp"

EUTF_TEST_SUITE(name)
{
	EUTF_NEW_TEST(test)
	{
		EUTF_EXPECT(2 == 3);
	}

	// and as many tests as you want(even nested test suites)
}
EUTF_END_TEST_SUITE();

```
And the output should be:
```c++
path/to/your/file.cpp(line) name->test [FAILURE]: 2 == 3
```
Check examples/ for more.
# Version Tracker
v1.0: 
* Basic test organizers(test case, test suite)
* Basic test helpers(assert, expect, check, message)
* Option to save output to a seperate file
 
