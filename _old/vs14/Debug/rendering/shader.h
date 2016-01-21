#ifndef SHADER_H
#define SHADER_H

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

#include <iostream>;
using std::ostream;

#include "material.h"
#include "shader_enums.h"

#include "..\math\vector2f.h"
#include "..\math\vector3f.h"
#include "..\math\matrix4f.h"

class Environment;
class Mesh;
class Camera;

class ShaderProperties
{
public:
	map<string, bool> values;

	ShaderProperties setProperty(string &name, bool &val);

	ShaderProperties()
	{
	}

	ShaderProperties (ShaderProperties &other)
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
		if (it != values.end())
			return true;
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

ShaderProperties ShaderProperties::setProperty(string &name, bool &val)
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
			std::map<string,bool>::iterator it;
			it = values.find(name);
			values.erase(it);
		}
		else
		{
			std::map<string,bool>::iterator it;
			it = values.find(name);
			it->second = val;
		}
	}

	return *this;
}

class Shader
{
protected:
	Material currentMaterial;
	int id;
private:
	ShaderProperties properties;
	Matrix4f worldMatrix, viewMatrix, projectionMatrix;
public:
	const static string		A_POSITION,
							A_TEXCOORD0,
							A_TEXCOORD1,
							A_NORMAL,
							A_TANGENT,
							A_BITANGENT,
							A_BONEWEIGHTS,
							A_BONEINDICES,

							APEX_WORLDMATRIX,
							APEX_VIEWMATRIX,
							APEX_PROJECTIONMATRIX,
							APEX_CAMERAPOSITION,
							APEX_ELAPSEDTIME,
							
							MATERIAL_ALPHADISCARD,
							MATERIAL_SHININESS,
							MATERIAL_ROUGHNESS,
							MATERIAL_AMBIENTCOLOR,
							MATERIAL_DIFFUSECOLOR,
							MATERIAL_SPECULARCOLOR,
							MATERIAL_SPECULARTECHNIQUE,
							MATERIAL_SPECULAREXPONENT,
							MATERIAL_PERPIXELLIGHTING,
							
							ENV_FOGCOLOR,
							ENV_FOGSTART,
							ENV_FOGEND,
							ENV_FOGDENSITY,
							ENV_NUMPOINTLIGHTS,
							ENV_NUMSPOTLIGHTS;
	void create();

	void use();

	void compileShader();

	void addProgram(ShaderType type, string &code);

	virtual void end();

	virtual void applyMaterial(Material &material);

	void setDefaultValues();

	virtual void update(Environment &environment, Camera &cam, Mesh &mesh);

	void setUniform(string name, int i);

	void setUniform(string name, float f);

	void setUniform(string name, float x, float y);

	void setUniform(string name, float x, float y, float z);

	void setUniform(string name, float x, float y, float z, float w);
	
	void setUniform(string name, Matrix4f mat);

	void setUniform(string name, Vector2f vec)
	{
		this->setUniform(name, vec.x, vec.y);
	}
	
	void setUniform(string name, Vector3f vec)
	{
		this->setUniform(name, vec.x, vec.y, vec.z);
	}

	void addVertexProgram(string &code)
	{
		addProgram(ShaderType::VertexShader, code);
	}

	void addFragmentProgram(string &code)
	{
		addProgram(ShaderType::FragmentShader, code);
	}

	Shader(ShaderProperties &properties, string &vs_code, string &fs_code)
	{
		this->properties = properties;
		this->create();
		this->addVertexProgram(ShaderUtil::formatShaderVersion(ShaderUtil::formatShaderProperties(vs_code, properties)));
		this->addFragmentProgram(ShaderUtil::formatShaderVersion(ShaderUtil::formatShaderProperties(fs_code, properties)));
	}

	ShaderProperties getProperties()
	{
		return this->properties;
	}

};

/* Default vertex attributes */
const string Shader::A_POSITION = "a_position";
const string Shader::A_TEXCOORD0 = "a_texcoord0";
const string Shader::A_TEXCOORD1 = "a_texcoord1";
const string Shader::A_NORMAL = "a_normal";
const string Shader::A_TANGENT = "a_tangent";
const string Shader::A_BITANGENT = "a_bitangent";
const string Shader::A_BONEWEIGHTS = "a_boneweights";
const string Shader::A_BONEINDICES = "a_boneindices";

/* Default shader uniforms */
const string Shader::APEX_WORLDMATRIX = "Apex_WorldMatrix";
const string Shader::APEX_VIEWMATRIX = "Apex_ViewMatrix";
const string Shader::APEX_PROJECTIONMATRIX = "Apex_ProjectionMatrix";
const string Shader::APEX_CAMERAPOSITION = "Apex_CameraPosition";
const string Shader::APEX_ELAPSEDTIME = "Apex_ElapsedTime";

/* Material shader uniforms */
const string Shader::MATERIAL_ALPHADISCARD = "Material_AlphaDiscard";
const string Shader::MATERIAL_SHININESS = "Material_Shininess";
const string Shader::MATERIAL_ROUGHNESS = "Material_Roughness";
const string Shader::MATERIAL_AMBIENTCOLOR = "Material_AmbientColor";
const string Shader::MATERIAL_DIFFUSECOLOR = "Material_DiffuseColor";
const string Shader::MATERIAL_SPECULARCOLOR = "Material_SpecularColor";
const string Shader::MATERIAL_SPECULARTECHNIQUE = "Material_SpecularTechnique";
const string Shader::MATERIAL_SPECULAREXPONENT = "Material_SpecularExponent";
const string Shader::MATERIAL_PERPIXELLIGHTING = "Material_PerPixelLighting";

/* Environment shader uniforms */
const string Shader::ENV_FOGCOLOR = "Env_FogColor";
const string Shader::ENV_FOGSTART = "Env_FogStart";
const string Shader::ENV_FOGEND = "Env_FogEnd";
const string Shader::ENV_FOGDENSITY = "Env_FogDensity";
const string Shader::ENV_NUMPOINTLIGHTS = "Env_NumPointLights";
const string Shader::ENV_NUMSPOTLIGHTS = "Env_NumSpotLights";


#endif