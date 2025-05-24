# File Name:  $(APP)/makefile
# Build Date: Mon Mar  4 09:11:39 AM CST 2024
# Version:    0.1.0
APP=rx
CXX=g++
CXXFLAGS=-Wall -std=c++20 -Wno-vla -fPIC
SRC?=src
BLD?=build
OBJ?=build
PREFIX=/usr/local

# lib settings
LIBS = -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/
LDFLAGS = $(LIBS) $(INCLUDES) -static -lcppunit

ifdef DEBUG
	CXXFLAGS +=-g -DDEBUG
endif

ifdef CYGWIN
	CXXFLAGS += -DCYGWIN
endif

all: $(BLD)/$(APP) $(BLD)/$(APP)2 $(BLD)/$(APP)_test $(BLD)/lib$(APP).so $(BLD)/lib$(APP).a

.PHONY: rebuild
rebuild: clean all

$(BLD)/$(APP): $(OBJ)/$(APP).o $(OBJ)/main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/$(APP).o $(OBJ)/main.o -o $(BLD)/$(APP)

$(BLD)/$(APP)2: $(BLD)/lib$(APP).so main.cpp
	$(CXX) $(CXXFLAGS) $(BLD)/lib$(APP).so $(OBJ)/main.o -o $(BLD)/$(APP)2

$(BLD)/$(APP)_test: $(OBJ)/$(APP).o $(OBJ)/$(APP)_test.o
	$(CXX) $(CXXFLAGS) $(OBJ)/$(APP).o $(OBJ)/$(APP)_test.o -lcppunit -o $(BLD)/$(APP)_test

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BLD)/lib$(APP).so: $(BLD)/$(APP).o
	$(CXX) $(CXXFLAGS) -fPIC --shared $(OBJ)/$(APP).o -o $(BLD)/lib$(APP).so
	chmod 755 $(BLD)/lib$(APP).so

$(BLD)/lib$(APP).a: $(BLD)/$(APP).o
	ar rvs $(BLD)/lib$(APP).a $(OBJ)/$(APP).o
	chmod 755 $(BLD)/lib$(APP).a

.PHONY: install
install:
	cp $(BLD)/$(APP) $(prefix)/bin/$(APP)

.PHONY: uninstall
uninstall:
	-rm $(prefix)/bin/$(APP)

.PHONY: clean
clean:
	-rm -f $(OBJ)/*.o
	-rm -f $(BLD)/*.o
	-rm -f $(BLD)/$(APP)*

.PHONY: help
help:
	@echo  '  all           - build all'
	@echo  '  $(APP)            - build $(APP) executable'
	@echo  '  $(APP).o          - build not link'
	@echo  '  $(APP)_test       - build cppunit test'
	@echo  '  $(APP)_test.o     - build cppunit test'
	@echo  '  clean         - remove all files from build dir'
	@echo  '  install       - copy files to usr/local'
	@echo  '  dist          - create distribution, tar.gz'
	@echo  '  install       - copy files to usr/local'
	@echo  '  dist          - create distribution, tar.gz'
