/*
Algoritmos e Estruturas de Dados “ Exercício 6 - Lista Duplamente Encadeada (PESO 3.0)"
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IB
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define MAX 1000

typedef struct lista2{
	int coeficiente;
	int expoente;
	struct lista2 *ant;
	struct lista2 *prox;
}TLista2;
typedef TLista2 *PLista2;

PLista2 insere(PLista2 l, int expoente, int coeficiente){
	
	PLista2 aux, ant;
	PLista2 novo = (PLista2) malloc(sizeof(TLista2));
	
	novo->coeficiente = coeficiente;
	novo->expoente = expoente;
	
	if(l == NULL){ //será o primeiro
		novo->ant = NULL;
		novo->prox = NULL;
		l = novo;
	}
	else{
		aux = l;
		while(aux->prox != NULL && aux->expoente > expoente){
			aux = aux->prox;
		}
		
		if(aux->expoente > expoente){ /* insere novo no fim */
			novo->prox = NULL; 
			novo->ant = aux;
			aux->prox = novo;
		}
		else{ /* insere depois de aux */
			novo->prox = aux; 
			novo->ant = aux->ant;
			
			if(aux->ant != NULL) /* se não for o 1o. nó */
				aux->ant->prox = novo;
			else{
				l = novo;/*atualiza início da lista */
				novo->ant = NULL; 
			}
			aux->ant = novo;
		}
	}
	
	return l;
}

void imprime(PLista2 l){
	
	PLista2 p;
	
	for(p = l; p != NULL; p = p->prox){
		if(p->coeficiente < 0){
			printf("%dx^%d", p->coeficiente, p->expoente);
		}
		else{
			printf("+%dx^%d", p->coeficiente, p->expoente);
		}
	}
	printf("\n");
}

PLista2 soma(PLista2 l1, PLista2 l2){
	
	PLista2 resposta = NULL;
	PLista2 poli1 = l1;
	PLista2 poli2 = l2;
	int coef, exp;
	
	if(l1 == NULL || l1 == NULL){
		printf("ERRO: quantidade de polinômios insuficiente.");
		printf("\nPressione qualquer tecla para voltar ao menu...\n");
		getch();
		return NULL;
	} 
	else{
	
		while(poli1 != NULL && poli2 != NULL){
			 
		 	if(poli1->expoente == poli2->expoente){
				exp = poli1->expoente;
		 		coef = poli1->coeficiente + poli2->coeficiente;
		 		poli1 = poli1->prox;
		 		poli2 = poli2->prox;
		 		if(coef != 0) resposta = insere(resposta, exp, coef);
		 	}
	
			 else if(poli1->expoente < poli2->expoente){
				exp = poli2->expoente;
		 		coef = poli2->coeficiente;
		 		poli2 = poli2->prox;
		 		if(coef != 0) resposta = insere(resposta, exp, coef);
		 	}
		 	
		 	else{
				exp = poli1->expoente;
		 		coef = poli1->coeficiente;
		 		poli1 = poli1->prox;
		 		if(coef != 0) resposta = insere(resposta, exp, coef);
		 	}
			 
			 if(poli1 != NULL && poli2 == NULL){
			 	while(poli1 != NULL){
			 		if(coef != 0) resposta = insere(resposta, poli1->expoente, poli1->coeficiente);
			 		poli1 = poli1->prox;
				 }
			 }
			 
			 if(poli1 == NULL && poli2 != NULL){
			 	while(poli2 != NULL){
			 		if(coef != 0) resposta = insere(resposta, poli2->expoente, poli2->coeficiente);
			 		poli2 = poli2->prox;
				 }
			 }	
		}
	}
	
	if(resposta == NULL){
		resposta = insere(resposta, 0, 0);
	}
	
	return resposta;
}

