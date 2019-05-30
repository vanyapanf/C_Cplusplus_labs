// Testing.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\Library\Vector.h"
#include "gtest\gtest.h"
TEST(VectorConstructor, DefaultConstructor) {
	Application::Vector v;
	ASSERT_EQ(0, v.GetSZ());
	ASSERT_EQ(NULL, v.GetZnach());
}
TEST(VectorConstructor, InitConstructor) {
	Application::Vector v1(4);
	Application::Vector v2("00xxx1111");
	ASSERT_EQ(4, v1.GetSZ());
	ASSERT_STREQ("xxxx", v1.GetZnach());
	ASSERT_EQ(9, v2.GetSZ());
	ASSERT_STREQ("00xxx1111",v2.GetZnach());
}
TEST(VectorConstructor, TestException) {
	ASSERT_ANY_THROW(Application::Vector("111100000sdede"));
	ASSERT_ANY_THROW(Application::Vector(-1));
}
TEST(VectorMethods, Setters) {
	Application::Vector v(4);
	ASSERT_EQ(4, v.GetSZ());
	ASSERT_STREQ("xxxx", v.GetZnach());
	Application::Vector v11("00xxx1111");
	ASSERT_EQ(9, v11.GetSZ());
	ASSERT_STREQ("00xxx1111", v11.GetZnach());
	Application::Vector v2("00111xxxx");
	Application::Vector v1(v2);
	ASSERT_EQ(9, v1.GetSZ());
	ASSERT_STREQ("00111xxxx", v1.GetZnach());
	Application::Vector v12(v2, 15);
	ASSERT_EQ(15, v12.GetSZ());
	ASSERT_STREQ("00111xxxxxxxxxx", v12.GetZnach());
}
TEST(VectorMethods, Parameters) {
	Application::Vector v1(5);
	Application::Vector v2("00xxx11110000");
	Application::Vector vres = v1 + v2;
	ASSERT_EQ(13, vres.GetSZ());
	ASSERT_STREQ("xxxxx1111xxxx", vres.GetZnach());
	vres = v1*v2;
	ASSERT_EQ(13, vres.GetSZ());
	ASSERT_STREQ("00xxxxxxx0000", vres.GetZnach());
	int res = v1 - v2;
	ASSERT_EQ(0, res);
	vres = ~v1;
	ASSERT_EQ(5, vres.GetSZ());
	ASSERT_STREQ("xxxxx", vres.GetZnach());
	vres = ~v2;
	ASSERT_EQ(13, vres.GetSZ());
	ASSERT_STREQ("11xxx00001111", vres.GetZnach());
	ASSERT_EQ(1, v1.Analysis());
	ASSERT_EQ(1, v2.Analysis());
}
int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}