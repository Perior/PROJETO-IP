#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define TAMANHO_VETOR 10

// Criação das Structs
typedef struct objeto_Motorista{
    char nome[20];
    char empresa[20];
    int dispon;
}Motorista;

typedef struct objeto_Cobrador{
    char nome[20];
    char empresa[20];
    int dispon;
}Cobrador;

typedef struct objeto_Onibus{
    char linha[30];
    char empresa[20];
    int num_Linha;
    int quant;
    int hora_Trajeto;
}Onibus;

// Essa variável vai ser usada depois pra teste (ja que ainda nao usamos arquivos/alocação)
int quantidade_usuarios;

// Criação dos vetores dos seus determinados tipos de Tamanho 10
Motorista motorista[TAMANHO_VETOR];
Cobrador cobrador[TAMANHO_VETOR];
Onibus bus[TAMANHO_VETOR];
/*
    WTFFFFF AAAAAA DEPOIS USO ISSO COROI
int DEBUG_MODE = 1;

// imprime informacoes de debug
void imprimeInformacoesDebug(){
    if(DEBUG_MODE){
        printf("\n*********************\n");
        printf("TAMANHO_VETOR = %d\n", TAMANHO_VETOR);
        printf("quantidade_usuarios = %d\n", quantidade_usuarios);
        printf("motorista = %p\n", motorista);
        printf("cobrador = %p\n", cobrador);
        printf("bus = %p\n", bus);
        printf("***********************\n");
    }
}
*/

// Fazer
Motorista infoMotorista(){
}

Cobrador infoCobrador(){
}

Onibus infoOnibus(){
}

// SubMenu referente a opção Motorista.
// Acho que da pra entender de boas.
void menuMotorista(){
    do{
        printf("Digite uma das opcoes a seguir.\n");
        printf("1 - Listar Motoristas\n");
        printf("2 - Adicionar Motoristas\n");
        printf("3 - Alterar Motoristas\n");
        printf("4 - Remover Motoristas\n");
        printf("5 - Voltar\n\n");

        int opc;
        scanf("%d%*c", &opc);

        switch(opc){
            case 1:
                system("cls");
                listarMotorista();
                break;

            case 2:
                system("cls");
                printf("Digite as informacoes do funcionario a ser inserido: \n");
                adicionarMotorista(infoMotorista());
                break;

            case 3:
                system("cls");
                alterarMotorista();
                break;

            case 4:
                system("cls");
                removerMotorista();
                break;

            case 5:
                break;
        }
    }while(0);
}

// SubMenu referente a opção Cobrador.
void menuCobrador(){
    do{
        printf("Digite uma das opcoes a seguir.\n");
        printf("1 - Listar Cobradores\n");
        printf("2 - Adicionar Cobradores\n");
        printf("3 - Alterar Cobradores\n");
        printf("4 - Remover Cobradores\n");
        printf("5 - Voltar\n\n");

        int opc;
        scanf("%d%*c", &opc);

        switch(opc){
            case 1:
                system("cls");
                listarCobrador();
                break;

            case 2:
                system("cls");
                printf("Digite as informacoes do funcionario a ser inserido: \n");
                adicionarCobrador(infoCobrador());
                break;

            case 3:
                system("cls");
                alterarCobrador();
                break;

            case 4:
                system("cls");
                removerCobrador();
                break;

            case 5:
                break;
        }
    }while(0);
}

// SubMenu referente a opção Onibus
void menuOnibus(){
    do{
        printf("Digite uma das opcoes a seguir.\n");
        printf("1 - Listar Linhas\n");
        printf("2 - Adicionar Nova Linha\n");
        printf("3 - Adicionar Novo(s) Onibus (Linha ja existente)\n");
        printf("4 - Alterar Linha\n");
        printf("5 - Remover Linha do Terminal\n");
        printf("6 - Remover Onibus de uma Linha\n");
        printf("7 - Voltar\n\n");

        int opc;
        scanf("%d%*c", &opc);

        switch(opc){
            case 1:
                system("cls");
                listarOnibus();
                break;

            case 2:
                system("cls");
                printf("Digite os dados da Linha a ser adicionada: \n");
                adicionarOnibus(infoOnibus());
                break;

            case 3:
                system("cls");
                printf("Digite a que Linha deseja adicionar Onibus.");
                //"quantos?" deve ficar na função abaixo.
                implementaOnibus();
                break;

            case 4:
                system("cls");
                alterarOnibus();
                break;

            case 5:
                system("cls");
                removerOnibus();
                break;

            case 6:
                system("cls");
                printf("Digite de qual Linha deseja retirar Onibus.");
                decrementaOnibus();
                break;

            case 7:
                break;
        }
    }while(0);
}

// SubMenu da opção Configurações (ainda vou pensar em como fazer, mas se quiser ir fazendo...
// São 3 opções aqui: Alterar Usuario/Senha; Limpar Dados; Voltar;
// Limpar Dados vai excluir tudo do arquivo; Voltar volta KEK; Usuario e Senha vai ser ToOoOP
void menuConfig(){
}

//Chupa bebe
int main()
{
    setlocale(LC_ALL, "portuguese");
    int sair=0;
    do{
        printf("Digite a opçao que deseja alterar.\n");
        printf("1 - MOTORISTAS\n");
        printf("2 - COBRADORES\n");
        printf("3 - ONIBUS\n");
        printf("4 - CONFIGURACOES\n");
        printf("5 - SAIR\n\n");

        int opc;
        scanf("%d%*c", &opc);

        switch(opc){
            case 1:
                system("cls");
                menuMotorista();
                break;

            case 2:
                system("cls");
                menuCobrador();
                break;

            case 3:
                system("cls");
                menuOnibus();
                break;

            case 4:
                system("cls");
                menuConfig();
                break;

            case 5:
                system("cls");
                sair=1;
                break;

            default:
                printf("Opcao nao existente//invalida!\n");
        }
    }while(!sair);
}