PLista2 subtrai(PLista2 l1, PLista2 l2){
	
	PLista2 resposta = NULL;
	PLista2 poli1 = l1;
	PLista2 poli2 = l2;
	int coef, exp;
	
	if(l1 == NULL || l1 == NULL){
		printf("ERRO: quantidade de polinômios insuficiente.");
		printf("\nPressione qualquer tecla para voltar ao menu...\n");
		getch();
		return NULL;
	} 
	else{
	
		while(poli1 != NULL && poli2 != NULL){
			 
			 if(poli1->expoente > poli2->expoente){
				exp = poli1->expoente;
			 	coef = poli1->coeficiente;
		 		poli1 = poli1->prox;
			 	if(coef != 0) resposta = insere(resposta, exp, coef);
			 	
			 }
		 	else if(poli1->expoente < poli2->expoente){
				exp = poli2->expoente;
			 	coef = poli2->coeficiente;
			 	poli2 = poli2->prox;
			 	if(coef != 0) resposta = insere(resposta, exp, coef);
			 }
			 else{
				exp = poli1->expoente;
			 	coef = poli1->coeficiente - poli2->coeficiente;
		 		poli1 = poli1->prox;
		 		poli2 = poli2->prox;
		 		if(coef != 0) resposta = insere(resposta, exp, coef);
		 	}
			 
			if(poli1 != NULL && poli2 == NULL){
				while(poli1 != NULL){
			 		if(coef != 0) resposta = insere(resposta, poli1->expoente, poli1->coeficiente);
			 		poli1 = poli1->prox;
				 }
			 }
			 
			if(poli1 == NULL && poli2 != NULL){
				while(poli2 != NULL){
			 		if(coef != 0) resposta = insere(resposta, poli2->expoente, poli2->coeficiente);
			 		poli2 = poli2->prox;
				 }
			 }		
		}
	}
	
	if(resposta == NULL){
		resposta = insere(resposta, 0, 0);
	}
	
	return resposta;
}

PLista2 deriva(PLista2 l){
	
	PLista2 resposta = NULL;
	PLista2 p;
	int coef, exp;
	
	if(l == NULL){
		printf("ERRO: polinômio não inserido.");
		printf("\nPressione qualquer tecla para voltar ao menu...\n");
		getch();
		return NULL;
	}
	else{
		
		for(p = l; p != NULL; p = p->prox){
			coef = p->coeficiente * p->expoente;
			exp = p->expoente - 1;
			
			if(coef != 0) resposta = insere(resposta, exp, coef);
			
		}
	}
	
	if(resposta == NULL){
		resposta = insere(resposta, 0, 0);
	}
	
	return resposta;
}

int verifica_grau(PLista2 l){
	
	if(l->expoente == 0){
		return 0;
	}
	else{
		return 1;
	}
}

PLista2 libera(PLista2 l){
	
	if(l != NULL){
		libera(l->prox);
		free(l);
	}
	
	return NULL;
}

