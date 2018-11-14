#pragma once
#ifndef EUTF_HPP
#define EUTF_HPP

///
/// @file EUTF.hpp
///
/// @brief Defines everything needed to use the framework.
///
/// It should be included everywhere you want to use the framework and in
/// the file you run the tests you should define @ref EUTF_MAIN. This should
/// happen ONCE across your entire project.
///
/// Since macros like TEST and ASSERT are common every macro starts with the
/// 'EUTF_' prefix. The short versions(without the prefix) are defined only 
/// if there is no other definition of them(meaning ther is an '#ifndef MACRO'
/// before their definition).
///
/// All assertion macros take a variable number of arguments so something like:
/// @code{.cpp}
///     ASSERT(std::is_same<int, user_type>::value);
/// @endcode
/// is possible.
///

// Helpers for declaring uniquely-named variables/structs 
#define EUTF_PASTE(a, b) a ## b
#define EUTF_CONCAT(a, b) EUTF_PASTE(a, b)
#define EUTF_UNAME(name) EUTF_CONCAT(name, __LINE__)

///
/// @brief Defines a new test.
///
/// You can specify as many tags(quoted strings) for the test as you want. 
/// One strategy for giving tags is:
///     tag0: the name of the group that the test belongs to(mimicking a test
///           suite).
///     tag1: the name of the actual test.
///     tag2: tag specifying whether the test is a normal one or an async one.
///
/// For example:
/// @code{.cpp}
/// NEW_TEST("Math", "Factorial", "normal") { /*...*/ }
/// @endcode  
///
#define EUTF_NEW_TEST(...) \
struct EUTF_UNAME(EUTF_Test_) : public eutf::test \
{ \
	EUTF_UNAME(EUTF_Test_)() \
		: eutf::test(std::vector<const char*>{ __VA_ARGS__ },\
                __FILE__, __LINE__) \
	{} \
	\
	void run(eutf::generator& generator____, \
            eutf::buffer& buffer____) override; \
}; \
static EUTF_UNAME(EUTF_Test_) EUTF_UNAME(eutf_test_); \
\
void EUTF_UNAME(EUTF_Test_)::run(eutf::generator& generator____,\
                                 eutf::buffer& buffer____)

#ifndef NEW_TEST
#define NEW_TEST(...) EUTF_NEW_TEST(__VA_ARGS__)
#endif

///
/// @brief A test in a test.
///
/// Can have as many tags as you want.
/// "Infinitely" nested sections are supported.
/// You can have sections in a loop.
///
#define EUTF_SECTION(...) \
this->m_section_tags = std::vector<const char*>{ __VA_ARGS__ }; \
\
for(int EUTF_UNAME(eutf_index_) = 0; \
	EUTF_UNAME(eutf_index_) < 1;\
    ++EUTF_UNAME(eutf_index_), \
    this->m_section_tags = std::vector<const char*>{})

#ifndef SECTION
#define SECTION(...) EUTF_SECTION(__VA_ARGS__)
#endif

///
/// @brief Yields a fatal error on failure.
///
/// If this fails the test that is currently run is completely
/// stopped and outputs a fatal error.
///
#define EUTF_ASSERT(...) \
if(!(__VA_ARGS__)) \
{ \
	this->fatal(eutf::test_info{\
            this->m_tags, this->m_section_tags,\
            __LINE__, __FILE__, \
            this->m_number_of_fatal_errors, this->m_number_of_errors, \
            this->m_number_of_warnings, this->m_number_of_messages, \
            #__VA_ARGS__\
            }, buffer____, generator____); \
	\
	return; \
}

#ifndef ASSERT
#define ASSERT(...) EUTF_ASSERT(__VA_ARGS__)
#endif

///
/// @brief Only used inside sections.
///
/// Let's say you are in a section:
/// @code{.cpp}
/// TEST("test") {
///     SECTION("section1") {
///         REQUIRE(2 == 3); 
///         
///         SECTION("section2") {
///             // ...
///         }
///     }
/// // rest of the test 
/// }
/// @endcode
///
/// This will fail and the section2 won't run but the rest of the test will.
/// If you want to exit the test completely when something fails inside a
/// section use @ref EUTF_ASSERT.
///
/// If @ref EUTF_REQUIRE fails it's considered an error(same as 
/// @ref EUTF_EXPECT).
///
/// The difference between this and @ref EUTF_EXPECT inside section is that
/// @ref EUTF_EXPECT will still allow section2 to run. Also keep in mind that
/// @ref EUTF_EXPECT is not limited to sections while @ref EUTF_REQUIRE can 
/// only be called inside a section.
///
/// You can still call @ref EUTF_CHECK, @ref EUTF_MESSAGE
/// inside sections.
///
#define EUTF_REQUIRE(...) \
if(!(__VA_ARGS__)) \
{ \
	this->require(eutf::test_info{\
            this->m_tags, this->m_section_tags,\
            __LINE__, __FILE__, \
            this->m_number_of_fatal_errors, this->m_number_of_errors, \
            this->m_number_of_warnings, this->m_number_of_messages, \
            #__VA_ARGS__\
            }, buffer____, generator____); \
	\
	break; \
}

#ifndef REQUIRE
#define REQUIRE(...) EUTF_REQUIRE(__VA_ARGS__)
#endif

///
/// @brief Yields an error on failure.
///
/// If it fails the rest of the test/section still executes but will output 
/// an error.
///
#define EUTF_EXPECT(...) \
if(!(__VA_ARGS__)) \
	this->expect(eutf::test_info{ \
            this->m_tags, this->m_section_tags,\
            __LINE__, __FILE__, \
            this->m_number_of_fatal_errors, this->m_number_of_errors, \
            this->m_number_of_warnings, this->m_number_of_messages, \
            #__VA_ARGS__\
            }, buffer____, generator____)

#ifndef EXPECT
#define EXPECT(...) EUTF_EXPECT(__VA_ARGS__)
#endif

///
/// @brief Only emits a warning on failure.
///
/// If this fails nothing is stopped and will output a simple warning.
///
#define EUTF_CHECK(...) \
if(!(__VA_ARGS__)) \
	this->warn(eutf::test_info{\
            this->m_tags, this->m_section_tags,\
            __LINE__, __FILE__, \
            this->m_number_of_fatal_errors, this->m_number_of_errors, \
            this->m_number_of_warnings, this->m_number_of_messages, \
            #__VA_ARGS__\
            }, buffer____, generator____)

