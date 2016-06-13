

#include "../common_utils.h"
#include "../minghu6.h"

#include <vector>
using std::vector;

namespace minghu6{
	void splitString(const string& s, vector<string>& v, const string& c);
	void splitString(const string& s, vector<string>& v, const char* c);

	string trimString(std::string & str);

	string ltrimString(std::string & str);

	string rtrimString(std::string & str);
}