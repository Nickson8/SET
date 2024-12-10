#include "RBT.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define PRETO 0
#define VERMELHO 1

/*DECLARAÇÕES**************************************************************/

//estrutura de nó que representará os vértices da arvore
typedef struct no NO;
struct no{
    int chave;
    NO *f_esq;
    NO *f_dir;
    int cor;
};

//estrutura que permite o acesso a arvore
struct rbt {
    NO *raiz;
};

/**
 * Cria uma arvore
 * 
 * @param void
 * 
 * @return O ponteiro para a arvore que foi criada
 */
RBT *rbt_criar (void) {
    RBT *T = malloc(sizeof(RBT));
    if (T == NULL) exit(-1);

    T->raiz = NULL;    
    return T;
}

/**
 * Funçao axiliar que cria um no
 * 
 * @param chave -> chave do no
 * 
 * @return no que foi criado
 */
NO *cria_no(int chave){
    NO *no = malloc(sizeof(NO));
    if (no == NULL) exit(-1);
    no->chave = chave;
    no->cor = VERMELHO;
    no->f_dir = NULL;
    no->f_esq = NULL;

    return no;
}

/*ARRUMA_ARVORE**************************************************************/

//permite que as funções sejam usados na "arruma_arvore"
NO *rbt_rodar_esq(NO *a);
NO *rbt_rodar_dir(NO *a);
void inverte(NO *raiz);
bool cor(NO *raiz);

/**
 * Funçao que verifica e realiza ajustes se necessário em algum nó da arvore
 * é tulizada após inserções e remoções para manter a propriedade de uma RBT 
 * 
 * @param h -> no que será verificado e possivelemente ajustado
 * 
 * @return novo ponteiro para o nó que estará no lugar de h
 */
NO *arruma_arvore(NO *h) {
    if (cor(h->f_dir) == VERMELHO && cor(h->f_esq) == PRETO)
        h = rbt_rodar_esq(h);
    else if (cor(h->f_esq) ==  VERMELHO && cor((h->f_esq->f_esq)) == VERMELHO)
        h = rbt_rodar_dir(h);
    else if (cor(h->f_dir) == VERMELHO && cor(h->f_esq) == VERMELHO)
        inverte(h); 

    return h;        
}

/*INSERCAO**************************************************************/

/**
 * Funçao que roda uma sub-arvore para a esquerda
 * 
 * @param a -> no que acontecera a rotaçao
 * 
 * @return no raiz da sub-arvora rotacionada
 */
NO *rbt_rodar_esq(NO *a) {
    NO *b = a->f_dir;

    //inverte a posicao e 'a' e 'b'
    a->f_dir = b->f_esq;
    b->f_esq = a;

    //troca das cores
    b->cor = a->cor;
    a->cor = VERMELHO;

    return b;
}

/**
 * Funçao que roda uma sub-arvore para a direita
 * 
 * @param a -> no que acontecera a rotaçao
 * 
 * @return no raiz da sub-arvora rotacionada
 */
NO *rbt_rodar_dir(NO *a) {
    NO *b = a->f_esq;

    //inverte a posicao e 'a' e 'b'
    a->f_esq = b->f_dir;
    b->f_dir = a;

    //troca das cores
    b->cor = a->cor;
    a->cor = VERMELHO;

    return b;
}

/**
 * Funçao que inverte as cores de um nó
 * 
 * @param raiz -> no que acontecera a inverção
 *
 * @return void
 */
void inverte(NO *raiz) {
    raiz->cor = !raiz->cor;
    if (raiz->f_dir != NULL)
        raiz->f_dir->cor = !raiz->f_dir->cor;
    if (raiz->f_esq != NULL)
        raiz->f_esq->cor = !raiz->f_esq->cor;
}

/**
 * Funçao que retorna a cor de um nó (nós nulos são tratados como pretos)
 * 
 * @param a -> no que terá sua cor verificada
 * 
 * @return 0 para nós pretos, 1 para nós vermelhos
 */
bool cor(NO *raiz) {
    if (raiz == NULL) 
        return 0;
    return raiz->cor;
}

/**
 * Funçao recursiva para achar a posiçao para se inserir um no,
 * realiza chamada do ajuste da árvore para manter suas propriedades
 * 
 * @param raiz -> no que esta sendo analisado para inserção
 * 
 * @return raiz da arvore ajustada
 */
NO *rbt_insere_no(NO *raiz, int chave) {
    if (raiz == NULL) {
        return cria_no(chave);
    }
    if (raiz->chave <= chave)
        raiz->f_dir = rbt_insere_no(raiz->f_dir, chave);
    else
        raiz->f_esq = rbt_insere_no(raiz->f_esq, chave);

    return arruma_arvore(raiz);  
}

/**
 * Funçao que insere um no na arvore
 * 
 * @param T -> arvore que tera o no inserido
 * @param chave -> chave do no
 * 
 * @return true caso consiga inserir, false caso contrario
 */
