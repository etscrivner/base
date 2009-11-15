# Makefile for Symphony
# Author: Eric Scrivner
#
# Time-stamp: <Last modified 2009-11-14 14:27:42 by Eric Scrivner>
#
# Can be used to build the first project
CC = g++
CCFLAGS = -Wall -c
OBJECTS = color.o plot.o main.o
NAME = symphony

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