#include "LoadShader.h"

int LoadAndCompileShader(char *Filepath, int type)
{   
    FILE *FileIN = fopen(Filepath, "r");
    if (FileIN == NULL){
        printf("Error reading shader type: %d\n");
    }
   
    fseek(FileIN, 0, SEEK_END);
    int FileLength = ftell(FileIN);
    rewind(FileIN);
    
    const char *Data =NULL;
    
    Data = (const char*)malloc(sizeof(char)*(FileLength+1));
    fread(Data, 1, FileLength, FileIN);
    
    
    
    printf("%s\n", Data);
    printf("Size of Data: %d\n", FileLength);
    unsigned int shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &Data, &FileLength);
    glCompileShader(shader);
    //free(Data);


    return shader;
}

int CreateProgram(char *VertexShader, char *FragmentShader)
{
    int fragmentShader = LoadAndCompileShader(VertexShader, GL_VERTEX_SHADER);
    int vertexShader = LoadAndCompileShader(FragmentShader, GL_FRAGMENT_SHADER);
	

	//Create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//Bind shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
    
    return shaderProgram;
}
