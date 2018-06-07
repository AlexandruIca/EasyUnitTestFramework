#pragma once
#ifndef EUTF_HPP
#define EUTF_HPP

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
// * Give the test some tags that have to be quoted strings
//
// * The first tag is considered the name of the test, the rest are there to differentiate tests with the same names
//
#define EUTF_NEW_TEST(...) \
struct EUTF_CONCAT(EUTF_Test_, __LINE__) : public eutf::Test \
{ \
	EUTF_CONCAT(EUTF_Test_, __LINE__)() \
		: eutf::Test(std::string{ eutf::TestSuiteName() }, std::list<const char*>{ __VA_ARGS__ }) \
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
	\
	return; \
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
// * 'name' has to be a quoted string
//
#define EUTF_TEST_SUITE(name) \
static int EUTF_CONCAT(eutf_test_suite_, __LINE__) = []() -> int \
{ \
	eutf::AddTestSuiteName(name); \
	\
	return 0; \
}(); \
namespace 

#define EUTF_END_TEST_SUITE() \
static int EUTF_CONCAT(eutf_test_suite_end_, __LINE__) = []() -> int \
{ \
	eutf::DeleteTestSuiteName(); \
	\
	return 0; \
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

#include <string>
#include <list>

namespace eutf {
	
	enum Log : int
	{
		CONSOLE //, XML in the future, maybe even json
	};

	struct Test
	{
	protected:
		std::string m_suite;
		std::list<const char*> m_tags;
		
		Test() = delete;
		Test(std::string&& suite, std::list<const char*>&& tags);
		virtual ~Test();

		void OnFatal(int log, const char* file, int line, const char* callstr);
		void OnFailure(int log, const char* file, int line, const char* callstr);
		void OnWarning(int log, const char* file, int line, const char* callstr);
		void OnMessage(int log, const char* file, int line, const char* msg);
	
	public:
		virtual void run() = 0;
	};

	std::string TestSuiteName();
	void AddTestSuiteName(const char* m_name);
	void DeleteTestSuiteName();

	void RunAll(int log);

}

#ifdef EUTF_MAIN

#include <iostream>
#include <vector>
#include <utility>

namespace eutf {
	std::vector<std::string> name;
	std::size_t warnings = 0;
	std::size_t errors = 0;
	std::size_t fatal_errors = 0;

	std::vector<Test*>& get_tests_queue()
	{
		static std::vector<Test*> tests_queue;
		return tests_queue;
	}
}

eutf::Test::Test(std::string&& suite, std::list<const char*>&& tags)
	: m_suite(std::move(suite))
	, m_tags(std::move(tags))
{
	eutf::get_tests_queue().push_back(this);
}

eutf::Test::~Test() {}

std::string eutf::TestSuiteName()
{
	std::string final_name;

	for (const auto& str : eutf::name) {
		final_name += str;
		final_name += "\\";
	}

	return final_name;
}

void eutf::AddTestSuiteName(const char* m_name)
{
	eutf::name.push_back(std::string{ m_name });
}

void eutf::DeleteTestSuiteName()
{
	eutf::name.pop_back();
}

static void RunTests(std::ostream& f)
{
	std::size_t n = eutf::get_tests_queue().size();

	if (n == 1) {
		f << "1 test" << std::endl;
	}
	else {
		f << n << " tests" << std::endl;
	}

	for (const auto& test : eutf::get_tests_queue()) {
		test->run();
	}

	f << std::endl;

	if (eutf::warnings) {
		f << "Warnings: " << eutf::warnings << std::endl;
	}
	else {
		f << "***No warnings" << std::endl;
	}
	if (eutf::errors) {
		f << "Failures: " << eutf::errors << std::endl;
	}
	else {
		f << "***No failures" << std::endl;
	}
	if (eutf::fatal_errors) {
		f << "Fatal errors: " << eutf::fatal_errors << std::endl;
	}
	else {
		f << "***No fatal errors";
	}
}

void eutf::RunAll(int log)
{
	switch (log)
	{
	case eutf::CONSOLE: {
		RunTests(std::cout);
		break;
	}
	}
}

static void PrintInfo(int log, const std::string& name, const std::list<const char*>& tags, const char* type, const char* file, int line, const char* str)
{
	switch (log)
	{
	case eutf::CONSOLE: {
		std::cout << file << "(" << line << ") " << name;

		for (const auto& tag : tags)
			std::cout << "{" << tag << "} ";

		std::cout << " [" << type << "]: " << str << std::endl;
	}
	}
}

void eutf::Test::OnFatal(int log, const char* file, int line, const char* callstr)
{
	++fatal_errors;
	PrintInfo(log, this->m_suite, this->m_tags, "FATAL", file, line, callstr);
}

void eutf::Test::OnFailure(int log, const char* file, int line, const char* callstr)
{
	++errors;
	PrintInfo(log, this->m_suite, this->m_tags, "FAILURE", file, line, callstr);
}

void eutf::Test::OnWarning(int log, const char* file, int line, const char* callstr)
{
	++warnings;
	PrintInfo(log, this->m_suite, this->m_tags, "WARNING", file, line, callstr);
}

void eutf::Test::OnMessage(int log, const char* file, int line, const char* msg)
{
	PrintInfo(log, this->m_suite, this->m_tags, "MESSAGE", file, line, msg);
}

#endif // EUTF_MAIN

#endif // !ETUF_HPP
