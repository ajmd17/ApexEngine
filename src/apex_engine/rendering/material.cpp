#include "material.h"

namespace apex
{
	const string Material::STRING_NAME = "matname";

	const string Material::BOOL_DEPTHTEST = "depthtest";
	const string Material::BOOL_DEPTHMASK = "depthmask";
	const string Material::BOOL_CULLENABLED = "cullenable";
	const string Material::BOOL_CASTSHADOWS = "cast_shadows";

	const string Material::COLOR_DIFFUSE = "diffuse";
	const string Material::COLOR_SPECULAR = "specular";
	const string Material::COLOR_AMBIENT = "ambient";

	const string Material::TEXTURE_DIFFUSE = "diffuse_map";
	const string Material::TEXTURE_NORMAL = "normal_map";
	const string Material::TEXTURE_SPECULAR = "specular_map";
	const string Material::TEXTURE_HEIGHT = "height_map";
	const string Material::TEXTURE_ENV = "env_map";

	const string Material::FLOAT_SPECULAR_EXPONENT = "spec_exponent";
	const string Material::FLOAT_SHININESS = "shininess";
	const string Material::FLOAT_ROUGHNESS = "roughness";
	const string Material::FLOAT_ALPHADISCARD = "alpha_discard";

	const string Material::INT_FACETOCULL = "cullface"; // 0 = back, 1 = front
	const string Material::INT_BLENDMODE = "blendmode"; // 0 = opaque, 1 = transparent
	const string Material::INT_TECHNIQUE_SPECULAR = "spec_technique";
	const string Material::INT_TECHNIQUE_PERPIXELLIGHTING = "per_pixel_lighting";

	Material::Material()
	{
		// Default values
		this->setVector4f(COLOR_DIFFUSE, Vector4f(1.0f));
		this->setVector4f(COLOR_SPECULAR, Vector4f(1.0f));
		this->setVector4f(COLOR_AMBIENT, Vector4f(0.0f));

		this->setFloat(FLOAT_SHININESS, 0.5f);
		this->setFloat(FLOAT_ROUGHNESS, 0.2f);
		this->setFloat(FLOAT_SPECULAR_EXPONENT, 20.0f);
		this->setFloat(FLOAT_ALPHADISCARD, 0.1f);

		this->setInt(INT_TECHNIQUE_SPECULAR, 1);
		this->setInt(INT_TECHNIQUE_PERPIXELLIGHTING, 1);
		this->setInt(INT_BLENDMODE, 0);
		this->setInt(INT_FACETOCULL, 0);

		this->setBool(BOOL_CASTSHADOWS, true);
		this->setBool(BOOL_DEPTHMASK, true);
		this->setBool(BOOL_DEPTHTEST, true);
		this->setBool(BOOL_CULLENABLED, true);
	}
}