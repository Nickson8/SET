#include "AVL.h"
#include <stdlib.h>
#include <stdio.h>


/// Estrututa auxiliar para a implementaçao
typedef struct no NO;
struct no{
    int chave;
    NO *f_esq;
    NO *f_dir;
    int FB;
};

// Estrutura que representa a arvore
struct avl{
    NO *raiz;
    int prof;
};

NO *criar_no(int chave);

int max(int a, int b){
    return(a>b ? a : b);
}
/***************************************************************/

/**
 * Cria uma arvore
 * 
 * @param void
 * 
 * @return O ponteiro para a arvore que foi criada
 */
AVL *avl_criar(void){
    AVL *ab = malloc(sizeof(AVL));
    if(ab != NULL){
        ab->raiz = NULL;
        ab->prof = -1;
    }

    return ab;
}

/***************************************************************/

/**
 * Verifica se a arvore esta cheia
 * 
 * @param T -> arvore que será analisada
 * 
 * @return true caso esteja cheia, false caso contrario
 */
bool avl_cheia(AVL *T){
    NO *no = (NO*) criar_no(0);
    if(no == NULL){
        return true;
    }
    free(no);
    return false;
}

/***************************************************************/

/**
 * Verifica se a arvore esta vazia
 * 
 * @param T -> arvore que será analisada
 * 
 * @return true caso esteja vazia, false caso contrario
 */
bool avl_vazia(AVL *T){
    if(T != NULL){
        if(T->raiz != NULL) return false;
    } else {
        return true;
    }
    return false;
}

/***************************************************************/

/**
 * Funçao recursiva para o calculo da altura de um no
 * 
 * @param r -> no que será analisado
 * 
 * @return altura do no
 */
int altura_no(NO *r){
    if(r == NULL) return -1;
    int e = altura_no(r->f_esq);
    int d = altura_no(r->f_dir);

    return (max(e,d)+1);
}

/**
 * Funçao que roda uma sub-arvore para a esquerda
 * 
 * @param a -> no que acontecera a rotaçao
 * 
 * @return no raiz da sub-arvora rotacionada
 */
