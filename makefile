# File Name:  rx/makefile
# Build Date: Mon Mar  4 09:11:39 AM CST 2024
# Version:    0.1.0

CXX=g++
CXXFLAGS=-g -Wall -std=c++11 -DDEBUG -DCYGWIN
SRC=src
BLD=build
OBJ=build

# lib settings
LDFLAGS = -static -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/

all: ./$(BLD)/rx ./$(BLD)/rx_test_test #./$(BLD)/rx_test

#rebuild: clean all

./$(BLD)/rx: ./$(OBJ)/rx.o ./$(OBJ)/main.o
	$(CXX) $(CXXFLAGS) ./$(OBJ)/rx.o ./$(OBJ)/main.o -o ./$(BLD)/rx

./$(OBJ)/main.o: ./$(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -c ./$(SRC)/main.cpp -o ./$(OBJ)/main.o

./$(OBJ)/rx.o: ./$(SRC)/rx.cpp
	$(CXX) $(CXXFLAGS) -c ./$(SRC)/rx.cpp -o ./$(OBJ)/rx.o

# ./$(BLD)/rx_test: rx_test.o
#  	$(CXX) $(CXXFLAGS) ./$(INCLUDES) ./$(OBJ)/rx_test.o ./$(OBJ)/rx.o ./$(LDFLAGS) -o ./$(BLD)/rx_test

./$(OBJ)/rx_test.o: ./$(SRC)/rx_test.cpp
	$(CXX) $(CXXFLAGS) -c ./$(SRC)/rx_test.cpp -o ./$(OBJ)/rx_test.o


./$(BLD)/rx_test_test: ./$(SRC)/rx_test_test.cpp ./$(SRC)/test.cpp
	$(CXX) $(CXXFLAGS) ./$(SRC)/rx_test_test.cpp ./$(SRC)/test.cpp -lcppunit -o ./$(BLD)/rx_test_test


.PHONY: install
install:
	cp ./$(BLD)/rx ./$(prefix)/bin/rx

.PHONY: uninstall
uninstall:
	-rm ./$(prefix)/bin/rx

.PHONY: clean
clean:
	-rm -f ./$(OBJ)/*
	-rm -f ./$(BLD)/*


.PHONY: help
help:
	@echo  '  all         - build all'
	@echo  '  rx          - build rx executable'
	@echo  '  rx.o        - build not link'
	@echo  '  rx_test     - build cppunit test'
	@echo  '  rx_test.o   - build cppunit test'
	@echo  '  clean       - remove all files from build dir'
	@echo  '  install     - copy files to usr/local'
	@echo  '  dist        - create distribution, tar.gz'