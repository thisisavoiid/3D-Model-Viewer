#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 uViewPos;
uniform vec3 uObjectColor;
uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform sampler2D uTexture;

void main(){
    float specularStrength=.5;
    float ambientStrength=.1;
        
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(uLightPos-FragPos);
    
    vec3 viewDir=normalize(uViewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    
    float spec=pow(max(dot(viewDir,reflectDir),0.),32);
    vec3 specular=specularStrength*spec*uLightColor;
    
    vec3 ambient=ambientStrength*uLightColor;

    float diff=max(dot(norm,lightDir),0.);
    vec3 diffuse=diff*uLightColor;
    
    vec4 result=vec4(ambient+diffuse+specular,1.);
    
    FragColor=texture(uTexture,TexCoord)*result;
}