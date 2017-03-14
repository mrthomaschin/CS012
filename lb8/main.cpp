
#include <iostream>
#include <string>

using namespace std;

void flipString(string &s)
{
	int sizeOf = s.size() - 1;
	string temp;
	char toAdd;

	if (s.size() <= 1)
	{
		return;
	}
	else
	{
		toAdd = s.at(sizeOf);
		temp = s.substr(0, sizeOf);
		flipString(temp);
		s = toAdd + temp;
	}
}

int main() {
	string line;
	cout << "Enter a sentence:" << endl;
	getline(cin, line);
	cout << endl;
	cout << line << endl;
	flipString(line);
	cout << line << endl;

	return 0;
}
