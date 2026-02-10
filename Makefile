CC ?= gcc

# Build mode: 'debug' or 'release'
BUILD ?= release

# Installation directory
PREFIX ?= /usr/local/bin/

TARGET = ttt
SRCDIR = src
INCDIR = includes
OBJDIR = obj
BINDIR = bin

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/func.c $(SRCDIR)/ui.c
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
HEADERS = $(INCDIR)/types.h $(INCDIR)/func.h $(INCDIR)/ui.h

CFLAGS = -Wall -std=c99
CPPFLAGS = -I$(INCDIR)

# Add debug or optimization flags based on build mode
ifeq ($(BUILD), debug)
	CFLAGS += -g
else 
	ifeq ($(BUILD), release)
		CFLAGS += -O2
	endif
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

distclean:
	rm -fr $(OBJDIR) $(BINDIR)

install:
	install -d $(PREFIX)
	install -m 755 ./$(BINDIR)/$(TARGET) $(PREFIX)

uninstall:
	rm -f $(PREFIX)/$(TARGET)

help:
	@echo "make - Build the program"
	@echo "make BUILD=debug - Build with debug flags"
	@echo "make BUILD=release - Build with optimization"
	@echo ""
	@echo "make clean - Remove all temporary files"
	@echo "make distclean - Remove all generated files"
	@echo "make install - Install the executable file to $(PREFIX)"
	@echo "make uninstall - Remove the installed executable file"
	@echo ""
	@echo "To change the installation and removal path, use PREFIX="

.PHONY: all clean distclean install uninstall help
