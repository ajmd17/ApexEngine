#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include "../util/strutil.h"
#include "../util/logutil.h"

#include <algorithm>

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

#include <iostream>
using std::ostream;

namespace apex
{
	class ShaderProperties
	{
	public:
		map<string, bool> values;

		ShaderProperties setProperty(string name, bool val)
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

		ShaderProperties(const ShaderProperties &other)
		{
			this->values.clear();
			this->values.insert(other.values.begin(), other.values.end());
		}

		friend ostream& operator<<(ostream& out, const ShaderProperties &props) // output
		{
			out << "ShaderProperties {\n";
			/*for (map<string, bool>::iterator i = props.values.begin(); i != props.values.end(); ++i)
			{
				out << "\t" << i->first << ":\t" << i->second << "\n";
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

		// TODO
		static string formatShaderProperties(string &code, ShaderProperties &properties)
		{
			return code;
		}

		static bool compareShaderProperties(ShaderProperties a, ShaderProperties b)
		{
			for (std::map<std::string, bool>::iterator i = a.values.begin(); i != a.values.end(); ++i)
			{
				if (b.values.find(i->first) != b.values.end())
				{
					if (b.values[i->first] != i->second)
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

			return true;
		}

	};
}
#endif
