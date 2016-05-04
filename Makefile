CC = gcc
CXX = g++
DEFINES =
CFLAGS =
CXXFLAGS = -m64 -pipe -O2 -Wall -W -D_REENTRANT -pthread -fPIC -std=c++11 ${DEFINES}
CPPFLAGS =
INCPATH = -I. -Isrc -I/usr/include/SDL2
LINK = g++
LFLAGS = -m64 -Wl,-O1
LIBS = $(SUBLIBS) -L/usr/X11R6/lib64 -lGL -lpthread -lSDL2 -lSDL2_image
TARGET = sdltest
Q = @

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

OBJECTS_DIR = .obj
SOURCES = $(call rwildcard, src/, *.cpp)
OBJECTS = $(patsubst %.cpp, .obj/%.o,$(SOURCES))


all: $(OBJECTS)
	mkdir -p $(OBJECTS_DIR)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

.obj/%.o: %.cpp
	@echo "CXX ===> $@"
	@mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $(INCPATH) $< -o $@

clean:
	@find . -type f -name '*.o' -delete
	@rm -Rf .obj/
	@rm -f $(TARGET)
	@echo cleaned objects
	@ccache -Cz

$(TARGET): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

install:  FORCE

uninstall:  FORCE

FORCE:
