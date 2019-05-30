// Testing.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\Library\Deltoida.h"
#include "gtest\gtest.h"
TEST(DeltoidaConstructor, DefaultConstructor) {
	Application::Deltoida D1;
	ASSERT_EQ(0, D1.GetP().x);
	ASSERT_EQ(0, D1.GetP().y);
	ASSERT_EQ(1, D1.GetR());
}
TEST(DeltoidaConstructor,InitConstructor) {
	Application::Deltoida D2(3);
	Application::Point p(2, 3);
	ASSERT_EQ(3, D2.GetR());
	ASSERT_EQ(0, D2.GetP().x);
	ASSERT_EQ(0, D2.GetP().y);
	Application::Deltoida D3(p,4);
	ASSERT_EQ(4, D3.GetR());
	ASSERT_EQ(2, D3.GetP().x);
	ASSERT_EQ(3, D3.GetP().y);
	Application::Deltoida D4(1, 2, 3);
	ASSERT_EQ(3, D4.GetR());
	ASSERT_EQ(1, D4.GetP().x);
	ASSERT_EQ(2, D4.GetP().y);
}
TEST(DeltoidaConstructor, TextException) {
	Application::Point p;
	ASSERT_ANY_THROW(Application::Deltoida(1, 2, -3));
	ASSERT_ANY_THROW(Application::Deltoida(p, -3));
}
TEST(DeltoidaMethods, Setters) {
	Application::Deltoida D;
	Application::Point p1(2,2);
	D.SetP(p1);
	ASSERT_EQ(2, D.GetP().x);
	ASSERT_EQ(2, D.GetP().y);
	Application::Point p2(-2, -2);
	D.SetP(p2);
	ASSERT_EQ(-2, D.GetP().x);
	ASSERT_EQ(-2, D.GetP().y);
	D.SetR(2);
	ASSERT_EQ(2, D.GetR());
	ASSERT_ANY_THROW(D.SetR(-1));
}
TEST(DeltoidaMethods, Parameters) {
	Application::Deltoida D1(1,1,1);
	const double err = 0.01, PI = 3.14;
	double r = D1.area();
	ASSERT_NEAR(0.698, D1.area(), err);// near eq
	ASSERT_NEAR(1.33, D1.lenght1(),err);
	ASSERT_NEAR(5.33, D1.lenght2(), err);
	Application::Point p;
	p = D1.coordinates(PI);
	ASSERT_NEAR(-1, p.x, err);
	ASSERT_NEAR(0, p.y, err);
	ASSERT_STREQ("x=2*1.00*cos(t)+1.00*cos(2*t);y=2*1.00*sin(t)-1.00*sin(2*t)\n",D1.frm());
}
int _tmain(int argc,_TCHAR* argv[])
{
	char c;
	::testing::InitGoogleTest(&argc, argv);
     RUN_ALL_TESTS();
	 std::cout << "Press x to quit" << std::endl;
	 std::cin >> c;
	 return 0;
}


