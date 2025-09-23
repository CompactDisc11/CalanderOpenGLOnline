#pragma once
#include "cglm.h"
#include "LoadShader.h"
#include "OBJLoader.h"


typedef struct {
    vec3 Position;
    vec3 Scale;
    vec3 Rotation;
} ModelTransformData;

typedef struct {
    int ProgramID;
    int NumberOfTextures;
    int *TextureIDs;
    
} ShaderData;
typedef struct{

    int VAO;
    ModelTransformData transformData;
    ShaderData ShaderData;  
    int Size;

    int Texture1;
    int Texture2;
} Model;


void CreateModelTransofrmData(ModelTransformData *data, vec3 Position, vec3 Scale);
void CreateModelNoIndeciesFromFileData(Vertex *vert, int VCount, int ShaderProgramID, vec3 Position, vec3 Scale, Model *m);
void CreateShaderData(ShaderData *data, int ShaderProgramID);

unsigned int LoadTexture(char *FilePath, int filter);


void LoadModelFromFile(char *FilePath, Model *m, unsigned int ModelProgram, vec3 position, vec3 scale);
void CreateModelData(int VAO, vec3 Position, vec3 Scale, int ShaderProgramID, Model *m);
void CreateModel(float *verticies, int *indiices, int ShaderProgramID, vec3 Position, vec3 Scale, Model*m);