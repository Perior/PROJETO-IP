#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

#define TAMANHO_VETOR 10

int quantidade_motoristas;


// Criação das Structs
typedef struct objeto_Motorista{
    char nome[20];
    char empresa[20];
    int dispon;
    int alt;
}Motorista;

Motorista motorista[TAMANHO_VETOR];

void leituraString(char string[], int quant_caracteres){
    fgets(string, quant_caracteres, stdin);
    if(string != NULL && strlen(string) > 0){
        if((string[strlen(string) - 1]) == '\n'){
            string[strlen(string) - 1] = '\0';
        }
    }
}

Motorista infoMotorista(){
    Motorista mot;

    printf("\n\t\tNome: ");
    leituraString(mot.nome, 20);
    printf("\t\tEmpresa: ");
    leituraString(mot.empresa, 20);

    return mot;
}

void listarMotorista(){
    int i;

    if(quantidade_motoristas == 0){
        printf("Nenhum motorista cadastrado no momento.\n\n");
    }
    else{
        for(i=0; i<quantidade_motoristas; i++){
            printf("============================\n");
            motorista[i].alt = (i+1);
            printf("(%d)\n", motorista[i].alt);
            printf("\nNome: %s", motorista[i].nome);
            printf("\nEmpresa: %s\n", motorista[i].empresa);
        }
    }
}

void adicionarMotorista(Motorista mot){
    if(quantidade_motoristas == TAMANHO_VETOR){
        printf("Não é possível adicionar mais motoristas(ate alocacao rs)\n");
        system("pause");
        return;
    }

    motorista[quantidade_motoristas] = mot;

    quantidade_motoristas++;
}
void alterarMotorista(){
    int i;
    int num;
    listarMotorista();
    if(quantidade_motoristas == 0){
        system("pause");
        return;
    }
    printf("\nDigite o numero do motorista que deseja alterar: ");
    scanf("%d%*c", &num);
    if(num>quantidade_motoristas || num < 0){
        printf("\nMotorista nao encontrado ou  inexistente. Tente novamente.\n");
        printf("Aperte uma tecla para voltar.");
        getchar();
        return;
    }

    else{
        for(i=0; i<=quantidade_motoristas; i++){
            if(num == motorista[i].alt){
                printf("\nDigite um novo nome: ");
                leituraString(motorista[i].nome, 20);
                printf("\nDigite a empresa: ");
                leituraString(motorista[i].empresa, 20);
                return;
            }
        }
    }
}

void menuMotorista(){

    int i;
    int key = 0;
    int tecla = 0;
    int atualiza = 0;
    char vetor[5] = {'>',' ',' ',' ',' '};


    do{

        printf("Escolha uma das opcoes a seguir e aperte Enter para confirmar.\n");
        for(i=atualiza; i<5; i++){
            if(key == KEY_DOWN){
                if(vetor[i+1] == ' '){
                    vetor[i]=' ';
                    vetor[i+1]='>';
                    atualiza++;
                    break;
                }
            }
            if(key == KEY_UP){
                if(vetor[i-1] == ' ' && atualiza > 0){
                    vetor[i] = ' ';
                    vetor[i-1] = '>';
                    atualiza--;
                    break;
                }
            }
        }

        printf("%c Listar Motoristas\n", vetor[0]);
        printf("%c Adicionar Motoristas\n", vetor[1]);
        printf("%c Alterar Motoristas\n", vetor[2]);
        printf("%c Remover Motoristas\n", vetor[3]);
        printf("%c Voltar\n\n", vetor[4]);

        key = getch();

        if(key == KEY_ENTER){
            for(i=0; i<5; i++){
                if(vetor[i]=='>'){
                    tecla=i+1;
                }
            }
        }

        switch(tecla){
            case 1:
                system("cls");
                listarMotorista();
                printf("\n\nPressione uma tecla para voltar.");
                break;

            case 2:
                printf("Digite as informacoes do funcionario a ser inserido: \n");
                adicionarMotorista(infoMotorista());
                break;

            case 3:
                system("cls");
                alterarMotorista();
                break;
/*
            case 4:
                system("cls");
                removerMotorista();
                break;
*/
            case 5:
                break;

        }
        if(tecla!=5){
            tecla=0;
        }
        system("cls");
    }while(tecla!=5);
}

int main()
{
    quantidade_motoristas = 0;
    menuMotorista();
    return 0;
}
