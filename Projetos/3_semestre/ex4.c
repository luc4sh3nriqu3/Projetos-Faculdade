#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
  int num;
  struct lista *prox;
}TLista;
typedef TLista *PLista;

PLista insere(PLista l, int num){

  PLista novo = (PLista) malloc(sizeof(TLista));

  novo->num = num;
  novo->prox = l;
  
  return novo;
}

void libera(PLista l){

  PLista p = l, t;

  while(p != NULL){
    t = p->prox;
    free(p);
    p = t;
  }
  
}

void imprime(PLista l){
  
  if(l != NULL){
    printf("%d ", l->num);
    imprime(l->prox);
  }

}

PLista ordena(PLista a, PLista b){

  PLista lista_ordenada = NULL;

  //casos em que teremos um nó com apenas um filho
  if(a == NULL){
    return b;
  }
  else if(b == NULL){
    return a;
  }

  //caso de nó com dois filhos
  if(a->num >= b->num){
    lista_ordenada = b;
    lista_ordenada->prox = ordena(a, b->prox);
  }
  else{
    lista_ordenada = a;
    lista_ordenada->prox = ordena(a->prox, b);
  }

  return lista_ordenada;
}

void divide_lista(PLista no_cabeca, PLista *a, PLista *b){

  PLista s;
  PLista f;

  s = no_cabeca;

  while(f != NULL){ //aqui, avancaremos o f para o anti-penultimo nó da lista, e o s para o nó anterior ao nó do meio da lista
    f = f->prox;
    
    if(f != NULL){
      s = s->prox;
      f = f->prox;
    }
  }

  *a = no_cabeca;
  *b = s->prox;
  s->prox = NULL;
}

void MergeSort(PLista *l){
  PLista no_cabeca = *l;
  PLista a;
  PLista b;

  if(no_cabeca == NULL || no_cabeca->prox == NULL){ //lista vazia
    return;
  }

  divide_lista(no_cabeca, &a, &b);

  MergeSort(&a); //aqui dividiremos todas as sublistas a e b
  MergeSort(&b);

  *l = ordena(a, b);
  
}



int main(void) {

  int N, i, num;
  PLista lista = NULL;
  PLista lista_ordenada = NULL;
  int nivel = 0;

  scanf("%d", &N);

  for(i = 0; i < N; i++){
    scanf("%d", &num);
    lista = insere(lista, num);
  }
  
  MergeSort(&lista);
  imprime(lista);
  libera(lista);
  
  return 0;
}