#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

#define TAMANHO_VETOR 10

// Criação das Structs
//Se eu conseguir fazer tudo funcionar com o cursor, retirar int alt das structs.
typedef struct objeto_Motorista{
    char nome[20];
    char empresa[20];
    int dispon;
    int alt;
}Motorista;


typedef struct objeto_Cobrador{
    char nome[20];
    char empresa[20];
    int dispon;
    int alt;
}Cobrador;


typedef struct objeto_Onibus{
    char linha[30];
    char empresa[20];
    int num_Linha;
    int quant;
    int tempo_viagem;
    int alt;
}Onibus;

typedef struct objeto_Tempo{
    int hora;
    int minuto;
}Tempo;


// Essas variáveis vao ser usadas depois pra teste (ja que ainda nao usamos arquivos/alocação)
int quantidade_motoristas;
int quantidade_cobradores;
int quantidade_onibus;

// Criação dos vetores dos seus determinados tipos de Tamanho 10
Motorista motorista[TAMANHO_VETOR];
Cobrador cobrador[TAMANHO_VETOR];
Onibus onibus[TAMANHO_VETOR];


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

//Isso aqui é autoexplicativo.
void leituraString(char string[], int quant_caracteres){
    fgets(string, quant_caracteres, stdin);
    if(string != NULL && strlen(string) > 0){
        if((string[strlen(string) - 1]) == '\n'){
            string[strlen(string) - 1] = '\0';
        }
    }
}

void substPause(){
    printf("\nAperte uma tecla para voltar.");
    getchar();
}


//Funçoes para converter hora:minuto em minuto e vice-versa. Vou utilizar minuto pra fazer os calculos futuros.
//Mas temos que mostrar o tempo no formato HH:MM para o usuario do programa, por isso o "desconversor".
int conversorTempo(int hora, int minuto){
    hora*=60;
    minuto+=hora;
    return minuto;
}

Tempo desconversorTempo(int minuto){
    Tempo temp;
    temp.hora=minuto/60;
    temp.minuto=minuto-(temp.hora*60);
    return temp;
}


//Funçoes que vao pedir as informaçoes dos usuarios a serem adicionados. É a entrada da função de adicionarX.
Motorista infoMotorista(){
    Motorista mot;

    printf("\n\t\tNome: ");
    leituraString(mot.nome, 20);
    printf("\t\tEmpresa: ");
    leituraString(mot.empresa, 20);

    return mot;
}

Cobrador infoCobrador(){
    Cobrador cob;

    printf("\n\t\tNome: ");
    leituraString(cob.nome, 20);
    printf("\t\tEmpresa: ");
    leituraString(cob.empresa, 20);

    return cob;
}

Onibus infoOnibus(){
    Onibus bus;
    int hora, minuto;


    printf("\n\t\tNome da Linha: ");
    leituraString(bus.linha, 30);
    printf("\n\t\tNumero da Linha: ");
    scanf("%d%*c", &bus.num_Linha);
    printf("\n\t\tEmpresa do Onibus: ");
    leituraString(bus.empresa, 20);
    printf("\t\tQuantidade de Onibus dessa Linha: ");
    scanf("%d%*c", &bus.quant);
    printf("\n\t\tTempo Medio de Viagem (formato hh:mm): ");
    scanf("%02d:%02d%*c", &hora, &minuto);

    bus.tempo_viagem = conversorTempo(hora, minuto);

    return bus;
}

//Também, autoexplicativo, essas funções irão listar (se ja cadastrados) os usuarios.
int listarMotorista(int n){
    int i;
    int key;
    int atualiza = 0;

    if(quantidade_motoristas == 0){
        printf("Nenhum motorista cadastrado no momento.\n\n");
    }
    else{
        do{
            system("cls");
            if(key == KEY_DOWN && (atualiza+1)<quantidade_motoristas && n){
                atualiza++;
            }
            if(key == KEY_UP && atualiza > 0 && n){
                atualiza--;
            }
            if(key == KEY_ENTER && n){
                return atualiza+1;
            }

            for(i=0; i<quantidade_motoristas; i++){
                if(atualiza == i && n){
                    printf("============================\n");

                    printf("%c (%d)\n", '>', i+1);
                    printf("\nNome: %s", motorista[i].nome);
                    printf("\nEmpresa: %s\n", motorista[i].empresa);
                }
                else{
                    printf("============================\n");

                    printf("%c (%d)\n", ' ', i+1);
                    printf("\nNome: %s", motorista[i].nome);
                    printf("\nEmpresa: %s\n", motorista[i].empresa);
                }
            }

            if(n){
                printf("\n======Selecione o funcionario que deseja modificar. (Clique Enter para selecionar)=====");
                key = getch();
            }

        }while(n!=0);
    }
}

