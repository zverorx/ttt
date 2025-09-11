# Compiler to use (default: gcc)
CC ?= gcc

# Build mode: 'debug' or 'release' (default: release)
BUILD ?= release

# Installation directory (default: /usr/local/bin/)
CONFIG_PREFIX ?= /usr/local/bin/

# Name of the final executable
TARGET = ttt

# Source directory
SRCDIR = src

# Include directory
INCDIR = includes

# List of source files
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/func.c $(SRCDIR)/ui.c

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
$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/types.h $(INCDIR)/func.h $(INCDIR)/ui.h
	@echo "Compiling $<"
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Remove object files
clean:
	rm -f $(OBJECTS)

# Remove all generated files (objects and executable)
distclean:
	rm -f $(OBJECTS) $(TARGET)

# Install the executable to the target directory
install:
	install -d $(CONFIG_PREFIX)
	install -m 755 ./$(TARGET) $(CONFIG_PREFIX)
	@echo "$(TARGET) installed to $(CONFIG_PREFIX)"

# Remove the installed executable
uninstall:
	rm -f $(CONFIG_PREFIX)/$(TARGET)
	@echo "$(TARGET) removed from $(CONFIG_PREFIX)"

# Show help message
help:
	@echo "Hints:"
	@echo ""
	@echo "make - Build the program"
	@echo "make BUILD=debug - Build with debug flags"
	@echo "make BUILD=release - Build with optimization"
	@echo ""
	@echo "make clean - Remove all temporary files"
	@echo "make distclean - Remove all generated files"
	@echo "make install - Install the executable file to $(CONFIG_PREFIX)"
	@echo "make uninstall - Remove the installed executable file"

.PHONY: all clean distclean install uninstall help
