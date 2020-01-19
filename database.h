#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<string>
#include<utility>
#include<algorithm>
#include<set>
#include<functional>
#include <stdexcept>

#include "date.h"

using namespace std;

class Database{
private:
	map<string,vector<string>> _database;
	map<string,set<string>> _database_check;

public:
	Database();
	bool Check(const string& date, const string& event);
	void Add(const Date& date, const string& event);
	void Add(const string& date, const string& event);
	void Print() const;
	void Print(ostream& os) const;
	string Last(const string& date) const;
	string Last(const Date& date) const;

	template <typename Funct>
	vector<string> FindIf(Funct Predicate) const{
		vector<string> entries;
		if(_database.empty()){
			return entries;
		}
		for( const auto& m : _database){
			auto it = m.second.begin();
			while(it != m.second.end()){
				string date = m.first;
				string event = *it;
				Date d(date);
				if(Predicate(d,event)){
					entries.push_back(date+" "+ event);
				}
			++it;
			}
		}
return entries;
}

	template<typename func>
	int RemoveIf(func Predicate){
			int counter = 0;
			vector<string> keys;
				for(auto m= _database.begin(); m!=_database.end(); ++m){
					string date = m->first;
					if(!m->second.empty()){

						auto it_begin = m->second.begin();
						auto it_end = m->second.end();
						Date d(date);
						auto Pred = [&Predicate,d](string event){ return !(Predicate(d,event));};
						auto it = stable_partition(it_begin,it_end,Pred);
						//Удаление из вспомогательной базы данных
						for(auto it_check = it; it_check != it_end; ++it_check){
							_database_check[date].erase(*it_check);
						}

						counter += (it_end - it);
						//cout<<"m->first = "<<m->first<<endl;
						//cout<<"counter="<<counter<<endl;
						_database[date].erase(it,it_end);

						if(_database[date].empty() || _database_check[date].empty()){
							if(_database[date].empty() == _database_check[date].empty()){
								keys.push_back(date);
							}
							else{
								cerr<<"In function RemoveIf() Database are not "<<
										"equal to Database_check"<<endl;
							}
						}


					}
					else{
						keys.push_back(date);
					}
				}
				for(const auto& v :keys){
					_database.erase(v);
					_database_check.erase(v);
				}
				//cout<<"return_counter="<<counter<<endl;;
				return counter;
		}


	bool CheckDatabases();

	const map<string,vector <string>>& database() ;
	const map<string,set<string>>& database_check();

};
