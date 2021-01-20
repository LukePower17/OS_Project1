all: shell

shell:
	gcc -o shell Project1.c EnvVariables.c Echo.c Prompt.c -std=c99

clean:
	rm shell
