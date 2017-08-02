#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

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
    int tempo_viagem;
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

//Isso aqui é autoexplicativo. Mas vê a questão do caracter \n se realmente vai interferir.
void leituraString(char string[], int quant_caracteres){
    fgets(string, quant_caracteres, stdin);
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
void listarMotorista(){
    int i;
    for(i=0; i<quantidade_motoristas; i++){
        if(quantidade_motoristas == 0){
            printf("Nenhum motorista cadastrado ainda.\n");
            break;
        }
        printf("============================\n");
        printf("(%d)\n", i+1);
        printf("Empresa: %s\n", motorista[i].empresa);
        printf("Nome: %s\n", motorista[i].nome);

    }
}

void listarCobrador(){
    int i;
    for(i=0; i<quantidade_cobradores; i++){
        if(quantidade_cobradores == 0){
            printf("Nenhum cobrador cadastrado ainda.\n");
            break;
        }
        printf("============================\n");
        printf("(%d)\n", i+1);
        printf("Empresa: %s\n", cobrador[i].empresa);
        printf("Nome: %s\n", cobrador[i].nome);

    }
}

void listarOnibus(){
    int i;
    Onibus bus;
    for(i=0; i<quantidade_onibus; i++){
        if(quantidade_onibus == 0){
            printf("Nenhum onibus cadastrado ainda.\n");
            break;
        }
        printf("============================\n");
        printf("(%d)\n", i+1);
        printf("| Empresa: %s |\t", onibus[i].empresa);
        printf("| Num: %d |\t", onibus[i].num_Linha);
        printf("| Nome: %s |\t", onibus[i].linha);
        printf("| Quant: %d |\t", onibus[i].quant);
        printf("| Viagem: %02d:%02d |\n", desconversorTempo(onibus[i].tempo_viagem));

    }
}

//Funções de adição de usuarios. Terão como entrada a função infoX.
void adicionarMotorista(Motorista mot){
    if(quantidade_motoristas == TAMANHO_VETOR){
        printf("Não é possível adicionar mais motoristas(ate alocacao rs)\n");
        return;
    }

    motorista[quantidade_motoristas] = mot;

    quantidade_motoristas++;
}

void adicionarCobrador(Cobrador cob){
    if(quantidade_cobradores == TAMANHO_VETOR){
        printf("Não é possível adicionar mais cobradores(ate alocacao rs)\n");
        return;
    }

    cobrador[quantidade_cobradores] = cob;

    quantidade_cobradores++;
}

void adicionarOnibus(Onibus bus){
    if(quantidade_onibus == TAMANHO_VETOR){
        printf("Não é possível adicionar mais onibus(ate alocacao rs)\n");
        return;
    }

    onibus[quantidade_onibus] = bus;

    quantidade_onibus++;
}


//KKKK Mudei tudoor!!11
//Agora da pra usar setinha pra mexer nos menus. #PAZ

//Submenu referente a opção Motorista.
void menuMotorista(){

    int i;
    int key = 0;
    int tecla = 0;
    int atualiza = 0;
    char vetor[5] = {'>',' ',' ',' ',' '};


    do{
        system("cls");
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
    }while(1);
}

// SubMenu referente a opção Cobrador.
void menuCobrador(){

    int i;
    int key = 0;
    int tecla = 0;
    int atualiza = 0;
    char vetor[5] = {'>',' ',' ',' ',' '};


    do{
        system("cls");
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

        printf("%c Listar Cobradores\n", vetor[0]);
        printf("%c Adicionar Cobradores\n", vetor[1]);
        printf("%c Alterar Cobradores\n", vetor[2]);
        printf("%c Remover Cobradores\n", vetor[3]);
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
    }while(1);
}

// SubMenu referente a opção Onibus
void menuOnibus(){
    int i;
    int key = 0;
    int tecla = 0;
    int atualiza = 0;
    char vetor[7] = {'>',' ',' ',' ',' ',' ',' '};


    do{
        system("cls");
        printf("Escolha uma das opcoes a seguir e aperte Enter para confirmar.\n");
        for(i=atualiza; i<7; i++){
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

        printf("%c Listar Linhas\n", vetor[0]);
        printf("%c Adicionar Nova Linha\n", vetor[1]);
        printf("%c Adicionar Novo(s) Onibus (Linha ja existente)\n", vetor[2]);
        printf("%c Alterar Linha\n", vetor[3]);
        printf("%c Remover Linha do Terminal\n", vetor[4]);
        printf("%c Remover Onibus de uma Linha\n", vetor[5]);
        printf("%c Voltar\n\n", vetor[6]);

        key = getch();

        if(key == KEY_ENTER){
            for(i=0; i<7; i++){
                if(vetor[i]=='>'){
                    tecla=i+1;
                }
            }
        }

        switch(tecla){
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
    }while(1);
}

// SubMenu da opção Configurações (ainda vou pensar em como fazer, mas se quiser ir fazendo...
// São 3 opções aqui: Alterar Usuario/Senha; Limpar Dados; Voltar;
// Limpar Dados vai excluir tudo do arquivo; Voltar volta KEK; Usuario e Senha vai ser ToOoOP

//Depois coloco esse menu com controle de direcional...
void menuConfig(){
}


int main()
{
    quantidade_cobradores = 0;
    quantidade_motoristas = 0;
    quantidade_onibus = 0;

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
