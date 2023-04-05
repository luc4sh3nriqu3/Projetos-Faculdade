/*
Algoritmos e Estruturas de Dados II “Exercício 1"
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IA
*/

#include <stdio.h>
#include<stdlib.h>

typedef struct lista{
  int info;
  int posicao;
  struct lista *prox;
  struct lista *ant;
}TLista;
typedef TLista *PLista;

PLista aloca_ordenado(PLista l, int v, int pos){

  PLista aux, ant;
  PLista novo = (PLista) malloc(sizeof(TLista));

  novo->info = v;
  novo->posicao = pos; //importante apenas para a função define_pos

  if(l == NULL){
    novo->prox = NULL;
    novo->ant = NULL;
    l = novo;
  }
  else{
    aux = l;
    while(aux->prox != NULL && aux->info < v){ //aqui, iremos andar até o nó onde deveremos inserir o novo numero
      aux = aux->prox;
    }

    if(aux->info < v){ //insere novo no fim, caso o novo numero seja maior
      novo->prox = NULL;
      novo->ant = aux;
      aux->prox = novo;
    }
    else{
      novo->prox = aux;
      novo->ant = aux->ant;

      if(aux->ant != NULL){ /* se não for o 1o. nó */
        aux->ant->prox = novo;
      }
      else{
        l = novo;
        novo->ant = NULL;
      }
      aux->ant = novo;
    }
  }
  
  return l;
}

PLista define_pos(PLista l, int N){ //criaremos uma nova lista porém com as posições de cada elemento
  
  PLista p = l;
  PLista l_nova = NULL;
  int i;
  
  for(i = 0; i < N; i++){
    l_nova = aloca_ordenado(l_nova, p->info, i);
    p = p->prox;
  }

  return l_nova;
}

int procura_num(PLista l, int numero, int min, int max, int *cont){

  PLista p = l;
  
  int meio_lista;
  int a;
  
  if(min <= max){ //enquato a lista for válida
    
      meio_lista = ((min + max) / 2);

      while(p->posicao != meio_lista){
        p = p->prox;
      }

      if(p->info == numero){
        return numero;
      }
      else if(p->info < numero){
        *cont = *cont + 1;
        return procura_num(p, numero, meio_lista + 1, max, cont);
      }
      else{
        *cont = *cont + 1;
        return procura_num(l, numero, min, meio_lista - 1, cont);
      }
    
    
  }
  
  return -1;
}

PLista libera(PLista l){

  if(l != NULL){
   libera(l->prox);
    free(l);
  }
  return NULL;
}

int main(void) {

  int N; //numero de elementos da sequencia
  int numero; //numeros da sequencia
  int i;
  int num_procura; //numero a ser procurado na sequencia
  PLista lista_num = NULL;
  int a; //se achar o numero o a será igual ao numero procurado, senao sera igual a -1
  int cont = 0; //contador de recursão
  
  scanf("%d", &N);

  for(i = 0; i < N; i++){
    scanf("%d", &numero);
    lista_num = aloca_ordenado(lista_num, numero, i);
  }
  
  lista_num = define_pos(lista_num, N);
  
  scanf("%d", &num_procura);
  
  a = procura_num(lista_num, num_procura, 0, N - 1, &cont);

  if(a == -1){
    printf("%d nao foi encontrado", num_procura);
  }
  else{
    printf("%d", cont);
  }

  lista_num = libera(lista_num);
  
  return 0;
}