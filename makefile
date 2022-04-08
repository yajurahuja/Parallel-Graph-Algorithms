# #First version, hence hardcoded the path, have to make this generic
.PHONY: all clean

EXECUTABLES = main

COMPILER = g++
CPP=FILES.cpp

all: $(EXECUTABLES)

clean:
	@echo Delete .obj files
	rm -f bin/interface.o bin/main.o
	@echo Delete exe file
	rm -rf $(EXECUTABLES)

bin/interface.o: src/interface.cpp
	@echo Compiling interface
	g++ -c -std=c++17 -march=native -g src/interface.cpp -o bin/interface.o

bin/main.o: src/main.cpp
	@echo Compiling main
	g++ -c -std=c++17 -march=native -g	src/main.cpp -o bin/main.o

$(EXECUTABLES): bin/interface.o bin/main.o
	@echo Linking executable
	g++ -g bin/interface.o bin/main.o -o main