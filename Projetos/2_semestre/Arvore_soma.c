/*
Algoritmos e Estruturas de Dados � Exerc�cio 8 - �rvores gen�ricas (PESO 1.5)"
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IB
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

#define MAX 502

typedef struct arvGen{
	char operador;
	int num;
	struct arvGen *prim;
	struct arvGen *prox;
}TArvGen;
typedef TArvGen *PArvGen;

char myexp2[MAX]; //Ser� a string final contendo a express�o arrumada

int arruma_exp(char exp[]){
	
	char *p = exp;
	char *aux;
	int i = 0;
	int verifica = 0;
	
	if(*p == '+'){ //pula o primeiro caractere caso ele seja um espa�o
		p++;
	}
	else if(*p == '-'){ //verifica o erro do primeiro numero ser negativo
		verifica = 1;
	}
	
	while(*p != '\0'){
		
		if(*p == ' ' || *p == '\n'){ //pula os espa�os da express�o e o '\n' pois pegamos a vari�vel pelo fgets
		 	p++;
		}
		else{
			if(isdigit(*p) != 0){ /*VERIFICA��O DE DIGITOS SEGUIDOS*/
				aux = p;
				aux++;
				
				while(*aux == ' '){
					aux++;
				}
				
				if(isdigit(*aux) != 0 && isdigit(*--aux) == 0){ //verifica se tem d�gitos seguidos. o *--aux � 
					verifica = 1;								//pra verificar se o caractere antes do d�gito � um espa�o
				}
				
			}
			myexp2[i] = *p;
			i++;
		 	p++;
		}
	}
	
	for(i = 0; i < strlen(myexp2); i++){
		
		if((myexp2[i] == '+' || myexp2[i] == '-') && (myexp2[i+1] == '+' || myexp2[i+1] == '-')){ //verifica se foram digitados 
			verifica = 1;																		  //dois operadores seguidos
		}
		
		if((isdigit(myexp2[i]) == 0) && (myexp2[i] != '+' && myexp2[i] != '-')){ //verifica se foi digitado algum caractere 
			verifica = 1;														 //al�m de '+' ou '-'
		}
	}
	
	if(myexp2[strlen(myexp2) - 1] == '+' || myexp2[strlen(myexp2) - 1] == '-'){ //verifica se o �ltimo caractere � um operador
		verifica = 1;
	}
	
	if(verifica == 1){
		memset(myexp2, 0, MAX); //limpar a vari�vel para que possa ser inserido um novo valor
	}
	
	return verifica;
}

PArvGen inicializa(){
	return NULL;
}

PArvGen cria(PArvGen esq, PArvGen dir, int numero, char operador){
	
	PArvGen a = (PArvGen) malloc(sizeof(TArvGen));
	
	if(operador == ' '){ //pois se for um espa�o, significa que o 
		a->num = numero; //n� � um n� que tem que guardar um numero
		a->prim = NULL;  
		a->prox = NULL;
		
		
	}
	else if(numero == -1){       //pois se for -1 significa que o n� � um 
		a->operador = operador;  //n� que tem que guardar um operador
		a->prim = dir;
		a->prox = esq;
	}
	
	return a;
}

PArvGen insere(char exp[]){
	
	int num1, num2, qtd_digitos;
	char operador;
	PArvGen a = inicializa();
	char *p = exp;
	
	/*A primeira inser��o ser� de forma manual. Leremos o primeiro numero, o 
	operador do segundo numero e o segundo numero
	iremos passar os valores de ' ' e '-1' para a fun��o cria para que ela saiba
	qual o tipo de n� que tem que ser alocado*/ 
	
	if(sscanf(p, "%d%c%d%n", &num1, &operador, &num2, &qtd_digitos) == 3){
		a = cria(cria(NULL, NULL, num1, ' '), cria(NULL, NULL, num2, ' '), -1, operador);
		p = p + qtd_digitos; //avan�amos o p para a posi��o desejada (posi��o de um operador)
	}
	else{
		return NULL;
	}
	
	//Aqui, leremos um numero e o seu respectivo operador
	while(sscanf(p, "%c%d%n", &operador, &num1, &qtd_digitos) == 2){
		a = cria(a, cria(NULL, NULL, num1, ' '), -1, operador);
		p = p + qtd_digitos; 
	}
	
	return a;
}

void imprime(PArvGen a, int nivel){  //imprime a �rvore
     int i;
     
	 if(a != NULL){
     	imprime(a->prim, nivel+1);
     	for(i = 0;i < nivel; i++){
        	printf("\t");
			}
     	if(a->operador == '+' || a->operador == '-'){
		
			printf("%c\n", a->operador);
			imprime (a->prox, nivel+1);
		}
		else{
			printf("%d\n", a->num);
		}
     }
}

int soma(PArvGen a){
	
	int somatorio = a->num;

	if(a != NULL){
		if(a->operador == '+'){
			somatorio = soma(a->prox) + soma(a->prim); //chamada recursiva da fun��o soma
		}
		else if(a->operador == '-'){
			somatorio = soma(a->prox) - soma(a->prim); //chamada recursiva da fun��o soma
		}
	}
	
	return somatorio; 
}

PArvGen libera(PArvGen a){
	
	if(a != NULL){
		libera(a->prox);
		libera(a->prim);
		free(a);
	}
}

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	char exp[MAX];
	char *p;
	int verif;
	int total = 0;
	char c;
	
	do{
		
		system("clear||cls");
		printf("Digite a express�o: ");
		fgets(exp, MAX, stdin);
	
		verif = arruma_exp(exp);
		
		if(verif == 1){
			printf("\nERRO: express�o inv�lida.");
			printf("\nPressione qualquer tecla para digitar novamente uma express�o...");
			getchar();
		}
	
	}while(verif == 1);

	PArvGen arv = insere(myexp2);
	
	printf("\n�rvore digitada:\n");
	printf("_______________________________________________\n\n");
	imprime(arv, 0);
	printf("_______________________________________________\n\n");
	total = soma(arv);
	
	
	printf("_______________________________________________\n\n");
	printf("A solu��o da express�o �: %d", total);
	printf("\n_______________________________________________\n\n");
	
	arv = libera(arv);
	
	return 0;
}
