CC			  = gcc
CXX           = g++
DEFINES       =
CFLAGS 		  = 
CXXFLAGS      =
INCPATH       =
LINK          = g++
LFLAGS        = 
LIBS          = -lglut -lGLU -lGL -lm
DEL_FILE      = rm -f

####### Files
SOURCES       = shapes.c hw2.c
OBJECTS       = $(SOURCES:.c=.o)
TARGET        = hw2

first: all

####### Implicit rules
.SUFFIXES: .cpp .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules
all:  $(TARGET)

$(TARGET):  clean $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

.PHONY: clean
clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)
