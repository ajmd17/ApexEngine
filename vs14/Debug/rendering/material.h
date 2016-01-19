#ifndef MATERIAL_H
#define MATERIAL_H

#include "..\math\vector4f.h"

#include <map>
using std::map;

#include <string>
using std::string;

class Material
{
public:
	enum Bucket { Opaque, Transparent, Particle, Skybox };
private:
	Bucket bucket;
	map<string, bool> booleans;
	map<string, int> integers;
	map<string, float> floats;
	map<string, Vector4f> vector4fs;
	map<string, string> strings;
public:
	const static string MATERIAL_NAME,
		MATERIAL_ALPHADISCARD,
		MATERIAL_BLENDMODE,
		MATERIAL_DEPTHTEST,
		MATERIAL_DEPTHMASK,
		MATERIAL_FACETOCULL,
		MATERIAL_CULLENABLED,
		MATERIAL_CASTSHADOWS,

		COLOR_DIFFUSE,
		COLOR_SPECULAR,
		COLOR_AMBIENT,

		TEXTURE_DIFFUSE,
		TEXTURE_NORMAL,
		TEXTURE_SPECULAR,
		TEXTURE_HEIGHT,
		TEXTURE_ENV,

		SPECULAR_EXPONENT,
		SHININESS,
		ROUGHNESS,
		TECHNIQUE_SPECULAR,
		TECHNIQUE_PERPIXELLIGHTING;

	/* Checks */

	bool hasBool(string name)
	{
		map<string, bool>::iterator it = booleans.find(name.c_str());
		if (it != booleans.end())
			return true;
		return false;
	}

	bool hasInt(string name)
	{
		map<string, int>::iterator it = integers.find(name.c_str());
		if (it != integers.end())
			return true;
		return false;
	}

	bool hasFloat(string name)
	{
		map<string, float>::iterator it = floats.find(name.c_str());
		if (it != floats.end())
			return true;
		return false;
	}

	bool hasVector4f(string name)
	{
		map<string, Vector4f>::iterator it = vector4fs.find(name.c_str());
		if (it != vector4fs.end())
			return true;
		return false;
	}

	bool hasString(string name)
	{
		map<string, string>::iterator it = strings.find(name.c_str());
		if (it != strings.end())
			return true;
		return false;
	}

	/* Getting values */

	bool getBool(string name, bool &outBool)
	{
		if (hasBool(name))
		{
			std::map<string, bool>::iterator it;
			it = booleans.find(name);
			outBool = it->second;
			return true;
		}
		else
			return false;
	}

	bool getInt(string name, int &outInt)
	{
		if (hasInt(name))
		{
			std::map<string, int>::iterator it;
			it = integers.find(name);
			outInt = it->second;
			return true;
		}
		else
			return false;
	}

	bool getFloat(string name, float &outFloat)
	{
		if (hasFloat(name))
		{
			std::map<string, float>::iterator it;
			it = floats.find(name);
			outFloat = it->second;
			return true;
		}
		else
			return false;
	}

	bool getVector4f(string name, Vector4f &outVec)
	{
		if (hasVector4f(name))
		{
			std::map<string, Vector4f>::iterator it;
			it = vector4fs.find(name);
			outVec = it->second;
			return true;
		}
		else
			return false;
	}

	bool getString(string name, string &outStr)
	{
		if (hasString(name))
		{
			std::map<string, string>::iterator it;
			it = strings.find(name);
			outStr = it->second;
			return true;
		}
		else
			return false;
	}

	/* Setting values */

	void setBool(string name, bool val)
	{
		bool hasVal = this->hasBool(name);

		if (!hasVal)
			booleans.insert(std::pair<string, bool>(name, val));
		else
		{
			std::map<string, bool>::iterator it;
			it = booleans.find(name);
			it->second = val;
		}
	}

