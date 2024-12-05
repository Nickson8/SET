#ifndef _AVL_H
  #define _AVL_H

  typedef struct avl AVL;

  #include "stdbool.h"
 
  AVL *avl_criar (void); 
  bool avl_inserir (AVL *T, int chave);
  void avl_imprimir (AVL *T);
  void avl_apagar (AVL **T);
  bool avl_remover(AVL *T, int chave);  
  bool avl_busca(AVL *T, int chave);
  bool avl_vazia(AVL *T);
  AVL *avl_copiar(AVL *T);
  AVL *avl_uniao(AVL *A, AVL *B);
  AVL *avl_inter(AVL *A, AVL *B);
  
#endif
