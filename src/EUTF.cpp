#include "EUTF.hpp"

#include <iostream>
#include <vector>
#include <utility>

namespace eutf 
{
	std::vector<Test*> test_queue;
	std::vector<std::string> name;
	std::size_t warnings = 0;
	std::size_t errors = 0;
}

eutf::Test::Test(Test* test, std::string&& name)
	: m_name(std::move(name))
{
	test_queue.push_back(test);
}

eutf::Test::~Test() {}

std::string eutf::TestName()
{
	std::string final_name;
	
	for (const auto& str : eutf::name) {
		final_name += str;
		final_name += "->";
	}

	return final_name;
}

void eutf::AddTestName(const char* m_name)
{
	eutf::name.push_back(std::string{ m_name });
}

void eutf::DeleteTestName()
{
	eutf::name.pop_back();
}

static void RunTests(std::ostream& f)
{
	std::size_t n = eutf::test_queue.size();

	if(n == 1) {
		f << "1 test" << std::endl;
	}
	else {
		f << n << " tests" << std::endl;
	}

	for(const auto& test : eutf::test_queue) {
		test->run();
	}

	f << std::endl;

	if(eutf::warnings) {
		f << "Warnings: " << eutf::warnings << std::endl;
	}
	else {
		f << "***No warnings" << std::endl;
	}
	if(eutf::errors) {
		f << "Failures: " << eutf::errors << std::endl;
	}
	else {
		f << "***No failures" << std::endl;
	}
}

void eutf::RunAll(int log)
{
	switch(log)
	{
	case eutf::CONSOLE: {
		RunTests(std::cout);
		break;
	}
	}
}

void eutf::Test::OnFatal(int log, const char* file, int line, const char* callstr)
{
	switch(log)
	{
	case eutf::CONSOLE: {
		std::cout << file << "(" << line << ") " << eutf::TestName() << this->m_name << " [FATAL]: " << callstr << std::endl;
	}
	}
}

void eutf::Test::OnFailure(int log, const char* file, int line, const char* callstr)
{
	++errors;
	switch(log)
	{
	case eutf::CONSOLE: {
		std::cout << file << "(" << line << ")" << eutf::TestName() << this->m_name << " [FAILURE]: " << callstr << std::endl;
	}
	}
}

void eutf::Test::OnWarning(int log, const char* file, int line, const char* callstr)
{
	++warnings;
	switch(log)
	{
	case eutf::CONSOLE: {
		std::cout << file << "(" << line << ")" << eutf::TestName() << this->m_name << " [WARNING]: " << callstr << std::endl;		
        }
	}
}

void eutf::Test::OnMessage(int log, const char* file, int line, const char* msg)
{
	switch(log)
	{
	case eutf::CONSOLE: {
		std::cout << file << "(" << line << ")" << eutf::TestName() << this->m_name << " [MESSAGE]: " << msg << std::endl;
	}
	}
}