NO* rodar_esq(NO *a){
    NO *b = a->f_dir;
    a->f_dir = b->f_esq;
    b->f_esq = a;

    // Ajustando os FB dependendo do caso
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

/**
 * Funçao que roda uma sub-arvore para a direita
 * 
 * @param a -> no que acontecera a rotaçao
 * 
 * @return no raiz da sub-arvora rotacionada
 */
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

/**
 * Funçao que roda uma sub-arvore, primeiro rodando seu filho para a esquerda,
 * depois a raiz para a direita
 * 
 * @param a -> no que acontecera a rotaçao
 * 
 * @return no raiz da sub-arvora rotacionada
 */
NO* rodar_esq_dir(NO *a){
    a->f_esq = rodar_esq(a->f_esq);
    return rodar_dir(a);
}

/**
 * Funçao que roda uma sub-arvore, primeiro rodando seu filho para a direita,
 * depois a raiz para a esquerda
 * 
 * @param a -> no que acontecera a rotaçao
 * 
 * @return no raiz da sub-arvora rotacionada
 */
NO* rodar_dir_esq(NO *a){
    a->f_dir = rodar_dir(a->f_dir);
    return rodar_esq(a);
}

/***************************************************************/

/**
 * Funçao recursiva para achar a posiçao para se inserir um no
 * 
 * @param raiz -> no que esta sendo analisado
 * @param no -> no que sera inserido
 * 
 * @return raiz (usado para as rotações)
 */
NO* inserir_no(NO *raiz, NO *no){
    if(raiz == NULL){
        raiz = no;
    }
    else if(no->chave < raiz->chave)
        raiz->f_esq = inserir_no(raiz->f_esq, no);
    else if(no->chave > raiz->chave)
        raiz->f_dir = inserir_no(raiz->f_dir, no);
    
    raiz->FB = altura_no(raiz->f_esq) - altura_no(raiz->f_dir);

    //Fazendo a rotaçao caso necessario
    if(raiz->FB == -2){
        if(raiz->f_dir->FB <= 0)
            raiz = rodar_esq(raiz);
        else
            raiz = rodar_dir_esq(raiz);
    }
    if(raiz->FB == 2){
        if(raiz->f_esq->FB >= 0)
            raiz = rodar_dir(raiz);
        else
            raiz = rodar_esq_dir(raiz);
    }

    return raiz;
    
}

/**
 * Funçao axiliar que cria um no
 * 
 * @param chave -> chave do no
 * 
 * @return no que foi criado
 */
NO* criar_no(int chave){
    NO *no = (NO*) malloc(sizeof(NO));
    if(no != NULL){
        no->chave = chave;
        no->FB = 0;
        no->f_dir = NULL;
        no->f_esq = NULL;
    }

    return no;
}

/**
 * Funçao que insere um no na arvore
 * 
 * @param T -> arvore que tera o no inserido
 * @param chave -> chave do no
 * 
 * @return true caso consiga inserir, false caso contrario
 */
bool avl_inserir (AVL *T, int chave){
    if(T == NULL){
        return false;
    }
    NO *no = (NO*) criar_no(chave);
    T-> raiz = inserir_no(T->raiz, no);
    return(true);
 }

/***************************************************************/

/**
 * Funçao recursiva para achar o maior no da sub-arvore esquerda e trocar ele
 * com o no que será removido
 * 
 * @param troca -> no que sera trocado
 * @param raiz -> no que sera removido
 * @param ant -> no pai do troca
 * 
 * @return void
 */
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

/**
 * Funçao recursiva para achar o no com a chave a ser removido
 * 
 * @param raiz -> endereço do ponteiro para o no que esta sendo analisado
 * @param chave -> chave do no a ser removido
 * 
 * @return true caso consiga remover, false caso contrario
 */
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
        // 2 filhos
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
    //Fazendo a rotaçao caso necessario
    if(*raiz != NULL){
        (*raiz)->FB = altura_no((*raiz)->f_esq) - altura_no((*raiz)->f_dir);

        if((*raiz)->FB == -2){
            if((*raiz)->f_dir->FB <= 0)
                (*raiz) = rodar_esq((*raiz));
            else
                (*raiz) = rodar_dir_esq((*raiz));
        }
        if((*raiz)->FB == 2){
            if((*raiz)->f_esq->FB >= 0)
                (*raiz) = rodar_dir((*raiz));
            else
                (*raiz) = rodar_esq_dir((*raiz));
        }
    }
}

/**
 * Funçao que remove um no da arvore
 * 
 * @param T -> arvore que tera o no removido
 * @param chave -> chave do no
 * 
 * @return true caso consiga remover, false caso contrario
 */
bool avl_remover(AVL *T, int chave){
    if(avl_vazia(T)) return false;
    return remover_aux(&(T->raiz), chave);

}

/***************************************************************/

/**
 * Funçao recursiva para achar o no
 * 
 * @param raiz -> no que esta sendo analisado
 * @param chave -> chave do no a ser encontrada
 * 
 * @return true caso consiga achar, false caso contrario
 */
bool buscar_no(NO *raiz, int chave){
    if(raiz == NULL){
        return false;
    }
    else if(chave == raiz->chave) return true;
    else if(chave < raiz->chave) return buscar_no(raiz->f_esq, chave);
    else if(chave > raiz->chave) return buscar_no(raiz->f_dir, chave);
    
    return false;
}

/**
 * Funçao que busca um no na arvore
 * 
 * @param T -> arvore que tera o no removido
 * @param chave -> chave do no
 * 
 * @return true caso consiga remover, false caso contrario
 */
bool avl_busca (AVL *T, int chave){
    if(T == NULL){
        return false;
    }
    return buscar_no(T->raiz, chave);
}

/***************************************************************/

/**
 * Funçao recursiva para dar print nos valores das chaves de todos os nos da
 * arvore
 * 
 * @param raiz -> no que esta sendo analisado
 * 
 * @return void
 */
void imprima(NO *raiz){
    if(raiz == NULL) return;
    imprima(raiz->f_esq);
    printf("%d ", raiz->chave);
    imprima(raiz->f_dir);
}

/**
 * Funçao para dar print nos valores das chaves de todos os nos da arvore
 * 
 * @param T -> arvore que tera suas chaves printadas
 * 
 * @return void
 */