void listarCobrador(){
    int i;

    if(quantidade_cobradores == 0){
        printf("Nenhum cobrador cadastrado no momento.\n\n");
    }
    else{
        for(i=0; i<quantidade_cobradores; i++){
            printf("============================\n");
            cobrador[i].alt = (i+1);
            printf("(%d)\n", cobrador[i].alt);
            printf("Empresa: %s\n", cobrador[i].empresa);
            printf("Nome: %s\n", cobrador[i].nome);
        }
    }
}

void listarOnibus(){
    int i;
    Onibus bus;

    if(quantidade_onibus == 0){
        printf("Nenhum onibus cadastrado no momento.\n\n");
    }
    else{
        for(i=0; i<quantidade_onibus; i++){
            printf("============================\n");
            onibus[i].alt = (i+1);
            printf("(%d)\n", onibus[i].alt);
            printf("| Empresa: %s |\t", onibus[i].empresa);
            printf("| Num: %d |\t", onibus[i].num_Linha);
            printf("| Nome: %s |\t", onibus[i].linha);
            printf("| Quant: %d |\t", onibus[i].quant);
            printf("| Viagem: %02d:%02d |\n", desconversorTempo(onibus[i].tempo_viagem));
        }
    }
}

//Funções de adição de usuarios. Terão como entrada a função infoX.
void adicionarMotorista(Motorista mot){
    if(quantidade_motoristas == TAMANHO_VETOR){
        printf("Não é possível adicionar mais motoristas(ate alocacao rs)\n");
        substPause();
        return;
    }

    motorista[quantidade_motoristas] = mot;

    quantidade_motoristas++;
}

void adicionarCobrador(Cobrador cob){
    if(quantidade_cobradores == TAMANHO_VETOR){
        printf("Não é possível adicionar mais cobradores(ate alocacao rs)\n");
        substPause();
        return;
    }

    cobrador[quantidade_cobradores] = cob;

    quantidade_cobradores++;
}

void adicionarOnibus(Onibus bus){
    if(quantidade_onibus == TAMANHO_VETOR){
        printf("Não é possível adicionar mais onibus(ate alocacao rs)\n");
        substPause();
        return;
    }

    onibus[quantidade_onibus] = bus;

    quantidade_onibus++;
}


//Alteração

void alterarMotorista(){
    int i;
    int num;

    num = listarMotorista(1);


    if(quantidade_motoristas == 0){
        substPause();
        return;
    }
    else{
        for(i=0; i<=quantidade_motoristas; i++){
            if(num == (i+1)){
                listarMotorista(0);
                printf("\nDigite um novo nome: ");
                leituraString(motorista[i].nome, 20);
                printf("Digite a empresa: ");
                leituraString(motorista[i].empresa, 20);
                return;
            }
        }
    }
}

void alterarCobrador(){
    int i;
    int num;
    listarCobrador();
    if(quantidade_cobradores == 0){
        substPause();
        return;
    }
    printf("\nDigite o numero do cobrador que deseja alterar: ");
    scanf("%d%*c", &num);
    if(num>quantidade_cobradores || num < 0){
        printf("\nCobrador nao encontrado ou  inexistente. Tente novamente.\n");
        substPause();
        return;
    }

    else{
        for(i=0; i<=quantidade_cobradores; i++){
            if(num == cobrador[i].alt){
                printf("\nDigite um novo nome: ");
                leituraString(cobrador[i].nome, 20);
                printf("\nDigite a empresa: ");
                leituraString(cobrador[i].empresa, 20);
                return;
            }
        }
    }
}

void alterarOnibus(){
    int i;
    int num;
    int hora, minuto;
    listarOnibus();
    if(quantidade_onibus == 0){
        substPause();
        return;
    }
    printf("\nDigite o numero do onibus que deseja alterar: ");
    scanf("%d%*c", &num);
    if(num>quantidade_onibus || num < 0){
        printf("\nOnibus nao encontrado ou  inexistente. Tente novamente.\n");
        substPause();
        return;
    }

    else{
        for(i=0; i<=quantidade_onibus; i++){
            if(num == onibus[i].alt){
                printf("\nDigite a empresa: ");
                leituraString(onibus[i].empresa, 20);
                printf("\nDigite novo numero de linha: ");
                onibus[i].num_Linha = scanf("%d%*c", &num);
                printf("\nDigite uma nova linha: ");
                leituraString(onibus[i].linha, 30);
                printf("\nDigite a nova quantidade de onibus: ");
                onibus[i].quant = scanf("%d%*c", &num);
                printf("Digite o novo tempo medio de viagem: ");
                scanf("%02d:%02d%*c", &hora, &minuto);
                onibus[i].tempo_viagem = conversorTempo(hora, minuto);
                return;
            }
        }
    }
}
/*
//remoção
void removerMotorista(){

    quantidade_motoristas--;
}
*/

//KKKK Mudei tudoor!!11
//Agora da pra usar setinha pra mexer nos menus. #PAZ
//Tem como fazer uma função só de menu que receba como entrada algo que e emita como saida cobrador ou motorista? (simplificar)

//Submenu referente a opção Motorista.
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
                listarMotorista(0);
                substPause();
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

int main(){
    menuMotorista();
    return 0;
}
