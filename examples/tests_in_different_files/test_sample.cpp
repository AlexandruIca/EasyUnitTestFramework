#include "test_sample.hpp"

#include <utility>

#include "EUTF.hpp"

Vec3::Vec3()
	: x(0.0)
	, y(0.0)
	, z(0.0)
{}

Vec3::Vec3(double a, double b, double c)
	: x(a)
	, y(b)
	, z(c)
{}

Vec3::Vec3(const Vec3& other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
{}

Vec3::Vec3(Vec3&& other)
	: x(std::move(other.x))
	, y(std::move(other.y))
	, z(std::move(other.z))
{}

//
// * Test the vector class right where it's been created
//
EUTF_TEST_SUITE(u8"Vec3 test suite")
{
	EUTF_NEW_TEST(u8"constructor", u8"default")
	{
		Vec3 vec{};

		EUTF_CHECK(vec.x == 0.0);
		EUTF_CHECK(vec.y == 0.0);
		EUTF_CHECK(vec.z == 0.0);
	}

	EUTF_NEW_TEST(u8"constructor", u8"double")
	{
		Vec3 vec{ 1.6, 2.3, 4.1 };

		EUTF_EXPECT(vec.x == 2.0);
		EUTF_EXPECT(vec.y == 2.3);
		EUTF_ASSERT(vec.z == 5.0);
		EUTF_CHECK(vec.x + vec.y == 4.0);
	}

	EUTF_NEW_TEST(u8"constructor", u8"copy")
	{
		Vec3 vec_tmp{ 2.0, 3.0, 4.0 };
		Vec3 vec{ vec_tmp };

		EUTF_EXPECT(vec.x == 2.0);
		EUTF_EXPECT(vec.y == 3.0);
		EUTF_EXPECT(vec.z == 4.0);
	}

	EUTF_NEW_TEST(u8"constructor", u8"move")
	{
		Vec3 vec{ Vec3{ 1.0, 2.0, 3.0 } };

		EUTF_MESSAGE(u8"Move constructor");
		EUTF_CHECK(vec.x + vec.y + vec.z == 6.0);
	}
}
EUTF_END_TEST_SUITE();

