#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int maior_palavra(char** palavras, int N){

  int i, j;
  int cont;
  int max;
  char aux[20];

  max = strlen(palavras[0]);

  for(i = 0; i < N; i++){
    cont = 0;
    for(j = 0; palavras[i][j] != '\0'; j++){
      cont++;
      }
    
    if(cont > max){
      max = cont;
    }
    
  }

  return max;
}

char** counting_sort(char** palavras, char**palavras2, int N, int c){

  int C[27];
  int i, pos, j;

  for(i = 0; i < 27; i++){
    C[i] = 0;
  }

  for(i = 0; i < N; i++){
    if(palavras[i][c] == ' '){
      C[0] = C[0] + 1;
    }
    else{
      pos = palavras[i][c] - 96;
      C[pos] = C[pos] + 1;
    }
  }

  printf("%d ", C[0]);
  for(i = 1; i < 27; i++){
    C[i] = C[i] + C[i-1];
    printf("%d ", C[i]);
  }
  if(c!= 0){
    printf("\n");
  }
  
  for(i = N-1; i >= 0; i--){
    if(palavras[i][c] == ' '){
      C[0] = C[0] - 1;
      palavras2[C[0]] = palavras[i];
    }
    else{
      pos = palavras[i][c] - 96;
      
      C[pos] = C[pos] - 1;
      palavras2[C[pos]] = palavras[i];
    }
  }

  return palavras2;
}

char** radix_sort(char** palavras, char** palavras_ordenadas, int max, int N){
  
  int i,j;
  
 for(i = max - 1; i >= 0; i--){
    palavras_ordenadas = counting_sort(palavras, palavras_ordenadas, N, i);
   for(j=0;j<N; j++){
     palavras[j] = palavras_ordenadas[j];
   }
  }

  return palavras_ordenadas;
}

int main(void) {

  int N;
  int P; //posição do elemento a ser mostrado na lista ordenada
  int M; //a partir do elemento na posicao P, mostrar mais M-1 (pois ja será impresso o da posicao P) elementos
  char **palavras, **palavras_ordenadas;
  int C[27], i, j;
  int max, inicio;

  scanf("%d", &N);

  palavras = (char**) malloc(N * sizeof(char*));

  for(i = 0; i < N; i++){
    palavras[i] = (char*) malloc(20 * sizeof(char));
    scanf("%s", palavras[i]);
  }

  scanf("%d", &P);
  scanf("%d", &M);

  //transformando todos os caracteres em minúsculos
  for(i = 0; i < N; i++){
    for(j=0; palavras[i][j] != '\0'; j++){
      if(palavras[i][j]>='A' && palavras[i][j]<='Z'){
        palavras[i][j] = palavras[i][j] + 32;
      }
    }
  }

  for(i=0;i<N;i++){
    printf("%s.\n", palavras[i]);
  }
  
  //achando a maior palavra
  max = maior_palavra(palavras, N);

  for(i = 0; i < N; i++){
    inicio = strlen(palavras[i]);

    //adicionando um espaço em branco nas palavras menores até completar o tamanho da maior palavra
    for(j = inicio; j < max; j++){
      palavras[i][j] = ' ';
    }
  }

  printf("%d\n", max);

  palavras_ordenadas = (char**) malloc(N * sizeof(char*)); 
  
  for(i = 0; i < N; i++){
    palavras_ordenadas[i] = (char*) malloc(20 * sizeof(char));
  }

  palavras_ordenadas = radix_sort(palavras, palavras_ordenadas, max, N);

  i = P-1;
  while(M > 0){
    printf("\n%s", palavras_ordenadas[i]);
    i++;
    M--;
  }

  free(palavras);
  free(palavras_ordenadas);
  
  return 0;
}