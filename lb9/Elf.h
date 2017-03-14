#ifndef ELF_H
#define ELF_H

#include "Character.h"
#include <iostream>
#include <string>

using namespace std;

class Elf : public Character
{
private:
	string famName;

public:
	Elf(const string &name, double health, double attackStrength, string famName);

	string getFamily();

	void attack(Character &opponent);
};

#endif