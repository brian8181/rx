# MAKE TEMPLATE 5-12-2020

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = rx
# EXT = .cpp
SRCDIR = ./
# OBJDIR = .

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
	 $(CXX) $(CXXFLAGS) *.o -o $(SRCDIR)$(APPNAME)

compile:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)*.cpp

# # Builds the app
# $(APPNAME): $(OBJ)
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: install
install: $(APPNAME)
	cp $(SRCDIR)$(APPNAME) /usr/local/bin/$(APPNAME)

.PHONY: uninstall
uninstall: 
	rm /usr/local/bin/$(APPNAME)

# delete object files & app executable
.PHONY: clean
clean:
	rm -f *.o $(SRCDIR)$(APPNAME)

archive: all
	git archive master | gzip > $(SRCDIR)$(APPNAME).latest.tgz
