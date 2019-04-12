//
//  Time.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-30.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "Time.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

/* default constructor */
Time::Time()
{
    hour = min = 0;
}
/* constructor with in-parameters */
Time::Time(int pHour, int pMin)
{
    hour = pHour;
    min = pMin;
}

/* Copying constructor */
Time::Time(const Time &t) {
    hour = t.getHour();
    min = t.getMin();
}

/* set-functions */
void Time:: setHour (int pHour)
{
    hour = pHour;
}

void Time:: setMin (int pMin)
{
    min = pMin;
}

/* operator +:
 * ----------
 * Overloaded operator +: addds two Time objects.
 */
Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.min = min + t.min;
    sum.hour = hour + t.hour + sum.min/60;
    sum.min %= 60;
    sum.hour %= 24;
    return sum;
}

/* operator -:
 * ----------
 * Overloaded operator -: substracts two Time objects.
 */
Time Time::operator-(const Time &t) const
{
    Time sub;
    int tmpMin;
    
    
    tmpMin = min - t.min;
    
    if(tmpMin >= 0) {
        sub.min = tmpMin;
        sub.hour = hour - t.hour;
    }
    
    else {
        sub.min = 60 + tmpMin;
        sub.hour = hour - t.hour - 1;
    }

    return sub;
}

/* operator <:
 * ----------
 * Overloaded operator <: compares two Time objects.
 */
bool Time::operator<(const Time &t) const
{
    return hour < t.hour || (hour == t.hour && min < t.min);
}

/* operator >:
 * ----------
 * Overloaded operator >: compares two Time objects.
 */
bool Time::operator>(const Time &t) const
{
    return hour > t.hour || (hour == t.hour && min > t.min);
}

/* operator ==:
 * -----------
 * Overloaded operator ==: equality operator for two Time objects.
 */
bool Time::operator==(const Time &t) const
{
    return hour == t.hour && min == t.min;
}

//-----------------------------------------------
// 2. CLASS TIME: non-member functions
//-----------------------------------------------
void showTime(Time t) {
    cout << right << setw(2) << setfill('0') << t.getHour() << ":";
    cout << setfill('0');
    cout << setw(2) << t.getMin();
}
/* operator >>:
 * -----------
 * Reads Time object info from file.
 */
istream &operator>>(istream &is, Time &t)
{
    Time tmpTime;
    int min, hr;
    char tmpChar;
    is >> hr >> tmpChar >> min;
    is.get();
    
    t.setHour(hr);
    t.setMin(min);
    
    return is;
}
