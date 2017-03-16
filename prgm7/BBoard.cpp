#include "BBoard.h"
#include "Topic.h"
#include "Reply.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

//default constructor that creates a board with a default title, empty user and message lists
//and a no current user (what should the pointer be set to if there is nothing to point to?)
BBoard::BBoard()
{
	title = "";
}

// Same as the default constructor except 
// it sets the title of the board
BBoard::BBoard(const string &ttl)
{
	title = ttl;
}

//destructor that deallocates all Messages ointed to by messageList
//THINK CAREFULLY ABOUT THIS!!!
BBoard::~BBoard()
{
	for (unsigned x = 0; x < messageList.size(); x++)
		delete messageList.at(x);
}

// Gets a filename(userfile) of a file that stores the user info in a given format
//Opens and reads the file of all authorized users and passwords
//constructs a User object from each name/password pair, and populated the userList Vector.
bool BBoard::loadUsers(const string &filename)
{
	User usertopush;
	ifstream fileIn;
	string username;
	string password;

	fileIn.open(filename.c_str());

	if (!fileIn.is_open())
	{
		return false;
	}

	while (fileIn >> username >> password)
	{
		if (username != "end")
		{
			addUser(username, password);
		}
	}
	fileIn.close();

	return true;
}

//NEW
//filename (datafile) of a file that stores the messages from the previous sessions in the given format
//It opens and reads the file, creating Topic and Reply objects as appropriate, and fills the message List vector
//Note: messageList is a vector of POINTERS	
bool BBoard::loadMessages(const string& datafile)
{
	ifstream fileIn;
	ofstream fileOut;
	stringstream ss;

	unsigned messageNum = 0;

	string tempStr;
	string checkType;
	vector<unsigned> childIndex;
	int counter = 0;
	int toInt = 0;

	string a;
	string s;
	string b;
	string child;
	unsigned i;
	
	fileIn.open(datafile.c_str());
	
	if (!fileIn.is_open())
	{
		return false;
	}
	
	Topic *tempTop = 0;
	Reply *tempRep = 0;
	
	fileIn >> messageNum;
	
	if(messageNum != 0)
	{
		
		for(unsigned x = 0; x < messageNum; x++)
		{
			fileIn >> tempStr;
			checkType = tempStr;
			
			a = "";
			s = "";
			b = "";
			child = "";
			i = 0;
	
			while(tempStr != "<end>")
			{
				if(tempStr != ":body:" && tempStr != ":children")
					fileIn >> tempStr;
	
				if(tempStr == ":id:")
				{
					fileIn.ignore(); //whitespace
					fileIn >> i;
				}
				else
					if(tempStr == ":subject:")
					{
						fileIn.ignore();
						getline(fileIn, s);
					}
					else
						if(tempStr == ":from:")
						{
							fileIn.ignore();
							fileIn >> a;
						}
						else
							if(tempStr == ":children:")
							{
								fileIn.ignore();
								
								while(tempStr != ":body:")
								{
									fileIn >> tempStr;
									
									ss.clear();
									ss.str(tempStr);
									ss >> toInt;
									childIndex.push_back(toInt);
								}
									
							}
							else
								if(tempStr == ":body:")
								{
									fileIn.ignore();
									getline(fileIn, tempStr);
									b += tempStr;
									
									while(tempStr != "<end>")
									{
										getline(fileIn, tempStr);
										if(tempStr != "<end>")
											b += "\n" + tempStr;
									}
								}
			}
			
			if(checkType == "<begin_topic>")
				{
					tempTop = new Topic(a, s, b, i);
					messageList.push_back(tempTop);
				}
				else
					if(checkType == "<begin_reply>")
					{
						tempRep = new Reply(a, s, b, i);
						messageList.push_back(tempRep);
					}
					
			childIndex.push_back(0);
		}
		
		for(unsigned y = 0; y < childIndex.size() - 1; y++) //Store child Messages in respected childLists
		{
			if(childIndex.at(y) != 0)
			{
				(messageList.at(counter))->addChild(messageList.at(childIndex.at(y) - 1));
			}
			else
				if(childIndex.at(y) == 0 && childIndex.at(y + 1) != 0)
				{
					counter++;
				}
		}
	}
	return true;
}

