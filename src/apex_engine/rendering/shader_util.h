#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include "../util/strutil.h"

#include <algorithm> 

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

#include <iostream>
using std::ostream;

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
		out << "ShaderProperties {\n";
		/*for (int i = 0; i < props.values.size(); i++)
		{
			std::map<string, bool>::iterator it;
			it = props.values.find(props.values.begin() + i);
			out << it->first << "\t" << it->second << "\n";
		}*/
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
	

public:
	static string formatShaderVersion(string &code)
	{
		string res = "";
		string verString = "";
		string ver = "#version";
		vector<string> lines = split(code, '\n');
		for (size_t i = 0; i < lines.size(); i++)
		{
			string line = lines[i];
			if (startsWith(ltrim(line), ver))
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