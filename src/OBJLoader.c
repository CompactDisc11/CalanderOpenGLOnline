#include "OBJLoader.h"
#include "string.h"
char  **SplitString(char *In, char Splitter, char Terminator)
{

    static char ReturnData[99][99];
    
  

    char SplitBuffer[99];
    int SplitCount = 0;
    int CurrentSplitIndex = 0;
    int i = 0;

    char c = In[i];

    
    while ( c != Terminator)
    {

        c = In[i];
    //    printf("%c", c);


        SplitBuffer[CurrentSplitIndex] = c;
        if (c == Splitter){
            SplitBuffer[CurrentSplitIndex] = '\0';
            memcpy(ReturnData[SplitCount], SplitBuffer, 99);
          
            
            SplitCount += 1;
            CurrentSplitIndex = 0;
            
        }
        else{
            CurrentSplitIndex += 1;

        }


        i += 1;
    }
    memcpy(ReturnData[SplitCount], SplitBuffer, 99*sizeof(char));

    
  //  free(SplitBuffer);

    return (char**)ReturnData;



}

void LoadOBJFromFile(char *FilePath, int *Size, Vertex *verts)
{
    FILE *FileIN = fopen(FilePath, "r");
    if (FileIN == NULL){
        printf("Error reading file: %d\n");
    }
    fseek(FileIN, 0, SEEK_END);
    int FileLength = ftell(FileIN);
    rewind(FileIN);
    
    printf("Loading OBJ\n");
    char Data[1024];
    
    vec3 Position[1024];
    int PositionIndex = 0;
    vec3 Normal[1024];
    int NormalIndex = 0;

    vec2 Texture[1024];
    int TextureIndex = 0;

    ivec3 Faces[1024*9];
    int FaceIndex = 0;


    Vertex vertex[1024];
    int VertexIndex = 0;
    printf("Starting Read of file\n");
    while (fgets(Data, 1024, FileIN) != NULL){
     

        char SplitStringData[99][99];
       // printf("%d, Finished Split\n", sizeof(Data));
        memcpy(SplitStringData, SplitString(Data, ' ', '\n'), 99*99);
        printf( "1: %s\n", SplitStringData[0]);
        printf( "2: %s\n", SplitStringData[1]);

        printf( "3: %s\n", SplitStringData[2]);
        printf( "4: %s\n", SplitStringData[3]);

        Vertex point;
        if (SplitStringData[0][0] == 'v'){


            vec3 Vector3Data;
            Vector3Data[0] = atof(SplitStringData[1]);
            Vector3Data[1] = atof(SplitStringData[2]);
            Vector3Data[2] = atof(SplitStringData[3]);


            if (SplitStringData[0][1]=='n'){
                printf("Normal \n");
                memcpy(Normal[NormalIndex], Vector3Data, sizeof(vec3));
                NormalIndex += 1;
            }
            else if(SplitStringData[0][1]=='t'){
                printf("Texture: \n");
                
                memcpy(Texture[TextureIndex], (vec2){Vector3Data[0], Vector3Data[1]}, sizeof(vec2));
                TextureIndex += 1;
            }
            else{
                printf("Vertex: \n");

                memcpy(Position[PositionIndex], Vector3Data, sizeof(vec3));
                PositionIndex += 1;
            }
          
            
            
        }      
        
        else if (Data[0]== 'f'){
            printf("Face: ");
            char V1[99][99];
            char V2[99][99];
            char V3[99][99];

    
            //No space its end of file
            memcpy(V1, SplitString(SplitStringData[1], '/', '\0'), 99*99);
            ivec3 F1Data;
            F1Data[0] = atoi(V1[0])-1;
            F1Data[1] = atoi(V1[1])-1;
            F1Data[2] = atoi(V1[2])-1;


            
      
            memcpy(vertex[VertexIndex].Position, Position[F1Data[0]], sizeof(vec3));
            memcpy(vertex[VertexIndex].TextureCoords, Texture[F1Data[1]], sizeof(vec2)); 
            memcpy(vertex[VertexIndex].Normal, Normal[F1Data[2]], sizeof(vec3));
            VertexIndex +=  1;

            //We have Normal and tex coords swapped
            //No i am wrong. its probalby something to do with the transformation

            memcpy(V2, SplitString(SplitStringData[2], '/', '\0'), 99*99);
            F1Data[0] = atoi(V2[0])-1 ;
            F1Data[1] = atoi(V2[1]) -1;
            F1Data[2] = atoi(V2[2])-1;
            

            
      
            memcpy(vertex[VertexIndex].Position, Position[F1Data[0]], sizeof(vec3));
            memcpy(vertex[VertexIndex].TextureCoords, Texture[F1Data[1]], sizeof(vec2)); 
            memcpy(vertex[VertexIndex].Normal, Normal[F1Data[2]], sizeof(vec3));
            VertexIndex +=  1;
            
            memcpy(V3, SplitString(SplitStringData[3], '/', '\0'), 99*99);
            F1Data[0] = atoi(V3[0])-1;
            F1Data[1] = atoi(V3[1])-1;
            F1Data[2] = atoi(V3[2])-1;


            
            memcpy(vertex[VertexIndex].Position, Position[F1Data[0]], sizeof(vec3));
            memcpy(vertex[VertexIndex].TextureCoords, Texture[F1Data[1]], sizeof(vec2)); 
            memcpy(vertex[VertexIndex].Normal, Normal[F1Data[2]], sizeof(vec3));
            VertexIndex +=  1;

            // memcpy(V2, SplitString(SplitStringData[2], '/'), 99*99);
            // memcpy(V2, SplitString(SplitStringData[3], '/'), 99*99);






        }
    }


    glm_vec3_print(vertex[0].Position, stdout);
    *Size = VertexIndex;
    printf("Vertex Index: %d\n", VertexIndex);
    memcpy(verts, vertex, sizeof(Vertex)*1024);
}