#ifndef CHECK
#define CHECK(...) EUTF_CHECK(__VA_ARGS__)
#endif

///
/// @brief Outputs the given message.
///
#define EUTF_MESSAGE(...) \
 {  std::stringstream EUTF_UNAME(tmp);\
    EUTF_UNAME(tmp) << __VA_ARGS__;\
this->message(eutf::test_info{\
        this->m_tags, this->m_section_tags,\
        __LINE__, __FILE__, \
        this->m_number_of_fatal_errors, this->m_number_of_errors, \
        this->m_number_of_warnings, this->m_number_of_messages, \
        EUTF_UNAME(tmp).str().c_str()\
        }, buffer____, generator____); }(void)0

#ifndef MESSAGE
#define MESSAGE(...) EUTF_MESSAGE(__VA_ARGS__)
#endif

#include <string>
#include <vector>
#include <iosfwd>

///
/// @brief Contains all necessary data to run tests and give output.
///
namespace eutf {
    ///
    /// @brief Containts info for logging test info on failures/messages.
    ///
    /// When we want to output something when an error/event occurs we need
    /// detailed information to let the user choose what needs to be shown.
    /// This is especially useful for defining custom output generators where
    /// the information needed to be displayed will be received as a parameter.
    /// The information may be a warning at a certain line in a certain file. 
    /// While not every single detail should be shown this struct should contain
    /// as many details as possible.
    ///
    /// @public tags Contains the current test tags.
    /// 
    /// @public section_tags Contains the current section test tags.
    ///                      If the info has been generated outside 
    ///                      a section it's empty.
    /// 
    /// @public line Line where the info was generated.
    /// 
    /// @public file The file where the info was generated. 
    /// 
    /// @public number_of_fatal_errors How many fatal errors does
    ///                                the test where the info was
    ///                                generated currently have?
    /// 
    /// @public number_of_errors How many errors does the test where
    ///                          the info was generated currently have?
    /// 
    /// @public number_of_warnings How many warnings does the test where
    ///                            the info was generated currently have?
    /// 
    /// @public number_of_messages How many messages does the test where
    ///                            the info was generated currently have?
    ///
    /// @public text For a fatal error, an error or a warning it is the 
    ///              code that failed (eg. for ASSERT(2 == 3) @ref text 
    ///              will be "2 == 3"). 
    ///              For a message @ref text will be the actual message
    ///              to be shown.
    ///
    struct test_info
    {
        const std::vector<const char*>& tags;
        const std::vector<const char*>& section_tags;
        const int line;
        const char* file;
        std::size_t number_of_fatal_errors;
        std::size_t number_of_errors;
        std::size_t number_of_warnings;
        std::size_t number_of_messages; 

        //int current_number_of_failures;
        //int current_number_of_errors;
        //int current_number_of_warnings;
        //int current_number_of_messages; 
        
        const char* text;

        test_info() = delete;
        test_info(const std::vector<const char*>& t_tags,
                  const std::vector<const char*>& t_section_tags,
                  const std::size_t t_line, const char* t_file,
                  const std::size_t t_num_of_fatal_errors, 
                  const std::size_t t_num_of_errors,
                  const std::size_t t_num_of_warnings, 
                  const std::size_t t_num_of_messages,
                  //const int t_curr_num_of_failures, 
                  //const int t_curr_num_of_errors,
                  //const int t_curr_num_of_warnings,
                  //const int t_curr_num_of_messages,
                  const char* t_text)
            : tags(t_tags)
            , section_tags(t_section_tags)
            , line(t_line)
            , file(t_file)
            , number_of_fatal_errors(t_num_of_fatal_errors)
            , number_of_errors(t_num_of_errors)
            , number_of_warnings(t_num_of_warnings)
            , number_of_messages(t_num_of_messages)
            //, current_number_of_failures(t_curr_num_of_failures)
            //, current_number_of_errors(t_curr_num_of_errors)
            //, current_number_of_warnings(t_curr_num_of_warnings)
            //, current_number_of_messages(t_curr_num_of_messages)
            , text(t_text)
        {}
        ~test_info() = default;
    };

    ///
    /// The buffer type that will be used for generating output. 
    ///
    using buffer = std::ostream;

    ///
    /// @brief Defines look of generated output.
    ///
    /// Any custom output generator should derive from this struct.
    ///
    struct generator;
    struct logic;

    ///
    /// @brief Every synchronous tests is derived from this struct.
    ///
    /// @protected m_tags Store the tags of the running test. 
    /// @protected m_section_tags Store the tags of the running section.
    ///
    /// @protected m_file The file in which the test has been defined.
    /// @protected m_line The line where the test has been defined.
    ///
    /// @protected m_number_of_fatal_errors The number of fatal errors
    ///                                     that the test has.
    /// @protected m_number_of_errors The number of errors that the test has.
    /// @protected m_number_of_warnings The number of warnings that the
    ///                                 test has.
    /// @protected m_number_of_messages The number of messages that the 
    ///                                 test has.
    ///
    /// @fn void test::fatal   Outputs a fatal error message with the 
    ///                        given output generator.
    /// @fn void test::error   Outputs an error message with the given
    ///                        output generator.
    /// @fn void test::warn    Outputs a warning message with the given
    ///                        output generator.
    /// @fn void test::message Outputs a message with the given output 
    ///                        generator. 
    ///
    /// @fn virtual void test::run Must be overriden, this is what is 
    ///                            called to run the actual tests.
    ///
    /// @fn const char* test::file Returns @ref m_file.
    /// @fn std::size_t test::line Returns a cast to size_t of @ref m_line.
    ///
    /// @fn std::vector<const char*> test::tags Returns the tags of the test. 
    /// @fn std::vector<const char*> test::section_tags Returns the tags of 
    ///                                                 the section. 
    ///                                                     
    /// @fn std::size_t test::get_number_of_fatal_errors Returns the number
    ///                                                  of fatal errors that 
    ///                                                  the test has.
    /// @fn std::size_t test::get_number_of_errors Returns the number of errors
    ///                                            that the test has.
    /// @fn std::size_t test::get_number_of_warnings Returns the number of 
    ///                                              warnings that the test
    ///                                              has.
    /// @fn std::size_t test::get_number_of_messages Returns the number of 
    ///                                              messages that the test has.
    ///
	struct test
	{
	protected:
		std::vector<const char*> m_tags;
		std::vector<const char*> m_section_tags;
		
