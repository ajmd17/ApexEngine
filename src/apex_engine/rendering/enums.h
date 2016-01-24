#ifndef SHADERENUMS_H
#define SHADERENUMS_H

// Common enums that are used in the rendering engine.
// Author: Andrew MacDonald

enum TextureWrapMode
{
	Repeat,
	ClampToBorder,
	ClampToEdge
};

enum TextureFilterMode
{
	Linear,
	Nearest,
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

enum BlendMode { AlphaBlend, Opaque };

enum AudioPlayState { Playing, Paused, Stopped };

#endif