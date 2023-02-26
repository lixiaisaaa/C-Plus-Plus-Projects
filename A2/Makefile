CC = g++
CFLAGS = -Wall -std=c++11
LIBHARU = ./libharu

spiralPDF: spiralPDF.o Spiral.o HaruPDF.o
	$(CC) $(CFLAGS) -I$(LIBHARU)/include -o spiralPDF spiralPDF.o Spiral.o HaruPDF.o -L$(LIBHARU)/src -lhpdfs

Spiral.o: Spiral.cpp Spiral.h 
	$(CC) $(CFLAGS) -c Spiral.cpp -L$(LIBHARU)/src -lhpdfs

HaruPDF.o: HaruPDF.cpp HaruPDF.h 
	$(CC) $(CFLAGS) -I$(LIBHARU)/include -c HaruPDF.cpp -L$(LIBHARU)/src -lhpdfs

spiralPDF.o: spiralPDF.cpp
	$(CC) $(CFLAGS) -I$(LIBHARU)/include -c spiralPDF.cpp -L$(LIBHARU)/src -lhpdfs

test: spiralPDF
	./spiralPDF "This is my sample text"

clean: 
	Irm spiralPDF *.o