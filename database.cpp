#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<utility>
#include<algorithm>
#include<iterator>
#include<exception>

#include "database.h"



	Database::Database(){}

	bool Database::Check(const string& date, const string& event){
		if(Database::_database_check.count(date) == 0){
			return true;
		}
		else{
			if(Database::_database_check[date].count(event) == 0){
				return true;
			}
		}
		return false;
	}
void Database::Add(const Date& date, const string& event){
if(date.date != ""){
			if(Database::Check(date.date,event)){
				Database::_database_check[date.date].insert(event);
				Database::_database[date.date].push_back(event);
			}
}
else{
	cout<<"Incorrect date in method 'Add' of class Database\n";
}
	}

	void Database::Add(const string& date, const string& event){
		if(date != ""){
			if(Database::Check(date,event)){
				Database::_database_check[date].insert(event);
				Database::_database[date].push_back(event);
			}
		}
		else{
			cout<<"Incorrect date in method 'Add' of class Database\n";
		}
	}
	string Database::Last(const string& date) const{
		if(Database::_database.empty()){
			string s;
			throw invalid_argument(s);
		}
		auto it = Database::_database.lower_bound(date);
		if(Database::_database.count(date) != 0){
			string answer =(it->first) + " " + (it->second).back();
			//cout<<answer<<endl;
			return answer;
		}
		else if(it == Database::_database.begin()){
			string s;
			throw invalid_argument(s);
		}
		else{
			auto it_answer = prev(it);
			string answer = (it_answer->first) + " " + (it_answer->second).back();
			//cout<<answer<<endl;
			return answer;
		}
	}
	string Database::Last(const Date& date) const{
			if(Database::_database.empty()){
				string s;
				throw invalid_argument(s);
			}
			auto it = Database::_database.lower_bound(date.date);
			if(Database::_database.count(date.date) != 0){
				string answer =(it->first) + " " + (it->second).back();
				//cout<<answer<<endl;
				return answer;
			}
			else if(it == Database::_database.begin()){
				string s;
				throw invalid_argument(s);
			}
			else{
				auto it_answer = prev(it);
				string answer = (it_answer->first) + " " + (it_answer->second).back();
				//cout<<answer<<endl;
				return answer;
			}
		}
	void Database::Print() const {
		for(const auto& m1 : Database::_database){
			for(const auto& m2 : m1.second){
				cout<<m1.first<<" "<<m2<<endl;
			}
		}
	}

	void Database::Print(ostream& os) const{
		for(const auto& m1 : Database::_database){
					for(const auto& m2 : m1.second){
						os<<m1.first<<" "<<m2<<endl;
					}
				}
	}
	const map<string,vector <string>>& Database::database() {
		return Database::_database;
	}
	const map<string,set<string>>& Database::database_check(){
		return Database::_database_check;
	}

