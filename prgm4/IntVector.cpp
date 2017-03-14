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

/**************NEW FUNCTIONS*********************/

//This function will return the value stored in the element at the passed in index position. 
//Your function should throw an outofrange exception if an invalid index is passed in. 
//An invalid index is an index greater than or equal to the size.
int & IntVector::at(unsigned index)
{
    if(index < 0 || index >= sz)
        throw out_of_range("IntVector::at_range_check");
    
    return data[index];
}

//This function will return the value stored in the first element.
int & IntVector::front()
{
    return data[0];
}

//This function will return the value stored in the last element.
int & IntVector::back()
{
    return data[sz - 1];
}

//This function will double the capacity of the vector.
//This function should reallocate memory for the dynamically allocated array and update the value of capacity. 
//Be careful to properly handle the case when capacity is 0 before calling expand().
//Make sure you don't create a memory leak here.
void IntVector::expand()
{
    if(cap == 0)
        cap++;
    else
        cap *= 2;
    
    int *temp = new int[cap];
    
    for(unsigned x = 0; x < sz; x++)
    {
        temp[x] = data[x];
    }
    
    data = temp;
}

//This function will expand the capacity of the vector by the amount passed in. 
//This function should reallocate memory for the dynamically allocated array and update the value of capacity.
//Make sure you don't create a memory leak here.
void IntVector::expand(unsigned amount)
{
    cap += amount;
    
    int *temp = new int[cap];
    
    for(unsigned x = 0; x < sz; x++)
    {
        temp[x] = data[x];
    }
    
    data = temp;
}

// This function inserts data at position index. 
//To do this, all values currently at position index and greater are shifted to the right by 1 (to the element right after its current position).
// Size will be increased by 1. However, If size will become larger than capacity, this function needs to first double the capacity. 
//In other words, if capacity and size are both 20 when this function is called, this function must first increase the capacity to 40 and then it will be able to increase the size to 21.
//Since other functions will also potentially need to expand (double) the capacity, call the private helper function named expand (see above) to do this for you.
//This function should throw an out_of_range exception, passing it the string "IntVector::insert_range_check" if the index is too large. 
//See bottom of specifications for more details on how to throw an exception and how to test that it works properly.
void IntVector::insert(unsigned index, int value)
{
    if(cap == 0)
        expand(1);
    else
        if(cap == sz)
            expand();
            
    sz++;
    
    if(index >= sz)
        throw out_of_range("IntVector::insert_range_check");
    else
    {
        for(unsigned x = sz - 1; x > index; x--)
        {
            at(x) = at(x - 1);
        }
        
        at(index) = value;
    }
}


//This function removes the value at position index and shifts all of the values at positions greater than index to the left by one (to the element right before its current position).
//Size is decreased by 1.
//This function should throw an out_of_range exception, passing it the string "IntVector::erase_range_check" if the index is too large. 
void IntVector::erase(unsigned index)
{
    if(index < 0 || index >= sz)
        throw out_of_range("IntVector::erase_range_check");
        
    for(unsigned x = index; x < sz - 1; x++)
    {
        data[x] = data[x + 1];
    }
    
    sz -= 1;
}


//This function inserts a value at the back end of the array.
//Size will be increased by 1. However, If size will become larger than capacity, this function needs to first increase the capacity. 
//In other words, if capacity and size are both 20 when this function is called, capacity must first be increased to 40 and then size can be increased to 21.
//Since other functions will also potentially need to expand (double) the capacity, call the private helper function named expand (see above) to do this for you.
void IntVector::push_back(int value)
{
    if(sz == cap)
        expand();
        
    sz++;
    
    data[sz - 1] = value;
}

//This function just needs to decrease size by 1.
//This function will never thrown an exception. Calling pop_back on an empty vector will cause undefined behavior.
void IntVector::pop_back()
{
    sz -= 1;
}

//This function reduces the size of the vector to 0.
void IntVector::clear()
{
    sz = 0;
}

//This function resizes the vector to contain size elements.
//If size is smaller than the current size(sz), this function just reduces the value of sz to size.
//If size is greater than the current size(sz), then the appropriate number of elements are inserted at the end of the vector, giving all of the new elements the value passed in through the 2nd parameter (value).
//If the new value of size will be larger than capacity, then the capacity must first be expanded by either doubling (expand()) or by increasing the capacity by a specific amount (expand(size - cap)), whichever results in the largest capacity. 
//Then, this function can then increase the size appropriately.
void IntVector::resize(unsigned size, int value)
{
    
    if(size < sz)
        sz = size;
    else
    {
        if(cap < size)
        {
            if(size < cap * 2 && cap != 0)
            {
                expand();
            }
            else
                expand(size - cap);
        }
        
        for(unsigned x = sz; x < size; x++)
        {
            data[x] = value;
        }
        
        sz = size;
    }
}


//This function requests that the capacity (the size of the dynamically allocated array) be set to n at minimum.
//This informs the vector of a planned increase in size, although notice that the parameter n informs of a minimum, so the resulting capacity may be any capacity equal or larger than this.
//This function should NOT ever reduce the size of the vector. 
//If n is larger than the current capacity then the capacity should be expanded by either doubling (expand()) or by increasing the capacity by a specific amount (expand(n - cap)), whichever results in the largest capacity.
//In any case, a call to this function never affects the elements contained in the vector, nor the vector size.
void IntVector::reserve(unsigned n)
{
    if(cap < n)
    {
        if(n < cap * 2 && cap != 0)
        {
            expand();
        }
        else
            expand(n - cap);
    }
}

//Assigns new content to the vector object, dropping all the elements contained in the vector before the call and replacing them by those specified by the parameters. 
//The new value of size will be n and all values stored in the vector will have the value of the 2nd parameter.
//If the new value of size will be larger than capacity, then this function must first expand capacity by either double (expand()) or 
//by increasing the capacity by a specific amount (expand(n - cap)), whichever results in the largest capacity.
void IntVector::assign(unsigned n, int value)
{
    if(cap < n)
    {
        if(n < cap * 2 && cap != 0)
        {
            expand();
        }
        else
            expand(n - cap);
    }

    sz = n;
                
        
    for(unsigned x = 0; x < n; x++)
    {
        data[x] = value;
    }
}