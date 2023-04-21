CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 -g 
SOURCES = ../construccion-grafo/APIG23.c ../construccion-grafo/vector.c ../construccion-grafo/rbt.c APIParte2.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = a

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
