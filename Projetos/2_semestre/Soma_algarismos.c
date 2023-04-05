/*
Algoritmos e Estruturas de Dados “ Exercício 4- Lista Encadeada (PESO 2.0)"
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IB
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<locale.h>

typedef struct lista{
	int info;
	struct lista *prox;
}TLista;
typedef TLista *PLista;

PLista inicia_lista();
PLista insere(PLista l, int v);
void imprime_soma(PLista l);
void imprime_num(PLista l);
PLista insere_depois(PLista l, int v);
PLista iguala_casas(PLista lista1, PLista lista2, int l1, int l2);
PLista soma(PLista l1, PLista l2);
void libera(PLista l);

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	PLista num1, num2, num_soma;
	char n1[20], n2[20];
	
	A: printf("Insira o valor do primeiro número a ser somado: ");
	scanf("%s", n1);
	
	for(i = 0; i < strlen(n1); i++){
	
		if(isdigit(n1[i]) == 0){
			system("cls");
			printf("ERRO: Digite apenas números!\n");
			goto A;
		}
	}

	B: printf("Insira o valor do segundo número a ser somado: ");
	scanf("%s", n2);
	
	for(i = 0; i < strlen(n2); i++){
	
		if(isdigit(n2[i]) == 0){
			system("cls");
			printf("Insira o valor do primeiro número a ser somado: %s", n1);
			printf("\nERRO: Digite apenas números!\n");
			goto B;
		}
	}
	
	system("cls");
	
	num1 = inicia_lista(num1);
	num2 = inicia_lista(num2);
	num_soma = inicia_lista(num_soma);
	
	for(i=0; i < strlen(n1); i++){
	
		num1 = insere(num1, n1[i] - '0');
	}
	
	
	
	for(i = 0; i < strlen(n2); i++){

		num2 = insere(num2, n2[i] - '0');
	}
	
	iguala_casas(num1, num2, strlen(n1), strlen(n2));
	
	printf("Primeiro número: ");
	imprime_num(num1);
	printf("\n-------------------------------");
	printf("\n");
	printf("Segundo número: ");
	imprime_num(num2);
	printf("\n-------------------------------");
	printf("\n");

	
	num_soma = soma(num1, num2);
	printf("Resultado da soma: ");
	imprime_soma(num_soma);
	printf("\n-------------------------------\n\n");
	
	libera(num1);
	libera(num2);
	libera(num_soma);
	
	return 0;
}

PLista inicia_lista(){
	
	return NULL;
}

PLista insere(PLista l, int v){
	
	PLista novo = (PLista) malloc(sizeof(TLista));
	
	novo->info = v;
	novo->prox = l;
	
	return novo;
}

void imprime_soma(PLista l){
	
	PLista p;
	
	for(p = l; p != NULL; p = p->prox){
		printf("%d", p->info);
	}
}

void imprime_num(PLista l){
	
	PLista p = NULL;
	int *num, i, aux;
	int valor;
	
	
	if(l == NULL){
		printf("Lista vazia!");
		return; 
	}
	
	valor = 0;
	i = 0;
	for(p = l; p != NULL; p = p->prox){
		num = &p->info;
		aux = *num;
		valor = valor + aux * (pow(10, i));
		i++;
	}
	
	printf(" %d", valor);
}

PLista insere_depois(PLista l, int v){
    
	PLista novo; 
	PLista ant = NULL; 
	PLista paux = l;
	
    novo = (PLista) malloc(sizeof(TLista));
    novo->info = v; 

    while (paux != NULL){
        ant = paux;
        paux = paux->prox;
    }

    if (ant == NULL){

        novo->prox = l;
        l = novo;
    }
    else{ 
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    
    return l;
}

PLista iguala_casas(PLista lista1, PLista lista2, int l1, int l2){
	
	int iguala, i;
	
	if(l1 > l2){
		iguala = l1 - l2;
		for(i = 0; i < iguala; i++){
			lista2 = insere_depois(lista2, 0);
		}
	}
	else if(l1 < l2){
		iguala = l2 - l1;
		for(i = 0; i < iguala; i++){
			lista1 = insere_depois(lista1, 0);
		}
	}
}

PLista soma(PLista l1, PLista l2){

	PLista resposta = NULL; 
	PLista lista1 = l1; 
	PLista lista2 = l2;
	int soma;
	
	for(lista1 = l1; lista1 != NULL && lista2 != NULL; lista1 = lista1->prox){
		
		soma = lista1->info + lista2->info;
		
		if(soma >= 10){
			soma = soma - 10;
			resposta = insere(resposta, soma);
			if(lista2->prox == NULL){
				resposta = insere(resposta, 1);
			}
			else{
				lista2 = lista2->prox;
				lista2->info = lista2->info + 1;
			}
		}
		else{
			resposta = insere(resposta, soma);
			lista2 = lista2->prox;
		}
	}
	
	return resposta;
}

void libera(PLista l){
	
	PLista p = l, aux;
	
	while(p != NULL){
		
		aux = p->prox;
		free(p);
		p = aux;
	}
}
