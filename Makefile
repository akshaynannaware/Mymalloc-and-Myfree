$(CC) = gcc
all:
	$(CC) Linked_List.c -o LL
	
Clean:
	rm *.o LL
