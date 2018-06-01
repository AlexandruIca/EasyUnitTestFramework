#include "EUTF.hpp"

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

std::size_t eutf::TestsCount() 
{
	return eutf::test_queue.size();
}

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

template<typename T>
static void RunTests(T& f)
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

void eutf::RunAll(std::ofstream& f)
{
	RunTests(f);
}

void eutf::RunAll(std::ostream& f)
{
	RunTests(f);
}

void eutf::RunAll(std::fstream& f)
{
	RunTests(f);
}

template<typename T>
static inline void LogType(T& f, const char* type, const std::string& name, const char* file, int line, const char* callstr)
{
	f << file << "(" << line << ") " << eutf::TestName() << name << " [" << type << "]: " << callstr << std::endl;
}

void eutf::Test::OnFatal(std::ofstream& f, const char* file, int line, const char* callstr)
{
	LogType(f, "FATAL", this->m_name, file, line, callstr);
}

void eutf::Test::OnFatal(std::ostream& f, const char* file, int line, const char* callstr)
{
	LogType(f, "FATAL", this->m_name, file, line, callstr);
}

void eutf::Test::OnFatal(std::fstream& f, const char* file, int line, const char* callstr)
{
	LogType(f, "FATAL", this->m_name, file, line, callstr);
}

void eutf::Test::OnFailure(std::ofstream& f, const char* file, int line, const char* callstr)
{
	++errors;
	LogType(f, "FAILURE", this->m_name, file, line, callstr);
}

void eutf::Test::OnFailure(std::ostream& f, const char* file, int line, const char* callstr)
{
	++errors;
	LogType(f, "FAILURE", this->m_name, file, line, callstr);
}

void eutf::Test::OnFailure(std::fstream& f, const char* file, int line, const char* callstr)
{
	++errors;
	LogType(f, "FAILURE", this->m_name, file, line, callstr);
}

void eutf::Test::OnWarning(std::ofstream& f, const char* file, int line, const char* callstr)
{
	++warnings;
	LogType(f, "WARINING", this->m_name, file, line, callstr);
}

void eutf::Test::OnWarning(std::ostream& f, const char* file, int line, const char* callstr)
{
	++warnings;
	LogType(f, "WARINING", this->m_name, file, line, callstr);
}

void eutf::Test::OnWarning(std::fstream& f, const char* file, int line, const char* callstr)
{
	++warnings;
	LogType(f, "WARINING", this->m_name, file, line, callstr);
}

void eutf::Test::OnMessage(std::ofstream& f, const char* file, int line, const char* msg)
{
	LogType(f, "MESSAGE", this->m_name, file, line, msg);
}

void eutf::Test::OnMessage(std::ostream& f, const char* file, int line, const char* msg)
{
	LogType(f, "MESSAGE", this->m_name, file, line, msg);
}

void eutf::Test::OnMessage(std::fstream& f, const char* file, int line, const char* msg)
{
	LogType(f, "MESSAGE", this->m_name, file, line, msg);
}

