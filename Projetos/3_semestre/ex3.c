#include <stdio.h>
#include <stdlib.h>

int busca_binaria(int vet[], int inicio, int fim, int chave){

    int meio = (inicio + fim) / 2;

    if (inicio >= fim){
        return meio;
		}
    else if( vet[meio] < chave){
	
        return busca_binaria(vet, meio+1, fim, chave);
    }
    else{
	
        return busca_binaria(vet, inicio, meio-1, chave);
    }

}

void ordena_vetor(int vet[], int tam, int *j, int *nivel){

  int chave;
  int i;
  int pos;
  
  if(tam > 1){
    
	chave = vet[*j];
    i = *j - 1;
    
   pos = busca_binaria(vet, 0, i, chave);
   
	while(i>pos){
		vet[i+1] = vet[i];
		i--;
	}
    
    if(vet[pos] <= chave){
      vet[pos+1] = chave;
      pos++;
    }

    else{
      vet[pos+1] = vet[pos];
      vet[pos] = chave;
    }
    
    printf("\n%d %d %d", *nivel, chave, pos);
    
    *j = *j + 1;
    
    tam = tam - 1;

    *nivel = *nivel - 1;
    
    ordena_vetor(vet, tam, j, nivel);
     
  }
  
}

int main(void) {

  int N;
  int i;
  int *vet;
  int j = 1;
  int nivel;

  scanf("%d", &N);

  if(N <= 1000){
    vet = (int *) malloc(N * sizeof(int));
    
    for(i = 0; i < N; i++){
      scanf("%d", &vet[i]);
    }

    nivel = N - 1;
    
    ordena_vetor(vet, N, &j, &nivel);

    printf("\n");
    for(i = 0; i < N; i++){
      printf("%d ", vet[i]);
    }
    
    free(vet);
    
  }
  
  return 0;
}