#include "Wizard.h"
#include <iostream>
#include <string>

using namespace std;

Wizard::Wizard(const string &name, double health, double attackStrength, int rank)
	: Character(WIZARD, name, health, attackStrength), rank(rank)
{

}

int Wizard::getRank()
{
	return rank;
}

void Wizard::attack(Character &opponent)
{
	double dmg;

	if (opponent.getType() == WIZARD)
	{
		Wizard &opp = dynamic_cast<Wizard &>(opponent);

		dmg = (rank * 1.0) / opp.getRank();
		dmg = dmg * attackStrength;

		cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl;
		cout << opponent.getName() << " takes " << dmg << " damage." << endl;
		opponent.setHealth(opponent.getHealth() - dmg);
	}
	else
	{
		dmg = attackStrength;

		cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl;
		cout << opponent.getName() << " takes " << dmg << " damage." << endl;
		opponent.setHealth(opponent.getHealth() - dmg);
	}
}