//Final action of the bulletin board before closing:
//Gets a filename (datafile) of a file that will store all of the messages, and after opening the file 
//writes the messages into it with the same format
//If an error occurs when opening the file, it returns false. Returns true otherwise
//"file not found" is NOT AN ERROR
bool BBoard::saveMessages(const string &datafile)
{
	ofstream fileOut;

	fileOut.open(datafile.c_str());

	fileOut << messageList.size() << endl;

	for (unsigned x = 0; x < messageList.size(); x++)
	{
		fileOut << messageList.at(x)->toFormattedString();
	}

	fileOut.close();

	return true;


}

// Asks for and validates a user/password.
//This function asls for a username and a password. and checks the userList vector for a matching User.
//If a match is found, it sets currentUser to the identified User from the list (remember POINTER)
//If not, it will keep asking unti a match is found or the user types 'q' or 'Q' as username
//When user chooses to quit, say "Bye!" and return from the login function
bool BBoard::login()
{
	User temp;
	bool checking = true;
	string user;
	string pass;

	cout << "Welcome to " << title << endl;
	while (checking)
	{
		cout << "Enter your username ('Q' or 'q' to quit): ";
		cin >> user;


		//If user hasn't enetered q, continue to password
		if (user != "q" && user != "Q")
		{
			cout << "Enter your password: ";
			cin >> pass;

			//Attempt to find user
			currentUser = getUser(user, pass);
			if (currentUser == 0)
			{
				//Prompts user to enter credentials again
				cout << "Invalid Username or Password!" << endl;
				cout << endl;
			}
			else
			{
				checking = false;
			}
		}
		else
		{
			cout << "Bye!" << endl;
			BBoard();
			exit(0);
		}

	}

	//Conclusion: User entered 'q' or "q"
	return false;
}

// Contains main loop of Bulletin Board.
// IF AND ONLY IF there is a valid currentUserm enter main loop, displaying menu items
//---Display Messages ('D' or 'd')
//---Add New Topic ('N' or 'n')
//---Add Reply ('R' or 'r')
//---Quit ('Q' or 'q')
//With any wrong input, user is asked to try again
//Q/q should reset curretnUser to 0 and then end return
//NOTE: if login() did not set a valid currentUSer, function must immediately return without showing menu
void BBoard::run()
{
	char action;
	bool stop = false;
	
	if(currentUser == 0)
		exit(0);

	while (!stop)
	{
		cout << "Menu" << endl;
		cout << "- Display Messages ('D' or 'd')" << endl;
		cout << "- Add New Topic ('N' or 'n')" << endl;
		cout << "- Add Reply to a Topic ('R' or 'r')" << endl;
		cout << "- Quit ('Q' or 'q')" << endl;
		cout << "Choose an action: ";
		cin >> action;

		if (action == 'D' || action == 'd')
		{
			cout << endl;
			display();
		}
		else
			if (action == 'N' || action == 'n')
			{
				addTopic();
			}
			else
				if (action == 'R' || action == 'r')
				{
					addReply();
				}
				else
					if (action == 'Q' || action == 'q')
					{
						cout << "Bye!";
						stop = true;
						cout << endl;
					}
	}
}


/******private*******/

//This function may be called from the loadUsers function to add the users from the file to the userList
void BBoard::addUser(const string &name, const string &pass)
{
	User tempUser = User(name, pass);
	userList.push_back(tempUser);
}

//Includes the functionality of the old "user_exists" helper
//It traverses the userList, testing for the existence of a User with the given name and password
//If this User is NOT found, the function returns 0 (nullptr)
//Otherwise it returns a POINTER to the identified User (return &userList.(i))
//May be used by login() to set the currentUser
//No other way to set current user to anything other than 0
const User *BBoard::getUser(const string &name, const string &pw) const
{
	User current;

	for (unsigned x = 0; x < userList.size(); x++)
	{
		current = userList.at(x);

		//compares username and password to current user
		if (current.check(name, pw))
		{
			//sets the entered user and pass to currentuser credentials
			cout << "\nWelcome back " << current.getUsername() << "!" << endl;
			cout << endl;

			return &userList.at(x);
		}
	}

	return 0;
}

//Traverses the BBoard's message list, and invoke the print function on Topic objects ONLY
//It will then be the responcilbilty of the Topic object to invoke the print function recursively on its own replies
//The BBoard display function will ignore all REply objects in its message list
void BBoard::display() const
{

	if (messageList.empty())
	{
		cout << "Nothing to Display." << endl;
		cout << endl;
	}
	else
	{
		for (unsigned x = 0; x < messageList.size(); x++)
		{
			if(messageList.at(x)->isReply() == false)
			{
				cout << "---------------------------------------------------------" << endl;
				(messageList.at(x))->print(0);
			}
		}

		cout << "---------------------------------------------------------" << endl;
		cout << endl;
	}
}

