CXX ?= g++

# Build mode: 'debug' or 'release'
BUILD ?= debug

TARGET = ttt
OBJDIR = obj
BINDIR = bin

SOURCES = main.cpp							\
		  entity/game/game.cpp				\
		  entity/player/player.cpp			\
		  entity/bot/bot.cpp				\
		  entity/console_ui/console_ui.cpp	\
		  entity/terminal/terminal.cpp

OBJECTS = $(OBJDIR)/main.o			\
		  $(OBJDIR)/game.o			\
		  $(OBJDIR)/player.o		\
		  $(OBJDIR)/bot.o			\
		  $(OBJDIR)/console_ui.o	\
		  $(OBJDIR)/terminal.o

CXXFAGS ?=
LDFLAGS ?=

ifeq ($(BUILD), debug)
	CXXFLAGS += -c -Wall -g
	LDFLAGS += -g
else
	ifeq ($(BUILD), release)
		CXXFLAGS += -c -O2
		LDFLAGS += -s
	endif
endif

ifeq ($(CXX), gcc)
	CXXFLAGS += -x c++
	LIBS += -lstdc++
endif


VPATH = entity/game			\
		entity/player		\
		entity/bot			\
		entity/console_ui	\
		entity/terminal

all : $(BINDIR)/$(TARGET) 

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) $^ $(LIBS) -o $@ 

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@ 

clean:
	rm -rf $(OBJDIR)

distclean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean distclean