        const char* m_file{ nullptr };
        int m_line{ 0 };

        std::size_t m_number_of_fatal_errors{ 0 };
        std::size_t m_number_of_errors{ 0 };
        std::size_t m_number_of_warnings{ 0 };
        std::size_t m_number_of_messages{ 0 };

		test() = delete;
		test(std::vector<const char*>&& t_tags, const char* t_file, 
             const int t_line);

		void fatal(const eutf::test_info& t_info,
                   eutf::buffer& t_buffer, eutf::generator& t_generator);
		
        void require(const eutf::test_info& t_info, eutf::buffer& t_buffer, 
                     eutf::generator& t_generator);
		
        void expect(const eutf::test_info& t_info, eutf::buffer& t_buffer,
                    eutf::generator& t_generator);
		
        void warn(const eutf::test_info& t_info, eutf::buffer& t_buffer,
                  eutf::generator& t_generator);
		
        void message(const eutf::test_info& t_info, eutf::buffer& t_buffer,
                     eutf::generator& t_generator);
	
    public:
		virtual ~test() = default;
		virtual void run(eutf::generator& generator____,
                         eutf::buffer& buffer____) = 0;

        inline const char* file() const 
        { return m_file; }
        inline std::size_t line() const
        { return static_cast<std::size_t>(m_line); }

        inline const std::vector<const char*>& tags() const 
        { return m_tags; }
        inline const std::vector<const char*>& section_tags() const
        { return m_section_tags; }

        constexpr std::size_t get_number_of_fatal_errors() const 
        { return m_number_of_fatal_errors; }
        constexpr std::size_t get_number_of_errors() const 
        { return m_number_of_errors; }
        constexpr std::size_t get_number_of_warnings() const 
        { return m_number_of_warnings; }
        constexpr std::size_t get_number_of_messages() const
        { return m_number_of_messages; }
    };

    ///
    /// @brief Every asyncronous test needs to derive from this.
    ///
    /// @protected m_tags Store the tags of the running test. 
    /// @protected m_section_tags Store the tags of the running section.
    ///
    /// @protected m_file The file in which the test has been defined.
    /// @protected m_line The line where the test has been defined.
    ///
    /// @protected m_number_of_fatal_errors The number of fatal errors
    ///                                     that the test has.
    /// @protected m_number_of_errors The number of errors that the test has.
    /// @protected m_number_of_warnings The number of warnings that the
    ///                                 test has.
    /// @protected m_number_of_messages The number of messages that the 
    ///                                 test has.
    ///
    /// @fn void async_test::fatal   Outputs a fatal error message with the 
    ///                              given output generator.
    /// @fn void async_test::error   Outputs an error message with the given
    ///                              output generator.
    /// @fn void async_test::warn    Outputs a warning message with the given
    ///                              output generator.
    /// @fn void async_test::message Outputs a message with the given output 
    ///                              generator. 
    ///
    /// @fn virtual void async_test::run Is not virtual like @ref test::run.
    ///
    /// @fn const char* async_test::file Returns @ref m_file.
    /// @fn std::size_t async_test::line Returns a cast to size_t of @ref m_line.
    ///
    /// @fn std::vector<const char*> async_test::tags Returns the tags of the test. 
    /// @fn std::vector<const char*> async_test::section_tags Returns the tags of 
    ///                                                       the section. 
    ///                                                     
    /// @fn std::size_t async_test::get_number_of_fatal_errors Returns the number
    ///                                                        of fatal errors that 
    ///                                                        the test has.
    /// @fn std::size_t async_test::get_number_of_errors Returns the number of errors
    ///                                                  that the test has.
    /// @fn std::size_t async_test::get_number_of_warnings Returns the number of 
    ///                                                    warnings that the test
    ///                                                    has.
    /// @fn std::size_t async_test::get_number_of_messages Returns the number of 
    ///                                                    messages that the test has.
    ///
    struct async_test
    {
    protected:
        std::vector<const char*> m_tags;
        std::vector<const char*> m_section_tags;
       
        const char* m_file{ nullptr };
        int m_line{ 0 };

        std::size_t m_number_of_fatal_errors{ 0 };
        std::size_t m_number_of_errors{ 0 };
        std::size_t m_number_of_warnings{ 0 };
        std::size_t m_number_of_messages{ 0 };
       
        async_test() = delete;
        async_test(std::vector<const char*>&&, const char* t_file, 
                   const int t_line);
        
        void fatal(const eutf::test_info& t_info, eutf::buffer& t_buffer, 
                   eutf::generator& t_generator);

        void require(const eutf::test_info& t_info, eutf::buffer& t_buffer,
                     eutf::generator& t_generator); 

        void expect(const eutf::test_info& t_info, eutf::buffer& t_buffer,
                    eutf::generator& t_generator);

        void warn(const eutf::test_info& t_info, eutf::buffer& t_buffer, 
                  eutf::generator& t_generator);

        void message(const eutf::test_info& t_info, eutf::buffer& t_buffer,
                     eutf::generator& t_generator);
    public:
        virtual ~async_test() = default;

        inline const char* file() const 
        { return m_file; }
        inline std::size_t line() const
        { return static_cast<std::size_t>(m_line); }

        inline const std::vector<const char*>& tags() const 
        { return m_tags; }
        inline const std::vector<const char*>& section_tags() const
        { return m_section_tags; }

        virtual void run(eutf::generator& generator____);
        virtual void actual_run(eutf::generator& generator____,
                                eutf::buffer& buffer____) = 0;

        constexpr std::size_t get_number_of_fatal_errors() const 
        { return m_number_of_fatal_errors; }
        constexpr std::size_t get_number_of_errors() const 
        { return m_number_of_errors; }
        constexpr std::size_t get_number_of_warnings() const 
        { return m_number_of_warnings; }
        constexpr std::size_t get_number_of_messages() const
        { return m_number_of_messages; }
    };
}

#ifdef EUTF_MAIN

