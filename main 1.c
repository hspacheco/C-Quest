#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>


 typedef struct cadastro_funcionario
{
    char nome [50], sexo, cpf[12];
    int cod;
    int senha;

}Funcionario;

int conta_digitos(int x);

void login();

void painel_gerente();

int  consulta_gerente();
void insere_gerente();

int consulta_estoquista();
void insere_estoquista();

int consulta_vendedor();
void insere_vendedor();


void cabecalho();

int acesso = 0;
int cargo = 0;

int main(){
    setlocale(LC_ALL,"Portuguese");
    cabecalho();

    while(1)
    {
        if(acesso == 0)
            login();

        if( cargo == 1) //gerente
        {

        }

        else if (cargo == 2)  //vendedor
        {

        }

        else   //estoquista
        {

        }

    }

}


void cabecalho(){
    system("cls");
    printf("-----------------------------------------------------------\n");
    printf("                       MY_LOJA\n");
    printf("-----------------------------------------------------------\n\n");


}

void login(){

    int opcao;

    printf("----- Faca o login -----\n\n");
    printf("(1) Gerente ");
    printf("(2) Vendedor ");
    printf("(3) Estoquista ");
    printf("(4) Sair\n");

    do{
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                acesso = consulta_gerente();
                cargo = 1;
            break;

            case 2:
            acesso = consulta_vendedor();
            cargo = 2;
            break;

            case 3:
            acesso = consulta_estoquista();
            cargo = 3;
            break;

            case 4:
            printf("Obrigado por usar o nosso sistema!\n");
            printf("Altarquia software. Todos os direitos reservados\n");
            system("pause");
            exit(1);
            break;

            default:
            printf("Opcão inválida!\n");
            break;

    }
  }while(1);
}

void painel_gerente(){
    int opcao;

    while(1)
    {
        printf("-------- PAINEL DO GERENTE --------\n");
        printf("(1) Cadastrar ");
        printf("(2) Alterar cadastro ");
        printf("(3) Consultar ");
        printf("(4) Deslogar");
        do{
            scanf("%d",&opcao);
            switch(opcao){
            case 1:
                cabecalho();
                printf("-------- PAINEL DO GERENTE --------\n");
                printf("");

            break;

            case 4:
                acesso = 0;
                cargo = 0;
                break;
            break;
            }
        }while(1);
    }

}

int conta_digitos(int x){
    int n=0;
    while(x>0){
        x = x/10;
        n++;
    }
    return n;
}

int  consulta_gerente(){
    FILE* arquivo;
    arquivo = fopen("gerente.txt", "rb");

    if(arquivo==NULL){
        printf("Não foi possível abrir o arquivo");
        system("pause");
        exit(1);

    }
    else{
        Funcionario g;
        int codigo, senha;
        printf("Digite a codigo do gerente: ");
        scanf("%d",&codigo);
        printf("Digite a senha do gerente: ");
        scanf("%d",&senha);


        while(fread(&g,sizeof(Funcionario),1,arquivo)==1){
            if((g.cod==codigo)&&(g.senha==senha)){
                printf("ACESSO AUTORIZADO\n");
                return 1;
            }
            else if((g.cod!=codigo)&&(g.senha!=senha)&&(!feof(arquivo))){
                    printf("Ainda estou procurando\n");
                    continue;

            }
            else if(feof(arquivo)==0){
                printf("acabou o arquivo e n achei nada \n");
                printf("ACESSO NEGADO\n");
                break;
            }
        }
       fclose(arquivo);
    }
}

void insere_gerente(){
    FILE* arquivo;
    arquivo = fopen("gerente.txt","ab");

    if(arquivo==NULL){
        printf("Não foi possível abrir o arquivo");
        system("pause");
        exit(1);

    }
    else{
        Funcionario g;
        char c;
        do{
            printf("Digite o nome do gerente: ");
            fflush(stdin);
            fgets(g.nome,50,stdin);

            printf("Digite o sexo(M/F): ");
            fflush(stdin);
            scanf("%c",&g.sexo);

            printf("Digite o cpf: ");
            fflush(stdin);
            fgets((g.cpf),12,stdin);

            fflush(stdin);
            printf("Digite o codigo(6 digitos): ");
            do{
                scanf("%d",&(g.cod));
            }while(conta_digitos(g.cod)!=6);

            fflush(stdin);
            printf("Digite a senha(6 digitos): ");
            do{
                scanf("%d",&(g.senha));
            }while(conta_digitos(g.senha)!=6);+

            printf("\nDeseja continuar(S/N)");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&g,sizeof(Funcionario),1,arquivo);
        }while((c == 's')||(c=='S'));
    }
    fclose(arquivo);
}

