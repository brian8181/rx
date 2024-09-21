<<<<<<< HEAD
# June 17, 2022
# MAKE_TEMPLATE = 1.6;
# BUILD_VERSION = 0.1.1

CXX = g++
CXXFLAGS = -Wall -std=c++11 -DDEBUG -ggdb
LDFLAGS = -static -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/
APPNAME = rx
EXT = cpp
ROOT  = .
SRCS = src
BLD = build
OBJ = build

# compile & link for debug
#debug: CXXFLAGS += -DDEBUG -g
debug: all

# compile & link for debug GDBversion variable
debuggdb: all

# compile & link
all: rx bash_color_test
	
# link
rx: rx.o main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/rx.o $(OBJ)/main.o -o $(BLD)/rx
	
# compile only
rx.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/rx.$(EXT) -o $(OBJ)/rx.o
	
main.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/main.$(EXT) -o $(OBJ)/main.o

# link
rx_test: rx_test.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ)/rx_test.o $(OBJ)/rx.o $(LDFLAGS) -o $(BLD)/rx_test

# compile only
rx_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/rx_test.cpp -o $(OBJ)/rx_test.o

bash_color_test: bash_color_test.o
	$(CXX) $(CXXFLAGS) $(OBJ)/bash_color_test.o -o $(BLD)/bash_color_test

bash_color_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/bash_color_test.cpp -o $(OBJ)/bash_color_test.o

.PHONY: clean
clean:
	-rm -rf ./$(OBJ)/*
	-rm -rf ./$(BLD)/*
	
# install man pages
.PHONY: man
man:
	cp ../man/rx.1 $(man1dir)
	gzip $(man1dir)/rx.1
	mandb
	
# uninstall man pages
.PHONY: unman
unman:
	rm $(man1dir)/rx.1.gz
	mandb

# install 
.PHONY: install
install: #man # no man for now
	-cp $(BLD)/rx $(prefix)/bin/rx

# uninstall
.PHONY: uninstall
uninstall: unman
	-rm $(prefix)/bin/rxINCLUDES = -I/usr/local/include/cppunit/
	-rm -f $(OBJ)/*
	-rm -f $(BLD)/* 
	
dist: 
	git archive HEAD | gzip > $(BLD)/rx.$(BLD_VERSION).tar.gz

dist-gz: dist
=======
# File Name:  rx/makefile
# Build Date: Mon Mar  4 09:11:39 AM CST 2024
# Version:    0.1.0

CXX=g++
CXXFLAGS=-g -Wall -std=c++11 -DDEBUG
SRC=src
BLD=build
OBJ=build

all: $(BLD)/rx

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
>>>>>>> 84b7b1a5e962c1bdf4981939b049e90a55c97bd8
