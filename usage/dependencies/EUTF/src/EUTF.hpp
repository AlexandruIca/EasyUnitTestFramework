#pragma once
#ifndef EUTF_HPP
#define EUTF_HPP

#include <string>

//
// * Where to print information regarding tests
//
#ifndef EUTF_LOG
#define EUTF_LOG eutf::CONSOLE
#endif

//
// * Helpers for declaring uniquely-named variables/structs 
//
#define EUTF_PASTE(a, b) a ## b
#define EUTF_CONCAT(a, b) EUTF_PASTE(a, b)

//
// * 'name' can can be anything
//
#define EUTF_NEW_TEST(name) \
struct EUTF_CONCAT(EUTF_Test_, __LINE__) : public eutf::Test \
{ \
	EUTF_CONCAT(EUTF_Test_, __LINE__)() \
		: eutf::Test(this, std::string{ eutf::TestName() + #name }) \
	{} \
	\
	void run() override; \
}; \
static EUTF_CONCAT(EUTF_Test_, __LINE__) EUTF_CONCAT(eutf_test_, __LINE__); \
\
void EUTF_CONCAT(EUTF_Test_, __LINE__)::run()

//
// * If this fails it's considered a fatal error
//
#define EUTF_ASSERT(P) \
if(!(P)) \
{\
	this->OnFatal(EUTF_LOG, __FILE__, __LINE__, #P);\
	return;\
}

//
// * If this fails it's considered an error
//
#define EUTF_EXPECT(P) \
if(!(P)) \
	this->OnFailure(EUTF_LOG, __FILE__, __LINE__, #P)

//
// * If this fails it's considered a warning
//
#define EUTF_CHECK(P) \
if(!(P)) \
	this->OnWarning(EUTF_LOG, __FILE__, __LINE__, #P)

#define EUTF_MESSAGE(msg) this->OnMessage(EUTF_LOG, __FILE__, __LINE__, msg)

//
// * 'name' can be anything
//
#define EUTF_TEST_SUITE(name) \
static int EUTF_CONCAT(eutf_test_suite_, __LINE__) = []() -> int \
{\
	eutf::AddTestName(#name);\
	return 0;\
}();\
namespace 

#define EUTF_END_TEST_SUITE() \
static int EUTF_CONCAT(eutf_test_suite_end_, __LINE__) = []() -> int \
{ \
	eutf::DeleteTestName();\
	return 0;\
}()

//
// * Doesn't provide a main function
//
// * Can be called in global namespace
//
#define EUTF_RUN_ALL_TESTS() \
static int EUTF_CONCAT(eutf_tests_results, __LINE__) = []() -> int \
{ \
	eutf::RunAll(EUTF_LOG); \
	\
	return 0; \
}()

namespace eutf {
	
	enum Log : int
	{
		CONSOLE //, XML in the future
	};

	struct Test
	{
	protected:
		std::string m_name;
		
		Test() = delete;
		Test(Test* test, std::string&& name);
		virtual ~Test();

		virtual void OnFatal(int log, const char* file, int line, const char* callstr);
		virtual void OnFailure(int log, const char* file, int line, const char* callstr);
		virtual void OnWarning(int log, const char* file, int line, const char* callstr);
		virtual void OnMessage(int log, const char* file, int line, const char* msg);
	
	public:
		virtual void run() = 0;
	};

	std::string TestName();
	void AddTestName(const char* m_name);
	void DeleteTestName();

	void RunAll(int log);

}

#endif
