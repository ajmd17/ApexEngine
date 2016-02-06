#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>
using std::unordered_map;

#include <memory>
using std::shared_ptr;

#include <string>
using std::string;

#include "../math/vector4f.h"
#include "texture.h"

namespace apex
{
	class Material
	{
	private:
		unordered_map<string, bool> booleans;
		unordered_map<string, int> integers;
		unordered_map<string, float> floats;
		unordered_map<string, Vector4f> vector4fs;
		unordered_map<string, string> strings;
		unordered_map<string, shared_ptr<Texture>> textures;
	public:
		const static string
			STRING_NAME,

			BOOL_DEPTHTEST,
			BOOL_DEPTHMASK,
			BOOL_CULLENABLED,
			BOOL_CASTSHADOWS,

			COLOR_DIFFUSE,
			COLOR_SPECULAR,
			COLOR_AMBIENT,

			TEXTURE_DIFFUSE,
			TEXTURE_NORMAL,
			TEXTURE_SPECULAR,
			TEXTURE_HEIGHT,
			TEXTURE_ENV,

			FLOAT_SPECULAR_EXPONENT,
			FLOAT_SHININESS,
			FLOAT_ROUGHNESS,
			FLOAT_ALPHADISCARD,

			INT_FACETOCULL,
			INT_BLENDMODE,
			INT_TECHNIQUE_SPECULAR,
			INT_TECHNIQUE_PERPIXELLIGHTING;


		// Constructor
		Material();

		// Checks 

		bool hasBool(string name)
		{
			unordered_map<string, bool>::iterator it = booleans.find(name.c_str());
			if (it != booleans.end())
				return true;
			return false;
		}

		bool hasInt(string name)
		{
			unordered_map<string, int>::iterator it = integers.find(name.c_str());
			if (it != integers.end())
				return true;
			return false;
		}

		bool hasFloat(string name)
		{
			unordered_map<string, float>::iterator it = floats.find(name.c_str());
			if (it != floats.end())
				return true;
			return false;
		}

		bool hasVector4f(string name)
		{
			unordered_map<string, Vector4f>::iterator it = vector4fs.find(name.c_str());
			if (it != vector4fs.end())
				return true;
			return false;
		}

		bool hasString(string name)
		{
			unordered_map<string, string>::iterator it = strings.find(name.c_str());
			if (it != strings.end())
				return true;
			return false;
		}

		bool hasTexture(string name)
		{
			unordered_map<string, shared_ptr<Texture>>::iterator it = textures.find(name.c_str());
			if (it != textures.end())
				return true;
			return false;
		}

		// Getting values 

		bool getBool(string name, bool &outBool)
		{
			if (hasBool(name))
			{
				outBool = booleans[name];
				return true;
			}
			else
				return false;
		}

		bool getInt(string name, int &outInt)
		{
			if (hasInt(name))
			{
				outInt = integers[name];
				return true;
			}
			else
				return false;
		}

		bool getFloat(string name, float &outFloat)
		{
			if (hasFloat(name))
			{
				outFloat = floats[name];
				return true;
			}
			else
				return false;
		}

		bool getVector4f(string name, Vector4f &outVec)
		{
			if (hasVector4f(name))
			{
				outVec = vector4fs[name];
				return true;
			}
			else
				return false;
		}

		bool getString(string name, string &outStr)
		{
			if (hasString(name))
			{
				outStr = strings[name];
				return true;
			}
			else
				return false;
		}

		bool getTexture(string name, shared_ptr<Texture> &outTex)
		{
			if (hasTexture(name))
			{
				outTex = textures[name];
				return true;
			}
			else
				return false;
		}

		// Setting values 

		void setBool(string name, bool val)
		{
			booleans[name] = val;
		}

		void setInt(string name, int val)
		{
			integers[name] = val;
		}

		void setFloat(string name, float val)
		{
			floats[name] = val;
		}

		void setVector4f(string name, Vector4f val)
		{
			vector4fs[name] = val;
		}

		void setString(string name, string val)
		{
			strings[name] = val;
		}

		void setTexture(string name, shared_ptr<Texture> val)
		{
			textures[name] = val;
		}
	};
}
#endif