#pragma once
#include<iostream>
#include<string>
#include<istream>
#include<sstream>
#include<iomanip>

using namespace std;


string ParseEvent(istream& is);

string ParseEvent(istringstream& is);

string ParseDate(istringstream& is);
string ParseDate(istream& is);


struct Date{
Date(const string& dat);
Date(const int& year, const int& month, const int& day);

void Set(const string& d);

string date;

int _year;
int _month;
int _day;

};

ostream& operator<<(ostream& os,Date d);
