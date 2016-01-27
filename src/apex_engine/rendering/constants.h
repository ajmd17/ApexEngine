#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants that are commonly used as part of the rendering engine.
// Author: Andrew MacDonald

#include <string>
using std::string;

// Default vertex attributes
const string A_POSITION = "a_position";
const string A_TEXCOORD0 = "a_texcoord0";
const string A_TEXCOORD1 = "a_texcoord1";
const string A_NORMAL = "a_normal";
const string A_TANGENT = "a_tangent";
const string A_BITANGENT = "a_bitangent";
const string A_BONEWEIGHTS = "a_boneweights";
const string A_BONEINDICES = "a_boneindices";

// Default shader uniforms 
const string APEX_MODELMATRIX = "Apex_ModelMatrix";
const string APEX_VIEWMATRIX = "Apex_ViewMatrix";
const string APEX_PROJECTIONMATRIX = "Apex_ProjectionMatrix";
const string APEX_CAMERAPOSITION = "Apex_CameraPosition";
const string APEX_ELAPSEDTIME = "Apex_ElapsedTime";

// Material shader uniforms 
const string MATERIAL_ALPHADISCARD = "Material_AlphaDiscard";
const string MATERIAL_SHININESS = "Material_Shininess";
const string MATERIAL_ROUGHNESS = "Material_Roughness";
const string MATERIAL_AMBIENTCOLOR = "Material_AmbientColor";
const string MATERIAL_DIFFUSECOLOR = "Material_DiffuseColor";
const string MATERIAL_SPECULARCOLOR = "Material_SpecularColor";
const string MATERIAL_SPECULARTECHNIQUE = "Material_SpecularTechnique";
const string MATERIAL_SPECULAREXPONENT = "Material_SpecularExponent";
const string MATERIAL_PERPIXELLIGHTING = "Material_PerPixelLighting";

// Environment shader uniforms 
const string ENV_FOGCOLOR = "Env_FogColor";
const string ENV_FOGSTART = "Env_FogStart";
const string ENV_FOGEND = "Env_FogEnd";
const string ENV_FOGDENSITY = "Env_FogDensity";
const string ENV_NUMPOINTLIGHTS = "Env_NumPointLights";
const string ENV_NUMSPOTLIGHTS = "Env_NumSpotLights";

#endif