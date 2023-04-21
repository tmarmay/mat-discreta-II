CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 -g 
SOURCES = APIG23.c vector.c main.c rbt.c
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
