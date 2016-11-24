#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall -std=c++14
RESINC = 
LIBDIR = 
LIB = -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g 
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = build
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/TurboMeteor

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = build
DEP_RELEASE = 
OUT_RELEASE = bin/Release/TurboMeteor

OBJ_DEBUG = $(OBJDIR_DEBUG)/Enemies.o $(OBJDIR_DEBUG)/Enemy.o $(OBJDIR_DEBUG)/Meteors.o $(OBJDIR_DEBUG)/PowerUps.o $(OBJDIR_DEBUG)/Projectiles.o $(OBJDIR_DEBUG)/ResourcePath.o $(OBJDIR_DEBUG)/Ship.o $(OBJDIR_DEBUG)/main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/Enemies.o $(OBJDIR_RELEASE)/Enemy.o $(OBJDIR_RELEASE)/Meteors.o $(OBJDIR_RELEASE)/PowerUps.o $(OBJDIR_RELEASE)/Projectiles.o $(OBJDIR_RELEASE)/ResourcePath.o $(OBJDIR_RELEASE)/Ship.o $(OBJDIR_RELEASE)/main.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/Enemies.o: Enemies.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Enemies.cpp -o $(OBJDIR_DEBUG)/Enemies.o

$(OBJDIR_DEBUG)/Enemy.o: Enemy.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Enemy.cpp -o $(OBJDIR_DEBUG)/Enemy.o

$(OBJDIR_DEBUG)/Meteors.o: Meteors.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Meteors.cpp -o $(OBJDIR_DEBUG)/Meteors.o

$(OBJDIR_DEBUG)/PowerUps.o: PowerUps.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c PowerUps.cpp -o $(OBJDIR_DEBUG)/PowerUps.o

$(OBJDIR_DEBUG)/Projectiles.o: Projectiles.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Projectiles.cpp -o $(OBJDIR_DEBUG)/Projectiles.o

$(OBJDIR_DEBUG)/ResourcePath.o: ResourcePath.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ResourcePath.cpp -o $(OBJDIR_DEBUG)/ResourcePath.o

$(OBJDIR_DEBUG)/Ship.o: Ship.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Ship.cpp -o $(OBJDIR_DEBUG)/Ship.o

$(OBJDIR_DEBUG)/main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)/main.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/Enemies.o: Enemies.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Enemies.cpp -o $(OBJDIR_RELEASE)/Enemies.o

$(OBJDIR_RELEASE)/Enemy.o: Enemy.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Enemy.cpp -o $(OBJDIR_RELEASE)/Enemy.o

$(OBJDIR_RELEASE)/Meteors.o: Meteors.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Meteors.cpp -o $(OBJDIR_RELEASE)/Meteors.o

$(OBJDIR_RELEASE)/PowerUps.o: PowerUps.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c PowerUps.cpp -o $(OBJDIR_RELEASE)/PowerUps.o

$(OBJDIR_RELEASE)/Projectiles.o: Projectiles.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Projectiles.cpp -o $(OBJDIR_RELEASE)/Projectiles.o

$(OBJDIR_RELEASE)/ResourcePath.o: ResourcePath.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ResourcePath.cpp -o $(OBJDIR_RELEASE)/ResourcePath.o

$(OBJDIR_RELEASE)/Ship.o: Ship.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Ship.cpp -o $(OBJDIR_RELEASE)/Ship.o

$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release
