#include "Model.h"
#include "OBJLoader.h"

void CreateModelTransofrmData(ModelTransformData *data, vec3 Position, vec3 Scale)
{
    data->Position[0] = Position[0];
    data->Position[1] = Position[1];
    data->Position[2] = Position[2];

    data->Scale[0] = Scale[0];
    data->Scale[1] = Scale[1];
    data->Scale[2] = Scale[2];


}

void CreateShaderData(ShaderData *data, int ShaderProgramID)
{
    data->ProgramID = ShaderProgramID;
}

void LoadModelFromFile(char *FilePath, Model *m, unsigned int ModelProgram, vec3 position, vec3 scale)
{
	Vertex Verts[1024];
	int Size = 0;
	LoadOBJFromFile(FilePath, &Size,  Verts );
	CreateModelNoIndeciesFromFileData(Verts, Size, ModelProgram, position, scale, m);

}

void CreateModelData(int VAO, vec3 Position, vec3 Scale, int ShaderProgramID, Model *m)
{
    CreateModelTransofrmData(&m->transformData, Position, Scale);
    CreateShaderData(&m->ShaderData, ShaderProgramID);
    m->VAO = VAO;
    
}

unsigned int LoadTexture(char *FilePath, int filter)
{
printf("Loadng texture\n");
	
	unsigned int texture;
	int width, height, nrChanels;
	unsigned char *data = stbi_load(FilePath, &width, &height, &nrChanels, 0);
	printf("Texture Loaded number of chanels: %d\n", nrChanels);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	printf("Textture generated\n");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	printf("opengl texture generated\n");

	stbi_image_free(data);
	return texture;
}

void CreateModelNoIndeciesFromFileData(Vertex *vert, int VCount, int ShaderProgramID, vec3 Position, vec3 Scale, Model *m){
    unsigned int VBO;
	unsigned int VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	
	//Bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//write data to the vertex buffer object

    //Issues with size of pointer versus size of array in total
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*VCount, &vert[0], GL_STATIC_DRAW);
	m->Size = VCount;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoords));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glBindVertexArray(0);

    CreateModelData(VAO, Position,  Scale, ShaderProgramID, m);



}
void CreateModel(float *verticies, int *indices, int ShaderProgramID, vec3 Position, vec3 Scale, Model *m)
{
    unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(int), indices, GL_STATIC_DRAW);
	//Bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//write data to the vertex buffer object

    //Issues with size of pointer versus size of array in total
	glBufferData(GL_ARRAY_BUFFER, 20*sizeof(float), verticies, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

    CreateModelData(VAO, Position,  Scale, ShaderProgramID, m);
}
