#version 330 core
out vec4 FragColor;


in vec2 TexCoord;
uniform float time;
uniform sampler2D tex;



uniform vec4 SliceArray[95];
uniform float OffsetY;


void main()
    {



      float XIndex = floor((TexCoord.x*2100)/(300));
      float YIndex = floor((TexCoord.y*2100)/(300));

      vec4 Slice = SliceArray[int(XIndex+(YIndex*7))];
      vec2 UV;
      //Like this because we are using the same model as background which has the verts setup like this i think
      vec2 st = TexCoord;
      st = fract(st*7.0);
      st -= vec2(75/300.0);
      st /= vec2(1024.0/300.0, 128.0/300.0);
      st*= vec2(1024, 128);
      
      st += Slice.xy;
      FragColor.rgb = vec3(0.0);
       if (st.x <= Slice.z+Slice.x+1 && st.y <= Slice.w+Slice.y+2
       
          && st.x >= Slice.x +1 && st.y >= Slice.y+1){
        st/= vec2(1024, 128);
        FragColor.rgb = texture(tex, st).rgb;

      // FragColor.rg = st;

       }
      
      FragColor.a = 1.0;
    }