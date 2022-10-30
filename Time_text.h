#ifndef TIME_TEXT_H
#define TIME_TEXT_H

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

struct Time
{
    int hh{};
    int mm{};
    int ss{};
};

bool is_valid(Time const& t);

std::string to_string(Time const& t, bool is24h);

bool is_am(Time const& t);

Time& operator++(Time& t);
Time operator++(Time& t, int);

Time& operator--(Time& t);
Time operator--(Time& t, int);

Time operator+(Time& t, int n);
Time operator+(int n, Time& t);
Time operator+(Time& t, Time& n);

Time operator-(Time& t, int n);
Time operator-(int n, Time& t);
Time operator-(Time& t, Time& n);

bool operator<(Time& t1, Time& t2);
bool operator>(Time& t1, Time& t2);
bool operator<=(Time& t1, Time& t2);
bool operator>=(Time& t1, Time& t2);
bool operator==(Time& t1, Time& t2);
bool operator!=(Time& t1, Time& t2);

std::ostream& operator<<(std::ostream& os, Time const& t);
std::istream& operator>>(std::istream& is, Time& t);

#endif
