#
# Example Makefile for MSPPG C++ output
#
# Copyright (C) Simon D. Levy 2015
#
# This code is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as 
# published by the Free Software Foundation, either version 3 of the 
# License, or (at your option) any later version.
#
# This code is distributed in the hope that it will be useful,     
# but WITHOUT ANY WARRANTY without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License 
# along with this code.  If not, see <http:#www.gnu.org/licenses/>.

# Change this to match your desired install directory
INSTALL_ROOT = /usr/local

ALL = libmsppg.so example
CFLAGS = -Wall -fPIC -static

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	EXT = so
else
	EXT = dylib
endif

libmsppg.$(EXT): 
	g++ $(CFLAGS) -c MSPPG.cpp
	g++ *.o -o libmsppg.$(EXT) -lpthread -shared

install: libmsppg.so
	cp msppg/MSPPG.h $(INSTALL_ROOT)/include
	cp libmsppg.so $(INSTALL_ROOT)/lib

test: example
	./example
  
example: example.o msppg.o
	g++ -o example example.o msppg.o
  
example.o: example.cpp MSPPG.h
	g++ -Wall -c example.cpp
  
msppg.o: MSPPG.cpp MSPPG.h
	g++ -std=c++11 -Wall -c MSPPG.cpp

clean:
	rm -f *.so *.o *~
