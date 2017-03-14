//Message.h

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message {
 private:
	string author;
	string subject;
	string body;

 public:

	// default constructor
	Message();
	
	// Parameterized constructor; 
	Message(const string &athr, 
	     const string &sbjct, 
	     const string &body);
	
	//displays Message.
	void display() const;	
};

#endif