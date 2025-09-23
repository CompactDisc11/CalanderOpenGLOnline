#version 330 core
out vec4 FragColor;


in vec2 TexCoord;
uniform float time;
void main()
    {

      float Percentage = ((1.0-TexCoord.x) + TexCoord.y)/2.0;
      float PercentageSin = abs(sin(Percentage*3.14));
      FragColor = vec4(abs(vec3(0.0, 0.8, 0.8)*(PercentageSin))*0.3, 1.0);
      gl_FragDepth = 20.0;
    }