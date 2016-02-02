#ifndef STRUTIL_H
#define STRUTIL_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

inline string to_str(int i)
{
	string str = std::to_string(static_cast<long long>(i));

	return str;
}

inline string to_str(float f)
{
	stringstream ss(stringstream::in | stringstream::out);
	ss << f;
	string str = ss.str();

	return str;
}

inline string to_str(double d)
{
	stringstream ss(stringstream::in | stringstream::out);
	ss << d;
	string str = ss.str();

	return str;
}

inline vector<string> removeEmptyStrings(const vector<string> &strings)
{
	vector<string> res;
	for (int i = 0; i < strings.size(); i++)
	{
		if (strcmp(strings[i].c_str(), "") != 0)
		{
			res.push_back(strings[i]);
		}
	}
	return res;
}

inline int parseInt(const string &str)
{
	int res;
	if (!(std::istringstream(str) >> res)) 
		res = 0;
	return res;
}

inline float parseFloat(const string &str)
{
	float res;
	if (!(std::istringstream(str) >> res))
		res = 0;
	return res;
}

inline vector<string> split(const string &text, char sep) 
{
	vector<string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) 
	{
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

inline std::string &ltrim(std::string &s) 
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

inline bool startsWith(string &str, string &startswith)
{
	if (str.find(startswith.c_str()) == 0)
	{
		return true;
	}
	return false;
}

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