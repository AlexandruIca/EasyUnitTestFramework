v1.3:
* Even more refactoring
* Added one more example
* Output is now more readable

v1.2:
* Refactored the code a bit
* Added sections
* Added EUTF_REQUIRE, a helper for sections
* Solved a dangerous static initialization problem

v1.1:
* Refactored a lot of the code to make it easier to read and implement xml and json output in the future
* Now the name of the tests and tests suites are quoted strings to allow for a wider variety of characters
* Tests can also have tags to differentiate them
* Removed the usage folder completely because it was unnecessary
* The framework is now header only to make it easier to set up
* Now counting the number of fatal errors 

v1.0: 
* Basic test organizers(test case, test suite)
* Basic test helpers(assert, expect, check, message)
* Option to save output to a seperate file(deprecated)

