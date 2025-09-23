#version 330 core
out vec4 FragColor;


in vec2 TexCoord;

uniform sampler2D tex;
uniform vec4 TextData;

void main()
    {

      //Fix UV
      
      

      vec2 uv = TexCoord;
      FragColor.rgb = vec3(TexCoord, 0.0);
      uv /= vec2(1024.0/TextData.z, 128.0/TextData.w);
      uv*= vec2(1024, 128);
      uv += TextData.xy;
   
      //  if (uv.x <= Slice.z+Slice.x+1 && uv.y <= Slice.w+Slice.y+2
       
          //&& uv.x >= Slice.x +1 && uv.y >= Slice.y+1){
        uv/= vec2(1024, 128);
        vec3 TexColor = texture(tex, uv).rgb;
        FragColor.rgb = vec3(smoothstep(0.4, 0.5, TexColor.r));
       if (FragColor.r == 0.0){
        discard;
       }

       //}

      // FragColor.rg = st;

       
      FragColor.a = 1.0;
    }