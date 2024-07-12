CC = gcc
CFLAGS = -Wall -g
DEPS = 
OBJ = main.o

# Rule to compile .c files into .o files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to link .o files into the final executable named 'hello_world'
metal: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

