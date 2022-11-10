#version 120
uniform float   uKa, uKd, uKs;		// coefficients of each type of lighting
uniform vec3  uColor;			// object color
uniform vec3  uSpecularColor;		// light color
uniform float   uShininess;		// specular exponent

varying  vec2  vST;			// texture coords
varying  vec3  vN;			// normal vector
varying  vec3  vL;			// vector from point to light
varying  vec3  vE;			// vector from point to eye

uniform float	uTime;		// "Time", from Animate( )

uniform bool bothVF;
uniform bool FOpen;
uniform bool VOpen;
void
main( )
{
    	vec3 Normal = normalize(vN);
	vec3 Light     = normalize(vL);
	vec3 Eye        = normalize(vE);

    vec3 myColor = vec3( 1., 0.5, 0. );
	vec3 mySpecularColor = vec3( 1., 1., 1. );

    if(bothVF)
    {
        if(vST.s<0.5+0.5*sin(uTime)&&vST.t<0.5+0.5*sin(uTime))
        {
            myColor = vec3(0.7*sin(uTime),0.3*sin(uTime),0.1);
        }
    }
    else
    {
        myColor = vec3(0.7,0.3,0.1);
    }


    if(FOpen)
    {
        if(vST.s<0.5+0.5*sin(uTime)&&vST.t<0.5+0.5*sin(uTime))
        {
            myColor = vec3(0.7*sin(uTime),0.3*sin(uTime),0.1);
        }
    }
    else
    {
        myColor = vec3(0.7,0.3,0.1);
    }


    vec3 ambient = uKa * myColor;
    float d = 0.;
    float s = 0.;
	if( dot(Normal,Light) > 0. )	          // only do specular if the light can see the point
	{
        d = dot(Normal,Light);
		vec3 ref = normalize(  reflect( -Light, Normal )  );
		s = pow( max( dot(Eye,ref),0. ), uShininess );
	}
    vec3 diffuse = uKd * d * myColor;
    vec3 specular = uKs * s * uSpecularColor;

	gl_FragColor = vec4( ambient + diffuse + specular,  1. );
}
