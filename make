# Compiler
C = g++

# Project Directories
SRCDIR = src
LIBDIR = libs
OBJDIR = obj

# SFML directories
SFMLDIR = $(LIBDIR)/SFML
SFMLINC = $(SFMLDIR)/include
SFMLLIB = $(SFMLDIR)/lib

LDFLAGS = -L/usr/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Compiler Flags
CFLAGS = -std=c++11 -I/usr/include

# Executable Name
EXEC = WaTorSimulation

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files for sources in the src directory
OBJ_SRC = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Object file for the main file outside src directory
OBJ_MAIN = $(OBJDIR)/main.o

# All object files
OBJECTS = $(OBJ_SRC) $(OBJ_MAIN)

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJECTS)
	$(C) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Compiling sources in the src directory
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(C) $(CFLAGS) -c $< -o $@

# Compiling the main file
$(OBJ_MAIN): main.cpp | $(OBJDIR)
	$(C) $(CFLAGS) -c $< -o $@

# Create the object files directory
$(OBJDIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(OBJDIR) $(EXEC)

.PHONY: all clean