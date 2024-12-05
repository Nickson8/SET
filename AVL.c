#include "AVL.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct no NO;
struct no{
    int chave;
    NO *f_esq;
    NO *f_dir;
    int FB;
};

struct avl{
    NO *raiz;
    int prof;
};

NO *criar_no(int chave);

int max(int a, int b){
    return(a>b ? a : b);
}
/***************************************************************/

 AVL *avl_criar(void){
    AVL *ab = malloc(sizeof(AVL));
    if(ab != NULL){
        ab->raiz = NULL;
        ab->prof = -1;
    }

    return ab;
 }

/***************************************************************/

bool avl_cheia(AVL *T){
    NO *no = (NO*) criar_no(0);
    if(no == NULL){
        free(no);
        return true;
    }
    return false;
}

/***************************************************************/

bool avl_vazia(AVL *T){
    if(T != NULL){
        return false;
    } else {
        return true;
    }
}

/***************************************************************/

int altura_no(NO *r){
    if(r == NULL) return -1;
    int e = altura_no(r->f_esq);
    int d = altura_no(r->f_dir);

    return (max(e,d)+1);
}

NO* rodar_esq(NO *a){
    NO *b = a->f_dir;
    a->f_dir = b->f_esq;
    b->f_esq = a;

    if(a->FB == -2 && b->FB == -2){
        a->FB = 1;
        b->FB = 0;
    }
    else if(a->FB == -2 && b->FB == -1){
        a->FB = 0;
        b->FB = 0;
    }
    else if(a->FB == -2 && b->FB == 0){
        a->FB = -1;
        b->FB = 1;
    }
    else if(a->FB == -1 && b->FB == -1){
        a->FB = 1;
        b->FB = 1;
    }
    else if(a->FB == -1 && b->FB == 0){
        a->FB = 0;
        b->FB = 1;
    }
    else if(a->FB == -1 && b->FB == 1){
        a->FB = 0;
        b->FB = 2;
    }

    return b;
}

NO* rodar_dir(NO *a){
    NO *b = a->f_esq;
    a->f_esq = b->f_dir;
    b->f_dir = a;

    if(a->FB == 2 && b->FB == 2){
        a->FB = -1;
        b->FB = 0;
    }
    else if(a->FB == 2 && b->FB == 1){
        a->FB = 0;
        b->FB = 0;
    }
    else if(a->FB == 2 && b->FB == 0){
        a->FB = 1;
        b->FB = -1;
    }
    else if(a->FB == 1 && b->FB == 1){
        a->FB = -1;
        b->FB = -1;
    }
    else if(a->FB == 1 && b->FB == 0){
        a->FB = 0;
        b->FB = -1;
    }
    else if(a->FB == 1 && b->FB == -1){
        a->FB = 0;
        b->FB = -2;
    }

    return b;
}

NO* rodar_esq_dir(NO *a){
    a->f_esq = rodar_esq(a->f_esq);
    return rodar_dir(a);
}

NO* rodar_dir_esq(NO *a){
    a->f_dir = rodar_dir(a->f_dir);
    return rodar_esq(a);
}

/***************************************************************/

NO* inserir_no(NO *raiz, NO *no){
    if(raiz == NULL){
        raiz = no;
    }
    else if(no->chave < raiz->chave)
        raiz->f_esq = inserir_no(raiz->f_esq, no);
    else if(no->chave > raiz->chave)
        raiz->f_dir = inserir_no(raiz->f_dir, no);
    
    raiz->FB = altura_no(raiz->f_esq) - altura_no(raiz->f_dir);

    if(raiz->FB == -2){
        if(raiz->f_dir->FB <= 0)
            raiz = rodar_esq(raiz);
        else
            raiz = rodar_dir_esq(raiz);
    }
    if(raiz->FB == 2){
        if(raiz->f_dir->FB >= 0)
            raiz = rodar_dir(raiz);
        else
            raiz = rodar_esq_dir(raiz);
    }

    return raiz;
    
}

NO* criar_no(int chave){
    NO *no = (NO*) malloc(sizeof(NO));
    if(no != NULL){
        no->chave = chave;
        no->f_dir = NULL;
        no->f_esq = NULL;
    }

    return no;
}

bool avl_inserir (AVL *T, int chave){
    if(T == NULL){
        return false;
    }
    if(!avl_cheia(T)){
        NO *no = (NO*) criar_no(chave);
        T-> raiz = inserir_no(T->raiz, no);
        return(true);
    }
    return false;
 }

