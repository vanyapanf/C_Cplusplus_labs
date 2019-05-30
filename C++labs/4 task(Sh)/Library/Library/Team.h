#pragma once
#include <iostream>
#include "MyVector.h"
#include "Game.h"
namespace Application {
	class Team
	{
	private:
		std::string KomName;
		std::string TrName;
		Vector <Player*> PlayerTab;
		Vector <Game*> GameTab;
		friend class P1It;
		friend class GIt;
	public:
		Team() {};
		Team(std::string s1, std::string s2);
		Team(Team&);
		~Team() {};
		std::string GetKomName() { return KomName; };
		std::string GetTrName() { return TrName; };
		//int *GetPlayerTab() { return &(PlayerTab.begin()); };
		//std::vector<Player *>& operator=(const std::vector <Player *> &);
		friend std::ostream &operator <<(std::ostream &, /*const*/ Team &);
		int AddGame(std::string,std::string);
		Game* FindGame(std::string);
		Vector<Game*>::iterator FindGame1(std::string);
		int DeleteGame(std::string);
		int AddPlayerGame(int, std::string);
		int ReplacePlayerGame(int, int, std::string);
		int AddPlayerTeam(/*const*/ Player*);
		Player* FindPlayerTeam(int);//player pointer 
		Vector<Player*>::iterator FindPlayerTeam1(int);//iterator
		int DeletePlayerTeam(int);
		int GetWrongTime(std::string);
		P1It beginP();
		P1It endP();
		GIt beginG();
		GIt endG();
	};
	class GIt
	{
	private:
		Vector<Game*>::iterator cur;
	public:
		GIt(Vector<Game*>::iterator Ob) :cur(Ob) {};
		GIt() :cur() {};
		const Game& operator*() const;
		GIt operator++();
		GIt operator++(int);
		int operator!=(const GIt&) const;
		int operator==(const GIt&) const;
	};
	class P1It
	{
	private:
		Vector<Player*>::iterator cur;
	public:
		P1It(Vector<Player*>::iterator Ob) :cur(Ob) {};
		P1It() :cur() {};
		const Player& operator*() const;
		P1It operator++();
		P1It operator++(int);
		int operator!=(const P1It&) const;
		int operator==(const P1It&) const;
	};
}

