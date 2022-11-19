#version 120

out vec3 EC_SurfacePosition; out vec3 EC_EyePosition;
out vec3 EC_SurfaceNormal; out vec3 EC_LightPosition; out vec2 vST;
void main()
{
    EC_SurfacePosition = (gl_ModelViewMatrix * gl_Vertex).xyz; EC_EyePosition = vec3( 0., 0., 0. );
    EC_SurfaceNormal = normalize( gl_NormalMatrix * gl_Normal ); EC_LightPosition = vec3( 0., 10., 0. );
    vST = gl_MultiTexCoord0.st;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
