
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
  
  int tmp = *a;
  *a = *b;
  *b = tmp;
  
}

int particao(int vet[], int min, int max){
  
  int x, i, j;
  
  x = vet[max];
  i = min;
  
  for(j = min; j <= max - 1; j++){
    if(vet[j] <= x){
      swap(&vet[i], &vet[j]);
       i++;
    }
  }

  swap(&vet[i], &vet[max]);

  return i;
}

int quicksort(int vet[], int min, int max, int k, int N){

  int posicao, i;

  
if (k > 0 && k <= max - min + 1){

    posicao = particao(vet, min, max);
    
    
    if(posicao - min == k - 1){
      return vet[posicao];
      
    }
    if(posicao - min > k - 1){
     return quicksort(vet, min, posicao - 1, k, N);
    }
    else{ 
     return quicksort(vet, posicao + 1, max, k - posicao + min - 1, N);
    }
  
  }
  
  return 0;
}

int main(void) {

  int k; //posição do elemento que estamos procurando
  int N; // tamanho do vetor
  int *vet;
  int i, num;

  scanf("%d", &k);
  scanf("%d", &N);

  if(k <= N){

    vet = (int*) malloc(N * sizeof(int));
    
    for(i = 0; i < N; i++){
      scanf("%d", &num);
      vet[i] = num;
    }

    printf("%do menor elemento eh o %d\n", k, quicksort(vet, 0, N-1, k, N)); //Passando N no ultimo argumento apenas na hora do print

    for(i = 0; i < N; i++){
      printf("%d ", vet[i]);
    }
    free(vet);
  }

  return 0;
}