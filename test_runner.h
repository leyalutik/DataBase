#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

template <typename T>
ostream& operator<<(ostream& os,vector<T> V){
	bool flag = false;
	os<<"{";
	for(auto v:V){
		if(flag){
			os<<",";
		}
			os<<v;
			flag = true;
	}
	os<<"}";
	return os;
}

template <typename T1,typename T2>
ostream& operator<<(ostream& os,map<T1,T2> m){
	for(auto a1 : m){
		os<< a1.first <<" - {";
		for(auto a2 : a1.second){
			os<< a2 <<" ";
		}
		os<<"}"<<endl;
	}
	return os;
}
template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& test_name){
	if( t != u){
		ostringstream s;
		s<<"Test "<<test_name<<" is fallen"<<endl;
		s<<t<<" != "<<u<<endl;
		throw runtime_error(s.str());
	}
}

template<typename U>
void Assert(const U& u, const string& name_check){
	//cerr << name_check<<endl;
	assert(u == true);
}


class TestRunner{
public:


	template<typename FuncTest>
	void RunTest(FuncTest function, const string& test_name){
		try{
			function();
			cerr<<"Test Ok"<<endl;
		}
		catch(runtime_error &e){
			++fail_count;
			cerr<<"Test "<<test_name<<" is failed : "<<endl;
			cerr<<e.what();
		}
		catch (...) {
		      ++fail_count;
		      cerr << "Unknown exception caught" << endl;
		    }
	}

	~TestRunner(){
		if(fail_count > 0 ){
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}
private:
	int fail_count = 0;

};

