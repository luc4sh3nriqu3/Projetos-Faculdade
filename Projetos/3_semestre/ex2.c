/*
Algoritmos e Estruturas de Dados II “Exercício 2"
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IA
*/

#include <stdio.h>
#include<stdlib.h>

int compra_vale(int qtd_vale, int val_vale){

  int livros_vale = 0;
  int resto_vale;
  
  if(qtd_vale >= val_vale){

    livros_vale = qtd_vale / val_vale;
    resto_vale = qtd_vale % val_vale;

    livros_vale = livros_vale + compra_vale(livros_vale + resto_vale, val_vale);
    
  }

  return livros_vale;

}

int main(void) {

  int N, i;
  int d, p, v;
  int livros;

  scanf("%d", &N);

  for(i = 0; i < N; i++){
    
    scanf("%d", &d); 
    scanf("%d", &p);
    scanf("%d", &v);

    livros = d / p;
    
    livros =  livros + compra_vale(livros, v);

    printf("\n%d", livros);
  }
  
  return 0;
}