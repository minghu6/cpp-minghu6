
#include "string.h"



void minghu6::splitString(const string& s, vector<string>& v, const string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
void minghu6::splitString(const string& s, vector<string>& v, const char* c){

	return minghu6::splitString(s, v, string(c));
}



string minghu6::trimString(std::string & str)
{
	int s = str.find_first_not_of(" ");
	int e = str.find_last_not_of(" ");
	string snew = str.substr(s, e - s + 1);
	return snew;
}
string minghu6::ltrimString(std::string & str)
{
	int s = str.find_first_not_of(" ");
	
	string snew = str.substr(s);
	return snew;
}
string minghu6::rtrimString(std::string & str)
{
	int e = str.find_last_not_of(" ");
	string snew = str.substr(0, e + 1);
	return snew;
}