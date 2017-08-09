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

//Mudou: Essas funções de listar agora vão apenas listar se receberem 0 como entrada ou vão listar com cursor se receberem 1.
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
                    printf("%c (%d)\n", '>', (i+1));
                    printf("\nNome: %s", motorista[i].nome);
                    printf("\nEmpresa: %s\n", motorista[i].empresa);
                }
                else{
                    printf("============================\n");
                    printf("%c (%d)\n", ' ', (i+1));
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

int listarCobrador(int n){
    int i;
    int key;
    int atualiza = 0;

    if(quantidade_cobradores == 0){
        printf("Nenhum cobrador cadastrado no momento.\n\n");
    }
    else{
        do{
            system("cls");
            if(key == KEY_DOWN && (atualiza+1)<quantidade_cobradores && n){
                atualiza++;
            }
            if(key == KEY_UP && atualiza > 0 && n){
                atualiza--;
            }
            if(key == KEY_ENTER && n){
                return atualiza+1;
            }

            for(i=0; i<quantidade_cobradores; i++){
                if(atualiza == i && n){
                    printf("============================\n");
                    printf("%c (%d)\n", '>', (i+1));
                    printf("\nNome: %s", cobrador[i].nome);
                    printf("\nEmpresa: %s\n", cobrador[i].empresa);
                }
                else{
                    printf("============================\n");
                    printf("%c (%d)\n", ' ', (i+1));
                    printf("\nNome: %s", cobrador[i].nome);
                    printf("\nEmpresa: %s\n", cobrador[i].empresa);
                }
            }

            if(n){
                printf("\n======Selecione o funcionario que deseja modificar. (Clique Enter para selecionar)=====");
                key = getch();
            }

        }while(n!=0);
    }
}

int listarOnibus(int n){
    int i;
    int key;
    int atualiza = 0;

    if(quantidade_onibus == 0){
        printf("Nenhum onibus cadastrado no momento.\n\n");
    }
    else{
        do{
            system("cls");
            if(key == KEY_DOWN && (atualiza+1)<quantidade_onibus && n){
                atualiza++;
            }
            if(key == KEY_UP && atualiza > 0 && n){
                atualiza--;
            }
            if(key == KEY_ENTER && n){
                return atualiza+1;
            }
            for(i=0; i<quantidade_onibus; i++){
                if(atualiza == i && n){
                    printf("============================\n");
                    printf("%c (%d)\n", '>', (i+1));
                    printf("| Empresa: %s |\t", onibus[i].empresa);
                    printf("| Num: %d |\t", onibus[i].num_Linha);
                    printf("| Nome: %s |\t", onibus[i].linha);
                    printf("| Quant: %d |\t", onibus[i].quant);
                    printf("| Viagem: %02d:%02d |\n", desconversorTempo(onibus[i].tempo_viagem));
                }
                else{
                    printf("============================\n");
                    printf("%c (%d)\n", ' ', (i+1));
                    printf("| Empresa: %s |\t", onibus[i].empresa);
                    printf("| Num: %d |\t", onibus[i].num_Linha);
                    printf("| Nome: %s |\t", onibus[i].linha);
                    printf("| Quant: %d |\t", onibus[i].quant);
                    printf("| Viagem: %02d:%02d |\n", desconversorTempo(onibus[i].tempo_viagem));
                }
            }

            if(n){
                printf("\n======Selecione o funcionario que deseja modificar. (Clique Enter para selecionar)=====");
                key = getch();
            }
        }while(n!=0);
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

//Funções de alteração

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

    num = listarCobrador(1);

    if(quantidade_cobradores == 0){
        substPause();
        return;
    }
    else{
        for(i=0; i<=quantidade_cobradores; i++){
            if(num == (i+1)){
                listarCobrador(0);
                printf("\nDigite um novo nome: ");
                leituraString(cobrador[i].nome, 20);
                printf("Digite a empresa: ");
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

    num = listarOnibus(1);

    if(quantidade_onibus == 0){
        substPause();
        return;
    }
    else{
        for(i=0; i<=quantidade_onibus; i++){
            if(num == (i+1)){
                listarOnibus(0);
                printf("\nDigite uma nova linha: ");
                leituraString(onibus[i].linha, 30);
                printf("\nDigite novo numero de linha: ");
                scanf("%d%*c", &onibus[i].num_Linha);
                printf("\nDigite a empresa: ");
                leituraString(onibus[i].empresa, 20);
                printf("\nDigite a nova quantidade de onibus: ");
                scanf("%d%*c", &onibus[i].quant);
                printf("Digite o novo tempo medio de viagem: ");
                scanf("%02d:%02d%*c", &hora, &minuto);
                onibus[i].tempo_viagem = conversorTempo(hora, minuto);
                return;
            }
        }
    }
}

//Funções de reorganização vetorial.
void reorganizaVetorM(int valorVetor){
    int i = valorVetor;
    while(i < quantidade_motoristas - 1){
        motorista[i] = motorista[i+1];
        i++;
    }
}

void reorganizaVetorC(int valorVetor){
    int i = valorVetor;
    while(i < quantidade_cobradores - 1){
        cobrador[i] = cobrador[i+1];
        i++;
    }
}

void reorganizaVetorO(int valorVetor){
    int i = valorVetor;
    while(i < quantidade_onibus - 1){
        onibus[i] = onibus[i+1];
        i++;
    }
}

//Funções de remoção
void removerMotorista(){
    int i;
    int num;

    num = listarMotorista(1);

    if(quantidade_motoristas == 0){
        printf("Não há motoristas para remover.\n\n");
        substPause();
    }
    else{
        for(i=0; i<quantidade_motoristas; i++){
            if(num == (i+1)){
                reorganizaVetorM(i);
                quantidade_motoristas--;
            }
        }
    }
}

void removerCobrador(){
    int i;
    int num;

    num = listarCobrador(1);

    if(quantidade_cobradores == 0){
        printf("Não há cobradores para remover.\n\n");
        substPause();
    }
    else{
        for(i=0; i<quantidade_cobradores; i++){
            if(num == (i+1)){
                reorganizaVetorC(i);
                quantidade_cobradores--;
            }
        }
    }
}

void removerOnibus(){
    int i;
    int num;

    num = listarOnibus(1);

    if(quantidade_onibus == 0){
        printf("Não há onibus para remover.\n\n");
        substPause();
    }
    else{
        for(i=0; i<quantidade_onibus; i++){
            if(num == (i+1)){
                reorganizaVetorO(i);
                quantidade_onibus--;
            }
        }
    }
}

//Essas duas funções mexem na quantidade de onibus de uma linha. E vou usá-la mais na frente.
void implementaOnibus(){
    int i;
    int num;

    num = listarOnibus(1);

    if(quantidade_onibus == 0){
        printf("Não há onibus para modificar. Adicione uma nova linha.\n\n");
        substPause();
    }
    else{
        for(i=0; i<quantidade_onibus; i++){
            if(num == (i+1)){
                printf("Quantos onibus deseja acrescentar a essa linha?\n");
                scanf("%d%*c", &num);
                onibus[i].quant += num;
            }
        }
    }
}

void decrementaOnibus(){
    int i;
    int num;

    num = listarOnibus(1);

    if(quantidade_onibus == 0){
        printf("Não há onibus para modificar. Adicione uma nova linha.\n\n");
        substPause();
    }
    else{
        for(i=0; i<quantidade_onibus; i++){
            if(num == (i+1)){
                printf("Quantos onibus deseja retirar dessa linha?\n");
                scanf("%d%*c", &num);
                if(num <= onibus[i].quant){
                    onibus[i].quant -= num;
                }
                else{
                    printf("Voce esta retirando onibus demais!\n");
                }
            }
        }
    }
}

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

            case 4:
                system("cls");
                removerMotorista();
                break;

            case 5:
                break;
        }
        if(tecla!=5){
            tecla=0;
        }
        system("cls");

    }while(tecla!=5);
}

// SubMenu referente a opção Cobrador.
void menuCobrador(){

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
                listarCobrador(0);
                substPause();
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
        if(tecla!=5){
            tecla=0;
        }
        system("cls");

    }while(tecla!=5);
}

// SubMenu referente a opção Onibus
void menuOnibus(){
    int i;
    int key = 0;
    int tecla = 0;
    int atualiza = 0;
    char vetor[7] = {'>',' ',' ',' ',' ',' ',' '};


    do{

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
                listarOnibus(0);
                substPause();
                break;

            case 2:
                system("cls");
                printf("Digite os dados da Linha a ser adicionada: \n");
                adicionarOnibus(infoOnibus());
                break;

            case 3:
                system("cls");
                printf("Digite a que Linha deseja adicionar Onibus.");
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
        if(tecla!=7){
            tecla=0;
        }
        system("cls");

    }while(tecla!=7);
}

// SubMenu da opção Configurações (ainda vou pensar em como fazer, mas se quiser ir fazendo...
// São 3 opções aqui: Alterar Usuario/Senha; Limpar Dados; Voltar;
// Limpar Dados vai excluir tudo do arquivo; Voltar volta KEK; Usuario e Senha vai ser ToOoOP

//Depois coloco esse menu com cursor...
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
