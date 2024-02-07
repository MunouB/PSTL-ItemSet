# Define the compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
INCLUDES =

# Define library paths in addition to /usr/lib
LFLAGS =

# Define any libraries to link into executable
LIBS =

# Define the source files
SRCS = main.c bad_functions.c constructors.c getters.c freers.c adders.c displayers.c verifiers.c hashers.c initializers.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the executable file
MAIN = main

.PHONY: clean

# The default target (all) to compile the executable
all:    $(MAIN)
	@echo  Program has been compiled!

# Link the object files to create the executable
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# Compile the source files into object files
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# Clean up the compiled files
clean:
	$(RM) *.o *~ $(MAIN)

