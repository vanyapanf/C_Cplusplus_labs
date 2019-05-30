#include "stdafx.h"
#include "Team.h"
#include "Game.h"
namespace Application{
//Team
Team::Team(Team &T) {
	KomName = T.GetKomName();
	TrName = T.GetTrName();
	std::vector<Player*>::iterator it;
	for (it = T.PlayerTab.begin(); it != T.PlayerTab.end(); ++it) {
		PlayerTab.push_back(*it);
	}
	std::vector<Game*>::iterator it1;
	for (it1 = T.GameTab.begin(); it1 != T.GameTab.end(); ++it1) {
		GameTab.push_back(*it1);
	}

}
Team::Team(std::string s1, std::string s2) {
	KomName = s1;
	TrName = s2;
}
std::ostream& operator <<(std::ostream &s, /*const*/ Team &t) {
	/*s << "KomName: " << t.KomName.c_str() << std::endl;
	s << "TrName: " << t.TrName.c_str() << std::endl;*/
	std::vector<Player*>::iterator it1 ;
	std::vector<Game*>::iterator it2;
	s << "TeamPlayers" << std::endl;
	for (it1=t.PlayerTab.begin(); it1 != t.PlayerTab.end(); ++it1)
		s << **it1 << std::endl;
	s << "TeamGames" << std::endl;
	for (it2 = t.GameTab.begin(); it2 != t.GameTab.end(); ++it2)
		s << **it2 << std::endl;
	return s;
}
int Team::AddGame(std::string s1,std::string s2) {
	Game* g = new Game;
	g->SetDate(s1);
	g->SetOppName(s2);
	GameTab.push_back(g);
	return 1;
}
Game* Team::FindGame(std::string dateGame) {
	int fl = 0;
	std::vector<Game*>::iterator it;
	for (it = GameTab.begin(); it != GameTab.end(); ++it) {
		std::string Date=(*it)->GetDate();
		if (Date == dateGame)
		{
			fl = 1;
			break;
		}
	}
	if (fl==0) {
		throw std::exception("GameTab have not Game");
		return nullptr;
	}
	return *it;
}
std::vector<Game*>::iterator Team::FindGame1(std::string dateGame) {
	std::vector<Game*>::iterator it;
	for (it = GameTab.begin(); it != GameTab.end(); ++it) {
		std::string Date = (**it).GetDate();
		if (Date == dateGame)
			break;
	}
	if (it == GameTab.end()) {
		throw std::exception("GameTab have not Game");
		return it;
	}
	return it;
}
int Team::DeleteGame(std::string dateGame) {
	std::vector<Game*>::iterator G= FindGame1(dateGame);
	delete(*G);
	GameTab.erase(G);
	return 1;
}
int Team::DeletePlayerTeam(int nom) {
	std::vector<Player *>::iterator P = FindPlayerTeam1(nom);	
	delete(*P);
	PlayerTab.erase(P);
	return 1;
}
int Team::AddPlayerTeam(Player* Pl) {

	PlayerTab.push_back(Pl->clone());
	return 1;
}
int Team::AddPlayerGame(int nom, std::string date) {
	Player* Pl = FindPlayerTeam(nom);
	Game* G = FindGame(date);
	(*G).AddPlayerGame(Pl);
	return 1;
}
int Team::ReplacePlayerGame(int nom1, int nom2, std::string date) {
	Player* Pl= nullptr;
	Game* G=new Game;
	try {
		Pl = FindPlayerTeam(nom1);
    }
    catch (std::exception &ex) {
	   std::cout << ex.what() << std::endl;
    }
	try {
		G = FindGame(date);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	(*G).ReplacePlayerGame(Pl, nom2);
	return 1;
}
Player* Team::FindPlayerTeam(int nom) {
	std::vector<Player*>::iterator it;
	for (it = PlayerTab.begin(); it != PlayerTab.end(); ++it) {
		int nomer = (**it).GetNom();
		if (nomer == nom)
			break;
		if (it == PlayerTab.end()) {
			throw std::exception("PlayerTab have not Player");
			return nullptr;
		}
	}
	return *it;
}
std::vector<Player*>::iterator Team::FindPlayerTeam1(int nom) {
	std::vector<Player*>::iterator it;
	for (it = PlayerTab.begin(); it != PlayerTab.end(); ++it) {
		int nomer = (**it).GetNom();
		if (nomer == nom)
			break;
		if (it == PlayerTab.end()) {
			throw std::exception("PlayerTab have not Player");
			return it;
		}
	}
	return it;
}
int Team::GetWrongTime(std::string s) {
	Game* G;
	int sum;
	try {
		G = FindGame(s);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
	sum = G->GetWrongSumTime();
	return sum;
}
P1It Team::beginP(){
 return P1It(PlayerTab.begin());
}
P1It Team::endP(){
 return	P1It(PlayerTab.end());
}
GIt Team::beginG(){
 return GIt(GameTab.begin());
}
GIt Team::endG(){
 return GIt(GameTab.end());
}
//PIt
const Player& P1It::operator*() const {
	return **cur;
}
int P1It::operator!=(const P1It& it) const {
	return cur != it.cur;
}
int P1It::operator==(const P1It& it) const {
	return cur == it.cur;
}
P1It P1It::operator++() {
	++cur;
	return *this;
}
P1It P1It::operator++(int) {
	P1It it(*this);
	++cur;
	return it;
}
//GIt
const Game& GIt::operator*() const {
	return **cur;
}
int GIt::operator!=(const GIt& it) const {
	return cur != it.cur;
}
int GIt::operator==(const GIt& it) const {
	return cur == it.cur;
}
GIt GIt::operator++() {
	++cur;
	return *this;
}
GIt GIt::operator++(int) {
	GIt it(*this);
	++cur;
	return it;
}
}