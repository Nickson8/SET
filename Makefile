OBJ_DIR = obj
TAD_DIR = TADs
TEST_DIR = casosTeste

all: $(OBJ_DIR) $(OBJ_DIR)/AVL.o $(OBJ_DIR)/RBT.o $(OBJ_DIR)/set.o $(OBJ_DIR)/main.o
	gcc $(OBJ_DIR)/AVL.o $(OBJ_DIR)/RBT.o $(OBJ_DIR)/set.o $(OBJ_DIR)/main.o -o alg -std=c99 -Wall 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/AVL.o: $(TAD_DIR)/AVL.c $(TAD_DIR)/AVL.h
	gcc -c $(TAD_DIR)/AVL.c -o $(OBJ_DIR)/AVL.o

$(OBJ_DIR)/RBT.o: $(TAD_DIR)/RBT.c $(TAD_DIR)/RBT.h
	gcc -c $(TAD_DIR)/RBT.c -o $(OBJ_DIR)/RBT.o

$(OBJ_DIR)/set.o: $(TAD_DIR)/set.c $(TAD_DIR)/set.h
	gcc -c $(TAD_DIR)/set.c -o $(OBJ_DIR)/set.o

$(OBJ_DIR)/main.o: main.c $(TAD_DIR)/AVL.h $(TAD_DIR)/RBT.h $(TAD_DIR)/set.h
	gcc -c main.c -o $(OBJ_DIR)/main.o

run:
	./alg

zip:
	zip FelipeCerri_NicolasMaia Makefile relatorio.txt *.c $(TAD_DIR)/*.c $(TAD_DIR)/*.h $(TEST_DIR)/*.in $(TEST_DIR)/*.out

clean:
	rm -rf $(OBJ_DIR) *.zip alg