#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <thread>
#include <map>
#include <mutex>

namespace eutf {
    ///
    /// Synchronous tests will use this to store the output.
    ///
    std::stringstream g_buffer;
    ///
    /// This will be used by macros used outside a unit test defined with eutf
    /// for storing the output.
    ///
    std::stringstream g_external_buffer;
    ///
    /// Macros outside eutf unit tests need to be thread safe so this is the 
    /// lock that they use for not having interleaved output.
    ///
    std::mutex g_external_buffer_mutex;
    ///
    /// The tabsize is represented as number of spaces.
    ///
    /// @attention By default the tab size is 4. Use @ref eutf::indent to 
    ///            put one tab, and eutf::indent(n) to put n tabs in 
    ///            an @ref eutf::buffer.
    ///
    /// @attention Use '--tabsize=n' or @ref eutf::tabsize to set the tab 
    ///            size to what you want.
    ///
    std::size_t g_tabsize{ 4 };
    ///
    /// Vector that stores the tags of the tests that should be omitted when 
    /// running the tests. 
    /// 
    /// @attention [WIP] Use '--ignore="tag1","tag2","etc."' or
    ///            @ref eutf::set_filter(std::vector<const char*>{"tags", ...}) 
    ///            to set this vector to whatever you want.
    ///
    /// @attention By default this is empty and all tests will run.
    ///
    std::vector<const char*> g_filter;

    ///
    /// @param[in] t_size The number of spaces for a tab.
    /// 
    /// Modifies the tab size to @ref t_size spaces.
    ///
    void set_tabsize(std::size_t t_size);
    ///
    /// @param[in] t_filter Sets the tags for the tests to be ignored.
    ///
    void set_filter(const std::vector<const char*>& t_filter);
  
    ///
    /// @private n How many times to call @ref eutf::indent.
    /// @public indent_times_t::level Returns how many times to call
    ///                               @ref eutf::indent.
    ///
    /// Structure that holds how many tabs to display to an @ref eutf::buffer. 
    /// There is an operator<< overload for this object type that will call
    /// @ref eutf::indent @ref n times.
    /// 
    struct indent_times_t
    {
    private:
        int n{ 1 };
    public:
        indent_times_t(const int t_n)
            : n(t_n)
        {}

        constexpr int level() const 
        { return n; }
    };
    
    ///
    /// Structure that has an operator() overload which will display however
    /// many tabs the user wants.
    ///
    /// @ref eutf::indent is an object of this type. Thus the user can use it
    /// like this:
    /// @code{.cpp}
    ///     eutf::buffer& out = std::cout;
    ///     out << eutf::indent; // to display one tab
    ///     out << eutf::indent(2); // to display two tabs
    /// @endcode
    /// 
    struct indent_t
    {
        indent_t() = default;

        indent_times_t operator()(const int t_n) const
        { return indent_times_t(t_n); }
    };
    ///
    /// A global object that is used to dislpay one tab in an 
    /// @ref eutf::buffer. 
    ///
    const indent_t indent = indent_t{};
}

std::ostream& operator<<(std::ostream& t_ostream, eutf::indent_t)
{
    for(int i = 0; i < eutf::g_tabsize; ++i) {
        t_ostream << ' ';
    }

    return t_ostream;
}

std::ostream& operator<<(std::ostream& t_ostream, 
                         const eutf::indent_times_t t_indent)
{
    for(int i = 0; i < t_indent.level(); ++i) {
        t_ostream << eutf::indent;
    }

    return t_ostream;
}

#include "cxxopts.hpp"

namespace eutf {
    ///
    /// In the future there should also be html, csv, toml.
    ///
    enum output_type
    { console, xml, json };

    ///
    /// Returns the total number of tests whether they are synchronous or 
    /// asynchronous. Doesn't count when you use macros outside a unit test 
    /// defined with eutf.
    ///
    std::size_t& number_of_tests()
    { 
        static std::size_t n{ 0 };
        return n; 
    }

    ///
    /// Any custom output generator must inherit from this.
    /// All default generators are built like a user might to 
    /// make sure that the structure is well formed.
    /// 
    /// @attention Make sure that everything you do in a generator 
    ///            is thread safe.
    ///            The same generator will be used for both synchronoys 
    ///            and asynchronoys tests. 
    ///            If you are only accessing the buffer and writing to it 
    ///            you are good to go. Just be careful when having your own 
    ///            variables inside a generator. 
    ///
    /// @fn generator::global_begin Will be called before running any tests. 
    ///                             It will be called only once. Useful for eg. for 
    ///                             displaying a byte order mask when saving
    ///                             output to a file.
    /// @fn generator::global_end Will be called once at the end of running all tests.
    ///                           Might want to display how many tests were run.
    /// @fn generator::test_begin Will be called before every test. Might want to 
    ///                           display it's tags here to know what is running.
    /// @fn generator::test_end Will be called at the end of every test. Might want 
    ///                         to display how many errors were in the test here.
    /// @fn generator::fatal Will be called when a fatal error is ecountered.
    /// @fn generator::require Will be called when @ref EUTF_REQUIRE fails. 
    /// @fn generator::error Will be called when @ref EUTF_EXPECT fails.
    /// @fn generator::warn Will be called when @ref EUTF_CHECK fails.
    /// @fn generator::message Will be called when @ref EUTF_MESSAGE gets called.
    ///
    /// For @ref generator::fatal, @ref generator::require, @ref generator::error, 
    /// @ref generator::warn and @ref generator::message you might want to show 
    /// information like the line number where the failure occured and the file
    /// where it happened.
    ///
    struct generator
    {
        virtual void global_begin(const eutf::test_info&,
                                  eutf::buffer&)
        { (void)0; }
        virtual void global_end(const eutf::test_info&,
                                eutf::buffer&) 
        { (void)0; }
        virtual void test_begin(const eutf::test_info&,
                                eutf::buffer&)
        { (void)0; }
        virtual void test_end(const eutf::test_info&,
                              eutf::buffer&) 
        { (void)0; }

        virtual void fatal(const eutf::test_info&,
                           eutf::buffer&) = 0;
        virtual void require(const eutf::test_info&,
                             eutf::buffer&) = 0;
        virtual void expect(const eutf::test_info&,
                            eutf::buffer&) = 0;
        virtual void warn(const eutf::test_info&,
                          eutf::buffer&) = 0;
        virtual void message(const eutf::test_info&,
                             eutf::buffer&) = 0;
    };

