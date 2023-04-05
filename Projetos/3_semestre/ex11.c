#include <stdio.h>
#include <stdlib.h>
#define M 2
#define MM (2 * M)

typedef struct chave{
  int chave;
}TItem;

typedef struct Pagina{
  TItem item[MM]; //informação de cada nó da pagina
  struct Pagina *pagina[MM + 1]; //ponteiros para as proximas paginas
  int n; //guarda a quantidade de elementos que ja foram usados na pagina
}TPag;
typedef TPag *PPag;

PPag busca_arvB(PPag arv, int num){

  PPag aux = arv;
  
  if(aux == NULL){
    return NULL; //não achou a chave 
  }
  else{
    int i = 0;

    while(aux->item[i].chave < num && i < aux->n){
      i++;
    }

    if(aux->item[i].chave == num && i < aux->n){
      return aux;
    }
    else{
      return busca_arvB(aux->pagina[i], num);
    }
  }
}

PPag cria_pag(PPag novo){

  int i;
  novo = (PPag)malloc(sizeof(TPag));
  
  for(i = 0; i <= MM; i++){
    novo->pagina[i] = NULL;
  }

  return novo;
}

PPag insere_pag(PPag arv, int num, int *fim, PPag *nova_pag, int *novo_num, int *cresceu){

  int i = 0;
  PPag temp1 = NULL, temp2 = NULL;
  int vet_aux[MM+1];

  //parada da recursão
  if(arv == NULL){
    *fim = 1;
    return arv;
  }
  else{

    while(arv->item[i].chave < num && i < arv->n){
      i++;
    }

    if(arv->item[i].chave == num){ //chave repetida
      *fim = 0;
      *cresceu = 0;
      return arv;
    }
      
    arv->pagina[i] = insere_pag(arv->pagina[i], num, fim, nova_pag, novo_num, cresceu);
      
  }

  if(*fim == 1 || *cresceu == 1){
    
    if(arv->n < MM){ //ainda cabe espaço na página
    
      i = arv->n - 1;

      //insertion sort
      while(i >= 0 && arv->item[i].chave > *novo_num){
        arv->item[i+1] = arv->item[i];
        arv->pagina[i+2] = arv->pagina[i+1];
        i--;
      }

      arv->item[i+1].chave = *novo_num;
      arv->n = arv->n + 1;
      arv->pagina[i+2] = *nova_pag;
      
      *fim = 0;
      *cresceu = 0;
    }
    else{ //não cabe espaço e teremos que criar uma nova página
      temp2 = *nova_pag;
      for(i = 0; i < MM; i++){
      vet_aux[i] = arv->item[i].chave;
      }
      vet_aux[4] = *novo_num;

      i = MM-1;

      while(i >= 0 && vet_aux[i] > *novo_num){
        vet_aux[i+1] = vet_aux[i];
        i--;
      }
      vet_aux[i+1] = *novo_num;

      //atualizando dados da pagina nova criada
      temp1 = (PPag)malloc(sizeof(TPag));
      temp1->item[0].chave = vet_aux[3];
      temp1->item[1].chave = vet_aux[4];
       //caso tenhamos crescido anteriormente e teremos um novo crescimento
      temp1->pagina[0] = arv->pagina[3];
      temp1->pagina[1] = arv->pagina[4];
      temp1->pagina[2] = temp2;
      temp1->n = 2;

      //atualizando dados da pagina
      arv->item[0].chave = vet_aux[0];
      arv->item[1].chave = vet_aux[1];
      arv->pagina[3] = NULL;
      arv->pagina[4] = NULL;
      arv->n = 2;
      
      *nova_pag = temp1;
      *novo_num = vet_aux[2];
      *cresceu = 1;
      *fim = 0;

    }
    return arv;
  }
  
  return arv;
}

PPag insere_arvB(PPag arv, int num){

  int cresceu = 0;
  int fim = 0;
  PPag arv_retorno = NULL;
  int num_retorno = num;
  
  if(arv == NULL){
    PPag novo = cria_pag(novo);
    novo->item[0].chave = num;
    novo->n = 1;
    
    return novo;
  }else{

  arv = insere_pag(arv, num, &fim, &arv_retorno, &num_retorno, &cresceu);
    if(cresceu == 1){ //verifica se tivemos crescimento na raiz
      PPag novo = cria_pag(novo);
      novo->item[0].chave = num_retorno;
      novo->pagina[0] = arv;
      novo->pagina[1] = arv_retorno;
      novo->n = 1;
      arv = novo;
    }

  return arv;
  }
}

int main(void) {

  int i;
  int num = 0;
  int num_busca;
  PPag arv = NULL, busca;
  PPag aux;

   while (num >= 0) {
    scanf("%d", &num);

    if (num >= 0) {
      arv = insere_arvB(arv, num);
    }
  }
  
  scanf("%d", &num_busca);

  busca = busca_arvB(arv, num_busca);

  printf("%d", arv->n);

  if(busca == NULL){
    printf("\nValor nao encontrado");
  }
  else{
    printf("\n%d", busca->n);
  }
  
  return 0;
}