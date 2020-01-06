#version 120

//  Per Pixel Lighting shader

varying vec3 View;
varying vec3 Light;
varying vec3 Normal;
uniform sampler2D tex;

// Spotlight Parameters
varying vec3 lightDir;
varying vec3 spotDir;
varying float Cutoff;
varying float dist;

void main()
{	

	vec3 ld = normalize(lightDir);
	vec3 ld2 = normalize(-lightDir);
	vec3 sd = normalize(-spotDir);

	float intensity = 0.0;
	float Is = 0.0;

	// Calculate Attenuation
	float attenuation = 1.0 / (gl_LightSource[1].constantAttenuation + gl_LightSource[1].linearAttenuation * dist + gl_LightSource[1].quadraticAttenuation * dist * dist);

	vec3 n = normalize(Normal);
	intensity = max(dot(n, ld), 0.0);
	intensity = max(dot(n, ld2), intensity);

	float dotProd = max(dot(sd, ld) - Cutoff, dot(sd, ld2) - Cutoff);

	if(intensity > 0.0)
	{
		vec3 v = normalize(View);
		vec3 h = normalize(ld + v);

		float s = max(dot(h, n), 0.0);
		Is = pow(s, gl_FrontMaterial.shininess);
	}

	if(dotProd > 0)
	{
		intensity *= (dotProd * 100) + 5;
	}


	//  Sum color types
	vec4 color = gl_FrontMaterial.emission
				+ gl_FrontLightProduct[1].ambient
				+ intensity*gl_FrontLightProduct[1].diffuse / 4
				+ Is*gl_FrontLightProduct[1].specular;

	//  Apply texture
	gl_FragColor = color * texture2D(tex,gl_TexCoord[0].xy) * attenuation + vec4 (intensity*0.03, 0, 0, 0); 
}
