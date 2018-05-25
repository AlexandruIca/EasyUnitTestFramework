#pragma once
#ifndef TEST_SAMPLE_HPP
#define TEST_SAMPLE_HPP

struct Vec3
{
	double x, y, z;
	
	Vec3();
	Vec3(double a, double b, double c);
	Vec3(const Vec3& other);
	Vec3(Vec3&& other);
};

#endif

