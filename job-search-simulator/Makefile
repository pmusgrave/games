CC=g++
OPT=-Og -std=c++14
BUILD_DIR=build

CPP_SOURCES= \
src/*.cpp \
#test/*.cpp

DEPS= \
inc/*.hpp \

CPP_INCLUDES= \
-Iinc \

LIBS= -lallegro -lallegro_main -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec
CFLAGS = $(OPT) $(CPP_INCLUDES) $(LIBS) -Wall

all: build/main
	build/main

build/main: $(CPP_SOURCES) $(DEPS)
	if [ ! -d "build" ]; then mkdir build; fi
	$(CC) $(CPP_SOURCES) -o $(BUILD_DIR)/main $(CFLAGS)

.PHONY: all test clean
clean:
	rm -f $(BUILD_DIR)/*
	rm -f test/*.o
