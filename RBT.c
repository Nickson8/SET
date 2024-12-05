#include "RBT.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define PRETO 0;
#define VERMELHO 1;

typedef struct no_ NO_RB;
struct no_{
    int chave;
    NO_RB *f_esq;
    NO_RB *f_dir;
    int cor;
};

struct rbt {
    NO_RB *raiz;
};

RBT *rbt_criar (void) {
    RBT *T = malloc(sizeof(RBT));
    if (T == NULL) exit(-1);

    T->raiz = NULL;    
    return T;
}

NO_RB *cria_no(int chave){
    NO_RB *no = malloc(sizeof(NO_RB));
    if (no == NULL) exit(-1);
    no->chave = chave;
    no->cor = VERMELHO;
    no->f_dir = NULL;
    no->f_esq = NULL;

    return no;
}


NO_RB *rbt_insere_no(NO_RB *no, int chave) {
    if (no == NULL) {
        return cria_no(chave);
    }
    if (no->chave <= chave)
        rbt_insere_no(no->f_dir, chave);
    else
        rbt_insere_no(no->f_esq, chave);

    //fazer rotacoes/inversoes
}

bool rbt_inserir (RBT *T, int chave) {
    if (T == NULL) exit(-1);
    if (rbt_insere_no(T->raiz, chave) == NULL) 
        return false;
    return true;
}

void rbt_imprimir_aux(NO_RB *raiz){
    if (raiz == NULL) return;
    printf("%d ", raiz->chave);
    rbt_imprimir_aux(raiz->f_esq);
    rbt_imprimir_aux(raiz->f_dir);
}

void rbt_imprimir (RBT *T) {
    if (T != NULL) 
        rbt_imprimir_aux(T->raiz);
}

void rbt_libera(NO_RB **raiz) {
    if (*raiz != NULL) {
        rbt_libera(&(*raiz)->f_dir); //chamada recursiva para arvore da direita
        rbt_libera(&(*raiz)->f_esq); //chamada recursiva para arvore da esquerda
        (*raiz)->f_esq = NULL;
        (*raiz)->f_dir = NULL;

        free(*raiz); //libera a memoria
        *raiz = NULL;
    }
}
void rbt_apagar (RBT **T) {
    if (T != NULL) {
        rbt_libera(&(*T)->raiz);
        free(*T);
        *T = NULL;
    }
}

bool rbt_remover(RBT *T, int chave);  

bool rbt_buscar_no(NO_RB *raiz, int chave){
    if(raiz == NULL){
        return false;
    }
    else if(chave == raiz->chave) return true;
    else if(chave < raiz->chave) return rbt_buscar_no(raiz->f_esq, chave);
    else if(chave > raiz->chave) return rbt_buscar_no(raiz->f_dir, chave);
    
}

bool rbt_busca(RBT *T, int chave) {
    if (T == NULL) return false;
    return rbt_buscar_no(T->raiz, chave);
}

bool rbt_vazia(RBT *T) {
    if (T == NULL) return true; //evita acesso indevido de memoria
    if (T->raiz == NULL) return true;
    return false;
}


RBT *rbt_copiar(RBT *T);
RBT *rbt_uniao(RBT *A, RBT *B);
RBT *rbt_inter(RBT *A, RBT *B);