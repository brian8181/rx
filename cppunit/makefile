CXX=g++
CXXFLAGS=-Wall -std=c++11 -DCYGWIN
CXXEXTRA=-fPIC
BLD=build
OBJ=build
SRC=src
DEBUG=1

ifdef DEBUG
	CXXFLAGS+=-DDEBUG -g
endif

all: ./$(BLD)/test_calculator

.PHONY: rebuild
rebuild: clean all

./$(BLD)/test_calculator: ./$(SRC)/main.cpp ./$(SRC)/Calculator.cpp
	$(CXX) $(CXXFLAGS) ./$(SRC)/main.cpp ./$(SRC)/Calculator.cpp -lcppunit -o ./$(BLD)/test_calculator

.PHONY: clean
clean:
	-rm -f ./$(OBJ)/*
	-rm -f ./$(BLD)/*

.PHONY: help
help:
	@echo
	@echo "Execute:"
	@echo '	./build/test_calculator'
	@echo
	@echo 'Targets:'
	@echo '	all         - build all'
	@echo '	clean       - remove all files from build directory'
	@echo '	rebuild     - clean & all'
