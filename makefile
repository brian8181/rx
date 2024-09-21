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
