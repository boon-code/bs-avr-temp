

MCU = atmega16
F_OSC=8000000

AVRDUDE_PORT = /dev/ttyACM0

BUILD_SYSTEM = python ./buildsystem/bs.py

#SRC = $(wildcard *.c)
SRC = src/main.c
HEADER = src/bla.h.in

INCLUDES = -I"./src"
TARGET = main

# List Assembler source files here.
ASRC = 
