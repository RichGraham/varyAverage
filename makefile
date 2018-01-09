# simple make file
# September 2004
SOURCES=varyAverage.c 
PRODUCT=$(HOME)/bin/varyAverage



CC=gcc
CFLAGS=-lm -O2 -I$(NR)/include

all: $(PRODUCT)

$(PRODUCT) : $(SOURCES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(SOURCES)