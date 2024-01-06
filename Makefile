########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++

# DEBUG or RELEASE
CXXFLAGS = -Wall -g -std=c++17 -L lib/
# CXXFLAGS = -Wall -O2 -std=c++17 -L lib/

LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm


# Makefile settings - Can be customized.
APPNAME = main.exe
EXT = .cpp
SRCDIR = src
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	rm $(OBJDIR)/*.o
	rm $(APPNAME)

