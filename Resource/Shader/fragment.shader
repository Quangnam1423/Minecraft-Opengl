#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 cube_color;

uniform sampler2D texture;

/*
void main()
{
    gl_FragColor = vec4(cube_color , 1.0f);
}
*/

float near = 0.1;   
float far  = 50.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
    float depth = 1.0 - LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    vec4 depthVec4 = vec4(vec3(pow(depth, 0.8)), 1.0);
    
    // Fetch texture color
    vec4 texColor = texture(texture, TexCoord);
    
    // Combine color with depth
    vec4 color = vec4(cube_color, 1.0) * depthVec4;
    
    // Output final color
    FragColor = texColor * depthVec4;
}
