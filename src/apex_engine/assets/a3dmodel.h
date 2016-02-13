#ifndef A3DMODEL_H
#define A3DMODEL_H

#include <string>
using std::string;

namespace apex
{
	const string TOKEN_FACES = "faces";
	const string TOKEN_FACE = "face";
	const string TOKEN_VERTEX = "vertex";
	const string TOKEN_VERTICES = "vertices";
	const string TOKEN_POSITION = "position";
	const string TOKEN_MESH = "mesh";
	const string TOKEN_NODE = "node";
	const string TOKEN_NAME = "name";
	const string TOKEN_ID = "id";
	const string TOKEN_PARENT = "parent";
	const string TOKEN_GEOMETRY = "geom";
	const string TOKEN_TEXCOORD0 = "uv0";
	const string TOKEN_TEXCOORD1 = "uv1";
	const string TOKEN_TEXCOORD2 = "uv2";
	const string TOKEN_TEXCOORD3 = "uv3";
	const string TOKEN_NORMAL = "normal";
	const string TOKEN_BONEWEIGHT = "bone_weight";
	const string TOKEN_BONEINDEX = "bone_index";
	const string TOKEN_VERTEXINDEX = "vertex_index";
	const string TOKEN_MATERIAL = "material";
	const string TOKEN_MATERIAL_PROPERTY = "material_property";
	const string TOKEN_MATERIAL_BUCKET = "bucket";
	const string TOKEN_SHADER = "shader";
	const string TOKEN_SHADERPROPERTIES = "shader_properties";
	const string TOKEN_SHADERPROPERTY = "property";
	const string TOKEN_CLASS = "class";
	const string TOKEN_TYPE = "type";
	const string TOKEN_TYPE_UNKNOWN = "unknown";
	const string TOKEN_TYPE_STRING = "string";
	const string TOKEN_TYPE_BOOLEAN = "boolean";
	const string TOKEN_TYPE_FLOAT = "float";
	const string TOKEN_TYPE_VECTOR2 = "vec2";
	const string TOKEN_TYPE_VECTOR3 = "vec3";
	const string TOKEN_TYPE_VECTOR4 = "vec4";
	const string TOKEN_TYPE_INT = "int";
	const string TOKEN_TYPE_COLOR = "color";
	const string TOKEN_TYPE_TEXTURE = "texture";
	const string TOKEN_VALUE = "value";
	const string TOKEN_HAS_POSITIONS = "has_positions";
	const string TOKEN_HAS_NORMALS = "has_normals";
	const string TOKEN_HAS_TEXCOORDS0 = "has_texcoords0";
	const string TOKEN_HAS_TEXCOORDS1 = "has_texcoords1";
	const string TOKEN_HAS_BONES = "has_bones";
	const string TOKEN_SKELETON = "skeleton";
	const string TOKEN_BONE = "bone";
	const string TOKEN_SKELETON_ASSIGN = "skeleton_assign";
	const string TOKEN_ANIMATIONS = "animations";
	const string TOKEN_ANIMATION = "animation";
	const string TOKEN_ANIMATION_TRACK = "track";
	const string TOKEN_KEYFRAME = "keyframe";
	const string TOKEN_KEYFRAME_TRANSLATION = "keyframe_translation";
	const string TOKEN_KEYFRAME_ROTATION = "keyframe_rotation";
	const string TOKEN_TIME = "time";
	const string TOKEN_BONE_ASSIGNS = "bone_assigns";
	const string TOKEN_BONE_ASSIGN = "bone_assign";
	const string TOKEN_BONE_BINDPOSITION = "bind_position";
	const string TOKEN_BONE_BINDROTATION = "bind_rotation";
	const string TOKEN_MODEL = "model";
	const string TOKEN_TRANSLATION = "translation";
	const string TOKEN_SCALE = "scale";
	const string TOKEN_ROTATION = "rotation";
	const string TOKEN_CONTROL = "control";
}
#endif