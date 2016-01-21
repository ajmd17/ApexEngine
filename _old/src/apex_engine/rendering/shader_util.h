#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

class ShaderProperties
{
public:
	map<string, bool> values;

	ShaderProperties setProperty(string &name, bool &val)
	{
		bool hasVal = this->hasValue(name);

		if (!hasVal)
		{
			if (val == true) // Only add true values.
			{
				values.insert(std::pair<string, bool>(name, val));
			}
		}
		else
		{
			if (val == false)
			{
				// False values are not needed. They will simply be removed.
				std::map<string, bool>::iterator it;
				it = values.find(name);
				values.erase(it);
			}
			else
			{
				std::map<string, bool>::iterator it;
				it = values.find(name);
				it->second = val;
			}
		}

		return *this;
	}


	ShaderProperties()
	{
	}

	ShaderProperties(ShaderProperties &other)
	{
		this->values.clear();
		this->values.insert(other.values.begin(), other.values.end());
	}

	friend ostream& operator<<(ostream& out, const ShaderProperties &props) // output
	{
		out << "{";
		out << "}\n";
		return out;
	}

	bool hasValue(string name)
	{
		map<string, bool>::iterator it = values.find(name.c_str());
        return (it != values.end());
	}
};

class ShaderUtil
{
private:
	static vector<string> split(const string &text, char sep) {
		vector<string> tokens;
		std::size_t start = 0, end = 0;
		while ((end = text.find(sep, start)) != string::npos) {
			tokens.push_back(text.substr(start, end - start));
			start = end + 1;
		}
		tokens.push_back(text.substr(start));
		return tokens;
	}

	static std::string &ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	static bool startswith(string &str, string &startswith)
	{
		if (str.find(startswith.c_str()) == 0)
		{
			return true;
		}
		return false;
	}

public:
	static string formatShaderVersion(string &code)
	{
		string res = "";
		string verString = "";
		string ver = "#version";
		vector<string> lines = split(code, '\n');
		for (int i = 0; i < lines.size(); i++)
		{
			string line = lines[i];
			if (startswith(ltrim(line), ver))
			{
				verString = ltrim(line);
			}
			else
			{
				if (line != "")
				{
					res += line + "\n";
				}
			}
		}
		code = verString + "\n" + res;
		return code;
	}

	static string formatShaderProperties(string &code, ShaderProperties &properties)
	{
		return code;
	}
};
#endif