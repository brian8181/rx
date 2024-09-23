CXX = g++
CXXFLAGS = -Wall -std=c++11 -DDEBUG -ggdb
EXT = cpp
SRC = src
BLD = build
OBJ = build

# compile & link
all: rx
	
rx: rx.o main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/rx.o $(OBJ)/main.o -o $(BLD)/rx
	
rx.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/rx.cpp -o $(OBJ)/rx.o
	
main.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

# rx_test: rx_test.o
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ)/rx_test.o $(OBJ)/rx.o $(LDFLAGS) -o $(BLD)/rx_test

# rx_test.o:
# 	$(CXX) $(CXXFLAGS) -c $(SRC)/rx_test.cpp -o $(OBJ)/rx_test.o

.PHONY: clean
clean:
	-rm -rf $(OBJ)/*
	-rm -rf $(BLD)/*

.PHONY: install
install: #man # no man for now
	-cp $(BLD)/rx $(prefix)/bin/rx

.PHONY: uninstall
uninstall: unman
	-rm $(prefix)/bin/rxINCLUDES = -I/usr/local/include/cppunit/
	-rm -f $(OBJ)/*
	-rm -f $(BLD)/* 
	
dist: 
	git archive HEAD | gzip > $(BLD)/rx.$(BLD_VERSION).tar.gz

dist-gz: dist
