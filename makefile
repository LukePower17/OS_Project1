shell: Project1.o Echo.o
	gcc -o shell Project1.o Echo.o

Project1.o: Project1.o Echo.o
	gcc -c -std=c99 Project1.c

Echo.o: Echo.c Echo.h
	gcc -c -std=c99 Echo.c

clean:
	rm *.o *.x


#please include  -std=c99		for all files
