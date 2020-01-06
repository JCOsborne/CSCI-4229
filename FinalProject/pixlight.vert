#version 120

//  Per Pixel Lighting shader

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;

// Spotlight Parameters
varying vec3 lightDir;
varying vec3 spotDir;
varying float Cutoff;
varying float dist;

void main()
{
   //  Vertex location in modelview coordinates
   vec4 P = gl_ModelViewMatrix * gl_Vertex;
   //  Light position
   Light  = gl_LightSource[0].position.xyz - P.xyz;
   // Spotlight Params
   lightDir = Light.xyz - P.xyz;
   spotDir = gl_LightSource[0].spotDirection;
   Cutoff = gl_LightSource[0].spotCosCutoff;
   dist = length(lightDir);
   //  Normal
   Normal = -spotDir;
   //  Eye position
   View  = -P.xyz;
   //  Texture
   gl_TexCoord[0] = gl_MultiTexCoord0;
   //  Set vertex position
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
