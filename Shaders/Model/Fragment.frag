#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D tex;
uniform sampler2D BaseTex;

uniform float time;
uniform int Index;



//0 to 9 indexes are 16 to 27



ivec2 RetrieveNumberOffset(int i){


      int Remainder;
      int Base10 = i;
      int NumberOffsetX = (Base10+16)%7;
      int NumberOffsetY = (Base10+16)/7;

      return ivec2(NumberOffsetX, NumberOffsetY);

}
void main()
    {

      //Fix UV

      vec3 TexCol = vec3(0.0);
      int Index10 = Index+1;
      int IndexOther = Index+1;
      vec2 UV = TexCoord;
      vec3 BaseCol = texture(BaseTex, vec2(UV.x, 1.0-UV.y)).rgb;
      while (Index10 > 9){

            Index10 = int(Index10 / 10);
            IndexOther = IndexOther%10;
            float OffsetX = TexCoord.x * 2100;
            float OffsetY = (1.0-TexCoord.y) * 2100; 
            OffsetX /= 1.5;
            OffsetY /= 1.5;
            vec2 o = RetrieveNumberOffset(Index10);
            OffsetX += (o.x*300)+32*1.5;
            OffsetX/= 2100;

            OffsetY += (o.y*300);
            OffsetY/= 2100;
            TexCol += texture(tex, vec2(OffsetX, OffsetY)).rgb;
      }
      float OffsetX = TexCoord.x * 2100;

      float OffsetY = (1.0-TexCoord.y) * 2100; 
      OffsetX /= 1.5;
      OffsetY /= 1.5;
       vec2 o = RetrieveNumberOffset(IndexOther);
       OffsetX += (o.x*300)+28;
       OffsetX/= 2100;

       OffsetY += (o.y*300);
       OffsetY/= 2100;
       TexCol += texture(tex, vec2(OffsetX, OffsetY)).rgb*vec3(1.0, 0.0, 0.0);



 
      
      vec3 Norm = normalize(Normal);
      vec3 lightDir = normalize(vec3(0.0    , 0.0, 1.0)-FragPos);
      float diff = max(dot(Normal, lightDir), 0.0);

      FragColor.rgb = BaseCol+vec3(smoothstep(0.4, 0.5, TexCol.r));
      FragColor.rgb *=diff*0.3;
      FragColor.a = 1.0;
    }