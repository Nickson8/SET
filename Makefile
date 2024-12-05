all:
	gcc main.c set.c AVL.c RBT.c -o alg

clean:
	rm ./alg

run:
	./alg