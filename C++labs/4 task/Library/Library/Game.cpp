#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <algorithm>
namespace Application {
	//Game
	Game::Game( Game &G) {
		Date = G.GetDate();
		OppName = G.GetOppName();
		Num = G.GetNum();
		std::vector<Player*>::iterator it;
		for (it = G.ActivePl.begin(); it != G.ActivePl.end(); ++it) {
			ActivePl.push_back(*it);
		}
	}
	std::ostream &operator <<(std::ostream &s, /*const*/ Game &g) {
		s << "Date:" << g.Date.c_str() << std::endl;
		s << "OppName:" << g.OppName.c_str() << std::endl;
		s << "GameNum:" << g.Num << std::endl;
		std::vector<Player*>::iterator it;
		s << "GamePlayers:" << std::endl;
		for (it = g.ActivePl.begin(); it != g.ActivePl.end(); ++it) {
			s << **it << std::endl;
		}
		return s;
	}
	Player* Game::FindPlayerGame(int nom) {
		std::vector<Player*>::iterator it;
		for (it = ActivePl.begin(); it != ActivePl.end(); ++it) {
			int nomer = (**it).GetNom();
			if (nomer == nom)
				break;
		}
		if (it == ActivePl.end())
		{
			throw std::exception("ActivePl have not Player");
			return nullptr;
		}
		return *it;
	}
	std::vector <Player*>::iterator Game::FindPlayerGame1(int nom) {
		std::vector<Player*>::iterator it;
		for (it = ActivePl.begin(); it != ActivePl.end(); ++it) {
			int nomer = (**it).GetNom();
			if (nomer == nom)
				break;
		}
		if (it == ActivePl.end())
		{
			throw std::exception("ActivePl have not Player");
			return it;
		}
		return it;
	}
	int Game::AddPlayerGame(Player* pl) {
		/*Player* pl1;
		pl1->SetName(pl->GetName());
		pl1->SetNom(pl->GetNom());
		pl1->SetGameTime(0);
		pl1->SetWrongTime(0);*/
		Player* Pl1 = pl->clone();
		ActivePl.push_back(Pl1);
		/*int k = pl->PlayerType();
		switch (k) {
		case 1: {
			GoalKeeper* GK=new  GoalKeeper;
			GK->SetName(pl->GetName());
			GK->SetNom(pl->GetNom());
			GK->SetGameTime(0);
			GK->SetWrongTime(0);
			GK->SetKolBrOtr(0);
			GK->SetKolBrNeotr(0);
			ActivePl.push_back(GK);
			break;
		}
		case 2:{
			Defender* DF=new Defender;
			DF->SetName(pl->GetName());
			DF->SetNom(pl->GetNom());
		    DF->SetGameTime(0);
			DF->SetWrongTime(0);
			ActivePl.push_back(DF);
			break;
		}
		case 3: {
			Attacker* AT=new Attacker;
			AT->SetName(pl->GetName());
			AT->SetNom(pl->GetNom());
			AT->SetGameTime(0);
			AT->SetWrongTime(0);
			AT->SetKolBrRes(0);
			AT->SetKolBrNeres(0);
			ActivePl.push_back(AT);
			break;
		}
		}*/
		++Num;
		return 1;
	}
	int Game::ReplacePlayerGame(Player* P1/*nom1*/, int nom/*nom2*/) {
		std::vector<Player*>::iterator it;
		for (it = ActivePl.begin(); it != ActivePl.end(); ++it) {
			if ((**it).GetNom() == nom) {
				delete(*it);
				ActivePl.erase(it);
				break;
			}
		}
		ActivePl.push_back(P1->clone());
		return 1;
	}
	int Game::DeletePlayerGame(int nom) {
		std::vector <Player*>::iterator P = FindPlayerGame1(nom);
		delete(*P);
		ActivePl.erase(P);
		return 1;
	}
	int Game::GetWrongSumTime() {
		int sum=0;
		std::vector<Player*>::iterator it;
		for (it = ActivePl.begin(); it != ActivePl.end(); ++it) {
			sum = sum + (*it)->GetWrongTime();
		}
		return sum;
	}
	PIt Game::begin()
	{
		return PIt(ActivePl.begin());
	}
	PIt Game::end() {
		return	PIt(ActivePl.end());
	}
	//PIt
	const Player& PIt::operator*() const {
		return **cur;
	}
	int PIt::operator!=(const PIt& it) const {
		return cur != it.cur;
	}
	int PIt::operator==(const PIt& it) const {
		return cur == it.cur;
	}
	PIt PIt::operator++() {
		++cur;
		return *this;
	}
	PIt PIt::operator++(int) {
		PIt it(*this);
		++cur;
		return it;
	}
}
		
