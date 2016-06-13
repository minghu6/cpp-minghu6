#include "Test.h"

#include "../utils.h"

#include <list>

using std::list;

using minghu6::CSV;

CSV test_read_csv_file(){
	CSV cs("D:\\Coding\\C-C++\\utils\\utils\\Test\\test.csv");
	map<u32, map<u32, string>> stringMap = cs.getCSVMap();

	map<u32, map<u32, string>>::iterator iter = stringMap.begin();
	for (; iter != stringMap.end(); ++iter)
	{
		map<u32, string> strmap = iter->second;
		cout << iter->first << "  ";
		map<u32, string>::iterator it = strmap.begin();
		for (; it != strmap.end(); ++it)
		{
			cout << it->first<<". "<<it->second << "  ";
		}
		cout << endl;
	}
	return cs;
}

void test_saveload(){
	CSV csv;
	csv=test_read_csv_file();

	csv.saveCSV();
	test_read_csv_file();

}
void test_find(){
	CSV cs("D:\\Coding\\C-C++\\utils\\utils\\Test\\test.csv");
	list<unsigned long> res, res2;
	//res = cs.find(2, string("¹«Ëï×ÓÁ¼"));
	res2 = cs.find(pair<unsigned long, string>(6, string("d")));

	/*
	list <unsigned long>::iterator iter;
	for (iter = res.begin(); iter != res.end(); iter++) {
		cout << *iter << endl;
	}

	for (iter = res2.begin(); iter != res2.end(); iter++) {
		cout << *iter << endl;
	}
	*/

}

int test_CSV(){
	//test_read_csv_file();
	//test_find();
	test_saveload();
	system("pause");
	return 0;
}