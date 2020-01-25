CC=g++
OPT=-Og -std=c++17
BUILD_DIR=build

CPP_SOURCES= \
src/*.cpp \
#test/*.cpp

DEPS= \
inc/*.hpp \

CPP_INCLUDES= \
-Iinc \

LIBS=
CFLAGS = $(OPT) $(CPP_INCLUDES) $(LIBS) -Wall

all: build/main
	build/main

build/main.o: $(CPP_SOURCES) $(DEPS)
	$(CC) $(CFLAGS) $(CPP_INCLUDES) src/*.cpp -o $(BUILD_DIR)/main

.PHONY: all test clean
clean:
	rm -f $(BUILD_DIR)/*
	rm -f test/*.o
