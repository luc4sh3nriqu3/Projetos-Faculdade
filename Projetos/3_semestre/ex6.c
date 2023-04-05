#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void swap(char** a, char** b){
  
  char aux[20];
  
  strcpy(aux, *a);
  strcpy(*a, *b);
  strcpy(*b, aux);
}

void heapify(char** palavra, int i, int N){
  
  int max, l, r;
  int j;
  
  l = (2 * i) + 1;
  r = (2 * i) + 2;
  
  if(l < N && strcmp(palavra[l], palavra[i]) > 0){
    max = l;
  }
  else{
    max = i;
  }

  if(r < N && strcmp(palavra[r], palavra[max]) > 0){
    max = r;
  }

  if(max != i){ //trocando as palavras de posição
    swap(&palavra[i], &palavra[max]);
    heapify(palavra, max, N);
  }
}

void heapsort(char** palavra, int N){

  int i;
  
  for(i = (N / 2) - 1; i >= 0; i--){
    heapify(palavra, i, N);
  }
  
  printf("build_heap:");
  for(i=0; i<N; i++){
    printf(" %s", palavra[i]);
  }

  for(i = N - 1; i > 0; i--){
    swap(&palavra[0], &palavra[i]);
    heapify(palavra, 0, i);
  }
}

int main(void) {

  int N, M;
  int i, j;
  char **palavras, **palavras_heap;
  int posicao;

  scanf("%d", &N);

  palavras = (char**) malloc (N  * sizeof(char*));

  for(i = 0; i < N; i++){
    palavras[i] = (char*) malloc(20 * sizeof(char));
  }

  for(i = 0; i < N; i++){
    scanf("%s", palavras[i]);
  }

  scanf("%d", &M);
  
  palavras_heap = (char**) malloc(M * sizeof(char*));
  
  for(i = 0; i < M; i++){
    palavras_heap[i] = (char*) malloc(20 *sizeof(char));
  }

  for(i = 0; i < M; i++){
    scanf("%d", &posicao);
    strcpy(palavras_heap[i], palavras[posicao]);
  }

  for(i = 0; i < N; i++){
    for(j = 0; palavras[i][j] != '\0'; j++){
      if(palavras[i][j] < 'a' || palavras[i][j] > 'z'){
        printf("a palavra %s eh invalida", palavras[i]);
        return 0;
      }
    }
  }
  
  heapsort (palavras_heap, M);

  printf("\npalavras:");
   for(i=0; i < M; i++){
    printf(" %s", palavras_heap[i]);
  }
 
  return 0;
}