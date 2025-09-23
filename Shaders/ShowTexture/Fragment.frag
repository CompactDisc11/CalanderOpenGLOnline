#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;
in vec2 TexCoord;

uniform vec4 TextPositions[95];
uniform int Text[512];
uniform sampler2D TextShader;
uniform float time;

void main()
    { 
     
      

      FragColor.a = 1.0;
      FragColor.g = 0.0;
      FragColor.rgb = vec3(0.0);
      float modifier = 12.0;

      vec2 uv = fract(TexCoord*modifier);
      vec2 IndexPosition = floor(vec2(1.0-TexCoord.x, TexCoord.y)*modifier)/modifier;
      int Index = int(((IndexPosition.x)*modifier)+(IndexPosition.y*modifier)*modifier);
      vec4 Slice = TextPositions[Text[Index]-32];
      vec2 st =  vec2(1.0-uv.x, uv.y)/modifier*2.0;





      st /= vec2(1024.0/(4*64), 128.0/(64*7));
      st *= vec2(1024, 128);
      st += Slice.xy;

  
    if (st.x <= Slice.z+Slice.x && st.y <= Slice.w+Slice.y && st.x >= Slice.x && st.y >= Slice.y){
        st/= vec2(1024, 128);
        
        FragColor.rgb += smoothstep(0.4, 0.5, texture(TextShader, st).r);
          }
      FragColor.a = 1.0;
    }