#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "hora.h"
#define MAX 100

typedef struct produto{
    char nome[30];
    char marca[30];
    char categoria[30];
    float valor;
    char cod[10];
    char cod_fornecedor[7];
    int quantidade;
    struct produto *prox;
}Produto;

typedef struct produto_carrinho{
    char nome[30];
    char marca[30];
    char categoria[30];
    float valor;
    char cod[10];
    char cod_fornecedor[7];
    int quantidade;
    float total;
}Prod_Carrinho;

typedef struct carrinho{
    Prod_Carrinho p[MAX];
    char cpf[12];
    int qntd_produtos;
    float total;
}Carrinho;

typedef struct relatorio{
    char cpf[12];
    float subtotal;
    float total;
    int parcelado;
    char modo_pag[15];
    char data_venda[20];
}Relatorio;

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
    printf("\tQUANTIDADE: %d\n",l->quantidade);
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

    /*printf("MARCA: ");
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
    fflush(stdin); */

    printf("PRECO: R$ ");
    scanf("%f", &p->valor);

    printf("QUANTIDADE: ");
    scanf("%d", &p->quantidade);

    system("cls");
    printf("\nProduto cadastrado com sucesso !\n");
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
    printf("PRODUTOS CADASTRADOS:\n");
    for(p=l;p!=NULL;p=p->prox){
        printf("NOME: %s || QUANTIDADE: %d || R$ %.2f\n", p->nome, p->quantidade, p->valor);
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
/* --- */
void salvar_lista_de_compras(Carrinho l){
    //printf("%d %s\n",l[0].p.quantidade,l[0].p.nome);
    FILE* f;

    f = fopen("Carrinho.dat", "a+b");
    if(f==NULL){
        printf("\nErro na busca da lista ...\n");
        exit(1);
    }

    fwrite(&l,sizeof(Carrinho),1,f);

    fclose(f);

    printf("ORCAMENTO SALVO COM SUCESSO !\n");

}

int buscar_orcamentos(char* cpf){
    FILE* arq;
    Carrinho l;
    int verificar = 0;
    int var,i;

    arq = fopen("Carrinho.dat","rb+");
    if(arq == NULL){
        printf("Nenhum arquivo encontrado\n");
    }

    while(fread(&l,sizeof(Carrinho),1,arq)){
       if(strcmp(l.cpf,cpf) == 0){
          printf("Orcamento de R$%.2f para o CPF %s\n", l.total, l.cpf);
          verificar = 1;
          break;
        }
    }

    if(verificar == 0){
        printf("Nenhum orcamento encontrado para o CPF\n", l.cpf);
        return 1;
    }

    printf("\nINSIRA [1] PARA EFETIVAR A VENDA,[2] PARA EXCLUIR O ORCAMENTO ANTERIOR OU [3] PARA CONTINUAR ...\n");
    scanf("%d", &var);
    fflush(stdin);

    if(var == 1){

    }
    else if (var == 2){
       for(i=0;i<l.qntd_produtos;i++){
           l.p[i].categoria[0] = '\0';
           l.p[i].cod[0] = '\0';
           l.p[i].marca[0] = '\0';
           l.p[i].nome[0] = '\0';
           l.p[i].quantidade = 0;
           l.p[i].total = 0;
           l.p[i].valor = 0;
       }
       l.cpf[0] = '\0';
       l.qntd_produtos = 0;
       l.total = 0;

       fseek(arq,-sizeof(Carrinho),SEEK_CUR);
       fwrite(&l,sizeof(Carrinho),1,arq);
    }

    fclose(arq);
    return 0;
}

int cria_lista_de_compras(Produto* l){
    Produto* p = l;
    Carrinho lista;
    int i = 0,j,quant,erro=0,var;
    char c = 'S';
    char nome[20];

    system("cls");
    all_nome(p);

    printf("\nCPF DO CLIENTE:\n");
    scanf("%[^\n]s", lista.cpf);
    fflush(stdin);

    if(buscar_orcamentos(lista.cpf)==0){
        printf("OBS: MY LOJA PERMITE APENAS UM ORCAMENTO POR CPF \n");
        return;
    }

    while(c == 'S' || c == 's'){
        printf("\nAdicionar ao orcamento:\n");
        scanf("%[^\n]s", nome);
        fflush(stdin);

        for(p=l;p!=NULL;p=p->prox){
            if(strcmp(p->nome,nome) == 0){
                strcpy(lista.p[i].nome,p->nome);
                strcpy(lista.p[i].marca,p->nome);
                strcpy(lista.p[i].categoria,p->categoria);
                strcpy(lista.p[i].cod,p->cod);
                strcpy(lista.p[i].cod_fornecedor,p->cod_fornecedor);
                lista.p[i].valor = p->valor;

                printf("Quantidade:");
                scanf(" %d", &quant);
                if((p->quantidade - quant) < 0){
                    printf("\nFora dos limites do estoque.\n");
                    printf("\nDisponiveis em estoque %d\n", p->quantidade);
                }
                while(quant>p->quantidade){
                    printf("Insira novamente: \n");
                    scanf(" %d", &quant);
                }
                lista.p[i].quantidade = quant;
                p->quantidade = p->quantidade - quant;

                lista.p[i].total = (lista.p[i].valor)*(lista.p[i].quantidade);

                printf("\n%d %s(s) ADICIONADO AO CARRINHO, UM TOTAL DE R$%.2f\n",lista.p[i].quantidade,lista.p[i].nome,lista.p[i].total);
                i++;
                erro = 1;
            }
        }
        if (erro == 0) printf("PRODUTO NAO ENCONTRADO\n");

        printf("\nAPERTE (S) PARA INSERIR OUTRO PRODUTO OU PRESSIONE QUALQUER TECLA PARA ENCERRAR\n");
        scanf(" %c", &c);
        fflush(stdin);
    }

    lista.qntd_produtos = 0;
    for(j=0;j<i;j++){
        lista.qntd_produtos  = lista.qntd_produtos + lista.p[j].quantidade;
    }

    lista.total = 0;
    system("cls");
    printf("\n-------- MEU CARRINHO --------\n");
    for(j=0;j<i;j++){
        printf("%d %s\n",lista.p[j].quantidade,lista.p[j].nome);
        lista.total = lista.total + lista.p[j].total;
    }
    printf("Total : R$ %.2f\n", lista.total);

    printf("\nINSIRA [1] PARA SALVAR ORCAMENTO OU [2] PARA CANCELAR OPERACAO\n");
    scanf("%d", &var);
    fflush(stdin);

    if(var == 1){
        salvar_lista_de_compras(lista);

    }
    else if(var == 2){
        printf("Saindo ...\n");
    }
}

void salvar_relat_venda(Relatorio r){
    FILE* arq;

    arq = fopen("Relatorio.dat","a+b");

    if(arq==NULL){
        printf("\nErro na busca dos relatorios ...\n");
        exit(1);
    }

    fwrite(&r,sizeof(Relatorio),1,arq);

    printf("\n\nAdicionado aos relatorios de venda \n");
    fclose(arq);
}

void efetuar_venda(char* cpf){
    FILE* arq;
    Carrinho l;
    Relatorio r;
    int i,soma = 0,var,var2=0 ;
    arq = fopen("Carrinho.dat", "rb+");

    if(arq == NULL){
        printf("Nenhum arquivo encontrado\n");
    }

    while(fread(&l,sizeof(Carrinho),1,arq)){
       if(strcmp(l.cpf,cpf) == 0){
          break;
        }
    }

    printf("------- INFORMACOES -------\n");
    printf("CPF:%s\n", l.cpf);
    printf("QUANTIDADE DE PRODUTOS: %d\n", l.qntd_produtos);
    printf("TOTAL: R$%.2f\n", l.total);

    printf("\nDIGITE [1] PARA PAGAMENTO A VISTA OU [2] PARA PARCELAMENTO\n");
    scanf("%d", &var);
    fflush(stdin);

    if(var == 1){
        printf("\n[1]DINHEIRO OU [2]DEBITO\n");
        scanf("%d", &var2);
        fflush(stdin);

        switch(var2){
            case 1:
                strcpy(r.modo_pag, "DINHEIRO");
                break;
            case 2:
                strcpy(r.modo_pag, "DEBITO");
                break;
        }
        r.subtotal = l.total;
        r.parcelado = 1;
        strcpy(r.cpf,l.cpf);
        strcpy(r.data_venda,data());

        printf("\nCARTAO: %s\n", r.modo_pag);
        printf("CPF: %s\n", r.cpf);
        printf("DATA DA VENDA: %s\n", r.data_venda);
        printf("PARCELADO EM x%d\n", r.parcelado);
        printf("SUBTOTAL: R$%.2f\n", r.subtotal);
        r.total = (r.subtotal*0.9);
        printf("\nTOTAL: R$%.2f COM DESCONTO DE 10%%\n", r.total);

    }
    else if(var == 2){
        printf("\n[1]VISA\n[2]MASTERCARD\n[3]ELO\n");
        scanf("%d", &var2);
        fflush(stdin);
        switch(var2){
            case 1:
                strcpy(r.modo_pag,"VISA");
                break;
            case 2:
                strcpy(r.modo_pag,"MASTERCARD");
                break;
            case 3:
                strcpy(r.modo_pag,"ELO");
                break;
        }
        printf("\nQUANTIDADE DE PARCELAS (ATE 12X):\n");
        do{
         scanf("%d", &var2);
         fflush(stdin);
        }while(var2>12 || var2 == 0);

        r.subtotal = l.total;
        r.parcelado = var2;
        strcpy(r.cpf,l.cpf);
        strcpy(r.data_venda,data());


        printf("\nCARTAO: %s\n", r.modo_pag);
        printf("CPF: %s\n", r.cpf);
        printf("DATA DA VENDA: %s\n", r.data_venda);
        printf("PARCELADO EM x%d\n", r.parcelado);
        printf("SUBTOTAL: R$%.2f", r.subtotal);
        r.total = r.subtotal;
        printf("\nTOTAL: %d PARCELAS DE R$%.2f\n", r.parcelado, (r.total/r.parcelado) );

    }

    salvar_relat_venda(r);

    fclose(arq);
}

void verificar_relatorios(){
    FILE* arq;
    Relatorio r;

    arq = fopen("Relatorio.dat","rb+");

    while(fread(&r,sizeof(Relatorio),1,arq)){
        printf("\nCARTAO: %s\n", r.modo_pag);
        printf("CPF: %s\n", r.cpf);
        printf("DATA DA VENDA: %s\n", r.data_venda);
        printf("PARCELADO EM x%d\n", r.parcelado);
        printf("SUBTOTAL: R$%.2f\n", r.subtotal);
        printf("\nTOTAL: R$%.2f (VERIFICAR PARCELAMENTO)\n", r.total);
        printf("________________________________________________\n\n");
    }

    fclose(arq);

}

int main(){
    Produto *l;
    Produto t;

    FILE* arq;
    l = inicializa();
    l = inserir_prod(l);
    //l = inserir_prod(l);
    cria_lista_de_compras(l);
    //efetuar_venda("123456789");
   // verificar_relatorios();

}
