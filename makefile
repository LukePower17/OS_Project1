all: shell

shell:
	gcc -o shell Project1.c tokenlist.c EnvVariables.c Echo.c Prompt.c Path.c CommandExe.c CD.c -std=c99

clean:
	rm shell *.o
