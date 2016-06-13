#include "Test.h"

#include "../CSV/CSV.h"


void test_read_csv_file(){
	CppCSV cs("test.csv");
	map<u32, map<u32, string>> stringMap = cs.GetCSVMap();

	map<u32, map<u32, string>>::iterator iter = stringMap.begin();
	for (; iter != stringMap.end(); ++iter)
	{
		map<u32, string> strmap = iter->second;
		map<u32, string>::iterator it = strmap.begin();
		for (; it != strmap.end(); ++it)
		{
			cout << it->second << "  ";
		}
		cout << endl;
	}
}
int test_CSV(){
	test_read_csv_file();
}