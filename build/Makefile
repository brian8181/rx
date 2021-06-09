# MAKE TEMPLATE 06-02-2020 1
# MAKE TEMPLATE 03-11-2021 1.1
# MAKE TEMPLATE 05-22-2021 1.2
MAKE_TEMPLATE = 1.2;
# RUN BEFORE autoreconf -ivfm
BUILD_VERSION = 0.1.0

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -std=c++11

# lib settings
LDFLAGS = -static -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/
# add addtional libs here

# Makefile settings - Can be customized.
APPNAME = rx
EXT = cpp
BUILDDIR = ~/src/rx/build
SRCDIR = ~/src/rx/src
OBJDIR = ~/src/rx/build

# complie & link for debug
debug: CXXFLAGS += -DDEBUG -g
debug: all

# complie & link for debug GDBversion variable
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: all

# complie & link
all: $(APPNAME) $(APPNAME)_test

# complie & link
$(APPNAME): $(APPNAME).o 
	 $(CXX) $(CXXFLAGS) $(BUILDDIR)/$(APPNAME).o $(BUILDDIR)/main.o -o $(BUILDDIR)/$(APPNAME)

# complie only
$(APPNAME).o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/$(APPNAME).$(EXT) -o $(BUILDDIR)/$(APPNAME).o
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.$(EXT) -o $(BUILDDIR)/main.o
	
# complie & link
$(APPNAME)_test: $(APPNAME)_test.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BUILDDIR)/$(APPNAME)_test.o $(BUILDDIR)/$(APPNAME).o $(LDFLAGS) -o $(BUILDDIR)/$(APPNAME)_test

# complie only
$(APPNAME)_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/$(APPNAME)_test.cpp -o $(BUILDDIR)/$(APPNAME)_test.o

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
	cp $(BUILDDIR)/$(APPNAME) $(prefix)/bin/$(APPNAME)

# uninstall
.PHONY: uninstall
uninstall: unman
	rm $(prefix)/bin/$(APPNAME)

# delete object files & app executable
.PHONY: clean
clean:
	rm -f $(BUILDDIR)/$(APPNAME) $(BUILDDIR)/*.o $(BUILDDIR)/*.xml $(BUILDDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz $(BUILDDIR)/$(APPNAME)_test

# delete all auto generated files
.PHONY: distclean
distclean: clean
	rm ../config.* ../Makefile ../Makefile.in ../INSTALL ../configure ../stamp-h1 ../aclocal.m4

dist: 
	git archive HEAD | gzip > $(BUILDDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz

dist-gz: dist
