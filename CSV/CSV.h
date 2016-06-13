#pragma once

#include <assert.h>
#include <map>
#include <vector>
#include <list>
#include <string>

#include "../minghu6.h"
using std::map;
using std::vector;
using std::pair;
using std::list;

typedef unsigned long   u32;

namespace minghu6{
	class CSV
	{
	private:
		map<u32, map<u32, string>> m_stringMap;
		string m_csvName;//Not Used...
		string m_csvPath;
	public:
		CSV(){}
		CSV(const char *path)
		{
			assert(loadCSV(path));
		}
		~CSV(){ saveCSV(); }

		bool loadCSV(const char *path);
		bool saveCSV(const char *path = NULL);
		bool flush(const char* path = NULL){ saveCSV(path); };


		bool getIntValue(u32 uiRow, u32 uiCol, int &riValue);
		bool getFloatValue(u32 uiRow, u32 uiCol, double &rfValue);
		string* getStringValue(u32 uiRow, u32 uiCol);

		int getParamFromString(string str, vector<string> &stringVec, char delim = ',');


		map<u32, map<u32, string>>& getCSVMap()
		{
			return m_stringMap;
		}

		/* start from 0 */
		list<u32>& find(u32 col, string item);
		list<u32>& find(pair<u32, string>query);

		void push_back(string item);
		void update(u32 col, u32 row, string item);
		void update(pair<u32, u32> pos, string item);
		void remove(string item);


		void update(map<u32, map<u32, string>> csvMap){ m_stringMap = csvMap; };
		
	};
}

