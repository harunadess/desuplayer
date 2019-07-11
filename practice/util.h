#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <algorithm>
#include <cwctype>

inline std::wstring wstringToLower(const std::wstring& inWStr)
{
	std::wstring outWStr = inWStr;
	std::transform(outWStr.begin(), outWStr.end(), outWStr.begin(), std::towlower);

	return outWStr;
}


#endif // !UTIL_H