    struct console_generator_t : eutf::generator
    {
        console_generator_t() = default;

        virtual void global_begin(const eutf::test_info& t_info,
                                  eutf::buffer& t_buffer) override
        {
            auto n = eutf::number_of_tests(); 
            t_buffer << "Running " << n;
            
            if(n == 1) {
                t_buffer << " test..." << std::endl; 
            }
            else {
                t_buffer << " tests..." << std::endl;
            }

            t_buffer << std::endl;
        }
        
        virtual void global_end(const eutf::test_info& t_info,
                                eutf::buffer& t_buffer) override
        { 
            auto n = eutf::number_of_tests();
            t_buffer << "Ran " << n;

            if(n == 1) {
                t_buffer << " test..." << std::endl; 
            }
            else {
                t_buffer << " tests..." << std::endl; 
            }
            
            t_buffer << std::endl;
        }
        
        virtual void test_begin(const eutf::test_info& t_info,
                                eutf::buffer& t_buffer) override
        {
            t_buffer << "Running test: " << t_info.tags.front();
            t_buffer << "[";

            for(int i = 2; i < t_info.tags.size() - 1; ++i) { 
                t_buffer << t_info.tags[i] << ", ";
            }
            
            if(t_info.tags.size() > 1) {
                t_buffer << t_info.tags.back();
            }

            t_buffer << "]" << std::endl;
            t_buffer << "File: " << t_info.file << std::endl;
            t_buffer << std::endl;
        }  
        virtual void test_end(const eutf::test_info& t_info,
                              eutf::buffer& t_buffer) override
        { 
            t_buffer << "Finished running test " << t_info.tags.front(); 
            t_buffer << std::endl;
            t_buffer << "Fatal errors in this test: ";
            t_buffer << t_info.number_of_fatal_errors << std::endl;
            t_buffer << "Errors in this test: ";
            t_buffer << t_info.number_of_errors << std::endl;
            t_buffer << "Warnings in this test: ";
            t_buffer << t_info.number_of_warnings << std::endl;
            t_buffer << "Messages in this test: ";
            t_buffer << t_info.number_of_messages << std::endl;
            t_buffer << std::endl;
        }

        virtual void fatal(const eutf::test_info& t_info,
                           eutf::buffer& t_buffer) override
        {
            t_buffer << "Fatal error encountered at line ";
            t_buffer << t_info.line << ", file: " << t_info.file << ":";
            t_buffer << std::endl << eutf::indent;
            t_buffer << t_info.text << std::endl; 
        }
        virtual void require(const eutf::test_info& t_info,
                             eutf::buffer& t_buffer) override
        {
            t_buffer << "Error encountered at line " << t_info.line;
            t_buffer << ", file: " << t_info.file << ": ";
            t_buffer << std::endl << eutf::indent;
            t_buffer << t_info.text << std::endl;
        }
        virtual void expect(const eutf::test_info& t_info,
                            eutf::buffer& t_buffer) override
        {
            t_buffer << "Error encountered at line " << t_info.line;
            t_buffer << ", file: " << t_info.file << ": ";
            t_buffer << std::endl << eutf::indent;
            t_buffer << t_info.text << std::endl;
        }
        virtual void warn(const eutf::test_info& t_info,
                          eutf::buffer& t_buffer) override
        { 
            t_buffer << "Warning! line " << t_info.line;
            t_buffer << ", file: " << t_info.file << ": ";
            t_buffer << std::endl << eutf::indent;
            t_buffer << t_info.text << std::endl;
        }
        virtual void message(const eutf::test_info& t_info,
                             eutf::buffer& t_buffer) override
        { 
            t_buffer << "Message: " << t_info.text << std::endl;
        }
    } console_generator;

    struct xml_generator_t : eutf::generator
    {
        ~xml_generator_t() = default;

        virtual void global_begin(const eutf::test_info& t_info,
                                  eutf::buffer& t_buffer) override
        {
            t_buffer << "<NumberOfTests>" << eutf::number_of_tests();
            t_buffer << "</NumberOfTests>" << std::endl << std::endl; 
        }
        virtual void global_end(const eutf::test_info& t_info,
                                eutf::buffer& t_buffer) override
        {
            t_buffer << "<!-- Finished running " << eutf::number_of_tests();
            t_buffer << " tests>" << std::endl;
        }
        virtual void test_begin(const eutf::test_info& t_info,
                                eutf::buffer& t_buffer) override
        {
            t_buffer << "<Test name=\"" << t_info.tags.front() << "\", ";
            t_buffer << "file=\"" << t_info.file << "\", "; 
            t_buffer << "line=" << t_info.line << ">" << std::endl; 

            for(int i = 1; i < t_info.tags.size(); ++i) {
                t_buffer << eutf::indent << "<Tag>";
                t_buffer << t_info.tags[i] << "</Tag>" << std::endl;
            }

            t_buffer << std::endl;
        }  
        virtual void test_end(const eutf::test_info& t_info,
                              eutf::buffer& t_buffer) override
        {
            t_buffer << std::endl;
            t_buffer << eutf::indent << "<!-- Finished running test: ";
            t_buffer << t_info.tags.front();
            t_buffer << ">" << std::endl;

            t_buffer << eutf::indent << "<FatalErrors>";
            t_buffer << t_info.number_of_fatal_errors;
            t_buffer << "</FatalErrors>" << std::endl;

            t_buffer << eutf::indent << "<Errors>"; 
            t_buffer << t_info.number_of_errors;
            t_buffer << "</Errors>" << std::endl;
            
            t_buffer << eutf::indent << "<Warnings>"; 
            t_buffer << t_info.number_of_warnings;
            t_buffer << "</Warnings>" << std::endl;
            
            t_buffer << eutf::indent << "<Messages>"; 
            t_buffer << t_info.number_of_messages;
            t_buffer << "</Messages>" << std::endl;
            
            t_buffer << "</Test>" << std::endl << std::endl;
        }

