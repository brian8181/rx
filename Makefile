# MAKE TEMPLATE 6-02-2020

prefix = /usr/local
mandir = $(prefix)/share/man/
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11 -Wall
#LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = rx
EXT = .cpp
SRCDIR = ./
OBJDIR = ./

# clean & build & debug
# .PHONY: debuggdb_clean
# debuggdb_clean: clean debuggdb 

# complie & link for debug
debug: CXXFLAGS += -DDEBUG -g
debug: all

# complie & link for debug GDB
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: all

# complie & link
all: $(APPNAME)
	
# compile only
$(APPNAME): compile
	 #$(CXX) $(CXXFLAGS) $(OBJDIR)*.o -o $(SRCDIR)$(APPNAME)
	 $(CXX) $(CXXFLAGS) $(OBJDIR)*.o -o $(SRCDIR)$@
	 
compile:
	#$(CXX) $(CXXFLAGS) -c $(SRCDIR)*.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)*$(EXT)
	#$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# install man pages
.PHONY: man
man: 
	cp ./man/rx.1 $(man1dir)
	gzip $(man1dir)/rx.1
	mandb
	
# uninstall man pages
.PHONY: unman
unman:
	rm $(man1dir)/rx.1.gz
	mandb

.PHONY: install
install: man
	cp $(SRCDIR)$(APPNAME) $(prefix)/bin/$(APPNAME)

.PHONY: uninstall
uninstall: unman
	rm $(prefix)/bin/$(APPNAME)

# delete object files & app executable
.PHONY: clean
clean:
	rm -f $(OBJDIR)*.o $(SRCDIR)$(APPNAME)

.PHONY: distclean
distclean: clean # clean $ distclean are the same

dist: all
	git archive master | gzip > $(SRCDIR)$(APPNAME).latest.tar.gz
