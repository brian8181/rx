# Wed Nov  8 08:33:47 AM CST 2023
# June 17, 2022

CXX = g++
CXXFLAGS = -Wall -std=c++11 -DDEBUG -ggdb
LDFLAGS = -static -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/
APPNAME = rx
EXT = cpp
ROOT  = .
SRCS = src
BUILD = build
OBJS = build

all: rx

debug: all

rebuild: clean all
	
rx: rx.o main.o
	$(CXX) $(CXXFLAGS) $(OBJS)/rx.o $(OBJS)/main.o -o $(BUILD)/rx

main.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/main.cpp -o $(OBJS)/main.o

rx.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/rx.cpp -o $(OBJS)/rx.o

rx_test: rx_test.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS)/rx_test.o $(OBJS)/rx.o $(LDFLAGS) -o $(BUILD)/rx_test

rx_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/rx_test.cpp -o $(OBJS)/rx_test.o

bash_color_test: bash_color_test.o
	$(CXX) $(CXXFLAGS) $(OBJS)/bash_color_test.o -o $(BUILD)/bash_color_test

bash_color_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/bash_color_test.cpp -o $(OBJS)/bash_color_test.o

# uninstall man pages
.PHONY: unman
unman:
	rm $(man1dir)/rx.1.gz
	mandb

# install 
.PHONY: install
install: #man # no man for now
	cp $(BUILD)/rx $(prefix)/bin/rx

# uninstall
.PHONY: uninstall
uninstall: unman
	rm $(prefix)/bin/rx

# clean
.PHONY: clean
clean:
	-rm -f $(OBJS)/*.o 
	-rm -f $(BUILD)/rx 
	-rm -f $(BUILD)/rx_test 
	-rm -f $(BUILD)/bash_color_test
	-rm -f $(BUILD)/*.xml $(BUILD)/rx.$(BUILD_VERSION).tar.gz
	-rm -f $(BUILD)/rx.core

# delete object files, app, executables, & all automake/autoconf generated files
.PHONY: distclean
distclean: clean
	-rm -f $(ROOT)/config.* $(ROOT)/Makefile $(ROOT)/Makefile.in $(ROOT)/INSTALL $(ROOT)/configure 
	-rm -f $(ROOT)/stamp-h1 $(ROOT)/aclocal.m4 $(ROOT)/compile 

clean-local:
	-rm -f config.status configure config.log
	-rm -rf autom4te.cache/
	-rm =-f aclocal.m4
	-rm -f compile install-sh missing Makefile.in
	
dist: 
	git archive HEAD | gzip > $(BUILD)/rx.$(BUILD_VERSION).tar.gz

dist-gz: dist
