#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  SET *A, *B;
  int n_a, n_b, x;
  int op;
  int tipo;

  scanf("%d", &tipo); /*0 -> AVL, 1 -> RBT*/

  A = set_criar(tipo);
  B = set_criar(tipo);

  scanf("%d %d", &n_a, &n_b);

  for(int i=0; i<n_a; i++){
    scanf("%d",&x);
    set_inserir(A, x);

  }

  for(int i=0; i<n_b; i++){
    scanf("%d",&x);
    set_inserir(B, x);

  }

  scanf("%d", &op);

  switch(op){
    case 1: {
              //pertence
              int n;
              scanf(" %d", &n);
              set_pertence(A, n) ? printf("Pertence\n") : printf("Não pertence\n");
              break;
    }
    case 2: {
              //uniao
              SET *C = (SET*) set_uniao(A, B);
              printf("Aqui esta SET da uniao entre A e B:\n");
              set_imprimir(C);
              set_apagar(&C);
              break;
    }
    case 3: {
              //intersecção
              SET *C = (SET*) set_interseccao(A, B);
              printf("Aqui esta SET da interseccao entre A e B:\n");
              set_imprimir(C);
              set_apagar(&C);
              break;
    }
    case 4: {
              //remoção
              int n;
              scanf(" %d", &n);
              if(set_remover(A, n)){
                printf("Elemento removido com sucesso! Aqui esta o SET atualizado:\n");
                set_imprimir(A);
              }
              else
                printf("Nao foi possivel remover tal elemento\n");
    }
  }
  set_apagar(&A);
  set_apagar(&B);
    
  return 0;
}
