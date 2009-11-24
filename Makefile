# Makefile for Base
# Author: Eric Scrivner
#
# Time-stamp: <Last modified 2009-11-19 09:42:52 by Eric Scrivner>
#
# Makefile which provides a starting point for building a base project
CC = g++
CCFLAGS = -Wall -c
OBJECTS = color.o plot.o main.o
NAME = base

SHELL = /bin/sh
OS = $(shell uname -s)
$(info OS=${OS})

ifeq (${OS}, Darwin)
LIBS = -framework OpenGL -framework GLUT -framework Cocoa
else
LIBS = -lGL -lglut -lGLU
endif

all: $(OBJECTS)
	g++ $(LIBS) $(OBJECTS) -o $(NAME)

main.o: main.cpp
	$(CC) $(CCFLAGS) main.cpp

color.o: color.cpp
	$(CC) $(CCFLAGS) color.cpp

plot.o: plot.cpp
	$(CC) $(CCFLAGS) plot.cpp

clean:
	rm -rf $(NAME) *.o *~