#include "stb_image.h"
#include "LoadShader.h"
#include "cglm.h"
#include "Model.h"
#include "OBJLoader.h"
#include "time.h"
#include "FontData.h"
#include "Font.h"
#include "EventLoader.h"

vec4 TextPositions[95];
void DrawModelIndicies(Model m){

	glBindVertexArray(m.VAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	
	
}

void DrawModel(Model m){
	glBindVertexArray(m.VAO);

	glDrawArrays(GL_TRIANGLES, 0, m.Size);
	glBindVertexArray(0);

}

void DrawTextOntoUV(Model N, int tex, int fbo){
	glDisable(GL_CULL_FACE);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 2100, 2100);
	glUseProgram(N.ShaderData.ProgramID);
	glBindTexture(GL_TEXTURE_2D, tex);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	int UniformSlices = glGetUniformLocation(N.ShaderData.ProgramID, "SliceArray");
	glUniform4fv(UniformSlices, 95, TextPositions[0]);
	DrawModelIndicies(N);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void DrawBackground(Model m, float t){
		
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		
		//Need to bind the shader, send relevent data THEN draw
		glUseProgram(m.ShaderData.ProgramID);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		int UniformT = glGetUniformLocation(m.ShaderData.ProgramID, "time");
		glUniform1f(UniformT, t);
		
		DrawModelIndicies(m);
		glUseProgram(0);
}

unsigned int GenerateTextureForFramebuffer(int width, int height){
	int texForBuffer;
	glGenTextures(1, &texForBuffer);
	glBindTexture(GL_TEXTURE_2D, texForBuffer);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	return texForBuffer;
}
unsigned int CreateRenderBufferObject(int width, int height){
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

unsigned int CreateFramebuffer(unsigned int TexFrameBuffer){
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TexFrameBuffer, 0);
	CreateRenderBufferObject(2100, 2100);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);  
	return FBO;
}

void HandleInput(){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.sym == 'q'){
					SDL_Quit();
					exit(0);
				}
			}
		}
}


int *ConvertStringToIntegers(char *text){
	static int Data[100]; 
	printf("Length: %d\n", strlen(text));
	for (int i = 0; i<strlen(text); i++){
		printf("%c\n", text[i]);
		Data[i] = (int)text[i];
	}
	return Data;
}

void DrawCalanderIcons(vec3 Positions[31], Model m, float tBegining, struct tm *t, int UniformMat, int UniformMatModel, int UniformIndex, mat4 PerspectiveMatrix){
		glEnable(GL_CULL_FACE);
		for (int i = 0; i < 31; i++){
			mat4 transform;
			mat4 ModelMat;
			glm_mat4_identity(ModelMat);
			//Modify only the model with transformations 
			glm_translate(ModelMat, Positions[i]);
			glm_translate(ModelMat, (vec3){0, 0, -15});
			glm_rotate_y(ModelMat, glm_rad(270), ModelMat);
			// glm_rotate_y(ModelMat, glm_rad(cos(tBegining/2.0)*45), ModelMat);
			glm_scale(ModelMat, m.transformData.Scale);
			//glm_mul(ModelMat, ViewMatrix, ModelMat);
			if (t->tm_mday == i+1){
				glm_rotate_y(ModelMat, glm_rad(cos(tBegining*3.0)*45), ModelMat);
			}
			else{	
				glm_translate(ModelMat, (vec3){0, sin(tBegining+i)*0.5, 0});
			}
			glm_mul(PerspectiveMatrix, ModelMat, transform);

			glUniformMatrix4fv(UniformMat, 1, GL_FALSE, (float*)transform);
			glUniformMatrix4fv(UniformMatModel, 1, GL_FALSE, (float*)ModelMat);
			glUniform1i(UniformIndex, i);
			DrawModel(m);
			
		}
}

void SetupShaders(int *shaderProgram, int *ModelProgram, int *ShaderBackground, int *NumberShader, int *defaultshader){
	*shaderProgram = CreateProgram("Shaders/ShowTexture/Vertex.vert", "Shaders/ShowTexture/Fragment.frag");
	*ModelProgram = CreateProgram("Shaders/Model/Vertex.vert", "Shaders/Model/Fragment.frag");
	*ShaderBackground = CreateProgram("Shaders/Background/Vertex.vert", "Shaders/Background/Fragment.frag");
	*NumberShader = CreateProgram("Shaders/NumberShader/Vertex.vert", "Shaders/NumberShader/Fragment.frag");
	*defaultshader = CreateProgram("Shaders/default/Vertex.vert", "Shaders/default/Fragment.frag");

}



