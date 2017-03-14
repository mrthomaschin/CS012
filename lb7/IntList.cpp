#include "IntList.h"
#include <iostream>
#include <vector>

using namespace std;

//Initializes an empty list.
IntList::IntList()
{
	head = 0;
	tail = 0;
}

//Deallocates all remaining dynamically allocated memory(all remaining IntNodes).
//Traverse, deleting each node
IntList::~IntList()
{
	while (head != 0)
		pop_front();
}

//Displays to a single line all of the int values stored in the list, each separated by a space.
//This function does NOT output a newline or space at the end.
void IntList::display() const
{
	IntNode* curr = 0;
	curr = head;

	while (curr != 0)
	{
		cout << curr->data;
		curr = curr->next;

		if (curr != 0)
		{
			cout << " ";
		}
	}
}

//Inserts a data value(within a new node) at the front end of the list.
void IntList::push_front(int value)
{
	IntNode* temp = head;
	head = new IntNode(value);

	head->next = temp;

	if (tail == 0)
		tail = head;
}

//Removes the value(actually removes the node that contains the value) at the front end of the list.
//Does nothing if the list is already empty.
void IntList::pop_front()
{
	this->head = head->next;
}

//Returns true if the list does not store any data values(does not have any nodes), otherwise returns false.
bool IntList::empty() const
{
	if (head == 0)
	{
		return true;
	}

	return false;
}

/*****************NEW STUFF*********************/

// the copy constructor.Make sure this performs deep copy.
IntList::IntList(const IntList &cpy)
{
	/*IntNode* temp1 = head;
	IntNode* temp2 = cpy.head;

	while (temp2 != 0)
	{
	temp1->data = (temp2->data);
	temp1 = temp1->next;
	temp2 = temp2->next;
	}*/

	head = cpy.head;
	tail = cpy.tail;
}

//the overloaded assignment operator. Make sure this performs deep copy.
IntList & IntList::operator=(const IntList &rhs)
{
	if (this != &rhs)
	{
		clear();
		head = rhs.head;
		tail = rhs.tail;
	}

	return *this;
}

//Inserts a data value(within a new node) at the back end of the list.
void IntList::push_back(int value)
{
	IntNode* toInsert = new IntNode(value);

	if (empty())
	{
		head = tail = toInsert;
		toInsert->next = 0;
	}
	else
	{
		tail->next = toInsert;
		toInsert->next = 0;
		tail = toInsert;
	}
}

//Removes(deallocates) all IntNodes in the IntList.
//Don't forget to set both head and tail to appropriate values for an empty list.
void IntList::clear()
{
	IntNode* curr = head;

	while (curr != 0)
	{
		head = head->next;
		delete curr;
		curr = head;
	}
}

// Sorts the integers in the list into ascending order.Do NOT move the nodes, just the integers.
void IntList::selection_sort()
{
	int swapVal;
	IntNode* minNode;
	IntNode* curr = head;
	IntNode* trav;

	if (curr != 0)
	{
		while (curr != 0)
		{
			trav = curr;
			minNode = curr;

			while (trav != 0)
			{
				if (trav->data < minNode->data)
					minNode = trav;

				trav = trav->next;
			}

			swapVal = curr->data;
			curr->data = minNode->data;
			minNode->data = swapVal;

			curr = curr->next;
		}
	}
}

//Inserts a data value(within a new node) in an ordered list.Assumes the list is already sorted in ascending order(i.e., Do not sort the list first, assume the list is already is sorted.) 
//This function loops through the list until if finds the correct position for the new data value 
//and then inserts the new IntNode in that location.
//This function may NOT ever sort the list.
void IntList::insert_ordered(int value)
{
	IntNode* prev;
	IntNode* curr;
	bool done = false;

	//IntNode* toInsert = new IntNode(value);

	if (head == 0)
	{
		push_back(value);
	}
	else
		if (value >= tail->data)
		{
			push_back(value);
		}
		else
			if (value < head->data)
			{
				push_front(value);
			}
			else
			{
				IntNode* toInsert = new IntNode(value);
				prev = head;
				curr = head->next;

				while (curr != 0 && !done)
				{
					if (value < curr->data)
					{
						toInsert->next = curr;
						prev->next = toInsert;
						done = true;
					}
					else
					{
						prev = curr;
						curr = curr->next;
					}
				}
			}
}

//Removes all duplicate data values(actually removes the nodes that contain the values) within the list.
//Always remove just the later value within the list when a duplicate is found.
//This function may NOT ever sort the list.
void IntList::remove_duplicates()
{
	IntNode* curr = head;
	IntNode* trav = 0;
	IntNode* prevTrav = 0;

	if (curr != 0)
	{
		while (curr != 0)
		{
			prevTrav = curr;
			trav = curr->next;

			while (trav != 0)
			{
				if (trav->data == curr->data)
				{
					trav = trav->next;
					prevTrav->next = trav;
				}
				else
				{
					prevTrav = trav;
					trav = trav->next;
				}
			}

			curr = curr->next;
		}
	}
}

//A global friend function that outputs to the stream all of the integer values within the list on a single line, 
//each separated by a space.
//This function does NOT send to the stream a newline or space at the end.
ostream & operator<<(ostream &out, const IntList &rhs)
{
	IntNode* curr = rhs.head;

	while (curr != 0)
	{
		out << curr->data;
		curr = curr->next;

		if (curr != 0)
			out << " ";
	}

	return out;
}