#pragma once
#include <iostream>
namespace Application {
	
	class Player
	{
	private:
		std::string Name;
		int GameTime;
		int WrongTime;
		int nom;
	public:
		virtual Player* clone() /*const*/ = 0;
		int GetNom()const { return nom; };
		std::string GetName()const { return Name; };
		int GetGameTime()const { return GameTime; };
		int GetWrongTime()const { return WrongTime; };
		int SetName(std::string s) { Name = s; return 1; }
		int SetNom(int nomer) { nom = nomer; return 1; }
		int SetGameTime(int gt) { GameTime = gt; return 1; }
		int SetWrongTime(int wt) { WrongTime = wt; return 1; }
		friend std::ostream& operator <<(std::ostream&, const Player&);
		virtual int PlayerType() const = 0;
	protected:
		virtual std::ostream& Print(std::ostream &) const;
	};
	class GoalKeeper :public Player {
	private:
		int KolBrOtr;
		int KolBrNeotr;
	public:
		GoalKeeper *clone()/* const*/ {
			GoalKeeper* GK = new GoalKeeper(*this);
			GK->SetGameTime(0);
			GK->SetWrongTime(0);
			GK->SetKolBrOtr(0);
			GK->SetKolBrNeotr(0);
			return GK;
		}
		int GetKolBrOtr()/*const*/ { return KolBrOtr; };
		int GetKolBrNeotr()/*const*/ { return KolBrNeotr; };
		/*int SetName(std::string s) { Name = s; return 1; }
		int SetGameTime(int gt) { GameTime = gt; return 1; }
		int SetWrongTime(int wt) { WrongTime = wt; return 1; }*/
		int SetKolBrOtr(int kol) { KolBrOtr = kol; return 1; }
		int SetKolBrNeotr(int kol) { KolBrNeotr = kol; return 1; }
		int PlayerType()const { return 1; };
	protected:
		std::ostream& Print(std::ostream &) const;
	};
	class Defender :public Player {
	public:
		Defender *clone()/*const*/ { 
			Defender* DF= new Defender(*this);
			DF->SetGameTime(0);
			DF->SetWrongTime(0);
			return DF;
		};
		int PlayerType()const { return 2; };
	};
	class Attacker :public Player {
	private:
		int KolBrRes;
		int KolBrNeres;
	public:
		Attacker *clone()/*const*/ { 
		   Attacker* AT=new Attacker(*this);
		   AT->SetGameTime(0);
		   AT->SetWrongTime(0);
		   AT->SetKolBrRes(0);
		   AT->SetKolBrNeres(0);
		   return AT;
		};
		int GetKolBrRes()const { return KolBrRes; };
		int GetKolBrNeres()const { return KolBrNeres; };
		int SetKolBrRes(int kol) { KolBrRes = kol; return 1; }
		int SetKolBrNeres(int kol) { KolBrNeres = kol; return 1; }
		int PlayerType()const { return 3; };
	protected:
		std::ostream& Print(std::ostream &) const;
	};
}



