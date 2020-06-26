# MAKE TEMPLATE 6-02-2020
BUILD_VERSION = 0.1.0

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11 
LDFLAGS = -static -lcppunit -L/usr/local/lib/
# INCLUDES= -I/usr/local/include/cppunit/
# LINKFLAGS= --static

# Makefile settings - Can be customized.
APPNAME = rx
EXT = cpp
SRCDIR = ./src
OBJDIR = ./src

# complie & link for debug
debug: CXXFLAGS += -DDEBUG -g
debug: all

# complie & link for debug GDBversion variable
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: all
  
# complie & link
all: $(APPNAME) rx_test
	
# compile only
$(APPNAME): rx.o main.o
	 $(CXX) $(CXXFLAGS) $(OBJDIR)/rx.o $(OBJDIR)/main.o -o $(SRCDIR)/$(APPNAME)
	 #$(CXX) $(CXXFLAGS) rx.o main.o -o $(SRCDIR)/$@

rx.o main.o:
	#$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/rx.$(EXT) -o $(SRCDIR)/rx.o
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.$(EXT) -o $(SRCDIR)/main.o

rx_test: rx_test.o
	$(CXX) $(CXXFLAGS) $(SRCDIR)/rx_test.o $(SRCDIR)/rx.o $(LDFLAGS) -o $(SRCDIR)/rx_test

rx_test.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/rx_test.cpp -o $(SRCDIR)/rx_test.o

.PHONY: check
check:
	echo "Checking ..."

# install man pages
.PHONY: man
man: 
	cp ./man/rx.1 $(man1dir)
	gzip $(man1dir)/rx.1
	mandb
	
# uninstall man pages
.PHONY: unmanversion variable
unman:
	rm $(man1dir)/rx.1.gz
	mandb

.PHONY: install
install: man
	cp $(SRCDIR)/$(APPNAME) $(prefix)/bin/$(APPNAME)

.PHONY: uninstall
uninstall: unman
	rm $(prefix)/bin/$(APPNAME)

# delete object files & app executable
.PHONY: clean
clean: distclean
	rm configure compile depcomp install-sh

.PHONY: distclean
distclean: 
	rm -f config.log config.status config.h* \
	*/Makefile.in $(OBJDIR)/*.o $(SRCDIR)/*.xml $(SRCDIR)/$(APPNAME) $(SRCDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz $(SRCDIR)/rx_test

dist: 
	git archive HEAD | gzip > $(SRCDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz
	#git archive --output=./$(SRCDIR)$(APPNAME).$(BUILD_VERSION).tar.gz --format=tar HEAD 

dist-gz: dist
