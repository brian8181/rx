# MAKE TEMPLATE 6-02-2020
BUILD_VERSION = 1.0.0

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11 -Wall
# LDFLAGS = -lcppunit -L/usr/local/lib/
# INCLUDES= -I/usr/local/include/cppunit/
# LINKFLAGS= --static

# Makefile settings - Can be customized.
APPNAME = rx
EXT = cpp
SRCDIR = .
OBJDIR = .

# complie & link for debug
debug: CXXFLAGS += -DDEBUG -g
debug: all

# complie & link for debug GDBversion variable
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: all

# complie & link
all: $(APPNAME) rx_test
	
# compile only
$(APPNAME): compile
	 #$(CXX) $(CXXFLAGS) $(OBJDIR)*.o -o $(SRCDIR)/$(APPNAME)
	 $(CXX) $(CXXFLAGS) rx.o -o $(SRCDIR)/$@

compile:
	#$(CXX) $(CXXFLAGS) -c $(SRCDIR)/*.cpp
	#$(CXX) $(CXXFLAGS) -c $(SRCDIR)/*.$(EXT)
	#$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	$(CXX) $(CXXFLAGS) -c rx.$(EXT)

rx_test: 
	$(CXX) $(CXXFLAGS) -c rx_test.cpp -I/usr/local/include/cppunit/ 
	$(CXX) $(CXXFLAGS) -static rx_test.o -lcppunit -L/usr/local/lib/ -o rx_test

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
clean:
	rm -f $(OBJDIR)*.o $(SRCDIR)/*.xml $(SRCDIR)/$(APPNAME) $(SRCDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz rx_test

.PHONY: distclean
distclean: clean # clean $ distclean are the same

dist: 
	git archive HEAD | gzip > $(SRCDIR)/$(APPNAME).$(BUILD_VERSION).tar.gz
	#git archive --output=./$(SRCDIR)$(APPNAME).$(BUILD_VERSION).tar.gz --format=tar HEAD 

dist-gz: dist
