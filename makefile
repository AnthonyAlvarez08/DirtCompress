CC = gcc
CFLAGS = -Wall -Wextra


all : main.o huffman.o
	$(CC) $(CFLAGS) $? -o dirtCompress

main.o : dirt_main.c
	$(CC) $(CFLAGS) -c $? -o $@

huffman.o : huffman.c
	$(CC) $(CFLAGS) -c $? -o $@

clean :
	rm *.o dirtCompress