// 
//  Date.cpp 
//  CppOptions 
#include "Date.h" 
#include <string> 
#include <iostream> 
using std::cout; 
using std::endl; 
using std::string; 
// constructor sets the weekday by default to DayOfTheWeek_UNKNOWN
// we create a date object with a year, month and day property
// and that date object has a number of functions and capabilities - comparison and computation
// capabilities as defined in this class
Date::Date(int year, int month, int day) 
 : m_year(year), 
   m_month(month), 
   m_day(day), 
   m_weekDay(DayOfTheWeek_UNKNOWN)    
 { 
 } 
 // the destructor 
Date::~Date() 
 { 
 } 
// copy constructor - creating a new Date object from an existing one
Date::Date(const Date &p) 
 : m_year(p.m_year), 
   m_month(p.m_month), 
   m_day(p.m_day), 
   m_weekDay(p.m_weekDay), 
   m_holidays(p.m_holidays) 
 { 
 } 
 // copy assignment operator - assigning values from one Date object to another
Date &Date::operator=(const Date &p) 
 { 
     if (&p != this) 
     { 
         m_day = p.m_day; 
         m_month = p.m_month; 
         m_year = p.m_year; 
         m_weekDay = p.m_weekDay; 
         m_holidays = p.m_holidays; 
     } 
     return *this; 
 } 
 // boolean operator overload stipulating how the '<' operator should be evaluated in a boolean context
 // the operator overload definition is similar to a function definition
 // returns true if the object date is earlier than the parameter date
 // here we are 'overloading the operator '<' and defining how the operator should
 // be evaluated in a boolean context when evaluated with a date
 // thus the process of overloading an operator  defines specifically how that operator 
 // should behave in a given context
   bool Date::operator<(const Date &d) const 
 { 
     if (m_year < d.m_year) return true; 
     if (m_year == d.m_year && m_month < d.m_month) return true;    
     if (m_year == d.m_year && m_month == d.m_month && m_day < d.m_day) return true; 
     return false; 
 } 
 // operator overload specification for the boolean equality operator in a date comparison context
 // stipulating how a date parameter should be compared to the date object
 // thus the date check comparison is effected over the day, month and year parts of the date(s)
 // separately
 // what is the benefit of overloading the operator and stipuating (for dates) how the operator should behave
 // in a boolean context? it means that we can determine exactly how the date comparison is effected
 // and thereby control and determined exactly how dates are compared/evaluated
   bool Date::operator==(const Date &d) 
 { 
     return d.m_day == m_day && d.m_month == m_month && d.m_year == m_year; 
 } 

 // m_holidays is defined as a vector or array or dates (holday dataes presumably)
 // by default, this vector of dates is empty, thus the set holdays function
 // takes an array of stipulated dates and sets the m_holidays vector to contain these dates
   void Date::setHolidays(const std::vector<Date> &days) 
 { 
     m_holidays = days; 
 } 

 // a boolean search using the array of holiday dates 'm_holidays' to check whether or not
 // a particular date is a holiday date
 // essentially a function caled isHoliday() which returns a boolean value
   bool Date::isHoliday()    
 { 
     return std::find(m_holidays.begin(), m_holidays.end(), *this) != m_holidays.end(); 
 } 

 // takes the content of variable m_month and converts that variable to a string appropriately
 // essentially a function called month() which returns a string value

   std::string Date::month() 
 { 
     switch (m_month) { 
         case Month_January: return "January"; 
         case Month_February: return "February"; 
         case Month_March: return "March"; 
         case Month_April: return "April"; 
         case Month_May: return "May"; 
         case Month_June: return "June"; 
         case Month_July: return "July"; 
         case Month_August: return "August"; 
         case Month_September: return "September"; 
         case Month_October: return "October"; 
         case Month_November: return "November"; 
         case Month_December: return "December"; 
         default: throw std::runtime_error("unknown month"); 
     } 
     return ""; 
 }

 // converts the day of the week to the relevant string
 // essentially a function called dayOfWeek() which returns a string value
   #define self  this
 //In C++, you can use the #define preprocessor directive to create macros. 
 //Defining self as this is a common practice in some programming communities 
 //to mimic the behavior of languages like Python
 // here then the self variable is used to refer to the current instance of the Date class
 // and set this reference to be 'this'    
   std::string Date::dayOfWeek() 
 { 
     switch (this->dayOfTheWeek()) { 
         case DayOfTheWeek_Sunday: return "Sunday"; 
         case DayOfTheWeek_Monday: return "Monday"; 
         case DayOfTheWeek_Tuesday: return "Tuesday"; 
         case DayOfTheWeek_Wednesday: return "Wednesday"; 
         case DayOfTheWeek_Thursday: return "Thursday"; 
         case DayOfTheWeek_Friday: return "Friday"; 
         case DayOfTheWeek_Saturday: return "Saturday"; 
         default: throw std::runtime_error("unknown day of week"); 
     } 
 } 

   void Date::add(int numDays)    
 { 
     for (int i=0; i<numDays; ++i) 
     { 
         ++*this; 
     } 
 } 

   void Date::addTradingDays(int numDays) 
 { 
     while (!isTradingDay()) 
     { 
         ++*this; 
     } 
     for (int i=0; i<numDays; ++i)    
     { 
         ++*this; 
         while (!isTradingDay()) 
         { 
             ++*this; 
         } 
     } 
 } 
   void Date::subtract(int numDays) 
 { 
     for (int i=0; i<numDays; ++i) 
     { 
         --*this; 
     } 
 } 
   void Date::subtractTradingDays(int numDays)    
 { 
     while (!isTradingDay()) 
     { 
         --*this; 
     } 
     for (int i=0; i<numDays; ++i) 
     { 
         --*this; 
         while (!isTradingDay()) 
         { 
             --*this; 
         } 
     } 
 } 
   int Date::dateDifference(const Date &date)    
 { 
     Date d = *this; 
     if (d < date) 
     { 
         int diff=0; 
         while (d < date) 
         { 
             ++d; 
             ++diff; 
         } 
         return diff; 
     } 

       int diff=0; 
     while (date < d) 
     { 
         --d; 
         --diff; 
     } 
     return diff; 
 } 
   int Date::tradingDateDifference(const Date &date)    
 { 
     Date d = *this; 
     if (d < date) 
     { 
         int diff=0; 
         while (!d.isTradingDay()) ++d; 
         while (d < date) 
         { 
             ++d; 
             ++diff; 
             while (!d.isTradingDay()) ++d; 
         } 
         return diff; 
     } 
       int diff=0; 
     while (!d.isTradingDay()) --d; 
     while (date < d) 
     { 
         --d; 
         --diff; 
         while (!d.isTradingDay()) --d; 
     } 
     return diff; 
 } 
   DayOfTheWeek Date::dayOfTheWeek()    
 { 
     if (m_weekDay != DayOfTheWeek_UNKNOWN) return m_weekDay; 
       int day = 1; 
     Date d(1900, 1, 1); 
     for (;d < *this; ++d) 
     { 
         if (day == 6) day = 0; 
         else day++; 
     } 
     m_weekDay = static_cast<DayOfTheWeek>(day);    
     return m_weekDay; 
 } 
   bool Date::isWeekDay() 
 { 
     DayOfTheWeek dayOfWeek = dayOfTheWeek(); 
     if (dayOfWeek == DayOfTheWeek_Sunday || dayOfWeek == DayOfTheWeek_Saturday) 
     { 
         return false; 
     } 
     return true; 
 } 
   bool Date::isTradingDay() 
 { 
     if (!isWeekDay()) return false; 
     if (m_holidays.size() == 0) return true;    
     if (isHoliday()) return false; 
     return true; 
 } 
   Date Date::nextTradingDay() 
 { 
     Date d = *this; 
     if (d.isTradingDay()) 
     { 
         return ++d; 
     } 
     while (!d.isTradingDay()) 
     { 
         ++d; 
     } 
     return d; 
 } 
   bool Date::isLeapYear() 
 { 
     if (m_year % 4 != 0) return false; 
     if (m_year % 100 != 0) return true;    
     if (m_year % 400 != 0) return false; 
     return true; 
 } 
   Date &Date::operator--() 
 { 
     if (m_weekDay != DayOfTheWeek_UNKNOWN) // update weekday 
     { 
         if (m_weekDay == DayOfTheWeek_Sunday) 
             m_weekDay = DayOfTheWeek_Saturday; 
         else 
             m_weekDay = static_cast<DayOfTheWeek>(m_weekDay - 1); 
     } 
       if (m_day > 1) 
     { 
         m_day--; 
         return *this;    
     } 
       if (m_month == Month_January) 
     { 
         m_month = Month_December; 
         m_day = 31; 
         m_year--; 
         return *this; 
     } 
       m_month--; 
       if (m_month == Month_February) 
     { 
         m_day = isLeapYear() ? 29 : 28; 
         return *this; 
     } 
       // list of months with 31 days 
     std::vector<int> monthsWithThirtyOneDays = { 1, 3, 5, 7, 8, 10, 12 }; 
     if (std::find(monthsWithThirtyOneDays.begin(), 
                   monthsWithThirtyOneDays.end(), m_month) 
                != monthsWithThirtyOneDays.end())    
     { 
         m_day = 31; 
     } 
     else 
     { 
         m_day = 30; 
     } 
     return *this; 
 } 
   Date &Date::operator++() 
 { 
     // list of months with 31 days 
     std::vector<int> monthsWithThirtyOneDays = { 1, 3, 5, 7, 8, 10, 12 }; 
       if (m_day == 31) 
     { 
         m_day = 1;    
         m_month++; 
     } 
     else if (m_day == 30 && 
              std::find(monthsWithThirtyOneDays.begin(), 
                        monthsWithThirtyOneDays.end(), m_month) 
                     == monthsWithThirtyOneDays.end()) 
     { 
         m_day = 1; 
         m_month++; 
     } 
     else if (m_day == 29 && m_month == 2) 
     { 
         m_day = 1; 
         m_month++; 
     } 
     else if (m_day == 28 && m_month == 2  && !isLeapYear()) 
     { 
         m_day = 1; 
         m_month++;    
     } 
     else 
     { 
         m_day++; 
     } 
       if (m_month > 12) 
     { 
         m_month = 1; 
         m_year++; 
     } 
       if (m_weekDay != DayOfTheWeek_UNKNOWN) // update weekday 
     { 
         if (m_weekDay == DayOfTheWeek_Saturday) 
             m_weekDay = DayOfTheWeek_Sunday; 
         else 
             m_weekDay = static_cast<DayOfTheWeek>(m_weekDay + 1);    
     } 
     return *this; 
 } 
   void Date::print() 
 { 
     cout << m_year << "/" << m_month << "/" << m_day << endl; 
 } 
 int main() 
{ 
    Date d(2015, 9, 12); 
    DayOfTheWeek wd = d.dayOfTheWeek(); 
    cout << " day of the week: " << wd <<  " " << d.dayOfWeek() <<   endl;  
    d.print(); 
    d.add(25); 
    d.print(); 
    d.addTradingDays(120); 
    d.print(); 
    cout << " day of the week: " << d.dayOfTheWeek() <<  " " << d.dayOfWeek() <<   endl; 
    return 0;  
}