#include <iostream>

using namespace std;

class Date {
 private:
   unsigned day;
   unsigned month;
   string monthName;
   unsigned year;

 public:
   // creates the date January 1st, 2000.
   Date();


   /* parameterized constructor: month number, day, year 
       - e.g. (3, 1, 2010) will construct the date March 1st, 2010

       If any of the arguments are invalid (e.g. 15 for month or 32 for day)
       then the constructor will construct instead a valid Date as close
       as possible to the arguments provided - e.g. in above example,
       Date(15, 32, 2010), the Date would be corrected to Dec 31st, 2010.
       In case of such invalid input, the constructor will issue a console error message: 

       Invalid date values: Date corrected to 12/31/2010.
       (with a newline at the end).
   */
   Date(unsigned m, unsigned d, unsigned y);


   /* parameterized constructor: month name, day, year
 ­      - e.g. (December, 15, 2012) will construct the date December 15th, 2012

       If the constructor is unable to recognize the string argument as a valid month name,
       then it will issue a console error message: 

       Invalid month name: the Date was set to 1/1/2000.
       (with a newline at the end).

       If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 

       This constructor will recognize both "december" and "December"
       as month name.
   */
   Date(const string &mn, unsigned d, unsigned y);


   /* Outputs to the console (cout) a Date exactly in the format "3/1/2012". 
      Does not output a newline at the end.
   */
   void printNumeric() const;


   /* Outputs to the console (cout) a Date exactly in the format "March 1, 2012".
      The first letter of the month name is upper case, and the month name is
      printed in full - January, not Jan, jan, or january. 
      Does not output a newline at the end.
   */
   void printAlpha() const;

 private:

   /* Returns true if the year passed in is a leap year, otherwise returns false.
   */
   bool isLeap(unsigned y) const;


   /* Returns number of days allowed in a given month
      -  e.g. daysPerMonth(9, 2000) returns 30.
      Calculates February's days for leap and non-­leap years,
      thus, the reason year is also a parameter.
   */
   unsigned daysPerMonth(unsigned m, unsigned y) const;

   /* Returns the name of a given month
      - e.g. name(12) returns the string "December"
   */
   string name(unsigned m) const;

   /* Returns the number of a given named month
      - e.g. number("March") returns 3
   */
   unsigned number(const string &mn) const;
};

Date::Date()
{
    day = 1;
    month = 1;
    monthName = "January";
    year = 2000;
}

Date::Date(unsigned m, unsigned d, unsigned y)
{
    day = d;
    month = m;
    year = y;
    bool done = true;
    
    do
    {
        if((month == 2) && isLeap(year) && (day > 29))
        {
            day = 29;
            done = false;
        }
        else
            if((month == 2) && !isLeap(year) && (day > 28))
            {
                day = 28;
                done = false;
            }
            else
                if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31))
                {
                    day = 31;
                    done = false;
                }
                else
                    if((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30))
                    {
                        day = 30;
                        done = false;
                    }
                    else
                        if(month < 1)
                        {
                            month = 1;
                            done = false;
                        }
                        else
                            if(month > 12)
                            {
                                month = 12;
                                done = false;
                            }
                            else
                                if(day < 1)
                                {
                                    day = 1;
                                    done = false;
                                }
                                else
                                {
                                    if(!done)
                                        cout << "Invalid date values: Date corrected to " << month << "/" << day << "/" << year << "." << endl;
                                    done = true;
                                }
    }
    while(!done);
                

                
     monthName = name(month);
            
    return;    
}

Date::Date(const string &mn, unsigned d, unsigned y)
{
    day = d;
    year = y;
    monthName = mn;
    bool done = true;
    
    month = number(monthName);
    
    if(month == 0)
    {
        cout << "Invalid month name: the Date was set to 1/1/2000." << endl;
        day = 1;
        month = 1;
        year = 2000;
        monthName = "January";
    }
    
    do
    {
        if((month == 2) && isLeap(year) && (day > 29))
        {
            day = 29;
            done = false;
        }
        else
            if((month == 2) && !isLeap(year) && (day > 28))
            {
                day = 28;
                done = false;
            }
            else
                if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31))
                {
                    day = 31;
                    done = false;
                }
                else
                    if((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30))
                    {
                        day = 30;
                        done = false;
                    }
                    else
                        if(day < 1)
                        {
                            day = 1;
                            done = false;
                        }
                        else
                        {
                            if(!done)
                                cout << "Invalid date values: Date corrected to " << month << "/" << day << "/" << year << "." << endl;
                            done = true;
                        }
    }
    while(!done);
    
    monthName = name(month);
}

