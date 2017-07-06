#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct produto{
    char nome[30];
    char marca[30];
    char categoria[30];
    float valor;
    char cod[10];
    struct produto *prox;
}Produto;

Produto* inicializa(void){
    return NULL;
}

void mostrar_categorias(){
    char cat[50][50];
    int i;

    strcpy(cat[0],"1 - Batedeira");
    strcpy(cat[1],"2 - Cafeteira");
    strcpy(cat[2],"3 - Fogao");
    strcpy(cat[3],"4 - Microondas");
    strcpy(cat[4],"5 - Geladeira");
    strcpy(cat[5],"6 - Liquidificador");
    strcpy(cat[6],"7 - Maquina de Lavar");
    strcpy(cat[7],"8 - Filmadora");
    strcpy(cat[8],"9 - Televisor");
    strcpy(cat[9],"10 - Computador");
    strcpy(cat[10],"11 - Notebook");

    for(i=0;i<11;i++){
        printf("\t %s\n", cat[i]);
    }

}

void exibir_informa(Produto *l){
    printf("\tNOME: %s\n", l->nome);
    printf("\tMARCA: %s\n", l->marca);
    printf("\tCATEGORIA: %s\n", l->categoria);
    printf("\tCODIGO DE BARRAS: %d\n", l->cod);
    printf("\tPRECO: R$ %.2f\n", l->valor);
}


Produto* cria_prod(Produto *l){
    Produto* p = l;
    p = (Produto*) malloc(sizeof(Produto));
    char var,cat;

    printf("\t\n########### INFORMACOES ###########\n");
    printf("NOME DO PRODUTO: ");
    scanf("%[^\n]s", p->nome);
    fflush(stdin);

   /* printf("MARCA: ");
    scanf("%[^\n]s",p->marca);
    fflush(stdin);

    printf("Verificar todas CATEGORIAS ""S"" ou ""N"" ? ");
    scanf("%c", &var);
    fflush(stdin);
    if(var == 'S' || var == 's'){
        mostrar_categorias();
    }

    printf("CATEGORIA: ");
    scanf("%[^\n]s",p->categoria);
    fflush(stdin);

    printf("CODIGO DE BARRAS (9 digitos): ");
    scanf("%[^\n]s", &p->cod);
    fflush(stdin);

    printf("PRECO: R$ ");
    scanf("%f", &p->valor);
    */

    system("cls");
    printf("\nProduto cadastrado com sucesso\n");
    fflush(stdin);
    exibir_informa(p);
    p->prox = NULL;

    return p;
}

Produto* inserir_prod(Produto* l){
    Produto* p=l;
    Produto* inicio = p;

    if(p == NULL){
        return cria_prod(p);
    }

    while(p->prox != NULL){
        p = p->prox;
    }

    p->prox = cria_prod(p);

    return inicio;
}

Produto* rmv_prod(Produto* l){
    Produto* p = l;
    Produto* inicio = p;
    Produto* ant=NULL;
    char nome[20];

    if(p == NULL){
        printf("Não existe produto nessa lista.\n");
        return 0;
    }

    printf("NOME DO PRODUTO A SER REMOVIDO\n");
    scanf("%[^\n]s", nome);
    fflush(stdin);

    while(strcmp(p->nome,nome)!=0){
        ant = p;
        p=p->prox;
    }

    if(ant == NULL){
        p=p->prox;
        printf("%s removido com sucesso\n", p->nome);
        return p;
    }

    if(strcmp(p->nome,nome)==0){
        printf("O produto foi %s removido com sucesso\n", p->nome);
        ant->prox = p->prox;
    }

    p=inicio;
    return p;

}

void all_nome(Produto* l){
    Produto* p;
    printf("NOMES CADASTRADOS:\n");
    for(p=l;p!=NULL;p=p->prox){
        printf("%s\n",p->nome);
    }
    printf("\n\n");
}

void busca_parecida(Produto* l){
    Produto* p=l;
    char nome[20];

    printf("NOME DO PRODUTO A SER BUSCADO\n");
    scanf("%[^\n]s", nome);
    fflush(stdin);

    printf("RESULTADOS:\n");
    while(p != NULL){
        if(strstr(p->nome,nome) != NULL){
            printf("%s\n", p->nome);
        }
    p=p->prox;
    }

}

int main(){
    Produto* l;
    l = inicializa();

    l = inserir_prod(l);
    l = inserir_prod(l);
    l = inserir_prod(l);

    all_nome(l);
    busca_parecida(l);
    //l = rmv_prod(l);

    //all_nome(l);

}
