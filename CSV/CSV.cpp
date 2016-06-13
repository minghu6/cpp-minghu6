#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <fstream>

#include "CSV.h"
#include "../string/string.h"

using std::ofstream;
using std::ifstream;

using minghu6::CSV;
using minghu6::trimString;
using minghu6::splitString;


bool CSV::loadCSV(const char *path)
{
	ifstream fin;
	fin.open(path);

	if (fin.is_open()){
		this->m_csvPath = path;
		const int len = 8000;//1kb
		char *buf = new char[8000];
		memset(buf, 0, sizeof(char) * len);

		int col = 0;
		while (fin.getline(buf, len)){
			
			vector<string> v = splitString(string(buf), ",");
			map<u32, string> stringMap;
			//cout << string(buf);
			for (u32 i = 0; i < v.size(); ++i){
				stringMap[i] = trimString(v[i]);
			}
			this->m_stringMap[col] = stringMap;
			col++;
			memset(buf, 0, sizeof(char) * len);
		}
		delete[] buf;
		return true;
	}
	else{
		this->m_csvPath = string();
		return false;
	}
	

}


bool CSV::saveCSV(const char *path /* = NULL */)
{
	if (path != NULL)
	{
		m_csvPath = path;
	}

	ofstream fout;
	fout.open(this->m_csvPath);

	if (fout.is_open())
	{
		map<u32, map<u32, string>>::iterator iter = m_stringMap.begin();
		for (; iter != m_stringMap.end(); ++iter)
		{
			map<u32, string> &rStringMap = iter->second;
			map<u32, string>::iterator it = rStringMap.begin();
			for (; it != rStringMap.end(); ++it)
			{
				string strTemp = it->second;
				strTemp += ',';
				fout << strTemp;
				//cout << strTemp.c_str() << "  ";
			}
			fout << endl;
		}

		fout.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool CSV::getIntValue(u32 uiRow, u32 uiCol, int &riValue)
{
	string *pStr = getStringValue(uiRow, uiCol);
	if (pStr)
	{
		riValue = atoi(pStr->c_str());
		return true;
	}
	else
	{
		return false;
	}
}

bool CSV::getFloatValue(u32 uiRow, u32 uiCol, double &rfValue)
{
	string *pStr = getStringValue(uiRow, uiCol);
	if (pStr)
	{
		rfValue = atof(pStr->c_str());
		return true;
	}
	else
	{
		return false;
	}
}

string* CSV::getStringValue(u32 uiRow, u32 uiCol)
{
	map<u32, map<u32, string>>::iterator iter = m_stringMap.find(uiRow);
	if (iter != m_stringMap.end())
	{
		map<u32, string> &rStrMap = iter->second;
		map<u32, string>::iterator it = rStrMap.find(uiCol);
		if (it != rStrMap.end())
		{
			return &(it->second);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

//用于分割字符串，将CSV表格中的一行按照规则解析成一组字符串，存储在一个vector中
//根据CSV表格中所存储的数据的不同，重载各函数
int CSV::getParamFromString(string str, vector<string> &stringVec, char delim)
{
	char *token = strtok(const_cast<char *>(str.c_str()), &delim);
	while (token)
	{
		string strTemp = token;
		//strTemp = trimString(strTemp);//trim space!!
		stringVec.push_back(strTemp);
		token = strtok(NULL, &delim);
	}

	return stringVec.size();
}

list<u32>& CSV::find(u32 col, string item){

	map<u32, map<u32, string>> stringMap = this->m_stringMap;
	list<u32> res;
	map<u32, map<u32, string>>::iterator iter;
	for (iter = stringMap.begin(); iter != stringMap.end(); ++iter)
	{
		map<u32, string> line=iter->second;

		cout << line[col];
		if (line[col] == item)res.push_back(iter->first);

	}

	return res;
}

list<u32>& CSV::find(pair<u32, string>query){
	return CSV::find(query.first, query.second);
}