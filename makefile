# File Name:  rx/makefile
# Build Date: Mon Mar  4 09:11:39 AM CST 2024
# Version:    0.1.0

APP=rx
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++20 -Wno-vla
SRC=src
BLD?=build
OBJ?=build

# lib settings
LDFLAGS = -static -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/

# ifdef NO_DEBUG
# 	RELEASE=TRUE
# endif

ifndef RELEASE NO_DEBUG
	CXXFLAGS +=-g -DDEBUG
endif

ifdef CYGWIN
	CXXFLAGS += -DCYGWIN
endif

all: $(BLD)/rx $(BLD)/rx_test

rebuild: clean all

$(BLD)/rx: $(OBJ)/rx.o $(OBJ)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BLD)/rx_test: $(OBJ)/rx.o $(OBJ)/rx_test.o
	$(CXX) $(CXXFLAGS) $(OBJ)/rx.o $(OBJ)/rx_test.o -lcppunit -o $@

#$(BLD)/rx: $(OBJ)/rx.o $(OBJ)/main.o
#	$(CXX) $(CXXFLAGS) $< -o $(BLD)/rx

#$(BLD)/rx_test: $(OBJ)/rx.o $(OBJ)/rx_test.o
#	$(CXX) $(CXXFLAGS) $< -lcppunit -o $(BLD)/rx_test

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

# $(OBJ)/main.o: $(SRC)/main.cpp
# 	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

# $(OBJ)/rx.o: $(SRC)/rx.cpp
# 	$(CXX) $(CXXFLAGS) -c $(SRC)/rx.cpp -o $(OBJ)/rx.o

# $(OBJ)/rx_test.o: $(SRC)/rx_test.cpp
# 	$(CXX) $(CXXFLAGS) -c $(SRC)/rx_test.cpp -o $(OBJ)/rx_test.o

.PHONY: install
install:
	cp ./$(BLD)/rx ./$(prefix)/bin/rx

.PHONY: uninstall
uninstall:
	-rm ./$(prefix)/bin/rx

.PHONY: clean
clean:
	-rm -f ./$(OBJ)/*.o
	-rm -f ./$(BLD)/*.o
	-rm -f ./$(BLD)/$(APP)*

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
