// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


#include <cassert>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <string>
#include <vector>

using namespace std;

inline string convertIntToString(size_t nNum) {
	string::value_type pstr[ 30 ];
	int res = sprintf_s(pstr, 30, "%d", nNum);
	if (res == -1) {
		assert(0);
		//throw "#conversion";
	}
	return string( pstr );
}

inline int convertStringToInt(const string& str) {
	int nRet = numeric_limits<int>::max();
	if (!sscanf_s(str.c_str(), "%d", &nRet, sizeof(nRet))) {
		assert(0);
		//throw "#conversion";
	}
	return nRet;
}

inline void trimStringRight(std::string& str, const string::value_type delimiters[])
{
	std::string::size_type pos = str.find_last_not_of(delimiters);
	if (pos == std::string::npos) str.erase();
	else str.erase(pos+1);
}

inline string getToken(const string& strLine, string::size_type& start, const string::value_type delimiters[]) {
	string::size_type index1, index2;
	index1 = strLine.find_first_not_of(delimiters, start);
	if (string::npos == index1) {
		start = strLine.length();
		return "";
	}
	index2 = strLine.find_first_of(delimiters, index1);
	if (string::npos == index2) {
		index2 = strLine.length();
	}
	start = index2 + 1;
	return strLine.substr(index1, index2 - index1);
}
