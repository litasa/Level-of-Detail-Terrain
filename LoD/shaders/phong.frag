#version 330 core
// data from vertex shader
in vec3 o_normal;
in vec3 o_toLight;
in vec3 o_toCamera;
in vec2 o_texCoords;

// texture with diffuese color of the object
uniform sampler2D u_diffuseTexture;

// color for framebuffer
layout(location = 0) out vec4	resultingColor;

/////////////////////////////////////////////////////////

// parameters of the light and possible values
uniform vec3 u_lightAmbientIntensitys; // = vec3(0.6, 0.3, 0);
uniform vec3 u_lightDiffuseIntensitys; // = vec3(1, 0.5, 0);
uniform vec3 u_lightSpecularIntensitys; // = vec3(0, 1, 0);

// parameters of the material and possible values
uniform vec3 u_matAmbientReflectances; // = vec3(1, 1, 1);
uniform vec3 u_matDiffuseReflectances; // = vec3(1, 1, 1);
uniform vec3 u_matSpecularReflectances; // = vec3(1, 1, 1);
uniform float u_matShininess; // = 64;

/////////////////////////////////////////////////////////

// returns intensity of reflected ambient lighting
vec3 ambientLighting()
{
   return u_matAmbientReflectances * u_lightAmbientIntensitys;
}

// returns intensity of diffuse reflection
vec3 diffuseLighting(in vec3 N, in vec3 L)
{
   // calculation as for Lambertian reflection
   float diffuseTerm = clamp(dot(N, L), 0, 1) ;
   return u_matDiffuseReflectances * u_lightDiffuseIntensitys * diffuseTerm;
}

// returns intensity of specular reflection
vec3 specularLighting(in vec3 N, in vec3 L, in vec3 V)
{
   float specularTerm = 0;

   // calculate specular reflection only if
   // the surface is oriented to the light source
   if(dot(N, L) > 0)
   {
      // half vector
      vec3 H = normalize(L + V);
      specularTerm = pow(dot(N, H), u_matShininess);
   }
   return u_matSpecularReflectances * u_lightSpecularIntensitys * specularTerm;
}

void main(void)
{
   // normalize vectors after interpolation
   vec3 L = normalize(o_toLight);
   vec3 V = normalize(o_toCamera);
   vec3 N = normalize(o_normal);

   // get Blinn-Phong reflectance components
   vec3 Iamb = ambientLighting();
   vec3 Idif = diffuseLighting(N, L);
   //vec3 Ispe = specularLighting(N, L, V);

   // diffuse color of the object from texture
   vec3 diffuseColor = texture(u_diffuseTexture, o_texCoords).rgb;

   // combination of all components and diffuse color of the object
   if(gl_FrontFacing)
   {
		resultingColor.xyz = diffuseColor * (Iamb + Idif); // + Ispe);
   }
   else
   {
		resultingColor.xyz = diffuseColor * vec3(1,1,1);
   }
   resultingColor.a = 1;
   
}