#include "Test.h"

#include "../utils.h"

using minghu6::splitString;
using minghu6::trimString;
using minghu6::ltrimString;
using minghu6::rtrimString;


void test_splitString(){
	string s="1999-09-02";
	vector<string>v;
	
	splitString(s, v, string("-"));

	
	cout << v.size() << endl;
	cout << v[0]<<" ";
	cout << v[1]<<" ";
	cout << v[2]<<" "<<endl;
	

	/*
	vector<string>::const_iterator the_iterator;
	
	while (the_iterator != v.end()) {
		cout << *the_iterator << endl;
		the_iterator++;
	}
	*/
	
}

void test_trim(){
	string s = "  abc   ";
	string s2 = "123";
	cout << s + s2 << endl;
	cout << trimString(s)+s2 << endl;
	cout << ltrimString(s) + s2 << endl;
	cout << rtrimString(s) + s2 << endl;
}
int test_string(){

	//test_splitString();
	test_trim();
	system("pause");
	return 0;

}