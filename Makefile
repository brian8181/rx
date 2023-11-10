# Wed Nov  8 08:33:47 AM CST 2023

CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -DDEBUG
SRC = src
BLD = build
OBJ = build

all: rx

debug: all

rebuild: clean all
	
rx: rx.o main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/rx.o $(OBJ)/main.o -o $(BLD)/rx

main.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

rx.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/rx.cpp -o $(OBJ)/rx.o

.PHONY: install
install: #man # no man for now
	cp $(BLD)/rx $(prefix)/bin/rx

.PHONY: uninstall
uninstall:
	-rm $(prefix)/bin/rx

.PHONY: clean
clean:
	-rm -f $(BLD)/*