bool rbt_inserir (RBT *T, int chave) {
    if (T != NULL) {
        T->raiz = rbt_insere_no(T->raiz, chave);
        if (T->raiz != NULL) {
            T->raiz->cor = PRETO;
            return true;
        }
            
    }
    return false;
}

/*LIBERA-MEMÓRIA**************************************************************/

/**
 * Funçao recursiva para liberar a memória de todos os nós de uma árvore RBT
 * 
 * @param raiz -> ponteiro para o ponteiro da raiz da árvore que será apagada
 * 
 * @return void
 */
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

/**
 * Funçao para apagar completamente uma árvore RBT e liberar sua memória
 * 
 * @param T -> ponteiro para o ponteiro da árvore que será apagada
 * 
 * @return void
 */
void rbt_apagar (RBT **T) {
    if (T != NULL) {
        rbt_libera(&(*T)->raiz);
        free(*T);
        *T = NULL;
    }
}

/*REMOÇÃO**************************************************************/

/**
 * Funçao que realiza o "MoveRedLeft" para ajustar a árvore na descida
 em busca de um nó a ser removido
 * 
 * @param a -> no que acontecera a operação
 * 
 * @return no raiz da sub-arvore que a operação foi realizada
 */
NO *move_esq(NO *a) {
    inverte(a);
    if (cor(a->f_dir->f_esq) == VERMELHO){
        a->f_dir = rbt_rodar_dir(a);
        a = rbt_rodar_esq(a);
        inverte(a);
    }
    return a;
}

/**
 * Funçao que realiza o "MoveRedRight" para ajustar a árvore na descida
 em busca de um nó a ser removido
 * 
 * @param a -> no que acontecera a operação
 * 
 * @return no raiz da sub-arvore que a operação foi realizada
 */
NO *move_dir(NO *a) {
    inverte(a);
    if (cor(a->f_esq->f_esq) == VERMELHO){
        a = rbt_rodar_dir(a);

        inverte(a);
    }
    return a;
}

/**
 * Funçao recursiva para deletar o menor no da sub-arvore direita
 * 
 * @param raiz -> no da sub-arovre que terá seu nó minimo removido
 * 
 * @return Nó raiz da sub-arvore ajustada
 */
NO *deleta_minimo(NO *raiz) {
    if (raiz->f_esq == NULL) {
        free(raiz);
        return NULL;
    }
    if (cor(raiz->f_esq) == PRETO && cor(raiz->f_esq->f_esq))
        raiz = move_esq(raiz);

    raiz->f_esq = deleta_minimo(raiz->f_esq);

    return arruma_arvore(raiz);
}

/**
 * Funçao recursiva para achar o menor no da sub-arvore direita e retornar sua chave
 * 
 * @param raiz -> no da sub-arovre que terá seu nó encontrado removido
 * 
 * @return Chave do menor nó
 */
int acha_minimo(NO *raiz) {
    if (raiz->f_esq == NULL)
        return raiz->chave;
    else
        return acha_minimo(raiz->f_esq);
}

/**
 * Funçao recursiva para achar e deletar o no com uma certa chave, realiza ajustes na
 * descida e na subida da arvore para manter as propriedades de uma arvore de busca balanceada
 * 
 * @param raiz -> endereço do ponteiro para o no que esta sendo analisado
 * @param chave -> chave do no a ser removido
 * 
 * @return true caso consiga remover, false caso contrario
 */
NO *deleta_no(NO  *raiz, int chave) {
    if (chave > raiz->chave ) {
        //ajuste "MoveRedLeft" caso necessário 
        if (cor(raiz->f_esq) == PRETO && raiz->f_esq != NULL && cor(raiz->f_esq->f_dir) == PRETO) {
            raiz = move_esq(raiz);
            raiz->f_esq = deleta_no(raiz->f_esq, chave);
        }
    }
    else {
        //ajuste "MoveRedRight" caso necessário
        if (cor(raiz->f_esq) == VERMELHO)
            raiz = rbt_rodar_dir(raiz);

        //a chave é menor mas não existe arvore na direta -> chave não esta na arvore
        if (raiz->chave == chave && raiz->f_dir == NULL) { 
                return NULL;
        }
        if (cor(raiz->f_dir) == PRETO && cor(raiz->f_dir->f_esq) == PRETO)
            raiz = move_dir(raiz);
        //chave foi encontrada então precisamos substituir com o minimo da sub arvore da esquerda
        if (raiz->chave == chave) {
            int NO_minimo = acha_minimo(raiz->f_dir);
            raiz->chave = NO_minimo;
            raiz->f_dir = deleta_minimo(raiz->f_dir);
        }
        else //segue busca pela sub arvore da direita
            raiz->f_dir = deleta_no(raiz->f_dir, chave);

    }   
    //ajusta arvore na volta
    return arruma_arvore(raiz);
}

