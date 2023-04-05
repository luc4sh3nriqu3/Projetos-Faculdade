/*
Algoritmos e Estruturas de Dados � Exerc�cio 1 - PESO 1.0
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IB
*/

#include<stdio.h>
#include<locale.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct produto PRODUTO;
struct produto{
    char nome[30];
    int quantidade;
    int mes;
    char comprador[30];
};

int main(){
    setlocale(LC_ALL, "Portuguese");

    PRODUTO *p;
    int n, a;
    int mes;
    int aux;
    int *buscaI;
    char produto[30], comprador[30];
    int comparacao1, comparacao2;
    int soma = 0;

    printf("----------------------------------------------------\n");
    printf("IN�CIO - CADASTRO DE PRODUTOS ");
    printf("\n----------------------------------------------------\n\n");
	printf("Digite a quantidade de produtos a ser alocada: ");
    scanf("%d", &n);

    p = (PRODUTO*) malloc(n*sizeof(PRODUTO));
    if(p == NULL){
    	printf("N�o foi poss�vel alocar esses espa�os.");
    	return 1;
	}

    for(a = 0; a < n; a++){
        
        system("cls");
        printf("----------------------------------------------------\n");
    	printf("IN�CIO - CADASTRO DE PRODUTOS ");
    	printf("\n----------------------------------------------------\n\n");
		printf("Produto %d\n", a+1);
		printf("-------------------------------\n");
        printf("Digite o nome do produto: ");
        scanf("%s", &p[a].nome);
        printf("Digite a quantidade vendida: ");
        scanf("%d", &p[a].quantidade);
        printf("Digite o m�s de vendas desse produto:");
		printf("\n(Dica: Digite um n�mero de 1 at� 12, sendo: )\n( 1 | Janeiro\t\t\t\t    )\n( 2 | Fevereiro\t\t\t\t    )\n( 3 | Mar�o\t\t\t\t    )\n( .\t\t\t\t\t    )\n( .\t\t\t\t\t    )\n( .\t\t\t\t\t    )\n( 12 | Dezembro\t\t\t\t    )");
	    printf("\nDigite aqui o m�s: ");
        scanf("%d", &p[a].mes);
        printf("Digite quem comprou este produto: ");
        scanf("%s", &p[a].comprador);
        printf("----------------------------------------------------\n");
        printf("Produto %d cadastrado com sucesso!\n", a+1);
        printf("\nPressione qualquer tecla para cadastrar o pr�ximo \nproduto, caso haja, ou para ir para o menu...");
        printf("\n----------------------------------------------------\n");
        getch();
    }

    int i = 1;

    while(i>0){
        
        int e;

		system("cls");
        printf("----------------------------------------------------\n");
        printf("VENDAS - MENU ");
        printf("\n----------------------------------------------------\n\n");
        printf("Op��o 1 | Total de vendas num dado m�s.\n");
        printf("Op��o 2 | Total de vendas de um determinado produto num dado m�s para um determinado cliente.\n");
        printf("Op��o 3 | Total de vendas de cada produto.\n");
        printf("Op��o 4 | Total vendido para cada cliente.\n");
        printf("Op��o 5 | Sair do menu.\n");
        printf("Digite aqui: ");
        scanf("%d", &e);

        switch(e){
            case 1:
            	//soma = 0;
                system("cls");
    			printf("----------------------------------------------------\n");
    			printf("VENDAS - TOTAL DE VENDAS NUM DADO M�S ");
    			printf("\n----------------------------------------------------\n\n");
    			
				printf("\nDigite o m�s em que deseja ver o numero total de vendas: ");
    			scanf("%d", &mes);
				if(mes > 12 || mes < 1){
					printf("ERRO: Selecione um m�s de 1 � 12: ");
					scanf("%d", &mes);
				}
				
				system("cls");
				printf("----------------------------------------------------\n");
    			printf("VENDAS - TOTAL DE VENDAS NUM DADO M�S ");
    			printf("\n----------------------------------------------------\n\n");
				printf("\nProdutos vendidos no m�s %d: \n", mes);
				printf("-------------------------------\n");
				
				for(buscaI = &p[0].quantidade, aux = 0; buscaI < &p[n].quantidade, aux < n; buscaI++, aux++){
					buscaI = &p[aux].quantidade;
					
					if(p[aux].mes == mes){
						printf("Produto: %s\n", p[aux].nome);
						printf("Quantidade: %d\n", p[aux].quantidade);
						printf("Cliente: %s\n\n", p[aux].comprador);
						soma = soma + *buscaI;
					}
				}
	
				printf("\n----------------------------------------------------\n");
				printf("O total de produtos vendidos nesse m�s foi de: %d", soma);
				soma = 0;
				printf("\n----------------------------------------------------\n");
				printf("\nPressione qualquer tecla para retornar ao menu...");
				getch();
				
                break;
            case 2:
                system("cls");
    			printf("----------------------------------------------------\n");
    			printf("VENDAS - TOTAL DE VENDAS ESPEC�FICA ");
    			printf("\n----------------------------------------------------\n\n");
    			
				printf("Digite o nome do produto: ");
    			scanf(" %s", &produto);
    			printf("Agora escolha o m�s: ");
    			scanf("%d", &mes);
    			if(mes > 12 || mes < 1){
					printf("ERRO: Selecione um m�s de 1 � 12: ");
					scanf("%d", &mes);
				}
    			printf("Por �ltimo, escolha o nome do cliente: ");
    			scanf(" %s", &comprador);
    			
				system("cls");
				printf("----------------------------------------------------\n");
    			printf("VENDAS - TOTAL DE VENDAS ESPEC�FICA ");
    			printf("\n----------------------------------------------------\n\n");
				printf("-------------------------------\n");
				
				for(buscaI = &p[0].quantidade, aux = 0; buscaI < &p[n].quantidade, aux < n; buscaI++, aux++){
					buscaI = &p[aux].quantidade;
					comparacao1 = strcmp(p[aux].nome, produto);
					comparacao2 = strcmp(p[aux].comprador, comprador);
					
					if(comparacao1 == 0 && p[aux].mes == mes && comparacao2 == 0){
						printf("Produto: %s\n", p[aux].nome);
						printf("M�s: %d\n", p[aux].mes);
						printf("Comprador: %s\n", p[aux].comprador);
						printf("-------------------------------\n");
						printf("\n----------------------------------------------------\n");
						printf("O total de unidades vendidas desse produto com essas \ncondi��es foi de: %d", p[aux].quantidade);
						printf("\n----------------------------------------------------\n");
					}
					else{
						printf("Cadastro n�o encontrado!");
						printf("\n-------------------------------\n");
					}
				}
				
				printf("\nPressione qualquer tecla para retornar ao menu...");
				getch();
				
                break;
            case 3:
            	//soma = 0;
                system("cls");
    			printf("----------------------------------------------------\n");
    			printf("VENDAS - TOTAL DE VENDAS DE CADA PRODUTO ");
    			printf("\n----------------------------------------------------\n\n");
    			
    			printf("Digite o produto que deseja saber a quantidade total vendida: ");
    			scanf(" %s", &produto);
    			
    			system("cls");
    			printf("----------------------------------------------------\n");
    			printf("VENDAS - TOTAL DE VENDAS DE CADA PRODUTO ");
    			printf("\n----------------------------------------------------\n\n");
    			printf("Produto: %s", produto);
				printf("\n-------------------------------\n");
				    			
    			for(buscaI = &p[0].quantidade, aux = 0; buscaI < &p[n].quantidade, aux < n; buscaI++, aux++){
					buscaI = &p[aux].quantidade;
					comparacao1 = strcmp(p[aux].nome, produto);
					
					if(comparacao1 == 0){
						printf("M�s: %d\n", p[aux].mes);
						printf("Quantidade: %d\n\n", p[aux].quantidade);
						
						soma = soma + *buscaI;
					}
				}
				
				printf("\n----------------------------------------------------\n");
				printf("O total de unidades vendidas desse produto foi de: %d", soma);
				soma = 0;
				printf("\n----------------------------------------------------\n");
				printf("\nPressione qualquer tecla para retornar ao menu...");
				getch();
				
                break;
            case 4:
            	//soma = 0;
                system("cls");
        		printf("----------------------------------------------------\n");
        		printf("VENDAS - TOTAL VENDIDO PARA CADA CLIENTE ");
        		printf("\n----------------------------------------------------\n\n");
        		
        		printf("Digite o nome do cliente: ");
        		scanf(" %s", &comprador);
        		
        		system("cls");
        		printf("----------------------------------------------------\n");
        		printf("VENDAS - TOTAL VENDIDO PARA CADA CLIENTE ");
        		printf("\n----------------------------------------------------\n\n");
        		printf("Cliente: %s\n", comprador);
        		printf("-------------------------------\n");
        		
        		for(buscaI = &p[0].quantidade, aux = 0; buscaI < &p[n].quantidade, aux < n; buscaI++, aux++){
					buscaI = &p[aux].quantidade;
					comparacao1 = strcmp(p[aux].comprador, comprador);
					
					if(comparacao1 == 0){
						printf("Produto: %s\n", p[aux].nome);
						printf("M�s: %d\n", p[aux].mes);
						printf("Quantidade: %d\n\n", p[aux].quantidade);
						
						soma = soma + *buscaI;
					}
				}
				
				printf("\n----------------------------------------------------\n");
				printf("O total de unidades vendidas para este cliente foi de: %d", soma);
				soma = 0;
				printf("\n----------------------------------------------------\n");
				printf("\nPressione qualquer tecla para retornar ao menu...");
				getch();
                break;
            case 5:
                system("cls");
        		printf("----------------------------------------------------\n");
        		printf("VENDAS - MENU ");
        		printf("\n----------------------------------------------------\n\n");
				printf("-------------------------------\n");
				printf("Voce saiu do menu!");
				printf("\n-------------------------------\n\n");
				
                return 1;
                break;
            default: 
                printf("op��o inv�lida.\n");
                printf("Pressione qualquer tecla para escolher novamente uma das op��es...");
                getch();
                break;
        }
        i++;
    }

    free(p);
    return 0;
}
