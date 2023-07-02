TARGET= hset.out
CC= gcc
CFLAGS= -ansi -g -pedantic 
OBJS= hashSet.o hashSetTest.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
hashSet: hashSet.h hashSet.c 
	$(CC) $(CFLAGS) -c hashSet.c
	
hashSetTest.o: hashSetTest.c hashSet.h 
	$(CC) $(CFLAGS) -c hashSetTest.c
	
clean:
	rm -f $(TARGET) $(OBJS)

