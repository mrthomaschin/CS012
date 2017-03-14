#include "Warrior.h"
#include <iostream>
#include <string>

using namespace std;

Warrior::Warrior(const string &name, double health, double attackStrength, string allegiance)
	: Character(WARRIOR, name, health, attackStrength), allegiance(allegiance)
{

}

string Warrior::getAlleg()
{
	return allegiance;
}

void Warrior::attack(Character &opponent)
{
	double dmg;

	dmg = (health * 1.0) / MAX_HEALTH;
	dmg = dmg * attackStrength;

	if (opponent.getType() == WARRIOR)
	{
		Warrior &opp = dynamic_cast<Warrior &>(opponent);

		if (allegiance == opp.getAlleg())
		{
			cout << "Warrior " << name << " does not attack Warrior " << opponent.getName() << "." << endl;
			cout << "They share an allegiance with " << allegiance << "." << endl;
		}
		else
		{
			cout << "Warrior " << name << " attacks " << opponent.getName() << " --- SLASH!!" << endl;
			opponent.setHealth(opponent.getHealth() - dmg);
			cout << opponent.getName() << " takes " << dmg << " damage." << endl;
		}
	}
	else
	{
		cout << "Warrior " << name << " attacks " << opponent.getName() << " --- SLASH!!" << endl;
		opponent.setHealth(opponent.getHealth() - dmg);
		cout << opponent.getName() << " takes " << dmg << " damage." << endl;
	}
}