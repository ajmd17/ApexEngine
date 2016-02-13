#version 150

#ifdef DEFAULT

#include <apex3d>

uniform sampler2D u_texture;
varying vec2 v_texCoord0;

varying vec3 v_normal;
varying vec3 ws_pos;

void main()
{
	vec3 n = normalize(v_normal);
	vec3 l = normalize(vec3(0.3, 1.0, 0.3));
	
	float ndotl = max(dot(n, l), 0.0);
	
	vec3 amb = vec3(0.05,0.05,0.05);
	vec3 color = vec3(ndotl, ndotl, ndotl);
	
	vec3 v = normalize(Apex_CameraPosition-ws_pos);
	vec3 hv = normalize(l+v);
	float ndotv = pow(max(dot(n, hv), 0.0), 100.0);
	
	color += amb;
	
	#ifdef diffuse_map
	vec4 diffuse = texture2D(u_texture, v_texCoord0);
	color *= diffuse.rgb;
	#endif
	
	gl_FragColor = vec4(color*vec3(0.6,0.3,0.1)+vec3(ndotv), 1.0);
	gl_FragColor.rgb = pow(gl_FragColor.rgb, vec3(1.0 / 2.2));
}

#endif