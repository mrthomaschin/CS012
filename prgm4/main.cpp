#include <iostream>
#include "IntVector.h"

using namespace std;

int main()
{
    unsigned size;
    int value;
    
    cout << "Enter size of the array: " << endl;
    cin >> size;
    cout << endl;
    
    cout << "Enter the value to be stored in the array: " << endl;
    cin >> value;
    cout << endl;
    
    IntVector lol(size, value);
    //size
    cout << "Size: " << lol.size() << endl;
    cout << endl;
    
    //capacity
    cout << "Capacity: " << lol.capacity() << endl;
    cout << endl;
    
    //empty
    if(lol.empty())
    {
        cout << "IntVector is empty" << endl;
        cout << endl;
    }
    else
    {
        cout << "IntVector is not empty" << endl;
        cout << endl;
    }
        
    //at    
    cout << "Value at index 3: " << lol.at(3) << endl;
    cout << endl;
    
    //front
    cout << "First value: " << lol.front() << endl;
    cout << endl;
    
    //back
    cout << "Last value: " << lol.back() << endl;
    cout << endl;
    
    cout << "All values are currently " << lol.front() << " and the size is  " << lol.size() << endl;
    cout << endl;
    
    //insert
    cout << "Insert value 5 at index 1" << endl;
    lol.insert(1, 5);
    cout << "Value at index 1: " << lol.at(1) << endl;
    cout << endl;
    
    //erase
    cout << "Erase value at index 1" << endl;
    lol.erase(1);
    cout << "Value at index 1: " << lol.at(1) << endl;
    cout << endl;
    
    //push_back
    cout << "Pushing back 5" << endl;
    lol.push_back(5);
    cout << "Value at last index: " << lol.at(lol.size() - 1) << endl;
    cout << endl;
    
    //pop_back
    cout << "Popping back" << endl;
    lol.pop_back();
    cout << "Value at last index: " << lol.at(lol.size() - 1) << endl;
    cout << endl;
    
    //resize 
    cout << "Resizing to smaller" << endl;
    lol.resize(5, 10);
    cout << "Size: " << lol.size() << endl;
    cout << "Resizing to bigger" << endl;
    lol.resize(10, 5);
    cout << "Size: " << lol.size() << endl;
    cout << "Value at index 8: " << lol.at(8) << endl;
    cout << endl;
    
    //reserve
    cout << "Reserving" << endl;
    lol.reserve(15);
    cout << "Size: " << lol.size() << endl;
    cout << endl;
    
    //assign
    cout << "Assigning to a smaller vector" << endl;
    lol.assign(5, 10);
    cout << "Size: " << lol.size() << endl;
    cout << "Value at index 3: " << lol.at(3) << endl;
    cout << "Assigning to a larger vector" << endl;
    lol.assign(10, 5);
    cout << "Size: " << lol.size() << endl;
    cout << "Value at index 8 " << lol.at(8) << endl;
    cout << endl;
    
    //clear
    cout << "Clearing everything" << endl;
    lol.clear();
    cout << "Size: " << lol.size() << endl;
    cout << endl;
    
    
    
    return 0;
}