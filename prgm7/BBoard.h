//BBoard.h
#ifndef BBOARD_H
#define BBOARD_H

#include <string>
#include <vector>
using namespace std;

#include "Message.h"
#include "User.h"

class BBoard {
private:
	//title of the board, intialized via constructor
	string title;

	//list of members; intially empty, then populated via loadUsers()
	vector<User> userList;

	//This is now a POINTER to the user who is currently logged in; initialized by constructor to 0
	//then set via login
	const User* currentUser;

	//List of message POINTERS, intially empty
	vector<Message*> messageList;

public:
	//default constructor that creates a board with a default title, empty user and message lists
	//and a no current user (what should the pointer be set to if there is nothing to point to?)
	BBoard();

	// Same as the default constructor except 
	// it sets the title of the board
	BBoard(const string &ttl);

	//destructor that deallocates all MEssages ointed to by messageList
	//THINK CAREFULLY ABOUT THIS!!!
	~BBoard();

	// Gets a filename(userfile) of a file that stores the user info in a given format
	//Opens and reads the file of all authorized users and passwords
	//constructs a User object from each name/password pair, and populated the userList Vector.
	bool loadUsers(const string & userfile);

	//NEW
	//filename (datafile) of a file that stores the messages from the previous sessions in the given format
	//It opens and reads the file, creating Topic and Reply objects as appropriate, and fills the message List vector
	//Note: messageList is a vector of POINTERS	
	bool loadMessages(const string &datafile);

	//Final action of the bulletin board before closing:
	//Gets a filename (datafile) of a file that will store all of the messages, and after opening the file 
	//writes the messages into it with the same format
	//If an error occurs when opening the file, it returns false. Returns true otherwise
	//"file not found" is NOT AN ERROR
	bool saveMessages(const string &datafile);

	// Asks for and validates a user/password.
	//This function asls for a username and a password. and checks the userList vector for a matching User.
	//If a match is found, it sets currentUser to the identified User from the list (remember POINTER)
	//If not, it will keep asking unti a match is found or the user types 'q' or 'Q' as username
	//When user chooses to quit, say "Bye!" and return from the login function
	bool login();

	// Contains main loop of Bulletin Board.
	// IF AND ONLY IF there is a valid currentUserm enter main loop, displaying menu items
	//---Display Messages ('D' or 'd')
	//---Add New Topic ('N' or 'n')
	//---Add Reply ('R' or 'r')
	//---Quit ('Q' or 'q')
	//With any wrong input, user is asked to try again
	//Q/q should reset curretnUser to 0 and then end return
	//NOTE: if login() did not set a valid currentUSer, function must immediately return without showing menu
	void run();

private:
	//This function may be called from the loadUsers function to add the users from the file to the userList
	void addUser(const string &name, const string &pass);

	//Includes the functionality of the old "user_exists" helper
	//It traverses the userList, testing for the existence of a User with the given name and password
	//If this User is NOT found, the function returns 0 (nullptr)
	//Otherwise it returns a POINTER to the identified User (return &userList.(i))
	//May be used by login() to set the currentUser
	//No other way to set current user to anything other than 0
	const User *getUser(const string &name, const string &pw) const;

	//Traverses the BBoard's message list, and invoke the print function on Topic objects ONLY
	//It will then be the responcilbilty of the Topic object to invoke the print function recursively on its own replies
	//The BBoard display function will ignore all REply objects in its message list
	void display() const;

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
	void addTopic();

	//This function asks the user to enter a reply to a given Message (which may be either a Topic or a Reply, so we can handle nested replies).
	//	The addReply function first asks the user for the id of the Message to which they are replying; 
	//if the number provided is greater than the size of messageList it should output an error message and loop back, 
	//continuing to ask for a valid Message id number until the user enters either - 1 (or any negative number, to return to the menu); or a valid id.

	//If the id is valid, then the function asks for the body of the new message, and constructs the Reply, pushing back a pointer to it on the messageList
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
	void addReply();
};

#endif