        virtual void fatal(const eutf::test_info& t_info,
                           eutf::buffer& t_buffer) override
        {
            t_buffer << eutf::indent;
            t_buffer << "<FatalError file=\"" << t_info.file << "\", ";
            t_buffer << "line=" << t_info.line << ">" << std::endl;
            t_buffer << eutf::indent(2) << t_info.text << std::endl;
            t_buffer << eutf::indent << "</FatalError>" << std::endl;
        }
        virtual void require(const eutf::test_info& t_info, 
                             eutf::buffer& t_buffer) override
        { 
            t_buffer << eutf::indent;
            t_buffer << "<Error file=\"" << t_info.file << "\", ";
            t_buffer << "line=" << t_info.line << ">" << std::endl;
            t_buffer << eutf::indent(2) << "<Section ";
            t_buffer << t_info.section_tags.front();
            t_buffer << ">" << std::endl;
            
            for(int i = 1; i < t_info.section_tags.size(); ++i) {
                t_buffer << eutf::indent(3) << "<Tag>";
                t_buffer << t_info.section_tags[i] << "</Tag>";
                t_buffer << std::endl;
            }
            
            t_buffer << eutf::indent(2) << "<Text>";
            t_buffer << t_info.text << "</Text>" << std::endl;
            t_buffer << eutf::indent << "</Error>" << std::endl;
        }
        virtual void expect(const eutf::test_info& t_info,
                            eutf::buffer& t_buffer) override
        { 
            t_buffer << eutf::indent;
            t_buffer << "<Error file=\"" << t_info.file << "\", ";
            t_buffer << "line=" << t_info.line << ">" << std::endl;
            
            if(!t_info.section_tags.empty()) {
                t_buffer << eutf::indent(2) << "<Section ";
                t_buffer << t_info.section_tags.front();
                t_buffer << ">" << std::endl;
                
                for(int i = 1; i < t_info.section_tags.size(); ++i) {
                    t_buffer << eutf::indent(3) << "<Tag>";
                    t_buffer << t_info.section_tags[i] << "</Tag>";
                    t_buffer << std::endl;
                }
                
                t_buffer << eutf::indent(2) << "<Text>";
                t_buffer << t_info.text << "</Text>" << std::endl;
            }
            else {
                t_buffer << eutf::indent(2) << t_info.text << std::endl;
            }

            t_buffer << eutf::indent << "</Error>" << std::endl;
        }
        virtual void warn(const eutf::test_info& t_info,
                          eutf::buffer& t_buffer) override
        {
            t_buffer << eutf::indent;
            t_buffer << "<Warning file=\"" << t_info.file << "\", ";
            t_buffer << "line=" << t_info.line << ">" << std::endl;

            if(!t_info.section_tags.empty()) {
                t_buffer << eutf::indent(2);
                t_buffer << "<Section>" << t_info.section_tags.front();
                t_buffer << std::endl;
                
                for(int i = 1; i < t_info.section_tags.size(); ++i) {
                    t_buffer << eutf::indent(3) << "<Tag>";
                    t_buffer << t_info.section_tags[i];
                    t_buffer << "</Tag>" << std::endl;
                }

                t_buffer << eutf::indent(2) << "</Section>" << std::endl;

                t_buffer << eutf::indent(2) << "<Text>";
                t_buffer << t_info.text << "</Text>" << std::endl;
            }
            else {
                t_buffer << eutf::indent(2) << t_info.text << std::endl;
            }

            t_buffer << eutf::indent << "</Warning>" << std::endl;
        }
        virtual void message(const eutf::test_info& t_info,
                             eutf::buffer& t_buffer) override
        {
            t_buffer << eutf::indent;
            t_buffer << "<Message file=\"" << t_info.file << "\", ";
            t_buffer << "line=" << t_info.line << ">" << std::endl;

            if(!t_info.section_tags.empty()) {
                t_buffer << eutf::indent(2);
                t_buffer << "<Section>" << t_info.section_tags.front();
                t_buffer << std::endl;
                
                for(int i = 1; i < t_info.section_tags.size(); ++i) {
                    t_buffer << eutf::indent(3) << "<Tag>";
                    t_buffer << t_info.section_tags[i];
                    t_buffer << "</Tag>" << std::endl;
                }

                t_buffer << eutf::indent(2) << "</Section>" << std::endl;

                t_buffer << eutf::indent(2) << "<Text>";
                t_buffer << t_info.text << "</Text>" << std::endl;
            }
            else {
                t_buffer << eutf::indent(2) << t_info.text << std::endl;
            }

            t_buffer << eutf::indent << "</Message>" << std::endl; 
        }
    } xml_generator;

    struct json_generator_t : eutf::generator
    {
        json_generator_t() = default;

        virtual void global_begin(const eutf::test_info& t_info,
                                  eutf::buffer& t_buffer) override
        {
            t_buffer << "{ NumberOfTests: \"" << eutf::number_of_tests() << "\"";
            t_buffer << "}" << std::endl;
        }
        virtual void global_end(const eutf::test_info&,
                                eutf::buffer&) override;
        virtual void test_begin(const eutf::test_info& t_info,
                                eutf::buffer& t_buffer) override  
        {
            t_buffer << "{ Test: { Name: \"" << t_info.tags.front();
        }
        virtual void test_end(const eutf::test_info&,
                              eutf::buffer&) override;

        virtual void fatal(const eutf::test_info&,
                           eutf::buffer&) override;
        virtual void require(const eutf::test_info&,
                             eutf::buffer&) override;
        virtual void expect(const eutf::test_info&,
                            eutf::buffer&) override;
        virtual void warn(const eutf::test_info&,
                          eutf::buffer&) override;
        virtual void message(const eutf::test_info&,
                             eutf::buffer&) override;
    };

    ///
    /// Structure that describes how to filter tests that shouldn't be run. 
    /// When setting @ref eutf::g_filter there needs to be a way to 
    /// describe how exactly to filter based on the test's tags.
    /// 
    /// @fn bool logic::operator() Receives two vectors as parameters, the first
    ///                            one being the filter vector and the second one
    ///                            the tags of the test that is currently waiting
    ///                            to be run or not.
    ///                            If this returns true the test will be run,
    ///                            otherwise it won't.
    ///
    /// @attention The default logic will return true if all the tags of the
    ///            test will be found in the filter vector.
    ///
    struct logic
    {
        virtual bool operator()(const std::vector<const char*>&,
                                const std::vector<const char*>&) = 0;
    };

