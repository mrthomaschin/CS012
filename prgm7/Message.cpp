#include "Message.h"
#include "Reply.h"
#include "Topic.h"
#include <sstream>
#include <iostream>

using namespace std;


// default constructor
// default constructor
Message::Message()
{
	author = "";
	subject = "";
	body = "";
}

// Parameterized constructor; 
Message::Message(const string &athr, const string &sbjct, const string &body, unsigned id)
{
	author = athr;
	subject = sbjct;
	this->body = body;
	this->id = id;
}

// Be very careful here: some Messages will have two pointers to 
// them, stored in very different places!
// Where are they, and who should be responsible for deleting 
// them?
Message::~Message()
{
	for (unsigned x = 0; x < childList.size(); x++)
		delete childList.at(x);
}

string Message::toFormattedString() const // New!!
{
	stringstream ss;
	string fullString;


	ss << ":id: " << id << endl;
	ss << ":subject: " << subject << endl;
	ss << ":from: " << author << endl;
	if(childList.size() != 0)
	{
		ss << ":children: ";
		for(unsigned c = 0; c < childList.size(); c++)
		{
			ss << (childList.at(c))->getID();
			if(c != childList.size() - 1)
				ss << " ";
		}
		ss << endl;
	}
	ss << ":body: " << body << endl;
	ss << "<end>" << endl;

	fullString = ss.str();

	return fullString;
}

/* This function is responsible for printing the Message
* (whether Topic or Reply), and and all of the Message's
* "subtree" recursively:
* After printing the Message with indentation n and appropriate
* format (see output details), it will invoke itself
* recursively on all of the Replies in its childList,
* incrementing the indentation value at each new level.
*
* Note: Each indentation increment represents 2 spaces. e.g. if
* indentation == 1, the reply should be indented 2 spaces, if
* it's 2, indent by 4 spaces, etc.
*/
void Message::print(unsigned indentation) const // New !!
{
	string space;

	for (unsigned x = 0; x < indentation; x++)
	{
		space += "  ";
	}
	
	if(indentation != 0)
		cout << endl;

	cout << space << "Message #" << id << ": " << subject << endl;
	cout << space << "from " << author << ": ";

	for (unsigned y = 0; y < body.size(); y++)
	{
		cout << body.at(y);
		if (body.at(y) == '\n')
		{
			cout << space;
		}
	}
	cout << endl;

	if (childList.size() != 0)
	{
		for (unsigned z = 0; z < childList.size(); z++)
		{
			childList.at(z)->print(indentation + 1);
		}
	}
}
										//returns the subject string.
const string & Message::getSubject() const
{
	return subject;
}

// returns the ID.
unsigned Message::getID() const // New !!    
{
	return id;
}

// Adds a pointer to the child to the parent's childList. 
void Message::addChild(Message *child) // New !! 
{
	childList.push_back(child);
}