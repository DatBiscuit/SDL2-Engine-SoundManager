OBJS = source/*.cpp 
INCLUDE_PATHS = -Iheaders -Iinclude/SDL2 -Iinclude/SDL2_image -Iinclude/SDL2_ttf
LIBRARY_PATHS = -Llib
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = build/SoccerWithGuns

#This is the target that compiles our executable
all: $(OBJS) 
	g++ $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)
