LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"

FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL 

COMPILERFLAGS = -Wall 
CC = g++ 
CFLAGS = $(COMPILERFLAGS) 
LIBRARIES = -lGL -lGLU -lm -lobjc -lstdc++ 

OBJECTS = main.o glMethods.o
All2: $(OBJECTS)
	$(CC) $(FRAMEWORK) $(CFLAGS) main.cpp glMethods.cpp -o $(OBJECTS)

main: main.o
	$(CC) $(FRAMEWORK) $(CFLAGS) main.cpp -o $@

glmethods: glMethods.o
	$(CC) $(FRAMEWORK) $(CFLAGS) glMethods.cpp -o glMethods.o

all: 
	$(CC) $(FRAMEWORK) $(CFLAGS) main.cpp glMethods.cpp -o practicaIDI.x

clean: 
	rm -f practicaIDI.x *.o *.out *.x

GlutExample: main.o $(OBJECTS) 
	$(CC) $(FRAMEWORK) $(CFLAGS) -o $@ $(LIBPATH) $(OBJECTS) $(LIBRARIES) ./GlutExample