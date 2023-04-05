/*
Algoritmos e Estruturas de Dados “ Exercício 7 - Árvores binárias (PESO 2.0)"
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IB
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<conio.h>
#include<ctype.h>

typedef struct arv{
	char info;
	struct arv *esq;
	struct arv *dir;
}TArv;
typedef TArv *PArv;

PArv inicializa();
PArv cria(char c);
PArv montar_arv(char s1[], char s2[], int pos_ini, int pos_fin, int qtd_nos);
void verifica_prefixa(PArv a, char *vet);
void verifica_infixa(PArv a, char *vet);
void imprime_prefixa(PArv a);
void imprime_infixa(PArv a);
void imprime_posfixa(PArv a);
void imprime(PArv a, int nivel);
PArv libera(PArv a);

int p = 0; //temos que definir esta variável como global para que o valor não se perca com a recursividade

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int i, cont = 0, verif = 0;
	char num_char[101], s1[101], s2[101];
	PArv a = inicializa();
	int num_int;
	char vet1[101], vet2[101];
	
	do{
		cont = 0;
		system("cls");
		printf("Digite a quantidade de nós que a árvore possui: ");
		scanf("%s", num_char);
		
		
		for(i = 0; i < strlen(num_char); i++){
			if(isdigit(num_char[i]) == 0){
				cont = 1;
			}
		}
		
		if(cont != 1){
			
			num_int = atoi(num_char);
			
			if(num_int > 100 || num_int <= 0){
				cont = 2;
			}
		}
		
		
			if(cont == 1){
				system("cls");
				printf("ERRO: Digite apenas números inteiros.");
				printf("\nPressione qualquer tecla para digitar um novo valor...");
				getch();
			}
			else if(cont == 2){
				system("cls");
				printf("ERRO: Valor inválido. \nPor favor digite valores <= 100.");
				printf("\nPressione qualquer tecla para digitar um novo valor...");
				getch();
			}
	
	}while(cont == 1 || cont == 2);
		
		do{
			printf("Digite a sequência dos nós em ordem prefixa: ");
			scanf("%s", s1);
			
			if(strlen(s1) != num_int){
				printf("ERRO: A quantidade de caractéres digitados não condiz com o nº de nós digitado anteriormente.");
				printf("\nPressione qualquer tecla para digitar uma nova sequência...");
				getch();
				system("cls");
			}
		}while(strlen(s1) != num_int);


		do{
			printf("Digite a sequência dos nós em ordem infixa: ");
			scanf("%s", s2);
			
			if(strlen(s2) != num_int){
				printf("ERRO: A quantidade de caractéres digitados não condiz com o nº de nós digitado anteriormente.");
				printf("\nPressione qualquer tecla para digitar uma nova sequência...");
				getch();
				system("cls");
			}
		}while(strlen(s2) != num_int);
		
		a = montar_arv(s1, s2, 0, num_int, num_int);
		
		p = 0;
		verifica_prefixa(a, vet1);
		vet1[num_int] = '\0';
		
		p = 0;
		verifica_infixa(a, vet2);
		vet2[num_int] = '\0';
		
		if(strcmp(vet1, s1) != 0 || strcmp(vet2, s2) != 0){
			printf("\nERRO: Com essas duas sequências digitadas não é possível criar uma árvore válida.");
			printf("\nReinicie o programa para digitar novos valores...");
			a = libera(a);
		}
		else{
			printf("\n\n-----------------------------------\n");
			printf("A árvore digitada é:\n\n");
			imprime(a, 0);
			printf("\n-----------------------------------\n\n");
		}
		
		if(a != NULL){
	
	
		printf("-----------------------------------\n");
		printf("Sequência prefixa:");
		imprime_prefixa(a);
		
		printf("\nSequência infixa:");
		imprime_infixa(a);
		
		printf("\nSequência posfixa:");
		imprime_posfixa(a);
		printf("\n-----------------------------------\n\n");
	}
	
	a = libera(a);
			
	return 0;
}

PArv inicializa(){
	return NULL;
}

PArv cria(char c){
	
	PArv novo = (PArv) malloc(sizeof(TArv));
	novo->info = c;
	novo->esq = NULL;
	novo->dir = NULL;
	
	return novo;
}

PArv montar_arv(char s1[], char s2[], int pos_ini, int pos_fin, int qtd_nos){
	
	int posicao, i;
	char aux;
	
	if((pos_ini > pos_fin) || (p == qtd_nos)){ //condições de parada 
		return NULL;
	}
	
	PArv a = cria(s1[p]); //criamos o nó
	
	if(pos_ini == pos_fin){
		p++;
		return a;
	}
	
	aux = s1[p++];
	
	for(i = 1; i < qtd_nos; i++){
		if(aux == s2[i]){
			posicao = i;
		}
	}
	
	/*Montando a árvore de forma recursiva*/
	a->esq = montar_arv(s1, s2, pos_ini, posicao - 1, qtd_nos); 
	a->dir = montar_arv(s1, s2, posicao + 1, pos_fin, qtd_nos);

	return a;
}

void verifica_prefixa(PArv a, char *vet){
	
	if(a != NULL){ 
		vet[p++] = a->info;
		verifica_prefixa(a->esq, vet);
		verifica_prefixa(a->dir, vet); 
	}

}

void verifica_infixa(PArv a, char *vet){
	
	if(a != NULL){
		verifica_infixa(a->esq, vet); 
		vet[p++] = a->info;
		verifica_infixa(a->dir, vet); 
	}

}

void imprime_prefixa(PArv a){
	int i;
	
	if(a != NULL){
		printf(" %c", a->info); /*Mostra a raiz*/
		imprime_prefixa(a->esq); /*Mostra sae*/
		imprime_prefixa(a->dir); /*Mostra sad*/
		
	}
	
}

void imprime_infixa(PArv a){
	int i;
	
	if(a != NULL){
		imprime_infixa(a->esq); /*Mostra sae*/
		printf(" %c", a->info); /*Mostra a raiz*/
		imprime_infixa(a->dir); /*Mostra sad*/
		
	}
	
}

void imprime_posfixa(PArv a){
	int i;
	
	if(a != NULL){
		imprime_posfixa(a->esq); /*Mostra sae*/
		imprime_posfixa(a->dir); /*Mostra sad*/
		printf(" %c", a->info); /*Mostra a raiz*/
	}
	
}

void imprime(PArv a, int nivel){
     int i;
     
	 if(a != NULL){
     	imprime(a->dir, nivel+1);
     	for(i=0;i<nivel;i++){
        	printf("\t");
			}
     	printf("%c\n", a->info);
     	imprime(a->esq, nivel + 1);
     }
     
}

PArv libera(PArv a){
	
	if(a != NULL){
		libera(a->esq);
		libera(a->dir);
		free(a);
	}
	
	return NULL;
}
