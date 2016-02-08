#ifndef STRUTIL_H
#define STRUTIL_H

#include <vector>
using std::vector;

#include <cstring>
using std::string;

#include <sstream>
using std::stringstream;

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

namespace apex
{
	inline bool contains(const std::string s1, const std::string s2)
	{
		return s1.find(s2) != std::string::npos;
	}

	template <typename T>
	inline std::string to_str(T val)
	{
		stringstream ss(stringstream::in | stringstream::out);
		ss << val;
		std::string str = ss.str();

		return str;
	}

	template <typename T>
	inline T parse(const std::string &str)
	{
		T res;
		if (!(std::istringstream(str) >> res))
			res = 0;
		return res;
	}

	inline vector<std::string> removeEmptyStrings(const vector<std::string> &strings)
	{
		vector<std::string> res;
		for (int i = 0; i < strings.size(); i++)
		{
			if (strcmp(strings[i].c_str(), "") != 0)
			{
				res.push_back(strings[i]);
			}
		}
		return res;
	}

	inline vector<std::string> split(const std::string &text, const char sep)
	{
		vector<std::string> tokens;
		std::size_t start = 0, end = 0;
		while ((end = text.find(sep, start)) != std::string::npos)
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

	inline std::string &rtrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	inline std::string &trim(std::string &s)
	{
		return ltrim(rtrim(s));
	}

	inline bool startsWith(const string &str, const string &startswith)
	{
		if (str.find(startswith.c_str()) == 0)
		{
			return true;
		}
		return false;
	}

	inline bool endsWith(const string &str, const string &suffix)
	{
		const char *strC, *suffixC;
		strC = str.c_str();
		suffixC = suffix.c_str();

		size_t lenstr = strlen(strC);
		size_t lensuffix = strlen(suffixC);

		if (lensuffix > lenstr)
			return false;

		return strncmp(strC + lenstr - lensuffix, suffixC, lensuffix) == 0;
	}
}
#endif