/*Função criada para avisar ao usuário qual a maneira correta de inserir o polinômio para que ele que ele possa ser 
manipulado pois naõ foi possível fazer a verificação de erros na entrada dos polinômios*/
void cabecalho(){
	
	system("cls");
	printf("INSERÇÃO DE NOVOS POLINÔMIOS");
	printf("\n---------------------------------------\n\n");
	printf("ATENÇÃO: Insira o polinômio de maneira correta!\nobs:\n");
	printf("1) Digitar todo o polinômio sem espaços\n");
	printf("2) Todo monômio (inclusive o primeiro) deve ter um operador '+' ou '-' na\nfrente do coeficiente\n");
	printf("3) Todos os coeficientes e expoentes devem ser colocados na hora de inserir o\npolinômio (incluindo os que são igual a 0 e igual a 1)\n\n");
	printf("Entradas válidas:\n");
	printf("1) +3x^2-24x^3+3x^5\n");
	printf("2) -1x^3+3x^10+12x^1\n");
	printf("3) +2x^1-3x^0+1x^8\n\n");
	printf("Entradas inválidas:\n");
	printf("1) +x^10 + 12x^2\n");
	printf("2) x^2+2x^4\n");
	printf("3) 2x+3\n\n");
	
}

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int e = 0, i, qtd_poli1 = 1, qtd_poli2 = 1, digitos;
	int verifica, contador = 0;
	char operador, aux, aux2, num_str[MAX];
	int coeficiente, expoente;
	char poli1[MAX], poli2[MAX];
	char *p;
	PLista2 polinomio1 = NULL, polinomio2 = NULL;
	PLista2 polinomio_soma = NULL, polinomio_subtracao = NULL;
	PLista2 polinomio_derivado = NULL;
	
	
	while(e < 5){
	
		A:system("cls"); 
		printf("MENU");
		printf("\n--------------------------------\n");
		printf("| 1 | Inserir novos polinômios\n");
		printf("| 2 | Somar polinômios\n");
		printf("| 3 | Subtrair polinômios\n");
		printf("| 4 | Derivar um polinômio\n");
		printf("| 5 | Sair\n\n");
		printf("Opção: ");
	
		scanf("%d", &e);
	
		switch(e){
			
			case 1:
				
				if(contador >= 1){
					polinomio1 = libera(polinomio1);
					polinomio2 = libera(polinomio2);
				}
				
				C: cabecalho();
				
				/*Caso tenha inserido o polinômio da maneira correta e aparecer mensagem de erro é só colocá-lo novamente
				da mesma maneira que irá funcionar*/
				printf("Insira o primeiro polinômio: ");
				scanf("%s", poli1);
				
				p = poli1;
				
				for(i = 0 ; i < strlen(poli1); i++){
					p = &poli1[i];
					if((*p == '-' || *p == '+') && p != &poli1[0]){
						qtd_poli1++;
					}
				}
				
				p = poli1;
				
				printf("%d", qtd_poli1);
				getch();
				
				for(i = 0; i < qtd_poli1; i++){
					p += sscanf(p, "%c%d%c%c%d", &operador, &coeficiente, &aux, &aux2, &expoente);
					
					itoa(coeficiente, num_str, 10);
					digitos = strlen(num_str);
					p += digitos - 1;
					
					itoa(expoente, num_str, 10);
					digitos = strlen(num_str);
					p += digitos - 1;
					
					if(operador == '-'){
						coeficiente = coeficiente - (2 * coeficiente);
					}
					
					if((operador != '-' && operador != '+') || (aux != 'x' ) || (aux2 != '^')){
						printf("\nERRO: Operação inválida!\n");
						printf("Pressione qualquer tecla para inserir novamente o polinômio...");
						polinomio1 = libera(polinomio1);
						qtd_poli1 = 1;
						getch();
						goto C;
					}
					
					if(coeficiente != 0) polinomio1 = insere(polinomio1, expoente, coeficiente);
					
				}
				
				verifica = verifica_grau(polinomio1);
				
				if(verifica == 0){
					printf("\nERRO: Polinômio de maior grau igual a zero!\n");
					printf("Pressione qualquer tecla para inserir novamente o polinômio...");
					polinomio1 = libera(polinomio1);
					qtd_poli1 = 1;
					getch();
					goto C;
				}
				
				
				D: cabecalho(); 
				
				/*Caso tenha inserido o polinômio da maneira correta e aparecer mensagem de erro é só colocá-lo novamente
				da mesma maneira que irá funcionar*/
				printf("Insira o segundo polinômio: ");
				scanf("%s", poli2);
				
				p = poli2;
				
				for(i = 0 ; i < strlen(poli2); i++){
					p = &poli2[i];
					if((*p == '-' || *p == '+') && p != &poli2[0]){
						qtd_poli2++;
					}
				}
				
				p = poli2;
				
				for(i = 0; i < qtd_poli2; i++){
					p += sscanf(p, "%c%d%c%c%d", &operador, &coeficiente, &aux, &aux2, &expoente);
					
					itoa(coeficiente, num_str, 10);
					digitos = strlen(num_str);
					p += digitos - 1;
					
					itoa(expoente, num_str, 10);
					digitos = strlen(num_str);
					p += digitos - 1;
					
					if(operador == '-'){
						coeficiente = coeficiente - (2 * coeficiente);
					}
					
					if((operador != '-' && operador != '+') || (aux != 'x' ) || (aux2 != '^')){
						printf("\nERRO: Operação inválida!\n");
						printf("Pressione qualquer tecla para inserir novamente o polinômio...");
						polinomio2 = libera(polinomio2);
						qtd_poli2 = 1;
						getch();
						goto D;
					}
					
					if(coeficiente  != 0) polinomio2 = insere(polinomio2, expoente, coeficiente);
					
				}
				
				verifica = verifica_grau(polinomio2);
				
				if(verifica == 0){
					printf("\nERRO: Polinômio de maior grau igual a zero!\n");
					printf("Pressione qualquer tecla para inserir novamente o polinômio...");
					polinomio2 = libera(polinomio2);
					qtd_poli1 = 1;
					getch();
					goto D;
				}
				
				system("cls");
				printf("\n------------------------------------------------------------------------------------\n");
				printf("\nPolinômio 1: ");
				printf("%s\n", poli1);
				printf("Polinômio 1 na forma decrescente de acordo com o coeficiente: ");
				imprime(polinomio1);
				printf("\n------------------------------------------------------------------------------------\n");
				printf("\nPolinômio 2:");
				printf("%s\n", poli2);
				printf("Polinômio 2 na forma decrescente de acordo com o coeficiente: ");
				imprime(polinomio2);
				printf("\n------------------------------------------------------------------------------------\n\n");
				printf("Pressione qualquer tecla para retornar ao menu...");
				getch();
				
				contador++;
				
			break;
				
			case 2:
				system("cls");
				printf("SOMA DE DOIS POLINÔMIOS");
				printf("\n---------------------------------------\n\n");
				
				polinomio_soma = soma(polinomio1, polinomio2);
				
				if(polinomio_soma == NULL){
					goto A;
				}
				
				printf("Polinômio 1: ");
				printf("%s\n", poli1);
				printf("\nPolinômio 2: ");
				printf("%s\n\n", poli2);
				printf("\nSoma: ");
				imprime(polinomio_soma);
				printf("\n---------------------------------------\n\n");
				polinomio_soma =  libera(polinomio_soma);
				printf("Pressione qualquer tecla para retornar ao menu...");
				getch();
				
			break;
			
			case 3:
				
				system("cls");
				printf("SUBTRAÇÃO DE DOIS POLINÔMIOS");
				printf("\n---------------------------------------\n\n");
				
				polinomio_subtracao = subtrai(polinomio1, polinomio2);
				
				if(polinomio_subtracao == NULL){
					goto A;
				}
				
				printf("Polinômio 1: ");
				printf("%s\n", poli1);
				printf("\nPolinômio 2: ");
				printf("%s\n\n", poli2);
				printf("\nSubtração: ");
				imprime(polinomio_subtracao);
				printf("\n---------------------------------------\n\n");
				polinomio_subtracao =  libera(polinomio_subtracao);
				printf("Pressione qualquer tecla para retornar ao menu...");
				getch();
				
			break;
			
			case 4:
				B: system("cls");
				printf("DERIVAR UM POLINÔMIO");
				printf("\n---------------------------------------\n\n");
				
				printf("Qual polinômio você deseja derivar?\n\n");
				printf("1 | Polinômio 1\n");
				printf("2 | Polinômio 2\n\n");
				printf("Opção: ");
				scanf("%d", &i);
				
				switch(i){
					
					case 1:
						system("cls");
						printf("DERIVAR UM POLINÔMIO");
						printf("\n---------------------------------------\n\n");
						
						polinomio_derivado = deriva(polinomio1);
						
						printf("Polinômio: ");
						printf("%s\n\n", poli1);
						
					break;
					
					case 2:
						system("cls");
						printf("DERIVAÇÃO DE UM POLINÔMIO");
						printf("\n---------------------------------------\n\n");
						
						polinomio_derivado = deriva(polinomio2);
						
						printf("Polinômio: ");
						printf("%s\n\n", poli2);
			
					break;
					
					default:
						printf("Escolha inválida!");
						printf("\nPressione qualquer tecla para escolher novamente uma das opções...\n");
						getch();
						goto B;
				}
				
				if(polinomio_derivado == NULL){
					goto A;
				}
				
				printf("Polinômio derivado: ");
				imprime(polinomio_derivado);
				printf("\n---------------------------------------\n\n");
				polinomio_derivado =  libera(polinomio_derivado);
				printf("Pressione qualquer tecla para voltar ao menu...\n");
				getch();
				
			break;
			
			case 5:
				system("cls");
				printf("\n---------------------------------------\n");
				printf("Obrigado pela visita!");
				printf("\n---------------------------------------\n");
				
				polinomio1 = libera(polinomio1);
				polinomio2 = libera(polinomio2);
				polinomio_soma = libera(polinomio_soma);
	 			polinomio_subtracao = libera(polinomio_subtracao);
 				polinomio_derivado = libera(polinomio_derivado);
				
			break;
			
			default:
				system("cls");
				printf("Escolha inválida!");
				printf("\nPressione qualquer tecla para voltar ao menu...\n");
				getch();
				system("cls");
				goto A;	
		}
	}
	
	return 0;
}
