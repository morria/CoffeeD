###########################################
# Simple Makefile for HIDAPI test program
#
# Alan Ott
# Signal 11 Software
# 2010-07-03
###########################################

all: coffeed

CC=gcc
CXX=g++
COBJS=hid.o coffeed.o
CPPOBJS=
OBJS=$(COBJS) $(CPPOBJS)
CFLAGS+=-Wall -g -c 
LIBS=-framework IOKit -framework CoreFoundation

coffeed: $(OBJS)
	g++ -Wall -g $^ $(LIBS) -o coffeed

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f *.o coffeed $(CPPOBJS)

.PHONY: clean
