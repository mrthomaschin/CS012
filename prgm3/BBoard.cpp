#include "BBoard.h"
#include <iostream>
#include <fstream>

using namespace std;

//Public

// Constructs a board with a default title, 
// empty user & message lists, 
// and the "default" User
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

// Imports all the authorized users from an input file, 
// storing them as User objects in the vector userList
// The name of the input file is passed in as a parameter to this function. 
// See below for file format.
bool BBoard::loadUsers(const string &filename)
{
    User usertopush;
    ifstream fileIn;
    string username;
    string password;
    
    fileIn.open(filename.c_str());
    
    if(!fileIn.is_open())
    {
        return false;
    }
    
    while(fileIn >> username >> password)
    {
        if(username != "end")
        {
            usertopush = User(username, password);
            userList.push_back(usertopush);
        }
    }
    fileIn.close();
    
    return true;
}

// Asks for and validates a user/password.
// Always asks for both user and password combo unless 'q' or 'Q' entered.
// Checks userList to validate user and password.
// If valid, sets currentUser to this User, outputs welcome message, 
// then returns true.
// Otherwise outputs error message and then repeats request
// for username/password.
// Continues until valid user/password 
// or until 'q' or 'Q' is entered for username.
// If 'q' or 'Q' is entered, does not ask for password, outputs "Bye!"
// and then returns false.
bool BBoard::login()
{
    User current;
    bool checking = true;
    string user;
    string pass;
    
    cout << "Welcome to " << title << endl;
    while(checking)
    {
        cout << "Enter your username ('Q' or 'q' to quit): ";
        cin >> user;
        cout << endl;
        
        //If user hasn't enetered q, continue to password
        if(user != "q" && user != "Q")
        {
            cout << "Enter your password: ";
            cin >> pass;
            cout << endl;
            
            //Traverses userList
            for(unsigned x = 0; x < userList.size(); x++)
            {
                current = userList.at(x);
                
                //compares username and password to current user
                if(current.check(user, pass))
                {
                    //sets the entered user and pass to currentuser credentials
                    currentUser = User(user, pass);
                    cout << "Welcome back " << currentUser.getUsername() << "!" << endl;
                    cout << endl;
                    
                    //return true; exit out of loop
                    return true;
                }
            }
            
            //Prompts user to enter credentials again
            cout << "Invalid Username or Password!" << endl;
            cout << endl;
            }
        else
        {
            //sets checcking to false; exists out of while loop
            cout << "Bye!" << endl;
            checking = false;
        }f
    
    }
    
    //Conclusion: User entered 'q' or "q"
    return false;
}

// Contains main loop of Bulletin Board.
// First verifies a User has been logged in.
// Exits **function** immediately if no User logged in (Default User).
// Continues to display menu options to user and performs requested action
// until user chooses to quit.
// See output samples for exact format of menu.
void BBoard::run()
{
    char action;
    bool stop = false;
    
    while(!stop)
    {
        cout << "Menu" << endl;
        cout << "- Display Messages ('D' or 'd')" << endl;
        cout << "- Add New Message ('N' or 'n')" << endl;
        cout << "- Quit ('Q' or 'q')" << endl;
        cout << "Choose an action: ";
        cin >> action;
        cout << endl;
        
        if(action == 'D' || action == 'd')
        {
            //Display message with display()
            display();
        }
        else
            if(action == 'N' || action == 'n')
            {
                //Add message with addMessage()
                addMessage();
            }
            else
                if(action == 'Q' || action == 'q')
                {
                    cout << "Bye!";
                    cout << endl;
                    return;
                }
    }
}

//Private

void BBoard::display() const
{
    Message currentMsg;
    
    if(messageList.empty())
    {
        cout << "Nothing to Display." << endl;
        cout << endl;
    }
    else
        {
            for(unsigned x = 0; x < messageList.size(); x++)
            {
                currentMsg = messageList.at(x);
                cout << "---------------------------------------------------------" << endl;
                cout << "Message #" << x + 1 << ": ";
                currentMsg.display();
            }
            
            cout << "---------------------------------------------------------" << endl;
            cout << endl;
        }
}

void BBoard::addMessage()
{
    Message msgtopush;
    string author = currentUser.getUsername();
    string subject;
    string body;
    
    cout << "Enter Subject: ";
    cin.ignore();
    getline(cin, subject);
    cout << endl;
    
    cout << "Enter Body: ";
    getline(cin, body);
    cout << endl;
    
    msgtopush = Message(author, subject, body);
    
    messageList.push_back(msgtopush);
    
    cout << "Message Recorded!" << endl;
    cout << endl;
}

bool BBoard::userExists(const string &user, const string &pass) const
{
    if(user != "" || pass != "")
        return true;
    
    return false;
}