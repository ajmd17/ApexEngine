#ifndef SHADERENUMS_H
#define SHADERENUMS_H

// Common enums that are used in the rendering engine.
// Author: Andrew MacDonald

enum TextureWrapMode
{
	ClampToEdge,
	ClampToBorder,
	Repeat
};

enum TextureFilterMode
{
	Nearest,
	Linear,
	Mipmap
};

enum PrimitiveType
{
	Triangles,
	TriangleStrip,
	TriangleFan,
	Quads,
	QuadStrip,
	Lines,
	Points,
	Patches
};

enum ShaderType { VertexShader, FragmentShader, GeometryShader, TessControlShader, TessEvalShader };

enum Face { Back, Front };

enum FaceDirection { Cw, Ccw };

enum BlendMode { Opaque, AlphaBlended };

enum AudioPlayState { Stopped, Paused, Playing };

#endif
