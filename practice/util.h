#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <algorithm>
#include <cwctype>

using std::wstring;

inline wstring wstringToLower(const wstring& inWStr)
{
	wstring outWStr = inWStr;
	std::transform(outWStr.begin(), outWStr.end(), outWStr.begin(), std::towlower);

	return outWStr;
}


#endif // !UTIL_H
