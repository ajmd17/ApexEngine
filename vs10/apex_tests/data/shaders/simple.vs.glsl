#version 150

attribute vec3 a_position;
attribute vec2 a_texcoord0;
attribute vec3 a_normal;

uniform mat4 Apex_ModelMatrix;
uniform mat4 Apex_ViewMatrix;
uniform mat4 Apex_ProjectionMatrix;
uniform mat4 Apex_NormalMatrix;

varying vec3 v_normal;
varying vec3 ws_pos;
varying vec2 v_texCoord0;

void main()
{
	ws_pos = (Apex_ModelMatrix * vec4(a_position, 1.0)).xyz;
	v_normal = (Apex_NormalMatrix * vec4(a_normal, 0.0)).xyz;
	v_texCoord0 = vec2(a_texcoord0.x, -a_texcoord0.y);
	gl_Position = Apex_ProjectionMatrix * Apex_ViewMatrix * vec4(ws_pos, 1.0);
}