    struct default_logic_t : eutf::logic
    {
        virtual bool operator()(const std::vector<const char*>&,
                                const std::vector<const char*>&) override
        { return true; }
    } default_logic;

    ///
    /// When called with no parameters the actual call will be:
    /// @code{.cpp}
    ///     run_all_tests(eutf::console_generator, eutf::default_logic, nullptr);
    /// @endcode
    ///
    void run_all_tests();
    ///
    /// @param[in] t_generator What the output should look like. By default
    ///                        there is a console generator, an xml generator
    ///                        and a json generator.
    /// @param[in] t_logic What tests to ignore. See @ref eutf::logic.
    /// @param[t_file] If not null it will save the output to a file with
    ///                the given name. If it's null it will print the output 
    ///                to the console.
    ///
	void run_all_tests(eutf::generator& t_generator, eutf::logic& t_logic, 
                       const char* t_file = nullptr);
   
    ///
    /// Describes what to do after parsing command line arguments.
    ///
    /// Command line options should be given like this:
    ///     --long_cmd arg1 arg2 --another_long_cmd 
    /// Or like this:
    ///     -short_cmd arg1 arg2 -another_short_cmd 
    ///
    /// For example specifying the the filter vector:
    ///     -f "async" "factorial"
    /// Or:
    ///     --filter "async" "factorial" 
    ///
    /// @public modify_tabsize If the '-t' or '--tabsize' option has been used
    ///                        then this will be true.
    /// @public tabsize Stores how many spaces a tab should have(if specified, 
    ///                 otherwise the default - 4 - will be considered).
    ///
    /// @public output_file Name of the file to save output to(if specified,
    ///                     otherwise output is printed to the console).
    ///                     Usage: -o Name 
    ///                            --output Name
    ///
    /// @public filter Vector of tags that will be used to ignore certain tests.
    ///                For eg. if '-f "async" "factorial" ' is specified only 
    ///                the tests that contain the tags "async" and "factorial"
    ///                will be run. Of course this is the default behaviour which 
    ///                can be changed by using a custom @ref eutf::logic. 
    ///                Usage: -f Tag1 Tag2 ... Tagn
    ///                       --filter Tag1 Tag2 ... Tagn
    ///
    /// @public output_format How the output should look like. The default 
    ///                       generators are: console, xml and json. Keep 
    ///                       in mind you can have your own custom generator
    ///                       by using a custom @ref eutf::generator.
    ///                       Usage: -s console|xml|json
    ///                              --style console|xml|json
    ///
    struct argparse_info 
    {
        bool modify_tabsize{ false };
        std::size_t tabsize{ 0 };

        const char* output_file{ nullptr };

        std::vector<const char*> filter{};

        eutf::output_type output_format{ eutf::output_type::console };

        argparse_info(const argparse_info&) = default;
        argparse_info(argparse_info&&) = default;
        
        argparse_info& operator=(const argparse_info&) = default;
        argparse_info& operator=(argparse_info&&) = default;
    };
    
    ///
    /// @param[in] t_argc How many arguments have been passed.
    /// @param[in] t_argv The arguments themselves.
    ///
    argparse_info argparse(const int t_argc, const char* const t_argv[])
    {
        argparse_info info;

        for(int i = 1; i < t_argc; ++i) {
            const std::string option = std::string{ t_argv[i] };

            if(option == "-t" || option == "--tabsize") {
                if(i + 1 >= t_argc) {
                    break;
                }
                if(t_argv[i + 1][0] == '-') {
                    continue;
                }

                info.modify_tabsize = true;
                info.tabsize = std::abs(std::stoi(std::string{ t_argv[i + 1] }));
                ++i;
            }
            else if(option == "-f" || option == "--filter") {
                int j;

                for(j = i + 1; j < t_argc; ++j) {
                    if(t_argv[j][0] == '-') {
                        i = j - 1;
                        break;
                    }

                    info.filter.push_back(std::string{ t_argv[j] });
                }
            }
            else if(option == "-o" || option == "--output") {
                if(i + 1 >= t_argc) {
                    break;
                }
                if(t_argv[i + 1][0] == '-') {
                    continue;
                }

                info.output_file = t_argv[i + 1];
                ++i;
            }
            else if(option == "-s" || option == "--style") {
                if(i + 1 >= t_argc) {
                    break;
                }
                if(t_argv[i + 1][0] == '-') {
                    continue;
                }

                const std::string output_format = std::string{ t_argv[i + 1] };

                if(output_format == "console") 
                { info.output_format = eutf::output_type::console; }
                else if(output_format == "xml")
                { info.output_format = eutf::output_type::xml; }
                else if(output_format == "json") 
                { info.output_format = eutf::output_type::json; }

                ++i;
            }
        }

        return info;
    }

    ///
    /// @param t_info Information extracted after parsing the command
    ///               line arguments.
    ///
    /// @param t_logic How to ignore the tests base on @ref eutf::g_filter.
    ///                Needs to be taken as a parameter because there is 
    ///                no way to describe the logic with command line
    ///                arguments. Suppose you want to run all the tests 
    ///                after parsing the command line arguments and want
    ///                a custom logic to ignore the tests. Without taking
    ///                @ref t_logic as a parameter there is no way to do that.
    ///
    void run_all_tests(const argparse_info& t_info, 
            eutf::logic& t_logic = eutf::default_logic)
    {
        if(t_info.modify_tabsize) {
            eutf::set_tabsize(t_info.tabsize);
        }
        if(!t_info.filter.empty()) {
            eutf::set_filter(t_info.filter);
        }

        eutf::generator& gen = [&]() -> eutf::generator& { 
            switch(t_info.output_format)
            {
                case eutf::output_type::console: return eutf::console_generator;
                case eutf::output_type::xml:     return eutf::xml_generator;
                case eutf::output_type::json:    return eutf::json_generator;
                default: return eutf::console_generator;
            }
        }();

        run_all_tests(gen, t_logic, t_info.output_file);
    }

    ///
    /// Returns the queue with the synchronous tests.
    ///
	std::vector<eutf::test*>& get_tests_queue()
	{
		static std::vector<eutf::test*> tests_queue;
		return tests_queue;
	}
    
