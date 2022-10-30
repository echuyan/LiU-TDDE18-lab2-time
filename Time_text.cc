#include <iostream>
#include <sstream>
#include <istream>
#include <ostream>
#include "Time_text.h"
#include <string>
#include <iomanip>

using namespace std;

struct Intervals
{
    int lower{};
    int upper{};
};

const Intervals hours{0, 23};
const Intervals minutes{0,59};
const Intervals seconds = {0,59};
const int noon = 12;
const int hours_per_day{24};
const int seconds_per_hour{3600};
const int seconds_per_minute{60};
const int maximum_seconds{hours_per_day*seconds_per_hour};
const int minimum_seconds{0};

bool in_interval(const int& integer, const int& lower, const int& upper)
{
    return (integer < upper && integer > lower);
}

bool is_valid(const Time& t)
{
    return(in_interval(t.hh, hours.lower, hours.upper)
    && in_interval(t.mm, minutes.lower, minutes.upper)
    && in_interval(t.ss, seconds.lower, seconds.upper));
}

bool is_am(const Time& t)
{
    return (t.hh < noon);
}

string time_Formatting(int  i)
{
    if (i<10)
    {
        return ('0'+to_string(i));
    }
    else
    {
        return to_string(i);
    }
}

// TODO: Complementary work. Do not use int for a true/false
// parameter.
//----DONE---
string to_string(Time const& t, bool is24h)
{
    if (is24h)
    {
        return time_Formatting(t.hh) + ":" + time_Formatting(t.mm)
        + ":"+ time_Formatting(t.ss);
    }
    else
    {
        int hours{t.hh};
        if (!is_am(t))
        {
            hours = hours - 12;
        }
        string states[2]{"pm", "am"};
        return time_Formatting(hours) + ":" + time_Formatting(t.mm)
        + ":"+ time_Formatting(t.ss) + " " + states[is_am(t)];
    }
}

//TODO: Complementary work. Do you want to change t?
//---DONE---
int time_to_seconds(Time const& t)
{
    return (t.hh*seconds_per_hour
    + t.mm*seconds_per_minute
    + t.ss);
}

void map_time(int& s)
{
    if (s >= maximum_seconds)
    {
        s = s%maximum_seconds;
    }
    else
    {
        s = (maximum_seconds+s)%maximum_seconds;
    }
}

Time seconds_to_time(int s)
{   
    Time t{};

    if (!in_interval(s, minimum_seconds, maximum_seconds))
    {
        map_time(s);
    }

    t.hh = s/seconds_per_hour;
    s = s-(t.hh*seconds_per_hour);
    t.mm = s/seconds_per_minute;
    t.ss = s%seconds_per_minute;

    return t;
}

// TODO: Complementary work. Only implement either + or ++ and then
// use the other to implement the second. This removes duplicated code
// and saves you work if you would have to change your implementation
// later. This applies to the <, >, ==, != operators as well, only
// implement the ones you need and then use these to implement the
// others.
//---DONE---

Time operator+(Time& t, int n)
{
    t = seconds_to_time(time_to_seconds(t) + n);
    return t;
}

Time operator+(int n, Time& t)
{
    t = seconds_to_time(time_to_seconds(t) + n);
    return t;
    }

Time operator+(Time& t, Time& n)
{
    t = seconds_to_time(time_to_seconds(t) + time_to_seconds(n));
    return t;
}

Time& operator++(Time& t)
{   
  t=t+1;
  return t;
}

Time operator++(Time& t, int)
{
    Time temp{t};
    t=t+1;
    return temp;
}

Time operator-(Time& t, int n)
{
    t = seconds_to_time(time_to_seconds(t) - n);
    return t;
}
Time operator-(int n, Time& t)
{
    t = seconds_to_time(n-time_to_seconds(t));
    return t;
    }

Time operator-(Time& t, Time& n)
{
    t = seconds_to_time(time_to_seconds(t) - time_to_seconds(n));
    return t;
}

Time& operator--(Time& t)
{
    t = t-1;
    return t;
}

Time operator--(Time& t, int)
{
    Time temp{t};
    t = t-1;
    return temp;
}

bool operator<(Time& t1, Time& t2)
{
    return time_to_seconds(t1) < time_to_seconds(t2);
}

bool operator>(Time& t1, Time& t2)
{
  return !(t1<t2);
}

bool operator<=(Time& t1, Time& t2)
{
    return time_to_seconds(t1) <= time_to_seconds(t2);
}

bool operator>=(Time& t1, Time& t2)
{
    return !(t1<t2);
}

bool operator==(Time& t1, Time& t2)
{
    return time_to_seconds(t1) == time_to_seconds(t2);
}

bool operator!=(Time& t1, Time& t2)
{
  return !(t1==t2);
}

// TODO: Complementary work. You have a function to transform a time
// into a string. Use that one instead.
//---DONE---
ostream& operator<<(ostream& os, Time const& t)
{
   os << to_string(t,true);
   return os;
}

// TODO: Complementary work. If the operator does not work as it
// usually do, this must be documented.
//---DONE---
/*
The overloaded operator extracts the input from the input stream and checks if the input corresponds to valid time format (validates the input).'
If the input is not a valid time format, the failbit flag is assigned to the input stream.
 */
istream& operator>>(istream& is, Time& t)
{
    string temp{};
    is >> t.hh >> temp >> t.mm >> temp >> t.ss;
    if (is_valid(t))
    {
        return is;
    }
	
    else
    {
        cin.setstate(ios_base::failbit);
        cerr << "Invalid input";

    }

} 


