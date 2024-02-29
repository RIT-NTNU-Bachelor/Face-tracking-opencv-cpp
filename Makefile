CC = "g++"
Project = TestOpenCV
SRC = src/main.cpp

LIBS = `pkg-config --cflags --libs opencv4`

$(Project) : $(SRC)
	$(CC) $(SRC) -o $(Project) $(LIBS)
