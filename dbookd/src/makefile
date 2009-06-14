#
# dbookd Makefile
#

CPPS = main.cpp Logic.cpp XSocket.cpp
OBJS = main.o Logic.o XSocket.o

LD = g++
CLFLAGS = 
SLFLAGS = -L../../libdbook/build/src -L/usr/local/lib -lyaml-cpp -ldbook -I../../libdbook/src -I/usr/local/include/yaml-cpp

all: $(CPPS) dbookd

%.o: %.cpp
	$(LD) $(CLFLAGS) $(SLFLAGS) -c $<

dbookd: $(OBJS)
	$(LD) -o ../bin/dbookd $(OBJS) $(CPPOFDB) $(SLFLAGS)

help:
	@echo "dbookd Makefile"
	@echo
	@echo "make"
	@echo "  Compiles dbookd"
	@echo
	@echo "make clean_o"
	@echo "  Only clean objects"
	@echo
	@echo "make clean"
	@echo "  Clean everything up"

clean_o:
	rm *.o

clean:
	rm *.o ../bin/dbookd*
