#include "RBT.h"

RBT *rbt_criar (void); 
bool rbt_inserir (RBT *T, int chave);
void rbt_imprimir (RBT *T);
void rbt_apagar (RBT **T);
bool rbt_remover(RBT *T, int chave);  
bool rbt_busca(RBT *T, int chave);
bool rbt_vazia(RBT *T);
RBT *rbt_copiar(RBT *T);
RBT *rbt_uniao(RBT *A, RBT *B);
RBT *rbt_inter(RBT *A, RBT *B);