#
# DBookClient Makefile
#

CPPS = main.cpp Logic.cpp XSocket.cpp
OBJS = main.o Logic.o XSocket.o

LD = g++
CLFLAGS = -I/usr/local/include/yaml-cpp -L/usr/local/lib
SLFLAGS = -lyaml-cpp

all: $(CPPS) DBookClient

%.o: %.cpp
	$(LD) $(CLFLAGS) $(SLFLAGS) -c $<

DBookClient: $(OBJS)
	$(LD) -o ../bin/DBookClient $(OBJS) $(CLFLAGS) $(SLFLAGS) $(CPPOFDB)

help:
	@echo "DBookClient Makefile"
	@echo
	@echo "make"
	@echo "  Compiles DBookClient"
	@echo
	@echo "make clean_o"
	@echo "  Only clean objects"
	@echo
	@echo "make clean"
	@echo "  Clean everything up"

clean_o:
	rm *.o

clean:
	rm *.o ../bin/DBookClient*
