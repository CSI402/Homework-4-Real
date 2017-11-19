CC =gcc
CFLAGS =-Wall
OBJECTS =  main.c BSTFunctions.c

firstpass: $(OBJECTS)
        $(CC) $(CFLAGS) $(OBJECTS) -o firstpass
main.o: main.c
        $(CC) $(CFLAGS) -c main.c
%.o: %.c
        $(CC) $(CFLAGS) -c $<
clean:
        rm firstpass

