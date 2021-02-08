CC=gcc
CFLAGS=-I. -ansi -pedantic -Wall -std=c99
# makes sure we are using standard c rules talked about at the end of rec 1

COM=$(CC) $(CFLAGS)
# general use command for compilation
# maps to the compiler code and flags listed above

DEP=Project1.o tokenlist.o EnvVariables.o Echo.o Prompt.o Path.o \
		CommandExe.o CD.o Piping.o BackgroundProcess.o jobStruct.o jobVector.o tokenlist2d.o

# to reference our dependency list throughout the shell command

all: shell

shell: $(DEP)
	$(COM) -o shell $(DEP)

Project1.o: Project1.c
	$(COM) -c Project1.c

BackgroundProcess.o: BackgroundProcess.c BackgroundProcess.h
	$(COM) -c BackgroundProcess.c

jobStruct.o: jobStruct.c jobStruct.h
	$(COM) -c jobStruct.c

jobVector.o: jobVector.c jobVector.h
	$(COM) -c jobVector.c

tokenlist.o: tokenlist.c tokenlist.h
	$(COM) -c tokenlist.c

tokenlist2d.o: tokenlist2d.c tokenlist2d.h
	$(COM) -c tokenlist2d.c

EnvVariables.o: EnvVariables.c EnvVariables.h
	$(COM) -c EnvVariables.c

Echo.o: Echo.c Echo.h
	$(COM) -c Echo.c

Prompt.o: Prompt.c Prompt.h
	$(COM) -c Prompt.c

Path.o: Path.c Path.h
	$(COM) -c Path.c

CommandExe.o: CommandExe.c CommandExe.h
	$(COM) -c CommandExe.c

CD.o: CD.c CD.h
	$(COM) -c CD.c

Piping.o: Piping.c Piping.h
	$(COM) -c Piping.c

clean:
	rm *.o shell