void Date::printNumeric() const
{
    cout << month << "/" << day << "/" << year;
}


void Date::printAlpha() const
{
    cout << monthName << " " << day << ", " << year;
}


/****PRIVATE FUNCTIONS ****/


bool Date::isLeap(unsigned y) const
{
    if(y % 4 == 0)
    {
        if(y % 400 == 0)
        {
           return true;
        }
        
        if(y % 100 == 0)
        {
            return false;
        }
        
        return true;
    }
    
    return false;
}


unsigned Date::daysPerMonth(unsigned m, unsigned y) const
{
    
    if(m == 2 && isLeap(y))
        return 29;
    else
        if(m == 2 && !isLeap(y))
            return 28;
        else
            if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) 
            {
                return 31;
            }
            else
                if(m == 4 || m == 6 || m == 9 || m == 11)
                {
                    return 30;
                }
        
    return 0;
}


string Date::name(unsigned m) const
{
    if(m == 1)
        return "January";
    else
        if(m == 2)
            return "February";
        else
            if(m == 3)
                return "March";
            else
                if(m == 4)
                    return "April";
                else
                    if(m == 5)
                        return "May";
                    else
                        if(m == 6)
                            return "June";
                        else
                            if(m == 7)
                                return "July";
                            else
                                if(m == 8)
                                    return "August";
                                else
                                    if(m == 9)
                                        return "September";
                                    else
                                        if(m == 10)
                                            return "October";
                                        else
                                            if(m == 11)
                                                return "November";
                                            else
                                                if(m == 12)
                                                    return "December";
    
    return 0;                                            
}

unsigned Date::number(const string &mn) const
{
    if(mn == "January" || mn == "january")
    {
        return 1;
    }
    else
        if(mn == "February" || mn == "february")
        {
            return 2;
        }
        else
            if(mn == "March" || mn == "march")
            {
                return 3;
            }
            else
                if(mn == "April" || mn == "april")
                {
                    return 4;
                }
                else
                    if(mn == "May" || mn == "may")
                    {
                        return 5;
                    }
                    else
                        if(mn == "June" || mn == "june")
                        {
                            return 6;
                        }
                        else
                            if(mn == "July" || mn == "july")
                            {
                                return 7;
                            }
                            else
                                if(mn == "August" || mn == "august")
                                {
                                    return 8;
                                }
                                else
                                    if(mn == "September" || mn == "september")
                                    {
                                        return 9;
                                    }
                                    else
                                        if(mn == "October" || mn == "october")
                                        {
                                            return 10;
                                        }
                                        else
                                            if(mn == "November" || mn == "november")
                                            {
                                                return 11;
                                            }
                                            else
                                                if(mn == "December" || mn == "december")
                                                {
                                                    return 12;
                                                }
                                                
    
    return 0;
}

/*********MAIN***********/

Date getDate();

int main() {

   Date testDate;
   testDate = getDate();
   cout << endl;
   cout << "Numeric: ";
   testDate.printNumeric();
   cout << endl;
   cout << "Alpha:   ";
   testDate.printAlpha();
   cout << endl;

   return 0;
}

Date getDate() {
   int choice;
   unsigned monthNumber, day, year;
   string monthName;

   cout << "Which Date constructor? (Enter 1, 2, or 3)" << endl
      << "1 - Month Number" << endl
      << "2 - Month Name" << endl
      << "3 - default" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      cout << "month number? ";
      cin >> monthNumber;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthNumber, day, year);
   } else if (choice == 2) {
      cout << "month name? ";
      cin >> monthName;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthName, day, year);
   } else {
      return Date();
   }
}