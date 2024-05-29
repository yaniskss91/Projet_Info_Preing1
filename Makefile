
all: CER_JO

CER_JO: main.o menu.o
	gcc -o CER_JO main.o menu.o -o CER_JO

main.o: main.c passerellejo.h
	gcc -c main.c -o main.o

menu.o: menu.c passerellejo.h
	gcc -c menu.c -o menu.o

clean:
	rm -f *.o
	rm -f CER_JO
