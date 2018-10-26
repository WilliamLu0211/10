all: randfile.o
	gcc randfile.o

randfile.o: randfile.c
	gcc -c randfile.c

run:
	./a.out

clean:
	rm *.o *.txt
