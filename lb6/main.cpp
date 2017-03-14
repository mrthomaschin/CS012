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
    
    cout << "Size: " << lol.size() << endl;
    cout << "Capacity: " << lol.capacity() << endl;
    
    if(lol.empty())
        cout << "IntVector is empty" << endl;
    else
        cout << "IntVector is not empty" << endl;
        
    cout << "Value at index 3: " << lol.at(3) << endl;
    cout << "First value: " << lol.front() << endl;
    cout << "Last value: " << lol.back() << endl;
    
    return 0;
}