#include <iostream>
#include "IntVector.h"
#include <stdexcept>

using namespace std;

//This function should set both the size and capacity of the IntVector to 0 and will not allocate any memory to store integers.
//(Make sure you do not have a dangling pointer.)
IntVector::IntVector()
{
    sz = 0;
    cap = 0;
    data = 0;
}

// Sets both the size and capacity of the IntVector to the value of the parameter passed in and dynamically allocates an array of that size as well. 
//This function should initialize all elements of the array to the value of the 2nd parameter.
IntVector::IntVector(unsigned size, int value)
{
    sz = size;
    cap = size;
    data = new int[size];
    
    for(unsigned x = 0; x < size; x++)
    {
        data[x] = value;
    }
}


//The destructor is used to clean up (delete) any remaining dynamically-allocated memory. 
//For this class, that will be the array pointed to by the int pointer called data.
IntVector::~IntVector()
{
    delete data;
}

//This function returns the current size (not the capacity) of the IntVector object, which is the values stored in the sz data field.
unsigned IntVector::size() const
{
    return sz;
}

//This function returns the current capacity (not the size) of the IntVector object, which is the value stored in the cap data field.
unsigned IntVector::capacity() const
{
    return cap;
}

//Returns whether the IntVector is empty (the sz field is 0).
bool IntVector::empty() const
{
    if(sz == 0)
        return true;
    
    return false;
}

//This function will return the value stored in the element at the passed in index position. 
//Your function should throw an outofrange exception if an invalid index is passed in. 
//An invalid index is an index greater than or equal to the size.
const int & IntVector::at(unsigned index) const
{
    if(index < 0 || index >= sz)
        throw out_of_range("IntVector::at_range_check");
    
    return data[index];
}

//This function will return the value stored in the first element.
const int & IntVector::front() const
{
    return data[0];
}

//This function will return the value stored in the last element.
const int & IntVector::back() const
{
    return data[sz - 1];
}