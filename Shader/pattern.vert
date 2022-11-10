#version 120


uniform float	uTime;		// "Time", from Animate( )
varying vec2  	vST;		// texture coords

varying  vec3  vN;		// normal vector
varying  vec3  vL;		// vector from point to light
varying  vec3  vE;		// vector from point to eye

const float PI = 	3.14159265;
const float AMP = 	0.2;		// amplitude
const float W = 	2.;		// frequency
vec3 LightPosition = vec3(  0., 5., 5. );
uniform bool bothVF;
uniform bool FOpen;
uniform bool VOpen;
void
main( )
{
    vST = gl_MultiTexCoord0.st;
	vec3 vert = gl_Vertex.xyz;
    if(bothVF)
    {
        vert.x *= (sin(uTime));
        vert.y *= (sin(uTime));
        vert.z *= (sin(uTime));
    }
    else
    {
        vert.x *= 1;
        vert.y *= 1;
        vert.z *= 1;
    }

    if(VOpen)
    {
        vert.x *= (sin(uTime));
        vert.y *= (sin(uTime));
        vert.z *= (sin(uTime));
    }
    else
    {
        vert.x =vert.x* 1;
        vert.y =vert.y* 1;
        vert.z =vert.z* 1;
    }
	vec4 ECposition = gl_ModelViewMatrix * vec4( vert, 1. );
	vN = normalize( gl_NormalMatrix * gl_Normal );	// normal vector
	vL = LightPosition - ECposition.xyz;		// vector from the point // to the light position
	vE = vec3( 0., 0., 0. ) - ECposition.xyz;	// vector from the point // to the eye position
	gl_Position = gl_ModelViewProjectionMatrix * vec4( vert, 1. );
}
