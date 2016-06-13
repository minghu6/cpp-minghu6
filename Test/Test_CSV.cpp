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
	res = cs.find(2, string("¹«Ëï×ÓÁ¼"));
	res2 = cs.find(pair<unsigned long, string>(6, string("d")));

	list <unsigned long>::iterator iter;
	for (iter = res.begin(); iter != res.end(); iter++) {
		cout << *iter <<":  " << cs.getline(*iter) << endl;
	}

	for (iter = res2.begin(); iter != res2.end(); iter++) {
		cout << *iter << ":  " << cs.getline(*iter) << endl;
	}
	
}

void test_remove_lines(){
	CSV &cs = test_read_csv_file();
	map<u32, string> line;

	/*
	line[0] = string("Student");
	line[1] = string("11111100011");
	line[2] = string("Anonymous");
	line[3] = string("1990-02-22");
	line[4] = string("");
	line[5] = string("");
	line[6] = string("d");
	*/
	cs.remove_lines(6, string("d"));
	cs.saveCSV();
	test_read_csv_file();
}
int test_CSV(){
	//test_read_csv_file();
	//test_find();
	//test_saveload();
	test_remove_lines();
	system("pause");
	return 0;
}