#include <stdio.h>
#include <stdlib.h>

typedef struct no{
  int num;
  struct no *prox;
}No;

typedef struct Hash{
  int tam_tabela; //aqui guardaremos o tamanho da nossa tabela
  No  *inicio; //Aqui guardamos o primeiro nó da lista encadeada
}Hash;

void inicializa_lista(Hash* l){
  l->inicio = NULL;
  l->tam_tabela = 0;
}

void inicializa_hash(Hash* t, int tam){

  int i;

  for(i=0; i < tam; i++){
    inicializa_lista(&t[i]);
  }
}

int funcao_hash(int num, int tam_tabela){
  return (num & 0x7FFFFFFF) % tam_tabela; //Aqui, retiramos o bit de sinal do numero para realizar a função de hash da maneira correta
}

void insere_lista(Hash* l, int num){
  No* novo = malloc(sizeof(No));
  No* aux;

  novo->num = num;
  novo->prox = NULL;

  if(l->inicio == NULL){
    inicializa_lista(l);
    l->inicio = novo;
    l->tam_tabela = l->tam_tabela + 1;
    return;
  }

  aux = l->inicio;
  while(aux->prox != NULL){
    aux = aux->prox;
  }

  aux->prox = novo;
  l->tam_tabela = l->tam_tabela + 1;
}

void remove_lista(Hash* l, int v){

  No* ant = NULL;
  No* p;

  for(p = l->inicio; p != NULL && p->num != v; p = p->prox){
    ant = p;
  }

  if(p == NULL){
    return;
  }
  if(ant == NULL){
    l->inicio = p->prox;
  }
  else{
    ant->prox = p->prox;
  }

  free(p);
  
}

int busca_lista(Hash* l, int n){
  No* aux = l->inicio;

  while(aux != NULL && aux->num != n){
    aux = aux->prox;
  }

  if(aux != NULL){
    return aux->num;
  }

}

int busca_hash(Hash* t, int num, int tam){

  int endereco = funcao_hash(num, tam);

  return busca_lista(&t[endereco], num);
}

void insere_hash(Hash* t, int num, int tam){
  
  int chave_enderecamento;
   No* novo;
  
  chave_enderecamento = funcao_hash(num, tam);

  if(t[chave_enderecamento].inicio == NULL){
    inicializa_lista(&t[chave_enderecamento]);
    insere_lista(&t[chave_enderecamento], num);
  }
  else{
    insere_lista(&t[chave_enderecamento], num);
  }

}

void remove_hash(Hash* t, int val, int tam){
  int chave_enderecamento;
  
  chave_enderecamento = funcao_hash(val, tam);

  remove_lista(&t[chave_enderecamento], val);
}

void libera_lista(No* l){

  No* p = l, *aux;

  while(p != NULL){
    aux = p->prox;
    free(p);
    p = aux;
  }
}

void libera_hash(Hash* t, int tam){

  int i;
  for(i = 0; i < tam; i++){
    libera_lista(t[i].inicio);
  }

  free(t);
}

void imprime_hash(Hash* t, int linha){
  
    No* aux = t[linha].inicio;

    while(aux != NULL){
      printf("%d ", aux->num);
      aux = aux->prox;
    }
  printf("\n");
}

int main(void) {

  int tam_hash;
  int num, chave, busca;
  int linha_hash;
  Hash* tabela;
  
  scanf("%d", &tam_hash);

  tabela = malloc(tam_hash * sizeof(Hash));

  inicializa_hash(tabela, tam_hash);

  do{
    scanf("%d", &num);

    if(num > 0){
      insere_hash(tabela, num, tam_hash);
    }
    
  }while(num != -1);

  scanf("%d", &chave);

  busca = busca_hash(tabela, chave, tam_hash);

  if(busca == chave){ //elemento na tabela
    remove_hash(tabela, chave, tam_hash);
  }
  else{
    printf("Valor nao encontrado\n");
  }

  scanf("%d", &linha_hash);

  printf("[%d] ", linha_hash);
  imprime_hash(tabela, linha_hash);
  
  libera_hash(tabela, tam_hash);
  
  return 0;
}