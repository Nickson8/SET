#include "stdlib.h"
#include "stdio.h"
#include "set.h"

struct set{
    int tipo;
    AVL *avl;
    RBT *rbt;
};

SET *set_criar(unsigned char tipo){
    SET *set = (SET*) malloc(sizeof(SET));
    if(set != NULL){
        set->tipo = tipo;
        if(tipo == 0) set->avl = avl_criar();
        // if(tipo == 1) set->rbt = rbt_criar();
    }

    return set;
}
bool set_pertence(SET *A, int elemento){
    if(A == NULL) return false;
    if(A->tipo == 0) return avl_busca(A->avl, elemento);
    // if(A->tipo == 1) return rbt_busca(A->rbt, elemento);
}
bool set_inserir (SET *s, int elemento){
    if(s == NULL) return false;
    if(s->tipo == 0) return avl_inserir(s->avl, elemento);
    // if(s->tipo == 1) return rbt_inserir(s->rbt, elemento);
}
bool set_remover(SET *s, int elemento){
    if(s == NULL) return false;
    if(s->tipo == 0) return avl_remover(s->avl, elemento);
    // if(s->tipo == 1) return rbt_remover(s->rbt, elemento);
}
void set_apagar(SET **s){
    if(*s == NULL) return;
    if((*s)->tipo == 0) return avl_apagar(&((*s)->avl));
    // if((*s)->tipo == 1) return rbt_apagar(&((*s)->rbt));
}
void set_imprimir(SET *s){
    if(s == NULL) return;
    if(s->tipo == 0) return avl_imprimir(s->avl);
    // if(s->tipo == 1) return rbt_imprimir(s->rbt);
}
SET *set_uniao(SET *A, SET *B){
    SET *C = (SET*) set_criar(A->tipo);
    if(A->tipo == 0){
        C->avl = avl_uniao(A->avl, B->avl);
    }
    if(A->tipo == 1){
        // C->rbt = rbt_uniao(A->rbt, B->rbt);
    }

    return C;
}
SET *set_interseccao(SET *A, SET *B){
    SET *C = (SET*) set_criar(A->tipo);
    if(A->tipo == 0){
        C->avl = avl_inter(A->avl, B->avl);
    }
    if(A->tipo == 1){
        // C->rbt = rbt_inter(A->rbt, B->rbt);
    }

    return C;
}