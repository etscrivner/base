# Makefile for Base
# Author: Eric Scrivner
#
# Time-stamp: <Last modified 2009-12-04 15:03:49 by Eric Scrivner>
#
# Makefile which provides a starting point for building a base project
CC = g++
CCFLAGS = -Wall -c
OBJECTS = color.o plot.o draw_line.o image.o model.o main.o
NAME = raytrace

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

image.o: image.cpp
	$(CC) $(CCFLAGS) image.cpp

model.o: model.cpp
	$(CC) $(CCFLAGS) model.cpp

draw_line.o: draw_line.cpp
	$(CC) $(CCFLAGS) draw_line.cpp

clean:
	rm -rf $(NAME) *.o *~