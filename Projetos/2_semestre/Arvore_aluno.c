/*
Algoritmos e Estruturas de Dados “ Exercício 8 - Árvores genéricas (PESO 1.5)"
Nome: Lucas Henrique Amorim da Silva
RA: 156695      Turma: IB
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

#define MAX 102

typedef struct arv{
	int ra;
	char nome[MAX];
	float nota1;
	float nota2;
	float nota3;
	float media;
	struct arv *esq;
	struct arv *dir;
}TArv;
typedef TArv *PArv;

void interface(){
	system("clear||cls");
	printf("\n_________________________________MENU_________________________________\n\n");
	printf("| 1 | Inserir um aluno na árvore\n");
	printf("| 2 | Imprimir a árvore atual\n");
	printf("| 3 | Mostrar os dados dos alunos que foram reprovados\n");
	printf("| 4 | Excluir da árvore todos os alunos que foram reprovados\n");
	printf("| 5 | Mostrar todos os alunos com chave menor ou igual a um dado RA\n");
	printf("| 6 | Iniciar uma nova árvore\n");
	printf("| 7 | Sair");
	printf("\n______________________________________________________________________\n\n");
	printf("obs: digite apenas números.\n");
	printf("Opção: ");
}

PArv buscaABB(PArv a, int valor){
	
	if(a == NULL){
		return NULL; //árvore vazia
	}
	else if(valor < a->ra){
		return buscaABB(a->esq, valor);
	}
	else if(valor > a->ra){
		return buscaABB(a->dir, valor);
	}
	else{
		return a; //encontrou o valor
	}
}

PArv insereABB(PArv a, int ra, char nome[], float nota1, float nota2, float nota3, float media){
	
	PArv novo;
	
	if(a == NULL){ //árvore vazia
		
		novo = (PArv)malloc(sizeof(TArv));
		novo->esq = NULL;
		novo->dir = NULL;
		novo->media = media;
		strcpy(novo->nome, nome);
		novo->nota1 = nota1;
		novo->nota2 = nota2;
		novo->nota3 = nota3;
		novo->ra = ra;
		
		return novo;
	}
	else if(ra < a->ra){
		a->esq = insereABB(a->esq, ra, nome, nota1, nota2, nota3, media);
	}
	else{
		a->dir = insereABB(a->dir, ra, nome, nota1, nota2, nota3, media);
	}
	
	return a;
}

void imprime(PArv a, int nivel){
     
	int i;
     
	if(a == NULL) return;
	else{
     	imprime(a->dir, nivel+1);
     	
		for(i=0;i<nivel;i++){
        	printf("\t");
		}
     	
		printf("%d\n", a->ra);
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

PArv verifica_reprovados(PArv a){
		
		if(a != NULL){
			verifica_reprovados(a->esq);
			verifica_reprovados(a->dir);
	
			if(a->media < 6){
				printf("____________________________\n");
				printf("\nNome do aluno: %s", a->nome);
				printf("\nRA: %d", a->ra);
				printf("\nNota 1: %.2f", a->nota1);
				printf("\nNota 2: %.2f", a->nota2);
				printf("\nNota 3: %.2f", a->nota3);
				printf("\nMédia Final: %.2f", a->media);
				printf("\n____________________________\n\n");
			}
		}	
	
	return NULL;
}

PArv remove_reprovados(PArv a, int ra){
	
	PArv pai, aux, t;
		
	if(a == NULL) return NULL;
	
	else if(ra < a->ra){
		a->esq = remove_reprovados(a->esq, ra); 
	}
	else if(ra > a->ra){
		a->dir = remove_reprovados(a->dir, ra);
	}
	else{
				
		if(a->esq == NULL && a->dir == NULL){ // elemento sem filhos
			free (a);
			a = NULL;
		}
		else if(a->esq == NULL) { // só tem filho à direita
			t = a;
			a = a->dir;
			free (t);
		} 
		else if(a->dir == NULL) { //só tem filho à esquerda
			t = a;
			a = a->esq;
			free (t);
		}
		else { // tem os dois filhos
			pai = a;
			aux = a->esq;
		
			while(aux->dir != NULL){ //busca o maior aa esquerda
				pai = aux;
				aux = aux->dir;
			}
			
			a->ra = aux->ra; // troca as informações
			strcpy(a->nome, aux->nome);
			a->nota1 = aux->nota1;
			a->nota1 = aux->nota2;
			a->nota3 = aux->nota3;
			a->media = aux->media;
			
			if (pai == a){ //quando o pai do maior valor é o próprio nó raiz que tem que ser removido
				pai->esq = aux->esq;
			}
			else{
				pai->dir = aux->esq;
				free(aux);
			}		
		}
	}
	
	return a;	
}

PArv mostrar_ra(PArv a, int ra){
	
	if(a == NULL) return NULL;
	
	if(a->ra <= ra){
		
		printf("_______________________________________\n");
		printf("\nNome do aluno: %s", a->nome);
		printf("\nRA: %d", a->ra);
		printf("\nNota 1: %.2f", a->nota1);
		printf("\nNota 2: %.2f", a->nota2);
		printf("\nNota 3: %.2f", a->nota3);
		printf("\nMédia Final: %.2f", a->media);
		printf("\n_______________________________________\n\n");
		mostrar_ra(a->dir, ra);
	}
	
	mostrar_ra(a->esq, ra); //chamamos somente a esquerda pois sabemos que os da esquerda são menores que o atual
	
	return NULL;
}

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int e, ra, cont = 0;
	int i = 0, a;
	char nome[MAX];
	PArv alunos = NULL, aux = NULL;
	float nota1, nota2, nota3, media;
	int ra_reprovados[MAX]; //guardará os ra's dos alunos reprovados
	int rep = 0; //indica a quantidade de alunos reprovados (nos ajudará no for na opção 4)
	
	do{
		interface();
		scanf("%d", &e);
		
		if(e == 1){
	
			if(cont == 0){ //estamos inserindo o primeiro aluno e não vamos precisar verificar se o ra é reptido
				system("clear||cls");
				printf("Digite o RA do aluno: ");
				scanf("%d", &ra);
			}
			else if(cont > 0){
				do{
					system("clear||cls");
					printf("Digite o RA do aluno: ");
					scanf("%d", &ra);
					
					aux = buscaABB(alunos, ra); //procura ra´s repetidos
					
					if (aux != NULL){ //achou o ra repetido
	
						if(aux->ra == ra){
							printf("\nERRO: Este RA já existe.");
							printf("\nPor favor, insira um novo RA não repetido.");
							printf("\nPressione qualquer tecla para digitar um novo RA...");
							getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
              getchar(); //caso esteja sendo executado duas vezes, apagar uma das duas
							i = 1;
						}	
					}
					else{
						i = 0;
					}	
					
				}while(i == 1);
			}
			
			printf("Digite o nome do aluno: ");
			fgets(nome, MAX, stdin); //o primeiro fgets foi colocado por conta de um erro, sem ele, o programa pula a parte de pegar os nomes(assim, coloquei o primeiro fgets pois ele provavelmente deve estar pegando algum espaço e o segundo esta pegando o nome)
			fgets(nome, MAX, stdin); //caso esteja sendo executado duas vezes, apagar uma das duas
		
			do{
				printf("Digite a primeira nota do aluno: ");
				scanf("%f", &nota1);
				if(nota1 < 0 || nota1 > 10){
					system("clear||cls");
					printf("ERRO: Nota inválida.");
					printf("\nDigite valores de 0 a 10.\n");
				}
			}while(nota1 < 0 || nota1 > 10);
			
			do{
				printf("Digite a segunda nota do aluno: ");
				scanf("%f", &nota2);
				if(nota2 < 0 || nota2 > 10){
					system("clear||cls");
					printf("ERRO: Nota inválida.");
					printf("\nDigite valores de 0 a 10.\n");
				}
			}while(nota2 < 0 || nota2 > 10);
			
			do{
				printf("Digite a terceira nota do aluno: ");
				scanf("%f", &nota3);
				if(nota3 < 0 || nota3 > 10){
					system("clear||cls");
					printf("ERRO: Nota inválida.");
					printf("\nDigite valores de 0 a 10.\n");
				}
			}while(nota3 < 0 || nota3 > 10);
			
			media = (nota1 + nota2 + nota3) / 3;
			
			alunos = insereABB(alunos, ra, nome, nota1, nota2, nota3, media);
			
			if(media < 6){
				ra_reprovados[rep] = ra; //vetor com os ra's dos alunos reprovados
				rep++; //adicionamos 1 ao número de alunos reprovados
			}
			
			cont++; // pois o primeiro aluno foi registrado
		}
		else if(e == 2){
			
			system("clear||cls");
			printf("\n\t\t Árvore atual\n");
			printf("_______________________________________________________\n\n");
			imprime(alunos, 0);
			printf("\n_______________________________________________________\n\n");
			printf("Pressione qualquer tecla para retornar ao menu...");
			getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
      getchar(); //caso esteja sendo executado duas vezes apagar uma das duas
		}
		else if(e == 3){
			system("clear||cls");
			printf("Alunos reprovados:\n");
			verifica_reprovados(alunos);
			printf("\nPressione qualquer tecla para retornar ao menu...");
			getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
      getchar(); //caso esteja sendo executado duas vezes,apagar uma das duas
		}
		else if(e == 4){
			
			do{
				system("clear||cls");
				printf("Você tem certeza que deseja deletar os dados dos alunos reprovados?\n");
				printf("Os dados serão perdidos permanentemente!\n");
				printf("____________________________________________________________________\n\n");
				printf("| 1 | Sim\n");
				printf("| 2 | Não\n");
				printf("\nOpção: ");
				scanf("%d", &i);
		
				if(i == 1){
		
					for(a = 0; a < rep; a++){
						alunos = remove_reprovados(alunos, ra_reprovados[a]);
					} 
					if(alunos == NULL){ //caso todos os alunos estejam abaixo da média devemos restaurar o cont para que a condição de verificar se é o primeiro aluno na opção 1 de inserção possa funcionar
						cont = 0;
					}
				
					printf("\nAlunos removidos com sucesso!\n\n");
					printf("Pressione qualquer tecla para retornar ao menu...");
					getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
          getchar(); //caso esteja sendo executado duas vezes, apagar uma das duas
					rep = 0; //como excluimos os alunos reprovados, zeramos a quantidade de alunos reprovados;
				}
		
				if (i != 1 && i != 2){
					printf("\nOpção Inválida!");
					printf("\nPressione qualquer tecla para digitar uma nova opção...");
					getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
          getchar(); //caso esteja sendo executado duas vezes, apagar uma das duas
				}
				
			}while(i != 1 && i != 2);
		}
		else if(e == 5){
			
			system("clear||cls");
			printf("Digite um RA (apenas números): ");
			scanf("%d", &ra);
			
			system("clear||cls");
			printf("\nRA digitado: %d", ra);
			printf("\nAlunos com RA's menores que o digitado\n");
			mostrar_ra(alunos, ra);
			printf("\nPressione qualquer tecla para retornar ao menu...");
			getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
      getchar(); //caso esteja sendo executado duas vezes,apagar uma das duas
		}
		else if(e == 6){
			
			alunos = libera(alunos);
			
			if(alunos == NULL){
				system("clear||cls");
				printf("\nÁrvore liberada!\n");
				printf("__________________________________________________\n\n");
				printf("Pressione qualquer tecla para retornar ao menu...");
				getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
        getchar(); //caso esteja sendo executado duas vezes, apagar uma das duas
			}
			
			rep = 0; //zeramos a quantidade de alunos reprovdos
			cont = 0; //restauramos o cont para que a condição de verificar se é o primeiro aluno na opção 1 de inserção possa funcionar
		}
		else if(e == 7){

      alunos = libera(alunos);
			system("clear||cls");
			printf("\nVocê saiu!\n");
			printf("________________________________\n\n");
		}
		else{
			printf("Escolha inválida.\n");
			printf("Escolha uma nova opção válida...");
      getchar(); //foram colocados dois pois o primeiro pega algum caractere aleatório e o segundo pega o caractere que o usuário digitar
      getchar(); //caso esteja sendo executado duas vezes,apagar uma das duas
			e = 0;
		}
		
	}while(e < 7);
	
	return 0;
}
