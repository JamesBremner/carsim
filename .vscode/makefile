#source file search paths
VPATH = ./src 

	# compiler include search paths
INCS = -I./include \
	-I../ravencode/pub/src \
	-I../raven-set \
	-I../boost/boost1_72 

LIBS = \
	-lgdiplus -lgdi32 -lcomdlg32 -lstdc++fs \
	#-mwindows

static_link_flags = -static-libstdc++ -static-libgcc -static

# folders
ODIR = ./.vscode/obj
RDIR = ../ravencode/pub/src

OPT = -g
CCflags = -std=c++17 $(OPT) -D_mingw_

# sources
OBJ = \
	$(ODIR)/main.o \
	$(ODIR)/cGUI.o \
	$(ODIR)/cFuelTable.o \
	$(ODIR)/cDrivePlan.o \
	$(ODIR)/cSimulation.o


### COMPILE

$(ODIR)/%.o: %.cpp sumo.h
	g++  $(CCflags) \
	-c -o $@ $< $(INCS)

sumo: $(OBJ)
	g++ $(OPT) \
	-o bin/sumo.exe $^  \
	$(static_link_flags) $(LIBS)

.PHONY: clean
clean:
	del /q .vscode\\obj\\*.o