/**
 * Funçao que remove um no da arvore
 * 
 * @param T -> arvore que tera o no removido
 * @param chave -> chave do no
 * 
 * @return true caso consiga remover, false caso contrario
 */
bool rbt_remover(RBT *T, int chave) {
    if (T != NULL) 
        if (deleta_no(T->raiz, chave) != NULL)
            return true;

    return false;
}



/*OPERAÇÕES-SET**************************************************************/

/**
 * Funçao recursiva para achar o no
 * 
 * @param raiz -> no que esta sendo analisado
 * @param chave -> chave do no a ser encontrada
 * 
 * @return true caso consiga achar, false caso contrario
 */
static bool buscar_no(NO *raiz, int chave){
    if(raiz == NULL){
        return false;
    }
    else if(chave == raiz->chave) return true;
    else if(chave < raiz->chave) return buscar_no(raiz->f_esq, chave);
    else if(chave > raiz->chave) return buscar_no(raiz->f_dir, chave);

    return false;
}

/**
 * Funçao recursiva para achar o no
 * 
 * @param raiz -> no que esta sendo analisado
 * @param chave -> chave do no a ser encontrada
 * 
 * @return true caso consiga achar, false caso contrario
 */
bool rbt_busca(RBT *T, int chave) {
    if (T == NULL) return false;
    return buscar_no(T->raiz, chave);
}


/**
 * Funçao recursiva para imprimir nos valores das chaves de todos os nos da
 * arvore em ordem
 * 
 * @param raiz -> no que esta sendo analisado
 * 
 * @return void
 */
static void imprima(NO *raiz){
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
void rbt_imprimir (RBT *T) {
    if (T != NULL) 
        imprima(T->raiz);
}


/**
 * Funçao recursiva para copiar os elementos de uma árvore RBT para outra
 * 
 * @param c    -> árvore destino onde os elementos serão inseridos
 * @param raiz -> nó atual da árvore origem sendo copiado
 * 
 * @return void
 */
static void copiar(RBT *c, NO* raiz){
    if(raiz == NULL) return;
    rbt_inserir(c, raiz->chave);
    copiar(c, raiz->f_esq);
    copiar(c, raiz->f_dir);
}

/**
 * Funçao para criar uma cópia de uma árvore RBT
 * 
 * @param T -> árvore que será copiada
 * 
 * @return RBT* -> ponteiro para a nova árvore copiada
 */
RBT *rbt_copiar(RBT *T){
    RBT *c = rbt_criar();
    copiar(c, T->raiz);

    return c;
}

/**
 * Funçao recursiva para unir os elementos de uma árvore RBT em outra,
 * inserindo apenas os elementos que não estão presentes na árvore de origem
 * 
 * @param C    -> árvore destino onde os elementos serão unidos
 * @param A    -> árvore origem que será comparada
 * @param raiz -> nó atual da árvore origem sendo analisado
 * 
 * @return void
 */
static void juntar_B(RBT *C, RBT *A, NO *raiz){
    if(raiz == NULL) return;
    if(!rbt_busca(A, raiz->chave)) rbt_inserir(C, raiz->chave);
    juntar_B(C, A, raiz->f_esq);
    juntar_B(C, A, raiz->f_dir);
}

/**
 * Funçao para realizar a união de duas árvores RBT, criando uma nova árvore
 * com todos os elementos das duas árvores sem repetições
 * 
 * @param A -> primeira árvore para a união
 * @param B -> segunda árvore para a união
 * 
 * @return RBT* -> ponteiro para a nova árvore resultante da união
 */
RBT* rbt_uniao(RBT *A, RBT *B){
    RBT *C = rbt_copiar(A);
    juntar_B(C, A, B->raiz);

    return C;
}

/**
 * Funçao recursiva para realizar a interseção dos elementos de uma árvore RBT
 * com outra, inserindo apenas os elementos comuns na árvore destino
 * 
 * @param C    -> árvore destino onde os elementos comuns serão inseridos
 * @param A    -> primeira árvore para comparação
 * @param raiz -> nó atual da segunda árvore sendo analisado
 * 
 * @return void
 */
void rbt_inter_B(RBT *C, RBT *A, NO *raiz){
    if(raiz == NULL) return;
    if(rbt_busca(A, raiz->chave)) rbt_inserir(C, raiz->chave);
    rbt_inter_B(C, A, raiz->f_esq);
    rbt_inter_B(C, A, raiz->f_dir);
}

/**
 * Funçao para realizar a interseção de duas árvores RBT, criando uma nova
 * árvore com os elementos comuns às duas árvores
 * 
 * @param A -> primeira árvore para a interseção
 * @param B -> segunda árvore para a interseção
 * 
 * @return RBT* -> ponteiro para a nova árvore resultante da interseção
 */
RBT* rbt_inter(RBT *A, RBT *B){
    RBT *C = rbt_criar();
    rbt_inter_B(C, A, B->raiz);

    return C;
}
