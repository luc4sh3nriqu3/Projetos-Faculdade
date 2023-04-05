#include <stdio.h>
#include <stdlib.h>

typedef struct arv {
  int info;
  int fb;
  int altura;
  struct arv *esq;
  struct arv *dir;
} TArv;
typedef TArv *PArv;

int max(int a, int b) { // usaremos para calcular as alturas das árvores
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

int fator_balanceamento(PArv a) {

  if (a == NULL) {
    return 0;
  }
  return (altura(a->esq) - altura(a->dir));
}

PArv rotacao_RR(PArv pA) {

  PArv pB = pA->dir;
  PArv aux;

  pA->dir = pB->esq;
  pB->esq = pA;
  aux = pA;
  pA = pB;
  pB = aux;

  pA->altura = altura(pA);
  pA->fb = fator_balanceamento(pA);
  
  pB->altura = altura(pB);
  pB->fb = fator_balanceamento(pB);

  return pA;
}

PArv rotacao_LL(PArv pA) {

  PArv pB = pA->esq;
  PArv aux;
  
  pA->esq = pB->dir;
  pB->dir = pA;
  aux = pA;
  pA = pB;
  pB = aux;
  

  pA->altura = altura(pA);
  pA->fb = fator_balanceamento(pA);
  
  pB->altura = altura(pB);
  pB->fb = fator_balanceamento(pB);

  return pA;
}

PArv rotacao_LR(PArv pA){

  PArv pB = pA->esq;
  PArv pC = pB->dir;
  PArv aux;

  pB->dir = pC->esq;
  pC->esq = pB;
  pA->esq = pC->dir;
  pC->dir = pA;

  aux = pA;
  pA = pC;
  pC = aux;

  pA->altura = altura(pA);
  pA->fb = fator_balanceamento(pA);
  
  pB->altura = altura(pB);
  pB->fb = fator_balanceamento(pB);

  pC->altura = altura(pC);
  pC->fb = fator_balanceamento(pC);
  
  return pA;
}

PArv rotacao_RL(PArv pA){

  PArv pB = pA->dir;
  PArv pC = pB->esq;
  PArv aux;

  pB->esq = pC->dir;
  pC->dir = pB;
  pA->dir = pC->esq;
  pC->esq = pA;

  aux = pA;
  pA = pC;
  pC = aux;

  pA->altura = altura(pA);
  pA->fb = fator_balanceamento(pA);
  
  pB->altura = altura(pB);
  pB->fb = fator_balanceamento(pB);

  pC->altura = altura(pC);
  pC->fb = fator_balanceamento(pC);

  return pA;
}

PArv buscaABB(PArv a, int valor) {

  if (a == NULL) {
    return NULL; //árvore vazia
  } else if (valor < a->info) {
    return buscaABB(a->esq, valor);
  } else if (valor > a->info) {
    return buscaABB(a->dir, valor);
  } else {
    return a; // encontrou o valor
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

PArv rebalanceamento(PArv a){
  
  a->fb = fator_balanceamento(a);
  a->altura = altura(a);

  if (a->fb > 1 && a->esq->fb >= 0) {
    return rotacao_LL(a);
  }
  if (a->fb < -1 && a->dir->fb <= 0) {
    return rotacao_RR(a);
  }
  if (a->fb > 1 && a->esq->fb < 0) {
    return rotacao_LR(a);
  }
  if (a->fb < -1 && a->dir->fb > 0) {
    return rotacao_RL(a);
  }
  
  return a;
}

PArv insereABB(PArv a, int valor) {

  PArv novo;

  if (a == NULL) { //árvore vazia
    novo = (PArv)malloc(sizeof(TArv));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->info = valor;
    novo->altura = 1;
    novo->fb = 0;

    return novo;
  } else if (valor < a->info) {
    a->esq = insereABB(a->esq, valor);
  } else if (valor > a->info) {
    a->dir = insereABB(a->dir, valor);
  } else {
    return a;
  }

  a = rebalanceamento(a);
  
  return a;
}

PArv removeABB(PArv a, int valor) {
  PArv t, pai, f;

  if (a == NULL) {
    return a; // nao encontrou a chave
  } else if (valor < a->info) {
    a->esq = removeABB(a->esq, valor);
  } else if (a->info < valor) {
    a->dir = removeABB(a->dir, valor);
  }
  else {                                    // achou o elemento
    if (a->esq == NULL && a->dir == NULL) { // elemento sem filhos
      free(a);
      a = NULL;
    } else if (a->esq == NULL) { // só tem filho à direita
      t = a;
      a = a->dir;
      free(t);
    } else if (a->dir == NULL) { // só tem filho à esquerda
      t = a;
      a = a->esq;
      free(t);
    } else { // tem os dois filhos
      pai = a;
      f = a->dir;

      while (f->esq != NULL) { // busca o menor a esquerda
        pai = f;
        f = f->esq;
      }

      a->info = f->info; // troca as informações

      if (pai == a) { // quando o pai do maior valor é o próprio nó raiz que tem
                      // que ser removido
        pai->dir = f->dir;
      } else {
        pai->esq = f->dir;
        free(f);
      }
      
      a = rebalanceamento(a);
      return a;
    }

  }

  if (a!= NULL){
    a = rebalanceamento(a);
  }

  return a;
}

int main() {

  PArv arv = NULL;
  PArv busca = NULL, no_procura = NULL;
  int num = 0;
  int alt, sub_d, sub_e;

  while (num >= 0) {
    scanf("%d", &num);

    if (num >= 0) {
      arv = insereABB(arv, num);
    }
  }

  alt = altura(arv);
  sub_d = altura(arv->dir);
  sub_e = altura(arv->esq);

  num = 0;
  while (num >= 0) {
    scanf("%d", &num);

    if (num >= 0) {
      busca = buscaABB(arv, num);
      if (busca == NULL) {
        arv = insereABB(arv, num);
      } else {
        arv = removeABB(arv, num);
      }
    }
  }

  scanf("%d", &num);

  no_procura = buscaABB(arv, num);

  printf("%d, %d, %d", alt - 1, sub_e, sub_d);
  
  
  if (no_procura == NULL) {
    printf("\nValor nao encontrado");
  } else {
    alt = altura(no_procura);
    sub_e = altura(no_procura->esq);
    sub_d = altura(no_procura->dir);

    printf("\n%d, %d, %d", alt - 1, sub_e, sub_d);
  }
  printf("\n\n");

  arv = libera(arv);

  return 0;
}