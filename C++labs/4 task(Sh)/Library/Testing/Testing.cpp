// Testing.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\Library\Team.h"
#include "gtest\gtest.h"
TEST(DefenderConstructor,InitConstructor){
	Application::Defender DF;
	Application::Player *P=&DF;
	P->SetGameTime(0);
	P->SetWrongTime(0);
	P->SetName("name");
	P->SetNom(0);
	ASSERT_EQ(0, P->GetGameTime());
	ASSERT_EQ(0, P->GetWrongTime());
	ASSERT_EQ("name", P->GetName());
	ASSERT_EQ(0, P->GetNom());
}
TEST(GoalKeeperConstructor, InitConstructor) {
	Application::GoalKeeper GK;
	Application::Player *P = &GK;
	P->SetGameTime(0);
	P->SetWrongTime(0);
	P->SetName("name");
	P->SetNom(0);
	GK.SetKolBrOtr(0);
	GK.SetKolBrNeotr(0);
	ASSERT_EQ(0, GK.GetKolBrOtr());
	ASSERT_EQ(0, GK.GetKolBrNeotr());
	ASSERT_EQ(0, P->GetGameTime());
	ASSERT_EQ(0, P->GetWrongTime());
	ASSERT_EQ("name", P->GetName());
	ASSERT_EQ(0, P->GetNom());
}
TEST(AttackerConstructor, InitConstructor) {
	Application::Attacker AT;
	Application::Player *P = &AT;
	P->SetGameTime(0);
	P->SetWrongTime(0);
	P->SetName("name");
	P->SetNom(0);
	AT.SetKolBrRes(0);
	AT.SetKolBrNeres(0);
	ASSERT_EQ(0, AT.GetKolBrRes());
	ASSERT_EQ(0, AT.GetKolBrNeres());
	ASSERT_EQ(0, P->GetGameTime());
	ASSERT_EQ(0, P->GetWrongTime());
	ASSERT_EQ("name", P->GetName());
	ASSERT_EQ(0, P->GetNom());
}
TEST(PlayerConstructor, PlayerParameters) {
	Application::GoalKeeper GK;
	GK.SetGameTime(0);
	GK.SetWrongTime(0);
	GK.SetName("name");
	GK.SetNom(0);
	GK.SetKolBrOtr(0);
	GK.SetKolBrNeotr(0);
	Application::Player* Pl = &GK;
	ASSERT_EQ(1, Pl->PlayerType());
	Application::Defender DF;
	GK.SetGameTime(0);
	GK.SetWrongTime(0);
	GK.SetName("name");
	GK.SetNom(0);
	Pl = &DF;
	ASSERT_EQ(2, Pl->PlayerType());
	Application::Attacker AT;
	AT.SetGameTime(0);
	AT.SetWrongTime(0);
	AT.SetName("name");
	AT.SetNom(0);
    AT.SetKolBrRes(0);
	AT.SetKolBrNeres(0);
	Pl = &AT;
	ASSERT_EQ(3, Pl->PlayerType());
}
int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
