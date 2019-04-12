//
//  Time.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-30.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp
#include <iostream>
#include <fstream>

/* class MENU:
 * ----------
 The class manages data for time (hours, minutes)
 */
class Time
{
private: //class members
    int hour;
    int min;
    
public:
    Time(); //default constructor
    Time(int pHour, int pMin); //constructor
    
    Time(const Time &t); // kopying constructor
    
    //set-functions
    void setHour (int pHour);
    void setMin (int pMin);
    
    //get-functions
    int getHour () const {return hour;};
    int getMin () const {return min;}
    
    //operator overloading
    Time operator+(const Time &t) const;
    Time operator-(const Time &t) const;
    bool operator<(const Time &t) const;
    bool operator>(const Time &t) const;
    bool operator==(const Time &t) const;
};
void showTime(Time t);
std::istream &operator>>(std::istream &is, Time &t);

#endif /* Time_hpp */
