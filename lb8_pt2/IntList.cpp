#include "IntList.h"

/***public***/

/* Initializes an empty list.
*/
IntList::IntList()
{
	head = 0;
}


/* Inserts a data value to the front of the list.
*/
void IntList::push_front(int value)
{
	IntNode* temp = head;
	head = new IntNode(value);

	head->next = temp;
}

/* Outputs to a single line all of the int values stored in the list, each separated by a space.
This function does NOT output a newline or space at the end.
*/
ostream & operator<<(ostream &out, const IntList &rhs)
{
	IntNode* temp = rhs.head;

	operator<<(out, temp);

	return out;
}

/* Returns true if the integer passed in is contained within the IntList,
otherwise returns false.
*/
bool IntList::exists(int num) const
{
	IntNode* temp = head;

	if (exists(temp, num))
		return true;
	else
		return false;
}


/***private***/

/* Helper function that returns true if the integer passed in is contained within
the IntNodes starting from the IntNode whose address is passed in,
otherwise returns false.
*/
bool IntList::exists(IntNode * temp, int num) const
{
	bool result;

	if (temp == 0)
	{
		result = false;
	}
	else
		if (temp->data == num)
		{
			result = true;
		}
		else
		{
			result = exists(temp->next, num);
		}

	return result;
}

/* Helper function that passes in the address of a IntNode within an IntList and outputs
all of integers within the IntList starting from this IntNode.
*/
ostream & operator<<(ostream &out, IntNode *temp)
{
	if (temp == 0)
	{
		return out;
	}
	else
	{
		out << temp->data;
		if(temp->next != 0)
		{
			out << " ";
		}
		operator<<(out, temp->next);
	}

	return out;
}
