#pragma once
#include "cglm.h"
#include "Model.h"
#include "FontData.h"
#include "LoadShader.h"
#define SCREEN_WIDTH (640.0*2.0)
#define SCREEN_HEIGHT (480.0*2.0)
typedef struct {
    

    char letter;

    unsigned int FontSDFTexture;
    vec3 Offset;
    vec4 Region;
    Model model;
    Character c;


    

} CharModel;

void SetupText(int *VAO, int *VBO);
void RenderText(unsigned int shader, char text[], float x, float y, float Scale, int TEXTVBO, int TEXTVAO, int SDFtex);