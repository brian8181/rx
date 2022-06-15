# MAKE TEMPLATE 06-02-2020 1
# MAKE TEMPLATE 03-11-2021 1.1
# MAKE TEMPLATE 05-22-2021 1.2
# MAKE TEMPLATE 07-07-2021 1.3
# MAKE TEMPLATE 10-09-2021 1.4
# January 1, 2022 1.5

# RUN BEFORE autoreconf -ivfm
# RUN BEFORE autoreconf -i

MAKE_TEMPLATE = 1.6;
BUILD_VERSION = 0.1.1

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -std=c++11 -std=gnu++17
CXXFLAGS += -DDEBUG -ggdb -fPIC

# lib settings
LDFLAGS = -static -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/
# add addtional libs here

# Makefile settings - Can be customized.
APPNAME = rx
EXT = cpp

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
# one up from build directory
ROOT  = /home/brian/src/rx
SRCS = $(ROOT)/src
BUILD = $(ROOT)/build
OBJS = $(ROOT)/build

# compile & link for debug
#debug: CXXFLAGS += -DDEBUG -g
debug: all

# compile & link for debug GDBversion variable
debuggdb: all

# compile & link
all: $(APPNAME) $(APPNAME)_test bash_color_test
	@echo "MAKE PATH:" $(mkfile_path)
	

# link
$(APPNAME): $(APPNAME).o main.o
	@echo "MAKE PATH:" $(mkfile_path)
	$(CXX) $(CXXFLAGS) $(OBJS)/$(APPNAME).o $(OBJS)/main.o -o $(BUILD)/$(APPNAME)
	
# compile only
$(APPNAME).o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/$(APPNAME).$(EXT) -o $(OBJS)/$(APPNAME).o
	
main.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/main.$(EXT) -o $(OBJS)/main.o

# link
$(APPNAME)_test: $(APPNAME)_test.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS)/$(APPNAME)_test.o $(OBJS)/$(APPNAME).o $(LDFLAGS) -o $(BUILD)/$(APPNAME)_test

# compile only
$(APPNAME)_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/$(APPNAME)_test.cpp -o $(OBJS)/$(APPNAME)_test.o

bash_color_test: bash_color_test.o
	$(CXX) $(CXXFLAGS) $(OBJS)/bash_color_test.o -o $(BUILD)/bash_color_test

bash_color_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCS)/bash_color_test.cpp -o $(OBJS)/bash_color_test.o

# install man pages
.PHONY: man
man:
	cp ../man/$(APPNAME).1 $(man1dir)
	# gzip $(man1dir)/$(APPNAME).1
	mandb
	
# uninstall man pages
.PHONY: unman
unman:
	rm $(man1dir)/$(APPNAME).1.gz
	mandb

# install 
.PHONY: install
install: man
	cp $(BUILD)/$(APPNAME) $(prefix)/bin/$(APPNAME)

# uninstall
.PHONY: uninstall
uninstall: unman
	rm $(prefix)/bin/$(APPNAME)

# delete object files & app executable
.PHONY: clean
clean:
	rm -f $(BUILD)/$(APPNAME) $(OBJS)/*.o $(BUILD)/$(APPNAME)_test $(BUILD)/bash_color_test
	rm -f $(BUILD)/*.xml $(BUILD)/$(APPNAME).$(BUILD_VERSION).tar.gz
	rm -f $(BUILD)/$(APPNAME).core

# delete object files, app, executables, & all automake/autoconf generated files
.PHONY: distclean
distclean: clean
	rm -f $(ROOT)/config.* $(ROOT)/Makefile $(ROOT)/Makefile.in $(ROOT)/INSTALL $(ROOT)/configure 
	rm $(ROOT)/stamp-h1 $(ROOT)/aclocal.m4 $(ROOT)/compile $(ROOT)/install-sh $(ROOT)/libtool $(ROOT)/ltmain.sh $(ROOT)/stamp-h1 $(ROOT)/missing $(ROOT)/depcomp
	rm $(SRCS)/Makefile $(SRCS)/Makefile.in
	rm -rf $(ROOT)/autom4te.cache $(SRCS)/.deps $(SRCS)/.libs

clean-local:
	rm config.status configure config.log
	rm Makefile
	rm -r autom4te.cache/
	rm aclocal.m4
	rm compile install-sh missing Makefile.in
	
dist: 
	git archive HEAD | gzip > $(BUILD)/$(APPNAME).$(BUILD_VERSION).tar.gz

dist-gz: dist
