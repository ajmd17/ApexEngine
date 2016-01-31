#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>
using std::string;

inline bool endsWith(const char *str, const char *suffix)
{
	if (!str || !suffix)
		return false;

	size_t lenstr = strlen(str);
	size_t lensuffix = strlen(suffix);

	if (lensuffix >  lenstr)
		return false;

	return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

#endif