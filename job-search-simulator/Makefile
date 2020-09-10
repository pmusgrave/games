SHELL := /bin/bash
CC=g++
OPT=-O3 -std=c++14
BUILD_DIR=build

CPP_SOURCES= \
src/*.cpp \
#test/*.cpp

DEPS= \
inc/*.hpp \

CPP_INCLUDES= \
-Iinc \

LIBS= \
-lallegro \
-lallegro_main \
-lallegro_font \
-lallegro_ttf \
-lallegro_image \
-lallegro_primitives \
-lallegro_audio \
-lallegro_acodec \
-lallegro_dialog \

CFLAGS = $(OPT) $(CPP_INCLUDES) $(LIBS) -Wall

OS := $(shell uname)

all: build/main
	build/main

build/main: $(CPP_SOURCES) $(DEPS)
	mkdir -p build
	$(CC) $(CPP_SOURCES) -o $(BUILD_DIR)/main $(CFLAGS)

release:
	if [[ "$(OS)" == "Linux"* ]]; then \
		make build/main; \
		mkdir -p release/linux; \
		cp -r build/* release/linux; \
		cp -r resources release/linux; \
	elif [[ "$(OS)" == "Darwin"* ]]; then \
		make build/main; \
		mkdir -p release/macos; \
		cp -r build/* release/macos; \
		cp -r resources release/macos; \
	else \
		echo "error"; \
	fi

.PHONY: all test clean release
clean:
	rm -f $(BUILD_DIR)/*
	rm -f test/*.o
