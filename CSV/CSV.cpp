#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <fstream>

#include "CSV.h"
#include "../string/string.h"

using std::ofstream;

using minghu6::CSV;
using minghu6::trimString;

bool CSV::loadCSV(const char *path)
{
	FILE *pFile = fopen(path, "r");

	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		u32 uSize = ftell(pFile);
		rewind(pFile);

		char *fileBuffer = new char[uSize];
		fread(fileBuffer, 1, uSize, pFile);

		map<u32, string> stringMap;
		u32 uiIndex = 1;
		char *pBegin = fileBuffer;
		char *pEnd = strchr(pBegin, '\n');


		pBegin = pEnd + 1;
		pEnd = strchr(pBegin, '\n');

		while (pEnd)
		{
			string strTemp;
			strTemp.insert(0, pBegin, pEnd - pBegin);
			assert(!strTemp.empty());
			stringMap[uiIndex++] = strTemp;
			pBegin = pEnd + 1;
			pEnd = strchr(pBegin, '\n');
		}
		delete[]fileBuffer;
		fileBuffer = NULL;
		pBegin = NULL;
		pEnd = NULL;

		map<u32, string>::iterator iter = stringMap.begin();
		for (; iter != stringMap.end(); ++iter)
		{
			vector<string> stringVec;
			map<u32, string> stringMapTemp;
			assert(getParamFromString(iter->second, stringVec) > 0);

			vector<string>::size_type idx = 0;
			for (; idx != stringVec.size(); ++idx)
			{
				stringMapTemp[idx + 1] = stringVec[idx];
			}

			m_stringMap[iter->first] = stringMapTemp;
		}

		fclose(pFile);
		m_csvPath = path;
		return true;
	}
	else
	{
		return false;
	}
}


bool CSV::saveCSV(const char *path /* = NULL */)
{
	if (path != NULL)
	{
		m_csvPath = path;
	}

	/*
	FILE *pFile = fopen(m_csvPath.c_str(), "w");
	if (pFile)
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
				fwrite(strTemp.c_str(), sizeof(strTemp.c_str()), 1, pFile);
				//cout << strTemp.c_str() << "  ";
			}

			char delim = '\n';
			fwrite(&delim, sizeof(delim), 1, pFile);
		}

		fclose(pFile);
		return true;
	}
	else
	{
		return false;
	}
	*/

	ofstream fout;
	fout.open(this->m_csvPath);

	if (fout)
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