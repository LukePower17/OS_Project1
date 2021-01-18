shell: Project1.o Echo.o 
	gcc -o shell Project1.o Echo.o

Project1.o: Project1.o Echo.o
	gcc -c Project1.c

Echo.o: Echo.c Echo.h
	gcc -c Echo.c