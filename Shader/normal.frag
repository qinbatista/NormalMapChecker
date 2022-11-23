#version 120
uniform float uKa;
uniform float uKd;
uniform float uKs;
uniform float uShininess;
uniform float uFreq;
uniform sampler2D Color_Map;
uniform sampler2D Normal_Map;
in vec3 EC_SurfacePosition;
in vec3 EC_EyePosition;
in vec3 EC_SurfaceNormal;
in vec3 EC_LightPosition;
in vec2 vST;

void main( )
{
    vec3 P = EC_SurfacePosition;
    vec3 E = normalize( EC_EyePosition - EC_SurfacePosition );
    vec3 N = normalize( gl_NormalMatrix * (2.*texture( Normal_Map, uFreq*vST ).xyz - vec3(1.,1.,1.) ) ); vec3 L = EC_LightPosition - P;
    vec3 Ambient_Color = uKa * texture( Color_Map, uFreq * vST ).gba; float Light_Intensity = 1.;
    L = normalize( EC_LightPosition - P );
    float Diffuse_Intensity = dot( N, L ) * Light_Intensity;
    vec3 Diffuse_Color = uKd * Diffuse_Intensity * texture( Color_Map, uFreq * vST ).rgb;
    float Specular_Intensity = pow( max( dot( reflect( -L, N ), E ), 0. ), uShininess ) * Light_Intensity; vec3 Specular_Color = uKs * Specular_Intensity * vec3( 1., 1., 1. );
    gl_FragColor = vec4(Ambient_Color + Diffuse_Color + Specular_Color, 1. );
}
