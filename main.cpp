#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<string>
#include<utility>
#include<algorithm>
#include<functional>
#include <iostream>
#include <stdexcept>


#include "Tests.h"
#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"


using namespace std;

//------------------------------------------

//-----------------------------------------------------------------

template <typename T>
void Print(T v){
	for(auto a : v){
		cout << a << " ";
	}
	cout<<endl;
}
template <typename T1,typename T2>
void Print (map<T1,T2> m){
	for(auto a1 : m){
		cout<< a1.first <<" - {";
		for(auto a2 : a1.second){
			cout<< a2 <<" ";
		}
		cout<<"}"<<endl;
	}
}

//--------------------------------------------------------------



void TestAll(){
	TestRunner tr;

	tr.RunTest(Test_Database,"Test_Database");
	tr.RunTest(Test_ComparisonDate,"Test_ComparisonDate");
	tr.RunTest(Test_ParseDate,"Test_ParseDate");
	tr.RunTest(Test_Last,"Test_Last");
	tr.RunTest(TestParseCondition,"TestParseCondition");
	tr.RunTest(TestParseEvent, "TestParseEvent");

}



int main(){
TestAll();



Database db;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
     // cout<<"command Add\n"<<"date="<<date<<" event="<<event<<endl;
    } else if (command == "Print") {
      db.Print();
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);};

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }


return 0;
}
/*
Add 2017-06-01 1st of June
Add 2017-07-08 8th of July
Add 2017-07-08 Someone's birthday
Del date == 2017-07-08
Print

 */
/*
Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-01-01 New Year
Find event != "Holiday"
 */