//This function asks the user to create a new Topic (i.e. the first message of a new discussion "thread"). 
//Every Topic includes a subject (single line), and a body that may consist of  multiple lines. e.g.,


/*Subject: "Thanks"
Body : "I would like to thank you for this awesome board.
I'll visit here regularly."*/


//The body ends when the user enters an empty line(i.e.a "double enter").
//Each Topic also stores the username of currentUser; and a message id, which is

//(index of its Message* +1)

//For example, the first message on the board will be a Topic whose pointer will be stored at index 0 of the messageList vector, 
//so its message id will be(0 + 1) = 1
//(there are better ways of establishing unique ids for a set of objects, but for now this will work fine)
//Once the Topic has been constructed, a pointer to it is added to messageList.
//Hint: Do you need pointers to automatic or dynamic Topics ?
void BBoard::addTopic()
{
	string athr;
	string sbjt;
	string body;
	unsigned id;
	
	string tempStr = "";

	athr = currentUser->getUsername();
	
	cin.ignore();
	cout << "Enter Subject: ";
	getline(cin, tempStr);
    
    sbjt = tempStr;

	cout << "Enter Body: ";
    getline(cin, tempStr);
    while(tempStr !=  "")
    {
        body += tempStr + '\n';
        getline(cin, tempStr);
    }
    
    body = body.substr(0, body.size() - 1);
    cout << endl;

	id = messageList.size() + 1;

	Topic *temp = new Topic(athr, sbjt, body, id);
	messageList.push_back(temp);
}

//This function asks the user to enter a reply to a given Message (which may be either a Topic or a Reply, so we can handle nested replies).
//	The addReply function first asks the user for the id of the Message to which they are replying; 
//if the number provided is greater than the size of messageList it should output an error message and loop back, 
//continuing to ask for a valid Message id number until the user enters either - 1 
//(or any negative number, to return to the menu); or a valid id.

//If the id is valid, then the function asks for the body of the new message, 
//and constructs the Reply, pushing back a pointer to it on the messageList
//The subject of the Reply is a copy of the parent Topic's subject with the "Re: " prefix.
//e.g., suppose the subject of message #9 was "Thanks", and a user is replying to that message :

	/*Enter Message ID : 9
	Body : It was a pleasure implementing this.
	I hope everyone likes it.*/



//Note : As before, the body ends when the user enters an empty line.
//The above dialog will generate a reply that has "Re: Thanks" as its subject 
//and "It was a pleasure implementing this.\nI hope everyone likes it." as its body.

//How will we know what Topic this is a reply to ?
//In addition to keeping a pointer to every Message(whether Topic or Reply) in BBoard's messageList vector, 
//every Message (whether Topic or Reply) will also store a vector of pointers to all its own Replies.
//So whenever we build a Reply, we must immediately store a pointer to it inside its parent Message.Therefore, you will :
//create a dynamic Reply with the input data.The Reply's constructor should set the Reply's subject to "Re: " + its parent's subject.
//call the addChild function on the parent message to push_back the Message* (to the new Reply) to the parent's childList vector;
//Finally, push_back the same pointer to BBoard's messageList.
//Note: When the user chooses to return to the menu, do not call run() again - just return from this addReply function.
void BBoard::addReply()
{
    //User currentUser = User(unme, paword);
    string tempStr;
    string sub;
    string bod = "";
    unsigned msID= messageList.size()+1;
    unsigned thisID;
    
    while(true)
    {
        cout << "Enter Message ID(-1 for Menu): ";
        cin >> thisID;
        
        if (thisID < 0)
        {
            return;
        }
        else 
        	if (thisID == 0 || thisID > messageList.size())
        	{
            	cout << "Invalid Message ID!!" << endl << endl;
        	}
        	else
        	{
            	break;
        	}
    }
    sub = "Re: " + messageList.at(thisID - 1)->getSubject();
    cin.ignore();
    cout << "Enter Body: ";
    getline(cin, tempStr);
    while(tempStr !=  "")
    {
        bod += tempStr + '\n';
        getline(cin, tempStr);
    }
    
    bod = bod.substr(0, bod.size() - 1);
    cout << endl;
    
    Reply* tempRep = new Reply(currentUser->getUsername(), sub, bod, msID);
    messageList.push_back(tempRep);
    messageList.at(thisID-1)->addChild(tempRep);
}
