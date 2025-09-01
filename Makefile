# Compiler to use (default: gcc)
CC ?= gcc

# Build mode: 'debug' or 'release' (default: debug)
BUILD ?= debug

# Name of the final executable
TARGET = ttt

# Source directory
SRCDIR = src

# Include directory
INCDIR = includes

# List of source files
SOURCES = $(SRCDIR)/main.c

# List of objects files
OBJECTS = $(SOURCES:.c=.o)

# Compiler flags
CFLAGS = -Wall -std=c99

# Preprocessor flags
CPPFLAGS = -I$(INCDIR)

# Add debug or optimization flags based on build mode
ifeq ($(BUILD), debug)
	CFLAGS += -g
else
	ifeq ($(BUILD), release)
		CFLAGS += -O2
	endif
endif

# Default target: build the program
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ 

# Compile .c files into .o files
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling $<"
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Remove object files
clean:
	rm -f $(OBJECTS)

# Remove all generated files (objects and executable)
distclean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean distclean
