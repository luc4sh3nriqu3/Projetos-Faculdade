#include <stdlib.h>
#include <stdio.h>

#define PRETO 0
#define VERMELHO 1

typedef struct arv {
  int info;
  int cor;
  struct arv *pai;
  struct arv *esq;
  struct arv *dir;
}TArv;
typedef TArv *PArv;

int max(int a, int b) { // usaremos para calcular as alturas das Ã¡ rvores
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int altura(PArv a) {
  if (a == NULL) {
    return 0;
  }
  return 1 + max(altura(a->esq), altura(a->dir));
}

int altura_rubro(PArv a){

  if(a == NULL){
    return 0;
  }

  return (a->cor) * 1 + max(altura_rubro(a->esq), altura_rubro(a->dir));
  
}

PArv acha_avo(PArv a) {
  if ((a != NULL) && (a->pai != NULL)){
    return a->pai->pai;
  }
  else{
    return NULL;
  }
}

PArv buscaABB(PArv a, int valor) {

  if (a == NULL) {
    return NULL; //Ã¡rvore vazia
  } else if (valor < a->info) {
    return buscaABB(a->esq, valor);
  } else if (valor > a->info) {
    return buscaABB(a->dir, valor);
  } else {
    return a; // encontrou o valor
  }
}

PArv acha_tio(PArv a) {
  
  PArv avo = acha_avo(a);
  
  if (avo == NULL) return NULL;

  if (a->pai == avo->esq){
    return avo->dir;
  }
  else{
    return avo->esq;
  }
  
}

void rotacao_direita(PArv *pA) {

  if (*pA == NULL) return;

  PArv pB = *pA;
  *pA = pB->esq;
  pB->esq = (*pA)->dir;
  (*pA)->dir = pB;

  (*pA)->pai = pB->pai;
  if(pB->dir != NULL){
      (pB->dir)->pai = pB;
  }

  pB->pai = *pA;

  pB->cor = VERMELHO;
  (*pA)->cor = PRETO;

}

void rotacao_esquerda(PArv *pA) {

  if (*pA == NULL) return;

  PArv pB = *pA;
  *pA = pB->dir;
  pB->dir = (*pA)->esq;
  (*pA)->esq = pB;

  (*pA)->pai = pB->pai;
  if (pB->esq != NULL)
      (pB->esq)->pai = pB;

  pB->pai = *pA;
 
  pB->cor = VERMELHO;
  (*pA)->cor = PRETO;
}

void dupla_rotacao_esquerda(PArv *pA) {

  rotacao_direita(&((*pA)->dir));
  rotacao_esquerda(pA);

}

void dupla_rotacao_direita(PArv *pA) {

  rotacao_esquerda(&((*pA)->esq));
  rotacao_direita(pA);
  
}

void rebalanceamento(PArv *a, PArv *raiz) {

  PArv avo = NULL;
  PArv tio = NULL;

  if((*a)->pai != NULL) {
    if((*a)->pai->cor == PRETO) return;

    if((*a)->cor == VERMELHO) {
      tio = acha_tio(*a); 
      //Caso 1:
      if (tio != NULL && tio->cor == VERMELHO) {
        avo = acha_avo(*a);
        (*a)->pai->cor = PRETO;
        tio->cor = PRETO;
        if (avo->pai != NULL) {
          avo->cor = VERMELHO;
        } 
      }
        //Caso 2:
      else {
        avo = acha_avo(*a);
        if (avo != NULL) {
          if ((*a)->pai == avo->esq) {
            //Subcaso 3a:
            if ((*a) == (avo->esq)->esq) { 
              if (avo->pai != NULL) {
                  if ((avo->pai)->esq == avo) {
                    rotacao_direita(&((avo->pai)->esq));
                  }
                  else {
                    rotacao_direita(&((avo->pai)->dir));
                  }
              } 
              else { //caso estejamos fazendo uma rotação proxima a raiz
                  rotacao_direita(raiz);
              }


            } 
            else { //subcaso 2a:
              if (avo->pai != NULL) {
                if ((avo->pai)->esq == avo) {
                  dupla_rotacao_direita(&((avo->pai)->esq));
                }
                else{
                  dupla_rotacao_direita(&((avo->pai)->dir));
                }
              } 
              else { 
                dupla_rotacao_direita(raiz);
              }
            }
          } 
          else { //pai eh filho direito
            //subcaso 3b:
            if ((*a) == ((avo->dir)->dir)) {
              if (avo->pai != NULL) {
                if (((avo->pai)->esq) == avo) {
                  rotacao_esquerda(&((avo->pai)->esq));
                }
                else{
                  rotacao_esquerda(&((avo->pai)->dir));
                  }
              } 
              else {
                rotacao_esquerda(raiz);
              }

            } 
            else { //subcaso 2b:
              if (avo->pai != NULL) {
                if((avo->pai)->esq == avo) {
                  dupla_rotacao_esquerda(&((avo->pai)->esq));
                } 
                else {
                  dupla_rotacao_esquerda(&((avo->pai)->dir));
                }
              } 
              else {
                dupla_rotacao_esquerda(raiz);
              }
            }
          }
        }
      }
    }
  }
}

void insereARN(PArv *a, PArv pai, PArv *raiz, int valor) {

  if (*a == NULL) {
    *a = (PArv) malloc(sizeof(TArv));

    (*a)->info = valor;
    (*a)->cor = VERMELHO;
    (*a)->esq = NULL;
    (*a)->dir = NULL;
    (*a)->pai = pai;
  } 
  else if (valor < (*a)->info) {
    insereARN(&((*a)->esq), *a, raiz, valor);
    rebalanceamento(&((*a)->esq), raiz);
  } 
  else if (valor > (*a)->info) {
    insereARN(&((*a)->dir), *a, raiz, valor);
    rebalanceamento(&((*a)->dir), raiz);
  }
    
  if (*a == *raiz){
    (*a)->cor = PRETO;
  }

}

PArv *menor_dir(PArv *a){
    
    if (*a == NULL) return NULL;

    if ((*a)->esq == NULL)
        return a;
    else
        return menor_dir(&((*a)->esq));
}

int filho_esq(PArv a){
    if(a->pai->esq == a)
        return 1;
    else
        return 0;
}

PArv acha_irmao(PArv pai, PArv a){
    if(pai == NULL) return NULL;

    if(pai->dir->info == a->info)
        return pai->esq;
    else
        return pai->dir;
}

void sobrinho_V(PArv a_remove, PArv *a){

    PArv pai_remove = a_remove->pai;

    if(filho_esq(a_remove) == 1){
        free(a_remove);
        a_remove->pai->esq = NULL;
    } else {
        free(a_remove);
        a_remove->pai->dir = NULL;
    }

    if(pai_remove->esq == NULL){
        if(pai_remove->pai == NULL){
            if((pai_remove->dir)->dir == NULL){
                rotacao_direita(&((*a)->dir));
            }
            rotacao_esquerda(a);
        } 
        else {
            if((pai_remove->dir)->dir == NULL){
                rotacao_direita(&(pai_remove->dir));
            }
            rotacao_esquerda(&pai_remove);
        }
    } 
    else {
        if(pai_remove->pai == NULL){
            if((pai_remove->esq)->esq == NULL){
                rotacao_esquerda(&((*a)->esq));
            }
            rotacao_direita(a);
        } else {
            if((pai_remove->dir)->dir == NULL){
                rotacao_esquerda(&(pai_remove->esq));
            }
            rotacao_direita(&pai_remove);
        }
    }
    return;
}

void irmao_V(PArv a_remove, PArv *a){

    PArv pai_remove = a_remove->pai;

    sobrinho_V(a_remove,a);

    pai_remove->cor = PRETO;
    if(pai_remove->esq != NULL)
        (pai_remove->esq)->cor = VERMELHO;
    if(pai_remove->dir != NULL)
        (pai_remove->dir)->cor = VERMELHO;
}

void RB_delete_fixup(PArv a_remove, PArv *a){

    PArv pai_remove = a_remove->pai;
    PArv irmao = acha_irmao(pai_remove, a_remove);

    irmao_V(a_remove, a);

    pai_remove->cor = PRETO;
    irmao->cor = VERMELHO;
}

void removeARN(PArv *a, int num){

    if(*a == NULL){
      return;
    }

    PArv a_remove = *a;

    a_remove  = buscaABB(a_remove, num);

    if(a == NULL) return;

    if(a_remove->dir == NULL && a_remove->esq == NULL){
        if(a_remove->pai == NULL){
            free(a_remove);
            *a = NULL;
            return;
        } else {
            if(a_remove->cor == VERMELHO && a_remove->dir == NULL && a_remove->esq == NULL){
                if(filho_esq(a_remove) == 1){
                    free(a_remove);
                    a_remove->pai->esq = NULL;
                } else {
                    free(a_remove);
                    a_remove->pai->dir = NULL;
                }
                return;
            } else {
                PArv irmao = acha_irmao(a_remove->pai,a_remove);
                    if(irmao == NULL) return;

                if(a_remove->cor == PRETO && irmao->cor == PRETO){
                    if(irmao->dir == NULL && irmao->esq == NULL){
                        RB_delete_fixup(a_remove, a);
                        return;
                    } else if(irmao->esq->cor == PRETO && irmao->dir->cor == PRETO){
                        RB_delete_fixup(a_remove, a);
                        return;
                    }
                    else if(irmao->dir->cor == PRETO && irmao->esq == NULL){
                        RB_delete_fixup(a_remove, a);
                        return;
                    }
                    else if(irmao->esq->cor == PRETO && irmao->dir == NULL){
                        RB_delete_fixup(a_remove, a);
                        return;
                    }
                } else if(a_remove->cor == PRETO && irmao->cor == PRETO && (irmao->esq->cor == VERMELHO || irmao->dir->cor == VERMELHO)){
                    if(irmao->esq != NULL){
                        sobrinho_V(a_remove, a);
                        return;
                    } else if (irmao->dir != NULL){
                        sobrinho_V(a_remove, a);
                        return;
                    }
                } else if(a_remove->cor == PRETO && irmao->cor == VERMELHO){
                    irmao_V(a_remove, a);
                }
            }

            return;
        }
    } else if (a_remove->dir == NULL || a_remove->esq == NULL){
        if(a_remove->dir != NULL){
            a_remove->info = a_remove->dir->info;
            free(a_remove->dir);
            a_remove->dir = NULL;
        } else {
            a_remove->info = a_remove->esq->info;
            free(a_remove->esq);
            a_remove->esq = NULL;
        }
    } else {
        PArv *novo = menor_dir(&(a_remove->dir));
        PArv aux_novo = *novo;

        a_remove->info = (*novo)->info;
        (*novo)->pai->dir = (*novo)->dir;


        if(a_remove->cor == VERMELHO){
            if(a_remove->esq == NULL && a_remove == a_remove->pai->esq && (a_remove->dir->dir != NULL || a_remove->dir->esq != NULL)){
                if(a_remove->dir->dir != NULL){
                    rotacao_direita(&(a_remove->esq));
                    rotacao_esquerda(&a_remove);
                }
                if(a_remove->dir->esq != NULL){
                    rotacao_direita(&(a_remove->dir));
                    rotacao_esquerda(&a_remove);
                }
            } else if(a_remove->esq == NULL && a_remove == a_remove->pai->dir && (a_remove->esq->dir != NULL || a_remove->esq->esq != NULL)){
                if(a_remove->esq->dir != NULL){
                    rotacao_esquerda(&(a_remove->esq));
                    rotacao_direita(&a_remove);
                }
                if(a_remove->esq->esq != NULL){
                    rotacao_esquerda(&(a_remove->esq));
                    rotacao_direita(&a_remove);
                }
            }

            a_remove->cor = PRETO;
            if(a_remove->esq != NULL)
                a_remove->esq->cor = VERMELHO;
            if(a_remove->dir != NULL)
                a_remove->dir->cor = VERMELHO;
        }
    }
}

PArv libera(PArv a) {

  if (a != NULL) {
    libera(a->esq);
    libera(a->dir);
    free(a);
  }

  return NULL;
}

int main() {

  PArv arv = NULL;
  PArv busca = NULL, no_procura = NULL;
  int num = 0;
  int alt, sub_d, sub_e;

  while (num >= 0) {
    scanf("%d", &num);

    if (num >= 0) {
      insereARN(&arv, NULL, &arv, num);
    }
  }
  
  alt = altura(arv);
  sub_d = altura(arv->dir);
  sub_e = altura(arv->esq);

  printf("%d, %d, %d\n", alt - 1, sub_e, sub_d);

  num = 0;
  while (num >= 0) {
    scanf("%d", &num);

    if (num >= 0) {
      
      busca = buscaABB(arv, num);
      
      if (busca == NULL) {
        insereARN(&arv, NULL, &arv, num);
      }
      else{

        alt = altura(busca);
        sub_d = altura(busca->dir);
        sub_e = altura(busca->esq);

        printf("%d, %d, %d\n", alt - 1, sub_e, sub_d);
        
        removeARN(&arv, num);
      }
    }
  }

  scanf("%d", &num);

  no_procura = buscaABB(arv, num);
  
  if (no_procura == NULL) {
    printf("Valor nao encontrado");
  } else {
    alt = altura_rubro(no_procura);

    printf("%d", alt);
  }
  
  arv = libera(arv);

  return 0;
}