CC = gcc
CFLAGS = -Wall -Wextra -g


#===========================BINARIES============================

all : main.o huffman.o zip.o unzip.o terminalio.o list.o binary_tree.o
	$(CC) $(CFLAGS) $? -o dirt.out

huffman_test: huffman_test.o huffman.o terminalio.o list.o binary_tree.o
	$(CC) $(CFLAGS) $? -o huffman_test.out

export_build : main.o huffman.o zip.o unzip.o terminalio.o list.o binary_tree.o
	$(CC) $(CFLAGS) $? -o dirt


#=============================OBJECT FILES=======================

main.o : dirt_main.c
	$(CC) $(CFLAGS) -c $? -o $@

huffman_test.o: tests/huffman_test.c
	$(CC) $(CFLAGS) -c $? -o $@

huffman.o : huffman.c
	$(CC) $(CFLAGS) -c $? -o $@

zip.o : zip.c
	$(CC) $(CFLAGS) -c $? -o $@

unzip.o : unzip.c
	$(CC) $(CFLAGS) -c $? -o $@

terminalio.o : terminalio.c
	$(CC) $(CFLAGS) -c $? -o $@

list.o : ./datastructures/list.c
	$(CC) $(CFLAGS) -c $? -o $@

binary_tree.o : ./datastructures/binary_tree.c
	$(CC) $(CFLAGS) -c $? -o $@

clean :
	rm *.o *.out dirt