#ifndef _SET_H
#define _SET_H

  #include "AVL.h"
  #include "RBT.h"

 typedef struct set SET;

  SET *set_criar(unsigned char tipo);
  bool set_pertence(SET *A, int elemento);
  bool set_inserir (SET *s, int elemento);
  bool set_remover(SET *s, int elemento);
  void set_apagar(SET **s);
  void set_imprimir(SET *s);
  SET *set_uniao(SET *A, SET *B);
  SET *set_interseccao(SET *A, SET *B);
  
#endif