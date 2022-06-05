tmcp: chunk.o main.o memory.o debug.o value.o vm.o
	gcc chunk.o main.o memory.o debug.o value.o vm.o -o tmcp
	rm *.o

chunk.o: chunk.h chunk.c
	gcc -c chunk.c
main.o: main.c
	gcc -c main.c
memory.o: memory.c memory.h
	gcc -c memory.c
debug.o: debug.c debug.h
	gcc -c debug.c
value.o: value.c value.h
	gcc -c value.c
vm.o: vm.c vm.h
	gcc -c vm.c