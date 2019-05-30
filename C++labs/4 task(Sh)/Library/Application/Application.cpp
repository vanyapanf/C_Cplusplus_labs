// Application.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\Library\Team.h"
#include <string.h>
#include <iostream>
using namespace Application;
int ShowTeamInfo(Team* t) {
	std::cout<< "KomName: " << (*t).GetKomName().c_str() << std::endl;
	std::cout << "TrName: " << (*t).GetTrName().c_str()<< std::endl;
	return 1;
}
int IncludeNewGame(Team* t) {
	char buf[80];
	std::string s1, s2;
	std::cout << "Enter GameDate:";
	std::cin.getline(buf, 80);
	s1 = buf;
	std::cin.clear();
	//std::cin.ignore(256, '\n');
	std::cout << std::endl;
	std::cout << "Enter OppName:";
	std::cin.getline(buf, 80);
	s2 = buf;
	std::cin.clear();
	//std::cin.ignore(256, '\n');
	Game G;
	//G.SetDate(s1);
	//G.SetOppName(s2);
	(*t).AddGame(s1,s2);
	return 1;
}
int FindGame(Team* t) {
	char buf[80];
	std::string s;
	Game* G;
	std::cout << "EnterDate:";
	std::cin.getline(buf, 80);
	s = buf;
	std::cin.clear();
	//std::cin.ignore(256, '\n');
	try {
		 G = (*t).FindGame(s);
	}
	catch(std::exception &ex){
		std::cout << ex.what() << std::endl;
		return 1;
	}
	std::cout << *G;
	return 1;
}
int DeleteGame(Team* t) {
	char buf[80];
	std::string s;
	std::cout << "EnterDate:" << std::endl;
	std::cin.getline(buf, 80);
	s = buf;
	std::cin.clear();
	//std::cin.ignore(256, '\n');
	try {
		(*t).DeleteGame(s);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	return 1;
}
int ShowTeamTables(Team* t) {
	std::cout << "AllTeamTables" << std::endl;
	std::cout << (*t);
	return 1;
}
int ModifyGameInfo(Team* t) {
	char buf[80];
	std::string s;
	std::cout << "EnterDate:";
	std::cin.getline(buf,80);
	s = buf;
	std::cin.clear();
	//std::cin.ignore(256, '\n');
	std::cout << "Enter deistvie:" << std::endl;
	char* ptr[4] = { "0.AddPlayerGame","1.ReplacePlayerGame","2.DeletePlayerGame","3.SetInfoGame" };
	for (int i = 0; i < 4; ++i)
		std::cout << ptr[i] << std::endl;
	int k;
	std::cout << "Enter deistvie or press ctrl+Z to quit:" << std::endl;
	std::cin >> k;
	switch (k) {
	case 0: {
		int nom;
		std::cout << "Enter NomPlayer:" << std::endl;
		std::cin >> nom;
		try {
			(*t).AddPlayerGame(nom, s);
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
		return 1;
	}
	case 1: {
		int nom1, nom2;
		std::cout << "Enter NomPlayerInTeam:" << std::endl;
		std::cin >> nom1;
		std::cout << "Enter NomPlayerInGame:" << std::endl;
		std::cin >> nom2;
		try {
			(*t).ReplacePlayerGame(nom1, nom2, s);
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
		return 1;
	}
	case 2: {
		Game* G;
		try {
			G = (*t).FindGame(s);
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
			return 1;
		}
		int nom;
		std::cout << "Enter NomPlayer:" << std::endl;
		std::cin >> nom;
		try {
			(*G).DeletePlayerGame(nom);
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
		return 1;
	}
	case 3: {
		Game* G;
		try {
			G = (*t).FindGame(s);
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
			return 1;
		}
		std::string s1, s2;
		char buf[80];
		std::cout << "Enter NewGameDate:" ;
		std::cin.ignore(256, '\n');
		std::cin.getline(buf, 80);
		s1 = buf;
		//std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Enter NewGameOppName:" ;
        std::cin.getline(buf, 80);
		s2 = buf;
		std::cin.clear();
		std::cin.ignore(256,'\n');
		G->SetDate(s1);
		G->SetOppName(s2);
		return 1;
	}
	}
    return 1;
}
int AddPlayerTeam(Team* t) {
	int k;
	char buf[80];
	std::string s;
	char* ptr[3] = { "0.GoalKeeper","1.Defender","2.Attacker" };
	std::cout << "PlayerTypes:" << std::endl;
	for (int i = 0; i < 3; ++i)
		std::cout << ptr[i] << std::endl;
	std::cin >> k;
	std::cin.ignore(256, '\n');
	std::cout << "Enter PlayerName:";
	std::cin.getline(buf, 80);
	s = buf;
    //	std::cin.clear();
	//std::cout<<std::endl;
	std::cout << "Enter PlayerNom:";
    int nomer;
	std::cin >> nomer;
	std::cout << std::endl;
	switch (k){
	case 0: {
		GoalKeeper GK;
		GK.SetName(s);
		GK.SetNom(nomer);
		GK.SetGameTime(0);
		GK.SetWrongTime(0);
		GK.SetKolBrOtr(0);
		GK.SetKolBrNeotr(0);
		(*t).AddPlayerTeam(&GK);
		break;
	}
	case 1: {
		Defender DF;
		DF.SetName(s);
		DF.SetNom(nomer);
		DF.SetGameTime(0);
		DF.SetWrongTime(0);
		(*t).AddPlayerTeam(&DF);
		break;
	}
	case 2: {
		Attacker AT;
		AT.SetName(s);
		AT.SetNom(nomer);
		AT.SetGameTime(0);
		AT.SetWrongTime(0);
		AT.SetKolBrRes(0);
		AT.SetKolBrNeres(0);
		(*t).AddPlayerTeam(&AT);
		break;
	}
	}
	return 1;
}
int ModifyPlayerInfo(Team* t) {
	int nomer, k;
	char buf[80];
	std::string s;
	Player* Pl;
	Player* Pl1;
	Game* G;
	std::cout << "Enter PlayerNom:" << std::endl;
	std::cin >> nomer;
	std::cin.clear();
	std::cin.ignore(256, '\n');
	std::cout << "Enter GameDate:" << std::endl;
	std::cin.getline(buf, 80);
	s = buf;
	std::cin.clear();
	std::cin.ignore(256, '\n');
	try {
		Pl = t->FindPlayerTeam(nomer);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}
	try {
		G = t->FindGame(s);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}
	try {
		Pl1 = G->FindPlayerGame(nomer);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}
	k = Pl->PlayerType();
	switch (k) {
	case 1: {
		int k1;
		char* ptr[4] = { "0.GameTime","1.WrongTime","2.KolBrOtr","3.KolBrNeotr" };
		std::cout << "Enter action:" << std::endl;
		for (int i = 0; i < 4; ++i)
			std::cout << ptr[i] << std::endl;
		GoalKeeper* GK = dynamic_cast<GoalKeeper*>(Pl);
		GoalKeeper* GK1 = dynamic_cast<GoalKeeper*>(Pl1);
		std::cin >> k1;
		switch (k1) {
		case 0: {
			int time;
			std::cout << "Enter Time" << std::endl;
			std::cin >> time;
			Pl->SetGameTime(time + Pl->GetGameTime());
			Pl1->SetGameTime(time);
			break;
		}
		case 1: {
			int time;
			std::cout << "Enter Time" << std::endl;
			std::cin >> time;
			Pl->SetWrongTime(time + Pl->GetWrongTime());
			Pl1->SetWrongTime(time);
			break;
		}
		case 2: {
			int kol;
			std::cout << "Enter KolBrOtr" << std::endl;
			std::cin >> kol;
			GK->SetKolBrOtr(kol + GK->GetKolBrOtr());
			GK1->SetKolBrOtr(kol);
			break;
		}
		case 3: {
			int kol;
			std::cout << "Enter KolBrNeotr" << std::endl;
			std::cin >> kol;
			GK->SetKolBrNeotr(kol + GK->GetKolBrNeotr());
			GK1->SetKolBrNeotr(kol);
			break;
		}
		}
		return 1;
	}
	case 2: {
		int k1;
		char* ptr[4] = { "0.GameTime","1.WrongTime" };
		std::cout << "Enter action:" << std::endl;
		for (int i = 0; i < 3; ++i)
			std::cout << ptr[i] << std::endl;
		/*GoalKeeper* GK = static_cast<GoalKeeper*>(Pl);
		GoalKeeper* GK1 = static_cast<GoalKeeper*>(Pl1);*/
		std::cin >> k1;
		switch (k1) {
		case 0: {
			int time;
			std::cout << "Enter Time" << std::endl;
			std::cin >> time;
			Pl->SetGameTime(time + Pl->GetGameTime());
			Pl1->SetGameTime(time);
			break;
		}
		case 1: {
			int time;
			std::cout << "Enter Time" << std::endl;
			std::cin >> time;
			Pl->SetWrongTime(time + Pl->GetWrongTime());
			Pl1->SetWrongTime(time);
			break;
		}
		}
		return 1;
	}
	case 3: {
		int k1;
		char* ptr[4] = { "0.GameTime","1.WrongTime","2.KolBrRes","3.KolBrNeres" };
		std::cout << "Enter action:" << std::endl;
		for (int i = 0; i < 4; ++i)
			std::cout << ptr[i] << std::endl;
		Attacker* AT = dynamic_cast<Attacker*>(Pl);
		Attacker* AT1 = dynamic_cast<Attacker*>(Pl1);
		std::cin >> k1;
		switch (k1) {
		case 0: {
			int time;
			std::cout << "Enter Time" << std::endl;
			std::cin >> time;
			Pl->SetGameTime(time + Pl->GetGameTime());
			Pl1->SetGameTime(time);
			break;
		}
		case 1: {
			int time;
			std::cout << "Enter Time" << std::endl;
			std::cin >> time;
			Pl->SetWrongTime(time + Pl->GetWrongTime());
			Pl1->SetWrongTime(time);
			break;
		}
		case 2: {
			int kol;
			std::cout << "Enter KolBrRes" << std::endl;
			std::cin >> kol;
			AT->SetKolBrRes(kol + AT->GetKolBrRes());
			AT1->SetKolBrRes(kol);
			break;
		}
		case 3: {
			int kol;
			std::cout << "Enter KolBrNeres" << std::endl;
			std::cin >> kol;
			AT->SetKolBrNeres(kol + AT->GetKolBrNeres());
			AT1->SetKolBrNeres(kol);
			break;
		}
		}
		return 1;
	}
	}
}
	int SumWrongTime(Team* t) {
		char buf[80];
		Game* G;
		std::string s;
		std::cout << "Enter Date:";
		std::cin.getline(buf, 80);
		s = buf;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		int kol = t->GetWrongTime(s);
		if (kol != -1)
			std::cout << "SumTime:" << kol << std::endl;
		return 1;
	}
	/*int SetTeamInfo(Team* t) {
		char buf[80];
		std::string s1,s2;
		std::cout << "Enter KomName:";
		std::cin.getline(buf, 80);
		s1 = buf;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Enter TrName:";
		std::cin.getline(buf, 80);
		s2 = buf;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		(*t)(s1, s2);
		return 1;
	}*/
int main()
{
	Team t("komname", "trname");
	char* ptr[9] = {"0.ShowTeamInfo","1.IncludeNewGame","2.FindGame","3.DeleteGame",
		"4.ShowTeamTables","5.ModifyGameInfo","6.IncludeNewPlayer","7.ModifyPlayerInfo","8.SumWrongTimeInTeam"/*,"9.SetNewTeamInfo"*/};
	std::cout << "Menu:" << std::endl;
	for (int i = 0; i < 9; ++i)
		std::cout << ptr[i] << std::endl;
	int fl = 1;
	while (fl) {
		int k;
		std::cout << "Enter deistvie or press ctrl+Z to quit:" << std::endl;
		std::cin >> k;
		std::cin.ignore(80, '\n');
		if (std::cin.eof())
			break;
		switch (k) {
		case 0: {
			int i = ShowTeamInfo(&t);
			break; }
		case 1: {
			int i = IncludeNewGame(&t);
			break; }
		case 2: {
			int i = FindGame(&t);
			break; }
		case 3: {
			int i = DeleteGame(&t);
			break; }
		case 4: {
			int i = ShowTeamTables(&t);
			break; }
		case 5: {
			int i = ModifyGameInfo(&t);
			break;
		}
		case 6: {
			int i = AddPlayerTeam(&t);
			break;
		}
		case 7: {
			int i = ModifyPlayerInfo(&t);
			break;
        }
		case 8: {
			int i = SumWrongTime(&t);
			break;
		}
		/*case 9: {
			int i = SetTeamInfo(&t);
			break;
		}*/
		}
	}
    return 0;
}

