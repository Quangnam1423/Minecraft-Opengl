# A 3D engine is built using OpenGL and supporting libraries to recreate Minecraft.
![Alternative](/Resources/Pictures/pic1.png)
![world view](/Resource/Pictures/pic2.png)
![world view](/Resource/Pictures/pic3.png)
![world view](/Resource/Pictures/pic4.png)

## Dependencies
- Libraries
    - glm library provide maths functions , matrices for the game to handle all things like coordinate , position...
    - glad library manages all the necessary functions for Opengl in the run-time
    - GLFW library create and control window , sound , and event ...
    - stb_image.h load assets files like png or jpg...vv
    - Fast_Noise_Life.h make noise for chunks
    - assimp library for load 3D model
- binaries file
    - kernel32.dll
    - opengl32.dll
    - openal32.dll
> **Note**: all libaries above, you can find them in github or in the website.

# Some basic Knowledge
There are some basic knowledge if you want to start learning Opengl that you should have before that.
- Maths and special **Linear Algebra**
- Projection: there are 2 most common projection that you should learn
    - **Orthographic Projection**
    - **Perspective Projection** High-recommend help you make the real-life view.
- GLSL: is a programming language for GPU, it's like C and quite easy to learn
- Learn how the program is processed by the GPU.

> This is my GLSL program:
>> vertex shader:

        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec2 textCoords;
        layout (location = 2) in int id;
        
        out vec2 TexCoord;
        out vec3 cube_color;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        
        vec3 hash31(float p) {
            vec3 p3 = fract(vec3(p * 21.2f) * vec3(0.1031f, 0.1030f, 0.0973f));
            p3 += dot(p3, p3.yzx + 33.33f);
            return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05f;
        }
        
        void main()
        {
            gl_Position = projection * view * model * vec4(position, 1.0f);
            TexCoord = textCoords;
            cube_color = hash31(id);
        }
>> fragment shader:

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
      
