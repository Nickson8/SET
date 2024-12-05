#include "RBT.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define PRETO 0
#define VERMELHO 1

typedef struct no NO;
struct no{
    int chave;
    NO *f_esq;
    NO *f_dir;
    int cor;
};

struct rbt {
    NO *raiz;
};

RBT *rbt_criar (void) {
    RBT *T = malloc(sizeof(RBT));
    if (T == NULL) exit(-1);

    T->raiz = NULL;    
    return T;
}

NO *cria_no(int chave){
    NO *no = malloc(sizeof(NO));
    if (no == NULL) exit(-1);
    no->chave = chave;
    no->cor = VERMELHO;
    no->f_dir = NULL;
    no->f_esq = NULL;

    return no;
}

void rodar_esq(NO *a) {
    NO *b = a->f_dir;

    a->f_dir = b->f_esq;
    b->f_esq = a;
}
void rodar_dir(NO *a) {
    NO *b = a->f_esq;

    a->f_esq = b->f_dir;
    b->f_dir = a;
}

void inverte(NO *raiz) {
    raiz->cor = !raiz->cor;
    if (raiz->f_dir != NULL)
        raiz->f_dir->cor = !raiz->f_dir->cor;
    if (raiz->f_esq != NULL)
        raiz->f_esq->cor = !raiz->f_esq->cor;
}

bool cor(NO *raiz) {
    if (raiz == NULL) 
        return 0;
    return raiz->cor;
}

NO *rbt_insere_no(NO *no, int chave) {
    if (no == NULL) {
        return cria_no(chave);
    }
    if (no->chave <= chave)
        rbt_insere_no(no->f_dir, chave);
    else
        rbt_insere_no(no->f_esq, chave);

    if (cor(no->f_dir) == VERMELHO && cor(no->f_esq) == PRETO)
        rodar_esq(no);
    else if (cor(no->f_dir) ==  PRETO && cor(no->f_esq) == VERMELHO)
        rodar_dir(no);
    else if (cor(no->f_dir) == VERMELHO && cor(no->f_esq) == VERMELHO)
        inverte(no);    
}

bool rbt_inserir (RBT *T, int chave) {
    if (T != NULL) {
        if (rbt_insere_no(T->raiz, chave) != NULL) 
            return true;
    }
    return false;
}

void rbt_imprimir_aux(NO *raiz){
    if (raiz == NULL) return;
    printf("%d ", raiz->chave);
    rbt_imprimir_aux(raiz->f_esq);
    rbt_imprimir_aux(raiz->f_dir);
}

void rbt_imprimir (RBT *T) {
    if (T != NULL) 
        rbt_imprimir_aux(T->raiz);
}

void rbt_libera(NO **raiz) {
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

bool rbt_buscar_no(NO *raiz, int chave){
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


void copiar(RBT *c, NO* raiz){
    if(raiz == NULL) return;
    rbt_inserir(c, raiz->chave);
    copiar(c, raiz->f_esq);
    copiar(c, raiz->f_dir);
}

RBT *rbt_copiar(RBT *T){
    RBT *c = rbt_criar();
    copiar(c, T->raiz);

    return c;
}

void juntar_B(RBT *C, RBT *A, NO *raiz){
    if(raiz == NULL) return;
    if(!rbt_busca(A, raiz->chave)) rbt_inserir(C, raiz->chave);
    juntar_B(C, A, raiz->f_esq);
    juntar_B(C, A, raiz->f_dir);
}

RBT* rbt_uniao(RBT *A, RBT *B){
    RBT *C = rbt_copiar(A);
    juntar_B(C, A, B->raiz);

    return C;
}

void inter_B(RBT *C, RBT *A, NO *raiz){
    if(raiz == NULL) return;
    if(rbt_busca(A, raiz->chave)) rbt_inserir(C, raiz->chave);
    inter_B(C, A, raiz->f_esq);
    inter_B(C, A, raiz->f_dir);
}

RBT* rbt_inter(RBT *A, RBT *B){
    RBT *C = rbt_criar();
    inter_B(C, A, B->raiz);

    return C;
}