    ///
    /// Returns the queue with the asynchronous tests.
    ///
    std::vector<eutf::async_test*>& get_async_tests_queue()
    {
        static std::vector<eutf::async_test*> async_tests_queue;
        return async_tests_queue;
    }
}

void eutf::set_tabsize(std::size_t t_size)
{ g_tabsize = t_size; }

void eutf::set_filter(const std::vector<const char*>& t_filter)
{ eutf::g_filter = t_filter; }

eutf::test::test(std::vector<const char*>&& t_tags,
                 const char* t_file, const int t_line)
	: m_tags(std::move(t_tags))
    , m_section_tags(std::vector<const char*>{})
    , m_file(t_file)
    , m_line(t_line)
    , m_number_of_fatal_errors(0)
    , m_number_of_errors(0)
    , m_number_of_warnings(0)
    , m_number_of_messages(0)
{
	eutf::get_tests_queue().push_back(this);
    ++eutf::number_of_tests();
}

eutf::async_test::async_test(std::vector<const char*>&& t_tags,
                             const char* t_file, const int t_line)
    : m_tags(std::move(t_tags))
    , m_section_tags(std::vector<const char*>{})
    , m_file(t_file)
    , m_line(t_line)
    , m_number_of_fatal_errors(0)
    , m_number_of_errors(0)
    , m_number_of_warnings(0)
    , m_number_of_messages(0)
{
    eutf::get_async_tests_queue().push_back(this);
    ++eutf::number_of_tests();
}

void eutf::async_test::run(eutf::generator& t_generator)
{
    std::stringstream tmp{};
    
    this->actual_run(t_generator, tmp);
    
    std::lock_guard<std::mutex> lock(eutf::g_external_buffer_mutex); 

    eutf::g_external_buffer << tmp.str(); 
}

void eutf::run_all_tests(eutf::generator& t_generator,
                         eutf::logic& t_logic,
                         const char* t_file)
{
    t_generator.global_begin(eutf::test_info{
        std::vector<const char*>{}, std::vector<const char*>{},
        0, nullptr, 0, 0, 0, 0, nullptr
    }, eutf::g_buffer);

    std::vector<std::thread> async_tests;

    for(auto& async_test : eutf::get_async_tests_queue()) {
        if(t_logic(eutf::g_filter, async_test->tags())) {
            async_tests.emplace_back([&](){ async_test->run(t_generator); });
        }
    }

    for(auto& test : eutf::get_tests_queue()) {
        if(t_logic(eutf::g_filter, test->tags())) {
            t_generator.test_begin(eutf::test_info{
                test->tags(), test->section_tags(), 
                test->line(), test->file(),
                test->get_number_of_fatal_errors(), 
                test->get_number_of_errors(), 
                test->get_number_of_warnings(), 
                test->get_number_of_messages(),
                nullptr
            }, eutf::g_buffer);

            test->run(t_generator, eutf::g_buffer);

            t_generator.test_end(eutf::test_info{
                test->tags(), test->section_tags(), 
                test->line(), test->file(),
                test->get_number_of_fatal_errors(), 
                test->get_number_of_errors(), 
                test->get_number_of_warnings(), 
                test->get_number_of_messages(),
                nullptr
            }, eutf::g_buffer);
        }
    }

    for(auto& elem : async_tests) {
        elem.join();
    }

    t_generator.global_end(eutf::test_info{
        std::vector<const char*>{}, std::vector<const char*>{},
        0, nullptr, 0, 0, 0, 0, nullptr
    }, eutf::g_buffer);
    
    eutf::g_buffer << eutf::g_external_buffer.str();

    if(!t_file) {
        std::cout << eutf::g_buffer.str();
    }
    else {
        std::ofstream{ t_file } << eutf::g_buffer.str();
    }
}

void eutf::run_all_tests()
{ run_all_tests(eutf::console_generator, eutf::default_logic, nullptr); }

void eutf::test::fatal(const eutf::test_info& t_info, 
                       eutf::buffer& t_buffer, eutf::generator& t_generator) 
{ 
    t_generator.fatal(t_info, t_buffer); 
    ++m_number_of_fatal_errors;
}

void eutf::async_test::fatal(const eutf::test_info& t_info,
                             eutf::buffer& t_buffer, eutf::generator& t_generator)
{
    t_generator.fatal(t_info, t_buffer);
    ++m_number_of_fatal_errors;
}

void eutf::test::require(const eutf::test_info& t_info,
                         eutf::buffer& t_buffer, eutf::generator& t_generator)
{ 
    t_generator.require(t_info, t_buffer);
    ++m_number_of_errors; 
}

void eutf::async_test::require(const eutf::test_info& t_info, 
                               eutf::buffer& t_buffer, 
                               eutf::generator& t_generator)
{
    t_generator.require(t_info, t_buffer);
    ++m_number_of_errors; 
}

void eutf::test::expect(const eutf::test_info& t_info, 
                        eutf::buffer& t_buffer, eutf::generator& t_generator)
{
    t_generator.expect(t_info, t_buffer);
    ++m_number_of_errors;
}

void eutf::async_test::expect(const eutf::test_info& t_info, 
                        eutf::buffer& t_buffer, eutf::generator& t_generator)
{
    t_generator.expect(t_info, t_buffer);
    ++m_number_of_errors;
}

void eutf::test::warn(const eutf::test_info& t_info, 
                      eutf::buffer& t_buffer, eutf::generator& t_generator)
{
    t_generator.warn(t_info, t_buffer);
    ++m_number_of_warnings;
}

void eutf::async_test::warn(const eutf::test_info& t_info, 
                            eutf::buffer& t_buffer, eutf::generator& t_generator)
{
    t_generator.warn(t_info, t_buffer);
    ++m_number_of_warnings;
}

void eutf::test::message(const eutf::test_info& t_info, 
                         eutf::buffer& t_buffer, eutf::generator& t_generator)
{
    t_generator.message(t_info, t_buffer);
    ++m_number_of_messages;
}

void eutf::async_test::message(const eutf::test_info& t_info, 
                               eutf::buffer& t_buffer, 
                               eutf::generator& t_generator)
{
    t_generator.message(t_info, t_buffer);
    ++m_number_of_messages;
}

#endif // EUTF_MAIN

#endif // !ETUF_HPP

