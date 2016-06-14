
#ifndef STRING_H
#define STRING_H


#include "../common_utils.h"
#include "../minghu6.h"

#include <vector>
using std::vector;

namespace minghu6{
	vector<string>  splitString(const string& s, const string& c);
	vector<string>  splitString(const string& s, const char* c);

	string trimString(std::string & str);

	string ltrimString(std::string & str);

	string rtrimString(std::string & str);
}

#endif