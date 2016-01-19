#ifndef SHADERENUMS_H
#define SHADERENUMS_H

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