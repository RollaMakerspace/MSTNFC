CC=g++
CFLAGS=-Wall -I /usr/local/include -I /home/kyler/projects/libraries -std=c++11
LFLAGS=-L /usr/local/lib -L /usr/lib -l nfc -l freefare

all: MSTNFC

MSTNFC: mstnfc.o
	$(CC) -shared -o MSTNFC.so mstnfc.o aes128key.o $(CFLAGS) $(LFLAGS)

aes128key.o: aes128key.cpp
	$(CC) -c aes128key.cpp $(CFLAGS)

mstnfc.o: aes128key.o
	$(CC) -c mstnfc.cpp $(CFLAGS)

clean:
	@rm -f *.o *.so