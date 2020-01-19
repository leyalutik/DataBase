#include "date.h"


string ParseEvent(istringstream& is){
int flag = 0;
	while(flag == 0){
		if(is.peek() == ' '){
			is.get();
		}
		else{
			flag = 1;
		}
	}

string str;
getline(is,str,'\n');
return str;

}


string ParseEvent(istream& is){
int flag = 0;
while(flag == 0){
	if(is.peek() == ' '){
		is.get();
	}
	else{
		flag = 1;
	}
}

	string str;
	getline(is,str,'\n');
	return str;
}

string ParseDate(istringstream& is){
string date;
int Year = 0;
int Month = 0;
int Day = 0;
int flag = 0;
while(flag == 0){
	if(is.peek() == ' '){
		is.get();
	}
	else{
		flag = 1;
	}
}

//Проверка что первый введенный символ - цифра
if(is.peek() == '0' || is.peek() == '1' || is.peek() == '2' || is.peek() == '3' ||
   is.peek() == '4' || is.peek() == '5' || is.peek() == '6' || is.peek() == '7' ||
   is.peek() == '8' || is.peek() == '9' ){

	is >> Year;
	//cout<<"Year="<<Year<<endl;
	if(is.peek() == '-' && Year <= 9999 && Year >= 0){
		is.get();// consume '-'
		is >> Month;
		//cout<<"Year="<<Year<<endl;
		//cout<<"Month="<<Month<<endl;
		if(is.peek() == '-' && Month >= 1 && Month <= 12){
			is.get();
			is >> Day;
			//cout<<"Year="<<Year<<endl;
			//cout<<"Month="<<Month<<endl;
			//cout<<"Day="<<Day<<endl;

			if(is.peek() == ' ' || is.peek() == ',' ){
				if(is.peek() == ','){
					is.get();
				}
				if(is.peek() == ' '){
					is.get();
				}
			}

				stringstream ss;
				ss << fixed << setw(4)<<setfill('0') <<Year <<'-';
				ss << fixed << setw(2) <<setfill('0') <<Month << '-';
				ss << fixed << setw(2) <<setfill('0') <<Day;
				//cout<<"ss.str()="<<ss.str()<<endl;
				return ss.str();

		}
		else{
			cerr<<"In function PardeDate incorrect input date\n";
				return "";
		}
	}
	else{
		cerr<<"In function PardeDate incorrect input date\n";
			return "";
	}
}
else{
	cerr<<"In function PardeDate incorrect input date\n";
	return "";
}

}

string ParseDate(istream& is){
	string date;
	int Year = 0;
	int Month = 0;
	int Day = 0;
	int flag = 0;
	while(flag == 0){
		if(is.peek() == ' '){
			is.get();
		}
		else{
			flag = 1;
		}
	}

	//Проверка что первый введенный символ - цифра
	if(is.peek() == '0' || is.peek() == '1' || is.peek() == '2' || is.peek() == '3' ||
	   is.peek() == '4' || is.peek() == '5' || is.peek() == '6' || is.peek() == '7' ||
	   is.peek() == '8' || is.peek() == '9' ){

		is >> Year;
		//cout<<"Year="<<Year<<endl;
		if(is.peek() == '-' && Year <= 9999 && Year >= 0){
			is.get();// consume '-'
			is >> Month;
			//cout<<"Year="<<Year<<endl;
			//cout<<"Month="<<Month<<endl;
			if(is.peek() == '-' && Month >= 1 && Month <= 12){
				is.get();
				is >> Day;
				//cout<<"Year="<<Year<<endl;
				//cout<<"Month="<<Month<<endl;
				//cout<<"Day="<<Day<<endl;

				if(is.peek() == ' ' || is.peek() == ',' ){
					if(is.peek() == ','){
						is.get();
					}
					if(is.peek() == ' '){
						is.get();
					}
				}

					stringstream ss;
					ss << fixed << setw(4)<<setfill('0') <<Year <<'-';
					ss << fixed << setw(2) <<setfill('0') <<Month << '-';
					ss << fixed << setw(2) <<setfill('0') <<Day;
					//cout<<"ss.str()="<<ss.str()<<endl;
					return ss.str();

			}
			else{
				cerr<<"In function PardeDate incorrect input date\n";
					return "";
			}
		}
		else{
			cerr<<"In function PardeDate incorrect input date\n";
				return "";
		}
	}
	else{
		cerr<<"In function PardeDate incorrect input date\n";
		return "";
	}

}

//-----------------------------------------------------------

Date::Date(const int& year, const int& month, const int& day){
	Date::_year = year;
	Date::_month = month;
	Date::_day = day;

		ostringstream os;
		os << setw(4) << setfill('0') << _year<<'-';
		os << setw(2) << setfill('0') << _month<<'-';
		os << setw(2) << setfill('0') << _day;
		Date::date = os.str();
	}

Date::Date(const string& dat){
	Date::_year = 0;
	Date::_month = 0;
	Date::_day = 0;
	Date::date = dat;


}

void Date::Set(const string& d){
	Date::date = d;

}

ostream& operator<<(ostream& os,Date d){
	os<<d.date;
	return os;
}
