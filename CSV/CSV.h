#pragma once

#include <assert.h>
#include <map>
#include <vector>
#include <string>

#include "../minghu6.h"
using std::map;
using std::vector;


typedef unsigned long   u32;

namespace minghu6{
	class CSV
	{
	private:
		map<u32, map<u32, string>> m_stringMap;
		string m_CSVName;
	public:
		CSV(){}
		CSV(const char *path)
		{
			assert(loadCSV(path));
		}
		~CSV(){}

		bool loadCSV(const char *path);
		bool saveCSV(const char *path = NULL);

		bool getIntValue(u32 uiRow, u32 uiCol, int &riValue);
		bool getFloatValue(u32 uiRow, u32 uiCol, double &rfValue);
		string* getStringValue(u32 uiRow, u32 uiCol);

		int getParamFromString(string str, vector<string> &stringVec, char delim = ',');


		map<u32, map<u32, string>>& getCSVMap()
		{
			return m_stringMap;
		}


	};
}

