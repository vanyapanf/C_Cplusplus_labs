#pragma once
#include <iostream>;
#include <vector>
#include  "Player.h";
namespace Application {
	class Game
	{
	private:
		std::string Date;
		std::string OppName;
		int Num;
		std::vector <Player*> ActivePl;
		friend class PIt;
	public:
		typedef PIt Iterator;
		Game() {};
		Game(/*const*/ Game&);
		~Game() {};
		int SetDate(std::string s) { Date = s; return 1; }
		int SetOppName(std::string s) { OppName = s; return 1; }
		//Game(std::string s1, std::string s2) { Date = s1; OppName = s2; Num = 0; }
		std::string GetDate() { return Date; };
		std::string GetOppName() { return OppName; };
		friend std::ostream &operator <<(std::ostream &, /*const*/ Game &);
		int GetNum() { return Num; };
		//std::vector <Player*> GetActivePl{  };
		Player* FindPlayerGame(int);
		std::vector <Player*>::iterator FindPlayerGame1(int);
		int AddPlayerGame(Player *);
		int ReplacePlayerGame(Player*, int);
		int DeletePlayerGame(int);
		int GetWrongSumTime();
		Iterator begin();
		Iterator end();
	};
	class PIt
	{
	private:
		std::vector<Player*>::iterator cur;
	public:
		PIt(std::vector<Player*>::iterator Ob) :cur(Ob) {};
		PIt() :cur() {};
		const Player& operator*() const;
		PIt operator++();
		PIt operator++(int);
		int operator!=(const PIt&) const;
		int operator==(const PIt&) const;
	};
}

