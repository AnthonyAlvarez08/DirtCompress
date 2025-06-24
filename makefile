CC = clang
CFLAGS = -Wall -Wextra


all : main.o huffman.o zip.o unzip.o terminalio.o list.o binary_tree.o
	$(CC) $(CFLAGS) $? -o dirt

main.o : dirt_main.c
	$(CC) $(CFLAGS) -c $? -o $@

huffman.o : huffman.c
	$(CC) $(CFLAGS) -c $? -o $@

zip.o : zip.c
	$(CC) $(CFLAGS) -c $? -o $@

unzip.o : unzip.c
	$(CC) $(CFLAGS) -c $? -o $@

terminalio.o : terminalio.c
	$(CC) $(CFLAGS) -c $? -o $@

list.o : datastuctures/list.c
	$(CC) $(CFLAGS) -c $? -o $@

binary_tree.o : datastuctures/binary_tree.c
	$(CC) $(CFLAGS) -c $? -o $@

clean :
	rm *.o dirt