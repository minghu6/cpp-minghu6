
#define _CRT_SECURE_NO_WARNINGS


#include<ctime>

#include "Date.h"

#include "../string/string.h"

using minghu6::Date;
//using minghu6::getcurrentDate;
using minghu6::trimString;
using minghu6::splitString;
using std::atoi;

map<int, int> Date::init_months(){
    map<int, int> m=map<int, int>();
    
    m.insert(pair<int, int>(1, 31));
    m.insert(pair<int, int>(2, 29));
    m.insert(pair<int, int>(3, 31));
    m.insert(pair<int, int>(4, 30));
    m.insert(pair<int, int>(5, 31));
    m.insert(pair<int, int>(6, 30));
    m.insert(pair<int, int>(7, 31));
    m.insert(pair<int, int>(8, 31));
    m.insert(pair<int, int>(9, 30));
    m.insert(pair<int, int>(10, 31));
    m.insert(pair<int, int>(11, 30));
    m.insert(pair<int, int>(12, 31));

	return m;
    
}

map<int, int>Date::real_months(int year){
	map<int, int> months_real = Date::months_t;
    
    if (!Date::isLeapyear(year))months_real[2]--;//不是闰年
    
    return months_real;
}
map<int, int> Date::months_t = Date::init_months();

map<int, int> Date::real_months(){
	return Date::real_months(this->getYear());
}

Date::Date(){}
Date::Date(int m, int d, int y){
	this->month = m;
    this->day=d;
    this->year=y;
    
}

Date::Date(Date& date){
	this->year = date.getYear();
	this->month = date.getMonth();
	this->day = date.getDay();
}

Date::Date(string date_s){
	date_s = trimString(date_s);
	vector<string>v;
	splitString(date_s, v, string("-"));
	int y = atoi(v[0].c_str());
	int m = atoi(v[1].c_str());
	int d = atoi(v[2].c_str());

	this->month = m;
	this->day = d;
	this->year = y;

}

void Date::setDate(int m, int d, int y){
	this->month = m;
    this->day=d;
    this->year=y;
}

void Date::setDate(Date date){
	this->setDate(date.getMonth(), date.getDay(), date.getYear());
}
string Date::getDate(){

	ostringstream ost;
	ost << this->year  << "-"
		<< setfill('0')<<setw(2)<<this->month << "-"
		<<setfill('0') << setw(2) << this->day;


    return ost.str();
}

long Date::toDays(){
    long sum =0;
    if (this->year >= 0) {// AD
        for (int y = 1; y<this->year; ++y) {
            sum += 365 + this->isLeapyear();
        }
        for (int m = 1; m < this->month; ++m) {
            map<int, int>months = Date::real_months(this->year);
            sum += months[m];
        }
        sum += this->day;
    }else{//this->year<0 BD
        for (int y = this->year; y<1; ++y) {
            sum -= 365 + this->isLeapyear();
        }
        for (int m = 1; m < this->month; ++m) {
            map<int, int>months = Date::real_months(this->year);
            sum += months[m];
        }
        sum += this->day;
    }
    return sum;  
}



Date Date::operator+(int day){
	
	Date d = Date(*this);
	
    if(day==0) return d;//如果天数为0，返回当个月  
    if(day>0){  
        d.setDay(d.getDay()+day);
        map<int, int>months=d.real_months();
		
        while(d.getDay()>months[d.getMonth()]){  
            d.setDay(d.getDay()-months[d.getMonth()]);
            d.setMonth(d.getMonth()+1);                         
            if(d.getMonth()>12){  
                d.setYear(d.getYear()+1);  
                d.setMonth(1);  
				months = d.real_months();
            }
			
        }
		//cout << d.getDate();
        return d;  
    }  
    else { 
		return this->operator-(-day);
    }
   
 }


/* need optimize!! */
Date Date::operator+ ( Date date2){
	
    Date d;
	d = Date::operator+(date2.toDays());

	
	return d;
}

Date Date::operator- (int day) {
    Date d = Date(*this);
    if (day == 0) return d;
    if (day > 0) {
        d.setDay(d.getDay()-day);
        map<int, int>months=d.real_months();
        while (d.getDay() <= 0) {
            d.setMonth(d.getMonth()-1);
            if (d.getMonth() == 0) {
                d.setMonth(12);
                d.setYear(d.getYear()-1);
                months=d.real_months();
            }
            d.setDay(d.getDay() + months[d.getMonth()]);
        }
        return d;
    }
    else {
		return this->operator+(-day);
    }
}
/* need optimize!! */
Date Date::operator- ( Date date2){
    Date d;
	d = this->operator-(date2.toDays());
	return d;
}


Date& Date::operator++ () {
    ++(this->day);
    map<int, int> months=this->real_months();
    
    if (this->day > months[this->month]) {
        this->day -= months[this->month];
        this->month++;
        if (this->month > 12) {
            ++this->year;
            this->month = 1;
        }
    }
    return (*this);  
}
Date& Date::operator++ (int) {
        Date tmp = *this;  
        ++(*this);    // Implemented by prefix increment  
        return Date(tmp); 
}

Date& Date::operator-- () {
   
    --this->day;
    map<int, int> months=this->real_months();
    
    while (this->day <= 0) {
        --this->month;
        if (this->month == 0) {
            this->month = 12;
            --this->year;
            months=this->real_months();
        }
        
        this->day += months[this->day];
    }
    return *this;  
}
Date& Date::operator-- (int) {
        Date tmp = *this;  
        --(*this);    // Implemented by prefix decrement  
        return Date(tmp); 
}

Date& Date::operator+= (int day){
	 Date d = (*this) + day;
	 this->setDate(d);
	 return *this;

}
Date& Date::operator+= ( Date &date){
	 Date d = (*this) + date;
	 this->setDate(d);
	 return *this;
}
Date& Date::operator-= ( int day){
	 Date d = (*this) - day;
	 this->setDate(d);
	 return *this;
}
Date& Date::operator-= ( Date &date){
	 Date d = (*this) - date;
	 this->setDate(d);
	 return *this;
}

 bool Date::operator> (Date date2) {
    if (this->getYear() > date2.getYear()) {
        return true;
	}
	else if (this->getYear() < date2.getYear()) {
        return false;
    } else {
		if (this->getMonth() > date2.getMonth()) {
            return true;
		}
		else if (this->getMonth() < date2.getMonth()) {
            return false;
        } else {
			if (this->getDay() > date2.getDay()) {
                return true;
			}
			else if (this->getDay() < date2.getDay()) {
                return false;
            } else {
                return false;
            }
        }
    }
}
 bool Date::operator== (Date date2){
	 if (this->getYear() == date2.getYear() && this->getMonth() == date2.getMonth() && this->getDay() == date2.getDay()){
        return true;
    }else{
        return false;
    }
}

 bool Date::operator>= (Date date2){
	 return (this->operator>(date2) || this->operator==(date2)) ? true : false;
}
 bool Date::operator< ( Date date2){
	 return !(this->operator>=(date2));
}
 bool Date::operator<= (Date date2){
    return !(operator>(date2));
}

 bool Date::operator!= ( Date date2){
	 return  !(this->operator==(date2));
}


Date minghu6::getcurrentDate(){
	 time_t calendar_time = time(NULL);

	 //locale time
	 struct tm * tm_local = localtime(&calendar_time);

	 int month = tm_local->tm_mon+1;
	 int day = tm_local->tm_mday;
	 int year = tm_local->tm_year + 1900;

	 return Date(month, day, year);
	 //time_t mk_time = mktime(tm_local);

 }