void avl_imprimir (AVL *T){
    if(T == NULL) return;
    imprima(T->raiz);
    printf("\n");
}

/***************************************************************/

/**
 * Funçao recursiva para liberar a memória de todos os nós de uma árvore AVL
 * 
 * @param raiz -> ponteiro para o ponteiro da raiz da árvore que será apagada
 * 
 * @return void
 */
void apagar_arv(NO **raiz){
    if(*raiz != NULL){
        apagar_arv(&((*raiz)->f_esq));
        apagar_arv(&((*raiz)->f_dir));
        free(*raiz);
        *raiz = NULL;
    }
    return;
}

/**
 * Funçao para apagar completamente uma árvore AVL e liberar sua memória
 * 
 * @param T -> ponteiro para o ponteiro da árvore que será apagada
 * 
 * @return void
 */
void avl_apagar(AVL **T){
    if(*T != NULL){
        apagar_arv(&((*T)->raiz));
        free(*T);
        *T = NULL;
    }
}

/**
 * Funçao recursiva para copiar os elementos de uma árvore AVL para outra
 * 
 * @param c    -> árvore destino onde os elementos serão inseridos
 * @param raiz -> nó atual da árvore origem sendo copiado
 * 
 * @return void
 */
void copiar(AVL *c, NO* raiz){
    if(raiz == NULL) return;
    avl_inserir(c, raiz->chave);
    copiar(c, raiz->f_esq);
    copiar(c, raiz->f_dir);
}

/**
 * Funçao para criar uma cópia de uma árvore AVL
 * 
 * @param T -> árvore que será copiada
 * 
 * @return AVL* -> ponteiro para a nova árvore copiada
 */
AVL *avl_copiar(AVL *T){
    AVL *c = avl_criar();
    copiar(c, T->raiz);

    return c;
}

/**
 * Funçao recursiva para unir os elementos de uma árvore AVL em outra,
 * inserindo apenas os elementos que não estão presentes na árvore de origem
 * 
 * @param C    -> árvore destino onde os elementos serão unidos
 * @param A    -> árvore origem que será comparada
 * @param raiz -> nó atual da árvore origem sendo analisado
 * 
 * @return void
 */
void juntar_B(AVL *C, AVL *A, NO *raiz){
    if(raiz == NULL) return;
    if(!avl_busca(A, raiz->chave)) avl_inserir(C, raiz->chave);
    juntar_B(C, A, raiz->f_esq);
    juntar_B(C, A, raiz->f_dir);
}

/**
 * Funçao para realizar a união de duas árvores AVL, criando uma nova árvore
 * com todos os elementos das duas árvores sem repetições
 * 
 * @param A -> primeira árvore para a união
 * @param B -> segunda árvore para a união
 * 
 * @return AVL* -> ponteiro para a nova árvore resultante da união
 */
AVL* avl_uniao(AVL *A, AVL *B){
    AVL *C = avl_copiar(A);
    juntar_B(C, A, B->raiz);

    return C;
}

/**
 * Funçao recursiva para realizar a interseção dos elementos de uma árvore AVL
 * com outra, inserindo apenas os elementos comuns na árvore destino
 * 
 * @param C    -> árvore destino onde os elementos comuns serão inseridos
 * @param A    -> primeira árvore para comparação
 * @param raiz -> nó atual da segunda árvore sendo analisado
 * 
 * @return void
 */
void inter_B(AVL *C, AVL *A, NO *raiz){
    if(raiz == NULL) return;
    if(avl_busca(A, raiz->chave)) avl_inserir(C, raiz->chave);
    inter_B(C, A, raiz->f_esq);
    inter_B(C, A, raiz->f_dir);
}

/**
 * Funçao para realizar a interseção de duas árvores AVL, criando uma nova
 * árvore com os elementos comuns às duas árvores
 * 
 * @param A -> primeira árvore para a interseção
 * @param B -> segunda árvore para a interseção
 * 
 * @return AVL* -> ponteiro para a nova árvore resultante da interseção
 */
AVL* avl_inter(AVL *A, AVL *B){
    AVL *C = avl_criar();
    inter_B(C, A, B->raiz);

    return C;
}