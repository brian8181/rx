# License:    None
# File Name:  ../rx/makefile
# Build Date: Fri Feb 16 04:38:08 PM CST 2024
# Version:    0.1.0

CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -DDEBUG
SRC = src
BLD = build
OBJ = build

all: $(BLD)/rx

debug: all

rebuild: clean all

$(BLD)/rx: $(OBJ)/rx.o $(OBJ)/main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/rx.o $(OBJ)/main.o -o $(BLD)/rx

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/rx.o: $(SRC)/rx.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/rx.cpp -o $(OBJ)/rx.o

.PHONY: install
install:
	cp $(BLD)/rx $(prefix)/bin/rx

.PHONY: uninstall
uninstall:
	-rm $(prefix)/bin/rx

.PHONY: clean
clean:
	-rm -f $(OBJ)/*
	-rm -f $(BLD)/*


.PHONY: help
help:
	@echo  '  all         - build all'
	@echo  '  rx          - build rx executable'
	@echo  '  rx.o        - build not link'
	@echo  '  clean       - remove most generated files but keep the config'
	@echo  '  install     - copy files to usr/local'
	@echo  '  dist        - create distribution, tar.gz'
