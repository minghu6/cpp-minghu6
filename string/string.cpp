
#include "string.h"



vector<string> minghu6::splitString(const string& s, const string& c)
{
	vector<string> v;
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

	return v;
}
vector<string>  minghu6::splitString(const string& s, const char* c){

	return minghu6::splitString(s, string(c));
}



string minghu6::trimString(std::string & str)
{	
	if (str.length() == 0) return str;

	int s = str.find_first_not_of(" ");
	int e = str.find_last_not_of(" ");
	string snew = str.substr(s, e - s + 1);
	return snew;
}
string minghu6::ltrimString(std::string & str)
{
	if (str.length() == 0) return str;

	int s = str.find_first_not_of(" ");
	
	string snew = str.substr(s);
	return snew;
}
string minghu6::rtrimString(std::string & str)
{
	if (str.length() == 0) return str;

	int e = str.find_last_not_of(" ");
	string snew = str.substr(0, e + 1);
	return snew;
}