	void setInt(string name, int val)
	{
		bool hasVal = this->hasInt(name);

		if (!hasVal)
			integers.insert(std::pair<string, int>(name, val));
		else
		{
			std::map<string, int>::iterator it;
			it = integers.find(name);
			it->second = val;
		}
	}

	void setFloat(string name, float val)
	{
		bool hasVal = this->hasFloat(name);

		if (!hasVal)
			floats.insert(std::pair<string, float>(name, val));
		else
		{
			std::map<string, float>::iterator it;
			it = floats.find(name);
			it->second = val;
		}
	}

	void setVector4f(string name, Vector4f val)
	{
		bool hasVal = this->hasVector4f(name);

		if (!hasVal)
			vector4fs.insert(std::pair<string, Vector4f>(name, val));
		else
		{
			std::map<string, Vector4f>::iterator it;
			it = vector4fs.find(name);
			it->second = val;
		}
	}

	void setString(string name, string val)
	{
		bool hasVal = this->hasString(name);

		if (!hasVal)
			strings.insert(std::pair<string, string>(name, val));
		else
		{
			std::map<string, string>::iterator it;
			it = strings.find(name);
			it->second = val;
		}
	}

	/* Constructor */
	Material()
	{
		// Default values
		this->setVector4f(COLOR_DIFFUSE, Vector4f(1.0f));
		this->setVector4f(COLOR_SPECULAR, Vector4f(1.0f));
		this->setVector4f(COLOR_AMBIENT, Vector4f(0.0f));
		this->setFloat(SHININESS, 0.5f);
		this->setFloat(ROUGHNESS, 0.2f);
		this->setFloat(SPECULAR_EXPONENT, 20.0f);
		this->setFloat(MATERIAL_ALPHADISCARD, 0.1f);
		this->setInt(TECHNIQUE_SPECULAR, 1);
		this->setInt(TECHNIQUE_PERPIXELLIGHTING, 1);
		this->setInt(MATERIAL_BLENDMODE, 0);
		this->setInt(MATERIAL_CASTSHADOWS, 1);
		this->setInt(MATERIAL_FACETOCULL, 0);
		this->setBool(MATERIAL_DEPTHMASK, true);
		this->setBool(MATERIAL_DEPTHTEST, true);
		this->setBool(MATERIAL_CULLENABLED, true);
	}

	Bucket getBucket()
	{
		return this->bucket;
	}

	void setBucket(Bucket bucket)
	{
		this->bucket = bucket;
	}
};

const string Material::MATERIAL_NAME = "matname";
const string Material::MATERIAL_ALPHADISCARD = "alpha_discard";
const string Material::MATERIAL_BLENDMODE = "blendmode"; // 0 = opaque, 1 = transparent
const string Material::MATERIAL_DEPTHTEST = "depthtest";
const string Material::MATERIAL_DEPTHMASK = "depthmask";
const string Material::MATERIAL_FACETOCULL = "cullface"; // 0 = back, 1 = front
const string Material::MATERIAL_CULLENABLED = "cullenable";

const string Material::MATERIAL_CASTSHADOWS = "cast_shadows";

const string Material::COLOR_DIFFUSE = "diffuse";
const string Material::COLOR_SPECULAR = "specular";
const string Material::COLOR_AMBIENT = "ambient";

const string Material::TEXTURE_DIFFUSE = "diffuse_map";
const string Material::TEXTURE_NORMAL = "normal_map";
const string Material::TEXTURE_SPECULAR = "specular_map";
const string Material::TEXTURE_HEIGHT = "height_map";
const string Material::TEXTURE_ENV = "env_map";

const string Material::SPECULAR_EXPONENT = "spec_exponent";
const string Material::SHININESS = "shininess";
const string Material::ROUGHNESS = "roughness";
const string Material::TECHNIQUE_SPECULAR = "spec_technique";
const string Material::TECHNIQUE_PERPIXELLIGHTING = "per_pixel_lighting";

#endif