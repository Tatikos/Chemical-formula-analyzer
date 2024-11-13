# Define compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Define target executable and object files
TARGET = parseFormula
OBJS = main.o stack.o data.o parser.o

# Default target
all: $(TARGET)

# Linking object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file into an object file
main.o: main.c data.h parser.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

data.o: data.c data.h stack.h
	$(CC) $(CFLAGS) -c data.c

parser.o: parser.c parser.h stack.h data.h
	$(CC) $(CFLAGS) -c parser.c

# Run target with arguments
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
