


#include "Tests.h"




void Test_Database(){

Database d;


string date("2017-00-00");
string event("New York");
map<string,vector<string>> m;
m["2017-00-00"].push_back("New York");

d.Add(date,event);


AssertEqual( m,d.database(),"1");

//------------------Проверка вывода базы

string s1 = "2017-01-01 Holiday";
istringstream is1("2017-01-01 Holiday");

date = ParseDate(is1);
event = ParseEvent(is1);

d.Add(date,event);
d.Add(date,event);


string s2 = "2017-1-1 New Year";
istringstream is2("2017-1-1 New Year");
date = ParseDate(is2);
event = ParseEvent(is2);
d.Add(date,event);
istringstream is3("2017-03-08 Holiday");
date = ParseDate(is3);
event = ParseEvent(is3);
d.Add(date,event);
map<string ,vector<string>> m2= {{"2017-00-00",vector<string>({"New York"})},
		{"2017-01-01",vector<string>({"Holiday","New Year"})},{"2017-03-08",
				vector<string>({"Holiday"})}};

AssertEqual( m2 ,d.database(),"2");


}

void Test_ParseDate(){
	istringstream is("12-12-12 1223-12-12, 0-12-12 ");
	AssertEqual("0012-12-12",ParseDate(is),"0");
	AssertEqual("1223-12-12",ParseDate(is),"1");
	//string s;is >> s;cout << s;
	AssertEqual("0000-12-12",ParseDate(is),"2");
	//AssertEqual("",ParseDate(is),"3");
	//AssertEqual("",ParseDate(is),"4");
}

void Test_EventDate(){
	istringstream is("12-12-12 New York of us");
	ParseDate(is);
	AssertEqual("New York of us",ParseEvent(is),"0");
}
void Test_ComparisonDate(){
	DateComparisonNode d1(Comparison::Less,{2017,01,02});
	EventComparisonNode ev1(Comparison::Equal,"New Year");
	AssertEqual( true ,d1.Evaluate(Date(2017,1,1),"New Year"),"1");
	AssertEqual( true ,ev1.Evaluate(Date(2017,1,1),"New Year"),"2");

}

void Test_Last(){
Database d;
try{
	//AssertEqual( "" ,d.Last ("2017-06-01"),"3");
}catch (invalid_argument&) {

}
d.Add("2017-01-01","New Year");
d.Add("2017-03-08","Holiday");
d.Add("2017-01-01","Holiday");
try{
	//AssertEqual( "" ,d.Last ("2016-12-31"),"1");
}catch (invalid_argument&) {
	cout << "No entries" << endl;
}

AssertEqual( "2017-01-01 Holiday" ,d.Last ("2017-01-01"),"2");
AssertEqual( "2017-03-08 Holiday" ,d.Last ("2017-06-01"),"3");
AssertEqual( "2017-03-08 Holiday" ,d.Last ("2017-03-08"),"4");
AssertEqual( "2017-01-01 Holiday" ,d.Last ("2017-02-01"),"3");
AssertEqual( "2017-03-08 Holiday" ,d.Last ("2017-06-01"),"3");


}
//---------------------


void TestParseCondition() {
  {
    istringstream is("date != 2017-11-18");
    shared_ptr<Node> root = ParseCondition(is);
    Date d(2017,1,1);
    Assert(root->Evaluate(d, ""), "Parse condition 1");
    Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
  }
  {
    istringstream is(R"(event == "sport event")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
    Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
  }
  {
    istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
    Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
    Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
    Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
    Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
  }
  {
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
    Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
    Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
  }
  {
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
    Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
    Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
  }
  {
    istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
  }
  {
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
  }
  {
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
    Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
    Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
  }
}


void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}




