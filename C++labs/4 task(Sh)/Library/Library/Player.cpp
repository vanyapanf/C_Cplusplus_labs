#include "stdafx.h"
#include <iostream>
#include "Player.h"
namespace Application {
	std::ostream & Player::Print(std::ostream &s) const {
		s << "Name:" << Name.c_str()  << std::endl;
		s << "GameTime:" << GameTime << std::endl;
		s << "WrongTime:" << WrongTime << std::endl;
		s << "nom:" << nom << std::endl;
		return s;
	}
	std::ostream & GoalKeeper::Print(std::ostream &s) const {
		Player::Print(s);
		s << "KolBrOtr:" << KolBrOtr << std::endl;
		s << "KolBrNeotr:" << KolBrNeotr << std::endl;
		return s;
	}
	std::ostream & Attacker::Print(std::ostream &s) const {
		Player::Print(s);
		s << "KolBrRes:" << KolBrRes << std::endl;
		s << "KolBrNeres:" << KolBrNeres << std::endl;
		return s;
	}
	std::ostream & operator <<(std::ostream &s, const Player& pl) {
		pl.Print(s);
		return s;
	}
}