int main(){


	char S1[] = "Hello World";
	char S2[] = "1";
	StringCopy(S1, S2);
	printf("1: %s| 2: %s", S1, S2);

	for (int i = 0; i<95; i++){
		Character c = characters_Arial[i];
		memcpy(TextPositions[i], (vec4){c.x, c.y, c.width, c.height}, sizeof(vec4));
	}

	float vertices[] = {
		0.5f,  0.5f, -0.f,  1.0, 1.0,// top right //TexCoords
		0.5f, -0.5f, -0.f,  1.0, 0.0,// bottom right
		-0.5f, -0.5f, -0.f,  0.0, 0.0,// bottom left
		-0.5f,  0.5f, -0.f,  0.0, 1.0// top left 
	};
	float VertBackground[] = {
		1.0,  1.0, 0,  1.0, 1.0,// top right //TexCoords
		1.0, -1.0, 0,  1.0, 0.0,// bottom right
		-1.0, -1.0, 0,  0.0, 0.0,// bottom left
		-1.0,  1.0, 0,  0.0, 1.0// top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	}; 
	SDL_Window *mainWindow;
	SDL_GLContext mainContext;
	if (SDL_Init(SDL_INIT_VIDEO)<0){
		printf("Error initilizing SDL\n");	
		printf("%s\n", SDL_GetError());
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	mainWindow = SDL_CreateWindow("Calander", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	mainContext = SDL_GL_CreateContext(mainWindow);
	
	//Needs to be called after the opengl context is created
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
			printf("Failed to initialize opengl\n");
			return -1;
		}
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Number Texture
	unsigned int texture = LoadTexture("Page/PageUV.png", GL_NEAREST_MIPMAP_NEAREST);
	unsigned int textureFontSDF = LoadTexture("font.png", GL_LINEAR_MIPMAP_LINEAR);
	//Number Texture
	unsigned int TextureForFrameBuffer = GenerateTextureForFramebuffer(2100, 2100);
	unsigned int TextFBO = CreateFramebuffer(TextureForFrameBuffer);
	
	int defaultshader;
	int shaderProgram, ModelProgram, ShaderBackground, NumberShader;
	SetupShaders(&shaderProgram, &ModelProgram, &ShaderBackground, &NumberShader, &defaultshader);

	Model Test;
	Model PanelRight;
	Model Background;
	Model NumberModel;
	vec3 TilePositions[31];
	LoadModelFromFile("Page/Page.obj", &Test, ModelProgram, (vec3){0, 0, 0}, (vec3){0.25, 0.25, 0.25});
	LoadModelFromFile("Panel/Panel.obj", &PanelRight, shaderProgram, (vec3){4.25, -0.5, 5}, (vec3){0.5, 0.5, 0.5});


	unsigned int Textvbo, Textvao;
	SetupText(&Textvao, &Textvbo);
	
	
	
	Test.Texture1 = texture;
		
	CreateModel(VertBackground, indices, ShaderBackground, (vec3){0, 0, 0}, (vec3){1, 1, 1}, &Background);
	CreateModel(VertBackground, indices, NumberShader, (vec3){0, 0, 0}, (vec3){1, 1, 1}, &NumberModel);
	for (int i = 0; i<31; i++){
		float xPos = i %7;
		float yPos = i / 7;
		memcpy(TilePositions[i], (vec3){(xPos*1.2)-4.5, (-yPos*1.2)+1.5, 5}, sizeof(vec3));
	
	}
	float t = 0.0;
	mat4 PerspectiveMatrix;
	glm_perspective(glm_rad(45.0), SCREEN_WIDTH/SCREEN_HEIGHT, 0.01, 100.0, PerspectiveMatrix);
	DrawTextOntoUV(NumberModel, textureFontSDF, TextFBO);
	glUseProgram(Test.ShaderData.ProgramID);
	glUniform1i(glGetUniformLocation(Test.ShaderData.ProgramID, "tex"), 0);
	glUniform1i(glGetUniformLocation(Test.ShaderData.ProgramID, "BaseTex"), 1);
	
	
	int UniformMat = glGetUniformLocation(Test.ShaderData.ProgramID, "transform");
	int UniformMatModel = glGetUniformLocation(Test.ShaderData.ProgramID, "Model");
	int UniformIndex = glGetUniformLocation(Test.ShaderData.ProgramID, "Index");


	while (1){
		t += 1.0/60.0;
		//Draw Calander			
		
		HandleInput();
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		DrawBackground(Background, t);
		glEnable(GL_DEPTH_TEST);
		
		
		
		
		glUseProgram(Test.ShaderData.ProgramID);
		glBindVertexArray(Test.VAO);
		
		
		int UniformT = glGetUniformLocation(Test.ShaderData.ProgramID, "time");
		
		glUniform1f(UniformT, t);
		float tBegining = t;
		
		time_t today = time(NULL);
		struct tm *timedate = localtime(&today);
		
		
		glUseProgram(Test.ShaderData.ProgramID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureForFrameBuffer);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Test.Texture1);
		
		
		DrawCalanderIcons(TilePositions, Test, tBegining, timedate, UniformMat, UniformMatModel, UniformIndex, PerspectiveMatrix);
		glUseProgram(0);
		RenderText(defaultshader, "Events:", 2000, -400.0, 1.5, Textvbo, Textvao, textureFontSDF);

		for (int i = 0; i<24; i++){
			char EventLine[] = "%d: ";
			sprintf(EventLine, "%d: ", i+1);
			
			RenderText(defaultshader, EventLine, 2000, -400.0-(40*(i+1))*1.5, 1.5, Textvbo, Textvao, textureFontSDF);
		}
		SDL_GL_SwapWindow(mainWindow);
	}
	return 0;
}

//Okay lets think. We are either going to render the text onto the numbers texture using a font file 
//Or sign distance fields... let us think on it while we sleep. then we add the numbers in, add in the two pannels 
//the ability to add events and show events then we call it quits
//top panel should show upcoming events
//side panel should show events by day