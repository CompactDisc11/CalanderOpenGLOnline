#pragma once
#include "cglm.h"
typedef struct
{
    vec3 Position;
    vec3 Normal;
    vec2 TextureCoords;
} Vertex;



char **SplitString(char* In, char Splitter,  char Terminator);

void LoadOBJFromFile(char *FilePath, int *Size, Vertex *verts);



