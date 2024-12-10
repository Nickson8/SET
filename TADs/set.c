#include "stdlib.h"
#include "stdio.h"
#include "set.h"

/**
 * Struct para o tipo SET
 */
struct set{
    int tipo;
    AVL *avl;
    RBT *rbt;
};



/**
 * Função que cria e retorna um SET, baseado no tipo fornecido
 * 
 * @param tipo -> tipo do SET (0 para uma AVL, 1 para uma RBT)
 * 
 * @return Retorna um SET do tipo especificado
 */
SET *set_criar(unsigned char tipo){
    SET *set = (SET*) malloc(sizeof(SET));
    if(set != NULL){
        set->tipo = tipo;
        if(tipo == 0) set->avl = avl_criar();
        if(tipo == 1) set->rbt = rbt_criar();
    }

    return set;
}



/**
 * Função que verifica se um item faz parte do SET fornecido
 * 
 * @param A -> SET para fazer a busca
 * @param elemento -> elemento a ser procurado
 * 
 * @return Retorna true caso o elemento pertença e false caso contrário
 */
bool set_pertence(SET *A, int elemento){
    if(A == NULL) return false;
    if(A->tipo == 0) return avl_busca(A->avl, elemento);
    if(A->tipo == 1) return rbt_busca(A->rbt, elemento);
    return false;
}



/**
 * Função para inserir um elemento em determinado SET
 * 
 * @param s -> SET para fazer a inserçao
 * @param elemento -> elemento a ser inserido
 * 
 * @return Retorna true caso o elemento seja inserido e false caso contrário
 */
bool set_inserir (SET *s, int elemento){
    if(s == NULL) return false;
    if(s->tipo == 0) return avl_inserir(s->avl, elemento);
    if(s->tipo == 1) return rbt_inserir(s->rbt, elemento);
    return false;
}



/**
 * Função para remover um elemento em determinado SET
 * 
 * @param s -> SET para fazer a remoção
 * @param elemento -> elemento a ser removido
 * 
 * @return Retorna true caso o elemento seja removido e false caso contrário
 */
bool set_remover(SET *s, int elemento){
    if(s == NULL) return false;
    if(s->tipo == 0) return avl_remover(s->avl, elemento);
    if(s->tipo == 1) return rbt_remover(s->rbt, elemento);
    return false;
}



/**
 * Função para apagar determinado SET
 * 
 * @param A -> SET a ser apagado
 * 
 * @return void
 */
void set_apagar(SET **s){
    if(*s == NULL) return;
    if((*s)->tipo == 0) return avl_apagar(&((*s)->avl));
    if((*s)->tipo == 1) return rbt_apagar(&((*s)->rbt));
    free(*s);
    *s = NULL;
}



/**
 * Função para imprimir os valores de um determinado SET
 * 
 * @param s -> SET que será impresso
 * 
 * @return void
 */
void set_imprimir(SET *s){
    if(s == NULL) return;
    if(s->tipo == 0) return avl_imprimir(s->avl);
    if(s->tipo == 1) return rbt_imprimir(s->rbt);
}



/**
 * Função que cria e retorna um SET, que é a uniao entre um SET A e um SET B
 * 
 * @param A -> SET a ser feito a uniao com outro
 * @param B -> SET a ser feito a uniao com outro
 * 
 * @return SET resultante do uniao
 */
SET *set_uniao(SET *A, SET *B){
    SET *C = (SET*) set_criar(A->tipo);
    if(A->tipo == 0){
        C->avl = avl_uniao(A->avl, B->avl);
    }
    if(A->tipo == 1){
        C->rbt = rbt_uniao(A->rbt, B->rbt);
    }

    return C;
}



/**
 * Função que cria e retorna um SET, que é a interseccao entre um SET A e um SET B
 * 
 * @param A -> SET a ser feito a interseccao com outro
 * @param B -> SET a ser feito a interseccao com outro
 * 
 * @return SET resultante da interseccao
 */
SET *set_interseccao(SET *A, SET *B){
    SET *C = (SET*) set_criar(A->tipo);
    if(A->tipo == 0){
        C->avl = avl_inter(A->avl, B->avl);
    }
    if(A->tipo == 1){
        C->rbt = rbt_inter(A->rbt, B->rbt);
    }

    return C;
}