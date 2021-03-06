# MAKE TEMPLATE 06-02-2020 1
# MAKE TEMPLATE 03-11-2021 1.1
# MAKE TEMPLATE 05-22-2021 1.2
# MAKE TEMPLATE 07-07-2021 1.3

# RUN BEFORE autoreconf -ivfm
# RUN BEFORE autoreconf -i

MAKE_TEMPLATE = 1.3;
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
ROOTDIR  = ~/src/rx
BUILDDIR = ~/src/rx/build
SRCDIR = ~/src/rx/src
OBJDIR = ~/src/rx/build

# compile & link for debug
debug: CXXFLAGS += -DDEBUG -g
debug: all

# compile & link for debug GDBversion variable
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: all

# compile & link
all: $(APPNAME) $(APPNAME)_test bash_color_test

# link
$(APPNAME): $(APPNAME).o main.o OptionParser.o
	 $(CXX) $(CXXFLAGS) $(BUILDDIR)/$(APPNAME).o $(BUILDDIR)/main.o $(BUILDDIR)/OptionParser.o -o $(BUILDDIR)/$(APPNAME)

# compile only
$(APPNAME).o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/$(APPNAME).$(EXT)  -o $(BUILDDIR)/$(APPNAME).o
	
main.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.$(EXT) -o $(BUILDDIR)/main.o

OptionParser.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/OptionParser.$(EXT) -o $(BUILDDIR)/OptionParser.o
	
# link
$(APPNAME)_test: $(APPNAME)_test.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BUILDDIR)/$(APPNAME)_test.o $(BUILDDIR)/$(APPNAME).o $(LDFLAGS) -o $(BUILDDIR)/$(APPNAME)_test

# compile only
$(APPNAME)_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/$(APPNAME)_test.cpp -o $(BUILDDIR)/$(APPNAME)_test.o

bash_color_test: bash_color_test.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/bash_color_test.o -o $(BUILDDIR)/bash_color_test

bash_color_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/bash_color_test.cpp -o $(BUILDDIR)/bash_color_test.o

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
	rm -f $(BUILDDIR)/$(APPNAME) $(BUILDDIR)/*.o $(BUILDDIR)/$(APPNAME)_test $(BUILDDIR)/bash_color_test
	rm -f $(BUILDDIR)/*.xml $(BUILDDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz

# delete all auto generated files
.PHONY: distclean
distclean: clean
	rm -f $(SRCDIR)/config.* $(SRCDIR)/Makefile $(SRCDIR)/Makefile.in $(SRCDIR)/INSTALL $(SRCDIR)/configure 
	# rm ../stamp-h1 ../aclocal.m4 ../compile ../install-sh ../libtool ../ltmain.sh ../stamp-h1 ../missing ../depcomp
	# rm ../src/Makefile ../src/Makefile.in
	# rm -rf ../autom4te.cache ../src/.deps ../src/.libs
	# rm ../src/.o

dist: 
	git archive HEAD | gzip > $(BUILDDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz

dist-gz: dist
