# June 17, 2022
# MAKE_TEMPLATE = 1.6;
# BUILD_VERSION = 0.1.1

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CC = $(CXX)

DEBUG_LEVEL      = -DDEBUG -ggdb
EXTRA_CXXFLAGS   = -Wall -std=c++11 -std=gnu++17
CXXFLAGS = $(EXTRA_CXXFLAGS) $(DEBUG_LEVEL)

# lib settings
LDFLAGS = -static -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/

# Makefile settings - Can be customized.
APPNAME = rx
EXT = cpp

# mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
# current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

ROOT  = .
SRCS = ./src
BUILD = ./build
OBJS = ./build

# compile & link for debug
#debug: CXXFLAGS += -DDEBUG -g
debug: all

# compile & link for debug GDBversion variable
debuggdb: all

# compile & link
all: $(APPNAME) $(APPNAME)_test bash_color_test

# link
$(APPNAME): $(APPNAME).o main.o
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
	gzip $(man1dir)/$(APPNAME).1
	mandb

# uninstall man pages
.PHONY: unman
unman:
	rm $(man1dir)/$(APPNAME).1.gz
	mandb

# install
.PHONY: install
install: #man # no man for now
	cp $(BUILD)/$(APPNAME) $(prefix)/bin/$(APPNAME)

# uninstall
.PHONY: uninstall
uninstall: unman
	rm $(prefix)/bin/$(APPNAME)
# delete object files & app executable
.PHONY: clean
clean:
	-rm -f $(OBJS)/*.o
	-rm -f $(BUILD)/$(APPNAME)
	-rm -f $(BUILD)/$(APPNAME)_test
	-rm -f $(BUILD)/bash_color_test
	-rm -f $(BUILD)/*.xml $(BUILD)/$(APPNAME).$(BUILD_VERSION).tar.gz
	-rm -f $(BUILD)/$(APPNAME).core

# delete object files, app, executables, & all automake/autoconf generated files
.PHONY: distclean
distclean: clean
	-rm -f $(ROOT)/config.* $(ROOT)/Makefile $(ROOT)/Makefile.in $(ROOT)/INSTALL $(ROOT)/configure
	-rm -f $(ROOT)/stamp-h1 $(ROOT)/aclocal.m4 $(ROOT)/compile $(ROOT)/install-sh $(ROOT)/libtool $(ROOT)/ltmain.sh $(ROOT)/stamp-h1 $(ROOT)/missing $(ROOT)/depcomp
	-rm -f $(SRCS)/Makefile $(SRCS)/Makefile.in
	-rm -rf $(ROOT)/autom4te.cache $(SRCS)/.deps $(SRCS)/.libs

clean-local:
	-rm -f config.status configure config.log
	-rm -rf autom4te.cache/
	-rm =-f aclocal.m4
	-rm -f compile install-sh missing Makefile.in

dist:
	git archive HEAD | gzip > $(BUILD)/$(APPNAME).$(BUILD_VERSION).tar.gz

dist-gz: dist

.PHONY: help
help:
	@echo  '  all         - build all'
	@echo  '  rx          - build rx executable'
	@echho '  rx.o        - build not link'
	@echo  '  clean		  - remove most generated files but keep the config'
	@echo  '  install     - copy files to usr/local'
	@echo  '  dist        - create distribution, tar.gz'
