#include "CSV.h"
#include <stdio.h>


bool CppCSV::LoadCSV(const char *path)
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
			assert(GetParamFromString(iter->second, stringVec) > 0);

			vector<string>::size_type idx = 0;
			for (; idx != stringVec.size(); ++idx)
			{
				stringMapTemp[idx + 1] = stringVec[idx];
			}

			m_stringMap[iter->first] = stringMapTemp;
		}

		fclose(pFile);
		m_CSVName = path;
		return true;
	}
	else
	{
		return false;
	}
}

bool CppCSV::SaveCSV(const char *path /* = NULL */)
{
	if (path != NULL)
	{
		m_CSVName = path;
	}

	FILE *pFile = fopen(m_CSVName.c_str(), "w");
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
				fwrite(strTemp.c_str(), 1, 1, pFile);
			}

			char delim = '\n';
			fwrite(&delim, 1, 1, pFile);
		}

		fclose(pFile);
		return true;
	}
	else
	{
		return false;
	}
}

bool CppCSV::GetIntValue(u32 uiRow, u32 uiCol, int &riValue)
{
	string *pStr = GetStringValue(uiRow, uiCol);
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

bool CppCSV::GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue)
{
	string *pStr = GetStringValue(uiRow, uiCol);
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

string* CppCSV::GetStringValue(u32 uiRow, u32 uiCol)
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

//���ڷָ��ַ�������CSV����е�һ�а��չ��������һ���ַ������洢��һ��vector��
//����CSV��������洢�����ݵĲ�ͬ�����ظ�����
int CppCSV::GetParamFromString(string str, vector<string> &stringVec, char delim)
{
	char *token = strtok(const_cast<char *>(str.c_str()), &delim);
	while (token)
	{
		string strTemp = token;
		stringVec.push_back(strTemp);
		token = strtok(NULL, &delim);
	}

	return stringVec.size();
}