int  consulta_estoquista(){
    FILE* arquivo;
    arquivo = fopen("estoquista.txt", "rb");

    if(arquivo==NULL){
        printf("Não foi possível abrir o arquivo");
        system("pause");
        exit(1);

    }
    else{
        Funcionario g;
        int codigo, senha;
        printf("Digite a codigo do estoquista: ");
        scanf("%d",&codigo);
        printf("Digite a senha do estoquista: ");
        scanf("%d",&senha);


        while(fread(&g,sizeof(Funcionario),1,arquivo)==1){
            if((g.cod==codigo)&&(g.senha==senha)){
                printf("ACESSO AUTORIZADO\n");
                return 1;
            }
            else if((g.cod!=codigo)&&(g.senha!=senha)&&(!feof(arquivo))){
                    printf("Ainda estou procurando\n");
                    continue;

            }
            else if(feof(arquivo)==0){
                printf("acabou o arquivo e n achei nada \n");
                printf("ACESSO NEGADO\n");
                break;
            }
        }
       fclose(arquivo);
    }
}

void insere_estoquista(){
    FILE* arquivo;
    arquivo = fopen("estoquista.txt","ab");

    if(arquivo==NULL){
        printf("Não foi possível abrir o arquivo");
        system("pause");
        exit(1);

    }
    else{
        Funcionario g;
        char c;
        do{
            printf("Digite o nome do estoquista: ");
            fflush(stdin);
            fgets(g.nome,50,stdin);

            printf("Digite o sexo(M/F): ");
            fflush(stdin);
            scanf("%c",&g.sexo);

            printf("Digite o cpf: ");
            fflush(stdin);
            fgets((g.cpf),12,stdin);

            fflush(stdin);
            printf("Digite o codigo(6 digitos): ");
            do{
                scanf("%d",&(g.cod));
            }while(conta_digitos(g.cod)!=6);

            fflush(stdin);
            printf("Digite a senha(6 digitos): ");
            do{
                scanf("%d",&(g.senha));
            }while(conta_digitos(g.senha)!=6);+

            printf("\nDeseja continuar(S/N)");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&g,sizeof(Funcionario),1,arquivo);
        }while((c == 's')||(c=='S'));
    }
    fclose(arquivo);
}

int  consulta_vendedor(){
    FILE* arquivo;
    arquivo = fopen("vendedor.txt", "rb");

    if(arquivo==NULL){
        printf("Não foi possível abrir o arquivo");
        system("pause");
        exit(1);

    }
    else{
        Funcionario g;
        int codigo, senha;
        printf("Digite a codigo do vendedor: ");
        scanf("%d",&codigo);
        printf("Digite a senha do vendedor: ");
        scanf("%d",&senha);


        while(fread(&g,sizeof(Funcionario),1,arquivo)==1){
            if((g.cod==codigo)&&(g.senha==senha)){
                printf("ACESSO AUTORIZADO\n");
                return 1;
            }
            else if((g.cod!=codigo)&&(g.senha!=senha)&&(!feof(arquivo))){
                    printf("Ainda estou procurando\n");
                    continue;

            }
            else if(feof(arquivo)==0){
                printf("acabou o arquivo e n achei nada \n");
                printf("ACESSO NEGADO\n");
                break;
            }
        }
       fclose(arquivo);
    }
}

void insere_vendedor(){
    FILE* arquivo;
    arquivo = fopen("vendedor.txt","ab");

    if(arquivo==NULL){
        printf("Não foi possível abrir o arquivo");
        system("pause");
        exit(1);

    }
    else{
        Funcionario g;
        char c;
        do{
            printf("Digite o nome do vendedor: ");
            fflush(stdin);
            fgets(g.nome,50,stdin);

            printf("Digite o sexo(M/F): ");
            fflush(stdin);
            scanf("%c",&g.sexo);

            printf("Digite o cpf: ");
            fflush(stdin);
            fgets((g.cpf),12,stdin);

            fflush(stdin);
            printf("Digite o codigo(6 digitos): ");
            do{
                scanf("%d",&(g.cod));
            }while(conta_digitos(g.cod)!=6);

            fflush(stdin);
            printf("Digite a senha(6 digitos): ");
            do{
                scanf("%d",&(g.senha));
            }while(conta_digitos(g.senha)!=6);+

            printf("\nDeseja continuar(S/N)");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&g,sizeof(Funcionario),1,arquivo);
        }while((c == 's')||(c=='S'));
    }
    fclose(arquivo);
}

