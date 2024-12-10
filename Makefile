all:
	gcc main.c set.c AVL.c RBT.c -o alg -std=c99 -Wall

clean:
	rm ./alg

run:
	./alg

faz:
	make clean; make; ./alg < casosTeste/3.in

zip:
	zip files.zip *.c *.h Makefile relatorio.txt