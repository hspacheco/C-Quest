#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>


//FILE* f;

typedef struct produto{
    char nome[30];
    char marca[30];
    char categoria[30];
    float valor;
    char cod[10];
    int quantidade;
    struct produto *prox;
}Produto;

typedef struct funcionario{

    char nome [50], sexo, cpf[12];
    char login[50];
    char senha[50];
    int privilegio;

}Funcionario;


void printa_funcionario(Funcionario *a){
    char cargo[30];
    printf("\n\t-----------INFORMACOES----------\n");
    printf("\tNOME: %s\n",a->nome);
    printf("\tSEXO: %c\n",a->sexo);
    printf("\tCPF: %s\n",a->cpf);
    printf("\tLOGIN: %s\n",a->login);
    printf("\tSENHA: %s\n",a->senha);

    if(a->privilegio==1){
        strcpy(cargo,"ESTOQUISTA\n");
    }
    else if(a->privilegio==2){
        strcpy(cargo,"VENDEDOR");
    }
    else if(a->privilegio==3){
        strcpy(cargo,"GERENTE");
    }
    else{
        cargo[0] = '\0';
    }
    printf("\tCARGO: %s\n",cargo);
    printf("\t---------------------------------\n");
}


void mostra_todos_funcionarios(){
    FILE* f;
    f = fopen("Funcionarios.dat","r+b");
    if(f==NULL){
        printf("Falha ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }
    Funcionario* a = malloc(sizeof(struct funcionario));
    while(fread(a,sizeof(Funcionario),1,f)==1){
        printa_funcionario(a);

    }

}


void cria_funcionario(){
    FILE* f;
    fopen("Funcionarios.dat","a+b");
    if(f==NULL){
        printf("Falha ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }
    Funcionario a;

    printf("Digite o nome: ");
    scanf(" %[^\n]s",a.nome);

    printf("Digite o sexo [M/F]: ");
    scanf(" %c",&a.sexo);
    a.sexo = toupper(a.sexo);

    printf("Digite o cpf (11 digitos): ");
    scanf(" %s",a.cpf);

    printf("Digite o login: ");
    scanf("%s",a.login);

    printf("Digite a senha: ");
    scanf("%s",a.senha);

    printf("Digite o cargo [1]Gerente, [2]Vendedor, [3]Estoquista: ");
    scanf(" %d",&a.privilegio);

    fwrite(&a,sizeof(struct funcionario),1,f);
    fclose(f);

}

void procura_funcionario(){
    FILE* f;
    f = fopen("Funcionarios.dat","r+b");
    if(f==NULL){
        printf("Falha ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }
    char cpf_aux[12];
    int verificador = 0;
    Funcionario* a = malloc(sizeof(struct funcionario));
    if(a==NULL){
        printf("ponteiro nulo");
    }

    printf("Digite o Cpf do Funcionário: ");
    scanf("%s",cpf_aux);

    while(fread(a,sizeof(Funcionario),1,f)==1){
        printf("procurando\n");
        if(strcmp(cpf_aux,a->cpf)==0){
            verificador = 1;
            break;
        }
        continue;
    }
    if(verificador == 0){
        char c;
        printf("CPF nao encontrado\n");
        printf("Deseja procurar um outro cpf?[S/N] ");
        scanf(" %c",&c);
        if(c=='S'||c=='s')
            procura_funcionario();
        else
            fclose(f);
            return; //chama a funcao de menu;
    }
    printa_funcionario(a);
    int opcao2;
    printf("DIGITE: [1] Alterar as informacoes do funcionario [2] Excluir o funcionario: ");
    scanf(" %d",&opcao2);

    if(opcao2==2){
            char opcao3;
            a->nome[0]='\0';
            a->sexo ='\0';
            a->cpf[0]='\0';
            a->login[0]='\0';
            a->senha[0]='\0';
            a->privilegio = 0;

            printf("Deseja realmente excluir o funcionario acima?[S/N] ");
            scanf(" %c",&opcao3);
            if(opcao3=='S'||opcao3=='s'){
                fseek(f ,-sizeof(struct funcionario),SEEK_CUR);
                fwrite(a,sizeof(Funcionario),1,f);
                printf("Operação realizada com sucesso!\n");
                fclose(f);
                return; //chama a funcao de menu
            }
            else{
                printf("Operação cancelada!\n");
                fclose(f);
                return; //chama a funcao de menu
            }
    }

    else if(opcao2==1){
    char escolha;
    int opcao;

    do{
    printf("Escolha os campos que voce deseja alterar:\n [1]NOME\n [2]SEXO\n [3]CPF\n [4]LOGIN\n [5]SENHA\n [6]CARGO\n [7]TODOS\n [8]VOLTAR\n");
    printf("Digite uma opção: ");

    scanf(" %d",&opcao);
    if(opcao==1 ){
        printf("Digite o novo nome: ");
        scanf(" %[^\n]s",a->nome);
    }
    else if(opcao== 2 ){
        printf("Digite o novo sexo: ");
        scanf(" %c",&a->sexo);
    }

    else if(opcao== 3 ){
        printf("Digite o novo cpf: ");
        scanf(" %s",a->cpf);
    }

    else if(opcao== 4){
        printf("Digite o novo login: ");
        scanf(" %s",a->login);
    }

    else if(opcao==5){
        printf("Digite a nova senha: ");
        scanf(" %s",a->senha);
    }


    else if(opcao==6){
        printf("Digite o novo cargo [1]Estoquista [2]Vendedor [3]Gerente: ");
        scanf(" %d",&a->privilegio);
    }

    else if(opcao==7){
        printf("Digite o novo nome: ");
        scanf(" %[^\n]s",a->nome);

        printf("Digite o novo sexo: ");
        scanf(" %c",&a->sexo);

        printf("Digite o novo cpf: ");
        scanf(" %s",a->cpf);

        printf("Digite o novo login: ");
        scanf(" %s",a->login);

        printf("Digite a nova senha: ");
        scanf(" %s",a->senha);

        printf("Digite o novo cargo [1]Estoquista [2]Vendedor [3]Gerente:");
        scanf(" %d",&a->privilegio);
    }

    else if(opcao==8){
        fclose(f);
        return;// chama  a funcao de retorno ao menu
    }

    else{
        printf("Comando inválido!\n");
    }


    system("cls");
    printf("Deseja fazer uma outra alteração?[S/N]\n");
    scanf(" %c",&escolha);

}while((escolha=='S')||(escolha=='s'));

    fseek(f,-sizeof(struct funcionario),SEEK_CUR);
    fwrite(a,sizeof(Funcionario),1,f);
    fclose(f);
    free(a);
}

}

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
    printf("\tCODIGO DE BARRAS: %s\n", l->cod);
    printf("\tPRECO: R$ %.2f\n", l->valor);
    printf("\tQUANTIDADE: %d\n",l->quantidade);
}

Produto* cria_prod(Produto *l){
    FILE* f;
    f = fopen("Lista.dat","a+b");
    if(f==NULL){
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }

    Produto* p = l;
    p = (Produto*) malloc(sizeof(Produto));
    char var,cat;

    fflush(stdin);
    printf("\t\n########### INFORMACOES ###########\n");
    printf("NOME DO PRODUTO: ");
    scanf("%[^\n]s", p->nome);
    fflush(stdin);

    printf("MARCA: ");
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
    scanf("%[^\n]s", p->cod);
    fflush(stdin);

    printf("PRECO: R$ ");
    scanf("%f", &p->valor);
    fflush(stdin);

    printf("QUANTIDADE: ");
    scanf("%d",&p->quantidade);

    system("cls");
    printf("\nProduto cadastrado com sucesso\n");
    fflush(stdin);
    exibir_informa(p);
    p->prox = NULL;

    fwrite(p,1,sizeof(struct produto),f);
    fclose(f);
    return p;
}

Produto* inserir_prod(Produto* l){
    Produto* p=l;
    Produto* inicio = p;
/*
    if(p == NULL){
        return cria_prod(p);
    }
*/

    while(p->prox != NULL){
        p = p->prox;
    }

    p->prox = l;

    return p;
}

void remove_prod_lista(Produto** l,char nome[30]){
    int verificador=0;
    Produto* aux = *l;
    Produto* aux2 = NULL;

    while(aux!=NULL){
        if(strcmp(aux->nome,nome)==0){
            verificador = 1;
            break;
        }
        aux2= aux;
        aux = aux->prox;

    }
    if(verificador==0){
        printf("Produto nao encontrado\n");
        return;
    }
    if(aux2==NULL){
        *l=aux->prox;
        //free(aux2);
        printf("aqui\n");
        return;
    }
    aux2->prox = aux->prox;
    free(aux);

}

void all_nome(Produto* l){
    Produto* p;
    printf("NOMES CADASTRADOS:\n");
    for(p=l;p!=NULL;p=p->prox){
        printf("%s\n",p->nome);
    }
    printf("\n\n");
}

int busca_parecida(Produto* l, char nome[30]){
    Produto* p=l;
    int achado =0 ;

    printf("RESULTADOS:\n");
    while(p != NULL){
        if(strstr(p->nome,nome) != NULL){
            printf("\tNOME: %s CÓDIGO: %s\n", p->nome,p->cod);
            achado = 1;
        }
    p=p->prox;
    }
    return achado;

}


Produto* cria_lista(Produto* l,FILE** f){

        Produto* aux = malloc(sizeof(struct produto));
        fread(aux,sizeof(Produto),1,*f);
        aux->prox = l;
        return aux;
}

Produto* inteiro_lista(Produto* l){

    FILE* f;
    f=fopen("Lista.dat","r+b");

    if(f==NULL){
        printf("ERRO NO ARQUIVO\n");
        exit(1);
    }

    while(!feof(f)){
        l = cria_lista(l,&f);
    }
    fclose(f);
    l=l->prox;
    return l;
}

Produto* remove_prod_arquivo(Produto* l){
    FILE* f;
    f = fopen("Lista.dat","r+b");
    if(f==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    Produto* aux=l;
    char codigo[10];
    int verificado = 0;
    /*
    while(aux!=NULL){
        if(aux->nome[0]!='\0')
        printf("\t%s - Codigo %s\n",aux->nome,aux->cod);
        aux = aux->prox;
    }
    */

    printf("Digite o codigo do produto que voce deseja excluir: ");
    scanf(" %s",codigo);
    while(l!=NULL){
        if(strcmp(codigo,l->cod)==0){
            verificado = 1;
            break;
        }
        l=l->prox;
    }
    if(verificado==0){
        char c;
        printf("Codigo nao encontrado. Deseja procurar um novo codigo?[S/N]");
        scanf(" %c",&c);
        if(c=='S'||c=='s')
            return remove_prod_arquivo(l);
        else
            return; //FUNCAO DE CHAMAR MENU PARA SER IMPLEMENTADA
    }
    else{
        printf("\t\n########### INFORMACOES ###########\n");
        printf("NOME DO PRODUTO: %s\n",l->nome);
        printf("MARCA: %s\n",l->marca);
        printf("CATEGORIA: %s\n",l->categoria);
        printf("CODIGO DE BARRAS: %s\n",l->cod);
        printf("PRECO: R$ %.2f\n",l->valor);
        printf("QUANTIDADE: %d\n",l->quantidade);
        printf("------------------------------------------\n");
        printf("DESEJA REALMENTE EXCLUIR O PRODUTO ACIMA?[S/N] ");
        char c;
        scanf(" %c",&c);
        if(c=='S'||c=='s'){
             Produto a;
             while(fread(&a,sizeof(struct produto),1,f)){
                if(strcmp(a.nome,l->nome)==0)
                    break;
            }

            remove_prod_lista(&l,l->nome);
            l->nome[0] ='\0';
            l->marca[0] = '\0';
            l->categoria[0] = '\0';
            l->cod[0] = '\0';
            l->valor = 0;
            l->quantidade = 0;


            fseek(f,-sizeof(struct produto),SEEK_CUR);
            fwrite(l,sizeof(struct produto),1,f);
            fclose(f);
            return l;


        }
        else
            return; //FUNCAO DE CHAMAR MENU PARA SER IMPLEMENTADO
    }


}

Produto* altera_prod(Produto* l){
    FILE* f;
    f = fopen("Lista.dat","r+b");
    if(f==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    Produto* aux = l;
    char cod_aux[10];
    int achado = 0;
    printf("Digite o codigo do produto: ");
    scanf(" %s",cod_aux);
    while(aux!=NULL){
        if(strcmp(cod_aux,aux->cod)==0){
            achado = 1;
            break;
        }
        aux = aux->prox;
    }
    if(achado==0){
        char c;
        printf("Nenhum Produto foi Encontrado. Deseja Tentar Procurar Outro Nome?[S/N] ");
        scanf(" %c",&c);
        if((c=='S')||(c=='s'))
            return altera_prod(l);
        else
            return; //chama a funcao de menu
    }
    else{
        printf("\t\n########### INFORMACOES ###########\n");
        printf("NOME DO PRODUTO: %s\n",aux->nome);
        printf("MARCA: %s\n",aux->marca);
        printf("CATEGORIA: %s\n",aux->categoria);
        printf("CODIGO DE BARRAS: %s\n",aux->cod);
        printf("PRECO: R$ %.2f\n",aux->valor);
        printf("QUANTIDADE: %d\n",aux->quantidade);
        printf("------------------------------------------\n");

        char escolha;
        int opcao;

        Produto* a = malloc(sizeof(struct produto));

        while(fread(a,sizeof(Produto),1,f)==1){
            printf("procurando\n");
            if(strcmp(aux->cod,a->cod)==0){
                break;
            }
            continue;
        }
fflush(stdin);
        do{

        printf("Escolha os Campos que Você Deseja Alterar:\n [1]Nome\n [2]Marca\n [3]Categoria\n [4]Código\n [5]Valor\n [6]Quantidade\n [7]Todos os Campos\n [8]Voltar\n");
        printf("Digite uma opção: ");
        scanf(" %d",&opcao);

        if(opcao==1 ){
            printf("Digite o Novo Nome: ");
            scanf(" %[^\n]s",aux->nome);
        }
        else if(opcao== 2 ){
            printf("Digite a Nova Marca ");
            scanf(" %s",aux->marca);
            fflush(stdin);
        }

        else if(opcao== 3 ){
            printf("Digite a Nova Categoria: ");
            scanf(" %s",aux->categoria);

        }

        else if(opcao== 4){
            printf("Digite o Novo Código: ");
            scanf(" %s",aux->cod);
        }

        else if(opcao==5){
            printf("Digite o Novo Valor: ");
            scanf(" %d",&aux->valor);
        }


        else if(opcao==6){
            printf("Digite a Nova Quantidade: ");
            scanf(" %d",&aux->quantidade);
        }

        else if(opcao==7){
            printf("Digite o Novo Nome: ");
            scanf(" %[^\n]s",aux->nome);
            printf("Digite a Nova Marca ");
            scanf(" %s",aux->marca);
            printf("Digite a Nova Categoria: ");
            scanf(" %s",aux->categoria);
            printf("Digite o Novo Código: ");
            scanf(" %s",aux->cod);
            printf("Digite o Novo Valor: ");
            scanf(" %d",&aux->valor);
            printf("Digite a Nova Quantidade: ");
            scanf(" %d",&aux->quantidade);

        }

        else if(opcao==8){
            fclose(f);
            return;// chama  a funcao de retorno ao menu
        }

        else{
            printf("Comando inválido!\n");
        }


        system("cls");
        printf("Deseja fazer uma outra alteração?[S/N]\n");
        scanf(" %c",&escolha);

    }while((escolha=='S')||(escolha=='s'));

        fseek(f,-sizeof(struct produto),SEEK_CUR);
        fwrite(a,sizeof(Produto),1,f);
        fclose(f);
        free(a);
        return l;
    }
}



void procura_produto(Produto* l){
    char prod[30];
    char achado;
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]s",prod);
    achado = busca_parecida(l,prod);
    if(achado == 0){
        char c;
        printf("Nenhum Produto foi Encontrado. Deseja Tentar Procurar Outro Nome?[S/N] ");
        scanf(" %c",&c);
        if((c=='S')||(c=='s'))
            return procura_produto(l);
        else
            return; //chama a funcao de menu
    }
    else{
        printf("AÇÕES: [1]Para Alterar o Produto [2]Para Remover o Produto [3]Voltar\n");
        printf("Escolha uma ação: ");
        int x;
        scanf(" %d",&x);
        if(x==1){
            l= altera_prod(l);
        }
        else if(x==2){
            l = remove_prod_arquivo(l);
        }
        else if(x==3){
            return; //chamada a funcao de menu
        }

    }

}



int main(){
    //FILE* f;
    //f= fopen("Lista.dat","a+b");

    setlocale(LC_ALL,"Portuguese");

    Produto* l;
    l= inicializa();
    l = inteiro_lista(l);
//mostra_todos_funcionarios();
    procura_produto(l);


    //procura_funcionario();

    //remove_prod_arquivo(l);

    while(l!=NULL){
        printf("%s\n",l->nome);
        l=l->prox;
    }

    /*
    FILE* f=NULL;
    f = fopen("Lista.dat","r+b");
    if(f==NULL){
        printf("ERRO NO ARQUIVO\n");
        exit(1);
    }
    Produto aux;
    fread(&aux,sizeof(Produto),1,f);
    printf("%s\n",aux.nome);
*/

    //l =cria_prod(l);
    //l = inteiro_lista(l);

    //l = inserir_prod(l);
    //all_nome(l);
    //busca_parecida(l);

    //l = rmv_prod(l);

    //all_nome(l);

}
