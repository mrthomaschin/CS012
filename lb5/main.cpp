#include <iostream>

using namespace std;
// Passes in an array along with the size of the array.
// Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize)
{
    double meanVal;
    double meanVal2;
    
    for(int x = 0; x < arraySize; x++)
    {
        meanVal += array[x];
    }
    
    meanVal2 = meanVal / arraySize;
    
    return meanVal2;
}

// Passes in an array, the size of the array by reference, and the index of a value to be removed from the array.
// Removes the value at this index by shifting all of the values after this value up, keeping the same relative order of all values not removed.
// Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index)
{
    arraySize--;
    for(int x = 0; x < arraySize; x++)
    {
        if(x >= index)
        {
            array[x] = array[x + 1];
        }
    }
}

// Passes in an array and the size of the array.
// Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
// main function requirements
void display(const double array[], int arraySize)
{
    for(int x = 0; x < arraySize; x++)
    {
        cout << array[x];
        
        if(x != arraySize - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;
}

int main()
{
    double ary[10];
    double avg;
    int indexToDel;
    int ARRAY_SIZE = 10;
    
    cout << "Enter 10 values:" << endl;
    
    for(int x = 0; x < ARRAY_SIZE; x++)
    {
        cin >> ary[x];
    }
    
     cout << endl;

    
    avg = mean(ary, ARRAY_SIZE);
    
    cout << "Mean: " << avg << endl;
    cout << endl;
    
    cout << "Enter index of value to be removed: ";
    cin >> indexToDel;
    cout << endl;
    
    cout << "Before removing value: ";
    display(ary, ARRAY_SIZE);
    
    remove(ary, ARRAY_SIZE, indexToDel);
    
    cout << "After removing value: ";
    display(ary, ARRAY_SIZE);
    
    
    
    return 0;
}