/***************************************************************/

void troca_max_esq(NO *troca, NO *raiz, NO *ant){
    if(troca->f_dir != NULL){
        troca_max_esq(troca->f_dir, raiz, troca);
        return;
    }
    if(raiz == ant) ant->f_esq = troca->f_esq;
    else ant->f_dir = troca->f_esq;

    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

bool remover_aux(NO **raiz, int chave){
    if(*raiz == NULL) return false;
    if((*raiz)->chave == chave){
        // 1 ou 0 filhos
        if(((*raiz)->f_esq == NULL) || ((*raiz)->f_dir == NULL)){
            NO *p = *raiz;
            if((*raiz)->f_esq == NULL) *raiz = (*raiz)->f_dir;
            else *raiz = (*raiz)->f_esq;
            free(p);
            p = NULL;
        } else{
            troca_max_esq((*raiz)->f_esq, (*raiz), (*raiz));
        }
        return true;
    } else{
        if((*raiz)->chave > chave)
            return remover_aux(&((*raiz)->f_esq), chave);
        else
            return remover_aux(&((*raiz)->f_dir), chave);
    }
    if(*raiz != NULL){
        (*raiz)->FB = altura_no((*raiz)->f_esq) - altura_no((*raiz)->f_dir);

        if((*raiz)->FB == -2){
            if((*raiz)->f_dir->FB <= 0)
                (*raiz) = rodar_esq((*raiz));
            else
                (*raiz) = rodar_dir_esq((*raiz));
        }
        if((*raiz)->FB == 2){
            if((*raiz)->f_dir->FB >= 0)
                (*raiz) = rodar_dir((*raiz));
            else
                (*raiz) = rodar_esq_dir((*raiz));
        }
    }
}

bool avl_remover(AVL *T, int chave){
    if(avl_vazia(T)) return false;
    return remover_aux(&(T->raiz), chave);

}

/***************************************************************/

bool buscar_no(NO *raiz, int chave){
    if(raiz == NULL){
        return false;
    }
    else if(chave == raiz->chave) return true;
    else if(chave < raiz->chave) return buscar_no(raiz->f_esq, chave);
    else if(chave > raiz->chave) return buscar_no(raiz->f_dir, chave);
    
}

bool avl_busca (AVL *T, int chave){
    if(T == NULL){
        return false;
    }
    return buscar_no(T->raiz, chave);
}

/***************************************************************/

void imprima(NO *raiz){
    if(raiz == NULL) return;
    imprima(raiz->f_esq);
    printf("%d ", raiz->chave);
    imprima(raiz->f_dir);
}

void avl_imprimir (AVL *T){
    if(T == NULL) return;
    imprima(T->raiz);
    printf("\n");
}

/***************************************************************/

void apagar_arv(NO **raiz){
    if(*raiz != NULL){
        apagar_arv(&((*raiz)->f_esq));
        apagar_arv(&((*raiz)->f_dir));
        free(*raiz);
        *raiz = NULL;
    }
    return;
}
 void avl_apagar(AVL **T){
    if(*T != NULL){
        apagar_arv(&((*T)->raiz));
        free(*T);
        *T = NULL;
    }
 }

void copiar(AVL *c, NO* raiz){
    if(raiz == NULL) return;
    avl_inserir(c, raiz->chave);
    copiar(c, raiz->f_esq);
    copiar(c, raiz->f_dir);
}

AVL *avl_copiar(AVL *T){
    AVL *c = avl_criar();
    copiar(c, T->raiz);

    return c;
}

void juntar_B(AVL *C, AVL *A, NO *raiz){
    if(raiz == NULL) return;
    if(!avl_busca(A, raiz->chave)) avl_inserir(C, raiz->chave);
    juntar_B(C, A, raiz->f_esq);
    juntar_B(C, A, raiz->f_dir);
}
AVL* avl_uniao(AVL *A, AVL *B){
    AVL *C = avl_copiar(A);
    juntar_B(C, A, B->raiz);

    return C;
}

void inter_B(AVL *C, AVL *A, NO *raiz){
    if(raiz == NULL) return;
    if(avl_busca(A, raiz->chave)) avl_inserir(C, raiz->chave);
    inter_B(C, A, raiz->f_esq);
    inter_B(C, A, raiz->f_dir);
}
AVL* avl_inter(AVL *A, AVL *B){
    AVL *C = avl_criar();
    inter_B(C, A, B->raiz);

    return C;
}