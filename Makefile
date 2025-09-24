OBJS = src/main.c src/glad.c src/LoadShader.c  src/stb_image.c src/Model.c src/OBJLoader.c src/Font.c src/EventLoader.c

OBJ_Name = main


CC = gcc
INCLUDE_PATHS = -I/usr/include/SDL2/ -I/home/Dimitris/Documents/CalanderOpenGL-main/Include/ -I/usr/local/include/cglm/
LINKER_FLAGS = -lSDL2  -lGL -L/usr/local/lib -lm
all: $(OBJS)	
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LINKER_FLAGS) -o $(OBJ_Name)