#include <iostream>
#include <math.h>

using namespace std;


int gcd(int num1, int num2) {
	int gcdVal = 0; // Holds GCD results

	if (num1 == num2) {    // Base case: Numbers are equal
		gcdVal = num1;       // Return value
	}
	else {                    // Recursive case: subtract smaller from larger
		if (num1 > num2) { // Call function with new values
			gcdVal = gcd(num1 - num2, num2);
		}
		else {
			gcdVal = gcd(num1, num2 - num1);
		}
	}

	return gcdVal;
}

/* Returns true if a solution was found and false if there is no solution.
x and y will contain a solution if a solution was found.
This function will NOT output anything.
*/

//If gcd(a,b) does not divide c, then there is no solution.
//If b divides a(the remainder of a / b is 0), then you can just divide by b to get the solution : x = 0, y = c / b.
//Otherwise(b does not divide a), through a substitution method, 
//we can come up with a simpler version of the original problem and solve the simpler problem using recursion.

bool diophantine(int a, int b, int c, int &x, int &y)
{
	int r;
	int q;
	int u;
	int v;

	if (c % gcd(abs(a), abs(b)) != 0)
	{
		return false;
	}
	else
		if ((a % b) == 0)
		{
			x = 0;
			y = (c / b);

			return true;
		}
		else
		{
			r = (a % b);
			q = (a / b);

			u = (q * x) + y;
			v = x;

			//bu + rv = c
			diophantine(b, r, c, u, v);

			x = v;
			y = u - (q * x);

			return true;
		}
}

int main() 
{

	int a, b, c, x, y;
	
	cout << "Enter a b c" << endl;
	cin >> a >> b >> c;
	cout << endl;

	cout << "Result: ";
	if (diophantine(a, b, c, x, y)) {
		cout << x << " " << y << endl;
	}
	else {
		cout << "No solution!" << endl;
	}

	return 0;
}
