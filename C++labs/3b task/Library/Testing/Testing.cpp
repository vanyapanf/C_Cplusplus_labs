// Testing.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\Library\Vector.h"
#include "gtest\gtest.h"
TEST(VectorConstructor, DefaultConstructor) {
	Application::Vector v;
	ASSERT_EQ(0, v.GetN());	ASSERT_EQ("", v.GetZnach());
}
/*
TEST(VectorConstructor, InitConstructor) {
	Application::Vector v1(4);
	Application::Vector v2("00xxx1111");
	ASSERT_EQ(4, v1.GetN());
	ASSERT_EQ("xxxx", v1.GetZnach());
	ASSERT_EQ(9, v2.GetN());
	ASSERT_EQ("00xxx1111", v2.GetZnach());
}
*/
int _tmain(int argc,_TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

