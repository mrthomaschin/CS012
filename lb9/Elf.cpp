#include "Elf.h"
#include <iostream>
#include <string>

using namespace std;

Elf::Elf(const string &name, double health, double attackStrength, string famName) 
	: Character(ELF, name, health, attackStrength), famName(famName)
{

}

string Elf::getFamily()
{
	return famName;
}


void Elf::attack(Character &opponent)
{
	double dmg = (health * 1.0) / MAX_HEALTH;
	dmg = dmg * attackStrength;

	if (opponent.getType() == ELF)
	{
		Elf &opp = dynamic_cast<Elf &>(opponent);

		if (famName == opp.getFamily())
		{
			cout << "Elf " << name << " does not attack Elf " << opponent.getName() << "." << endl;
			cout << "They are both members of the " << famName << " family." << endl;
		}
		else
		{
			cout << "Elf " << name << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
			opponent.setHealth(opponent.getHealth() - dmg);
			cout << opponent.getName() << " takes " << dmg << " damage." << endl;
		}
	}
	else
	{
		cout << "Elf " << name << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
		opponent.setHealth(opponent.getHealth() - dmg);
		cout << opponent.getName() << " takes " << dmg << " damage." << endl;
	}
}
