#ifndef IntVector_H
#define IntVector_H

using namespace std;

class IntVector
{
    private:
        unsigned sz;    //stores the size of the IntVector (the number of elements currently being used).
        unsigned cap;   //store the size of the array
        int *data;      //stores the address of the dynamically-allocated array of integers
    
    public:
        //This function should set both the size and capacity of the IntVector to 0 and will not allocate any memory to store integers.
        //(Make sure you do not have a dangling pointer.)
        IntVector();
        
        // Sets both the size and capacity of the IntVector to the value of the parameter passed in and dynamically allocates an array of that size as well. 
        //This function should initialize all elements of the array to the value of the 2nd parameter.
        IntVector(unsigned size, int value = 0);
        
     
        //The destructor is used to clean up (delete) any remaining dynamically-allocated memory. 
        //For this class, that will be the array pointed to by the int pointer called data.
        ~IntVector();
        
        //This function returns the current size (not the capacity) of the IntVector object, which is the values stored in the sz data field.
        unsigned size() const;
        
        //This function returns the current capacity (not the size) of the IntVector object, which is the value stored in the cap data field.
        unsigned capacity() const;
        
        //Returns whether the IntVector is empty (the sz field is 0).
        bool empty() const;
        
        //This function will return the value stored in the element at the passed in index position. 
        //Your function should throw an outofrange exception if an invalid index is passed in. 
        //An invalid index is an index greater than or equal to the size.
        const int & at(unsigned index) const;
        
        //This function will return the value stored in the first element.
        const int & front() const;

        //This function will return the value stored in the last element.
        const int & back() const;
    
};


#endif