#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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

typedef struct login_Adm{
    char user[20];
    char password[20];
}Login;

// Essas variáveis vao ser usadas depois pra teste (ja que ainda nao usamos arquivos/alocação)
int quantidade_motoristas;
int quantidade_cobradores;
int quantidade_onibus;

// Criação dos vetores dos seus determinados tipos, com Tamanho 10
Motorista motorista[TAMANHO_VETOR];
Cobrador cobrador[TAMANHO_VETOR];
Onibus onibus[TAMANHO_VETOR];
Login dados;

//Mensagem de erro para problemas na abertura do arquivo.
void errorArquivo(char nome_arquivo[]){
    printf("\nErro: Não foi possível abrir o arquivo %s\n", nome_arquivo);
}

//Função que lê o que está no arquivo.
void lerArquivo(){
    FILE *arquivo = fopen("terminal.bin", "rb");

    if(arquivo!=NULL){
        int aux;
    //Motorista
        aux = (int)fread(&quantidade_motoristas, sizeof(int), 1, arquivo);
        if(aux < 1){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        aux = (int)fread(motorista, sizeof(Motorista), TAMANHO_VETOR, arquivo);
        if(aux < TAMANHO_VETOR){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }
    //Cobrador
        aux = (int)fread(&quantidade_cobradores, sizeof(int), 1, arquivo);
        if(aux < 1){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        aux = (int)fread(cobrador, sizeof(Cobrador), TAMANHO_VETOR, arquivo);
        if(aux < TAMANHO_VETOR){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }
    //Onibus
        aux = (int)fread(&quantidade_onibus, sizeof(int), 1, arquivo);
        if(aux < 1){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        aux = (int)fread(onibus, sizeof(Onibus), TAMANHO_VETOR, arquivo);
        if(aux < TAMANHO_VETOR){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }
    //Login
        aux = (int)fread(&dados, sizeof(Login), 2, arquivo);
        if(aux < 2){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        fclose(arquivo);
    }
    else{
        criacaoLogin();
    }
}

//Função que escreve as informações no arquivo.
void escreveArquivo(){
    FILE *arquivo = fopen("terminal.bin", "wb");
    if(arquivo == NULL){
        errorArquivo("terminal.bin");
        exit(1);
    }
    else{
        int aux;
    //Motorista
        aux = (int)fwrite(&quantidade_motoristas, sizeof(int), 1, arquivo);
        if(aux < 1){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        aux = (int)fwrite(motorista, sizeof(Motorista), TAMANHO_VETOR, arquivo);
        if(aux < TAMANHO_VETOR){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }
    //Cobrador
        aux = (int)fwrite(&quantidade_cobradores, sizeof(int), 1, arquivo);
        if(aux < 1){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        aux = (int)fwrite(cobrador, sizeof(Cobrador), TAMANHO_VETOR, arquivo);
        if(aux < TAMANHO_VETOR){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }
    //Onibus
        aux = (int)fwrite(&quantidade_onibus, sizeof(int), 1, arquivo);
        if(aux < 1){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        aux = (int)fwrite(onibus, sizeof(Onibus), TAMANHO_VETOR, arquivo);
        if(aux < TAMANHO_VETOR){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }
    //Login
        aux = (int)fwrite(&dados, sizeof(Login), 2, arquivo);
        if(aux < 2){
            errorArquivo("terminal.bin");
            fclose(arquivo);
            return;
        }

        fclose(arquivo);
    }
}

//Função de leitura de strings.
void leituraString(char string[], int quant_caracteres){
    fgets(string, quant_caracteres, stdin);
    if(string != NULL && strlen(string) > 0){
        if((string[strlen(string) - 1]) == '\n'){
            string[strlen(string) - 1] = '\0';
        }
    }
}

//Função para ler e mascarar a senha de Login.
void leituraSenha(char string[], int quant_caracteres){
    int i;

    for(i=0; i<quant_caracteres; i++){
        string[i] = getch();
        if(string[i] == KEY_ENTER){
            string[i] = '\0';
            break;
        }
        else if(string[i] == 8){
            if(i == 0){
                string[i] = '\b';
                i--;
            }
            else{
                printf("\b \b");
                string[i] = '\0';
                string[i-1] = '\0';
                i-=2;
            }
        }
        else{
            printf("*");
        }
    }
}

//Função para substituir o uso do system("pause").
void substPause(){
    printf("\n\n\t\t\tAperte uma tecla para continuar.");
    getchar();
}


//Funçoes para converter hora:minuto em minuto e vice-versa. Vou utilizar minuto pra fazer cálculos futuros.
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


//Funçoes que vão pedir as informações dos usuários a serem adicionados. É a entrada da função adicionarX.
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
    printf("\n\t\tNúmero da Linha: ");
    scanf("%d%*c", &bus.num_Linha);
    printf("\n\t\tEmpresa do Ônibus: ");
    leituraString(bus.empresa, 20);
    printf("\t\tQuantidade de Ônibus dessa Linha: ");
    scanf("%d%*c", &bus.quant);
    printf("\n\t\tTempo Médio de Viagem (formato hh:mm): ");
    scanf("%02d:%02d%*c", &hora, &minuto);

    bus.tempo_viagem = conversorTempo(hora, minuto);

    return bus;
}

//Funções para listar os dados.
//Ela recebe um inteiro 0 para apenas listar ou recebe 1 para listar com o caracter '>' para usarmos o cursor.
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
                printf("\n======Selecione o funcionário que deseja modificar. (Clique Enter para confirmar)=====");
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
                printf("\n======Selecione o funcionário que deseja modificar. (Clique Enter para confirmar)=====");
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
        printf("Nenhum ônibus cadastrado no momento.\n\n");
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
                    printf("| Núm.: %d |\t", onibus[i].num_Linha);
                    printf("| Nome: %s |\t", onibus[i].linha);
                    printf("| Quant.: %d |\t", onibus[i].quant);
                    printf("| Viagem: %02d:%02d |\n", desconversorTempo(onibus[i].tempo_viagem));
                }
                else{
                    printf("============================\n");
                    printf("%c (%d)\n", ' ', (i+1));
                    printf("| Empresa: %s |\t", onibus[i].empresa);
                    printf("| Núm.: %d |\t", onibus[i].num_Linha);
                    printf("| Nome: %s |\t", onibus[i].linha);
                    printf("| Quant.: %d |\t", onibus[i].quant);
                    printf("| Viagem: %02d:%02d |\n", desconversorTempo(onibus[i].tempo_viagem));
                }
            }

            if(n){
                printf("\n======Selecione a linha que deseja modificar. (Clique Enter para confirmar)=====");
                key = getch();
            }
        }while(n!=0);
    }
}

//Funções de adição de dados. Terão como entrada a função infoX.
void adicionarMotorista(Motorista mot){
    if(quantidade_motoristas == TAMANHO_VETOR){
        printf("Não é possível adicionar mais motoristas.\n");
        substPause();
        return;
    }

    motorista[quantidade_motoristas] = mot;

    quantidade_motoristas++;
}

void adicionarCobrador(Cobrador cob){
    if(quantidade_cobradores == TAMANHO_VETOR){
        printf("Não é possível adicionar mais cobradores.\n");
        substPause();
        return;
    }

    cobrador[quantidade_cobradores] = cob;

    quantidade_cobradores++;
}

void adicionarOnibus(Onibus bus){
    if(quantidade_onibus == TAMANHO_VETOR){
        printf("Não é possível adicionar mais ônibus.\n");
        substPause();
        return;
    }

    onibus[quantidade_onibus] = bus;

    quantidade_onibus++;
}

//Funções de alteração dos dados.

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
                printf("\nDigite novo número de linha: ");
                scanf("%d%*c", &onibus[i].num_Linha);
                printf("\nDigite a empresa: ");
                leituraString(onibus[i].empresa, 20);
                printf("\nDigite a nova quantidade de onibus: ");
                scanf("%d%*c", &onibus[i].quant);
                printf("Digite o novo tempo médio de viagem: ");
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

//Funções de remoção dos dados inseridos.
void removerMotorista(){
    int i;
    int num;

    num = listarMotorista(1);

    if(quantidade_motoristas == 0){
        substPause();
        return;
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
        substPause();
        return;
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
        substPause();
        return;
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

//Essas duas funções alteram a quantidade de ônibus de uma linha apenas. Vou usá-la mais na frente.
void implementaOnibus(){
    int i;
    int num;

    num = listarOnibus(1);

    if(quantidade_onibus == 0){
        substPause();
        return;
    }
    else{
        for(i=0; i<quantidade_onibus; i++){
            if(num == (i+1)){
                printf("Quantos ônibus deseja acrescentar a essa linha?\n");
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
        substPause();
        return;
    }
    else{
        for(i=0; i<quantidade_onibus; i++){
            if(num == (i+1)){
                printf("Quantos ônibus deseja retirar dessa linha?\n");
                scanf("%d%*c", &num);
                if(num <= onibus[i].quant){
                    onibus[i].quant -= num;
                }
                else{
                    printf("Você está retirando ônibus demais!\n");
                }
            }
        }
    }
}

//Função que cadastra o Usuario do programa.
void criacaoLogin(){
    printf("\n\n\t\t\t==================================================\n");
    printf("\t\t\t||\t       BEM VINDO NOVO USUÁRIO   \t||\n");
    printf("\t\t\t==================================================");
    printf("\n\t\t\t**************************************************");
    printf("\n\t\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t\t*    Crie um login para acessar este programa.   *\n");
    printf("\t\t\t*\t\t\t\t\t\t *\n");
    printf("\t\t\t**************************************************\n");
    printf("\t\t\t   Nome de Usuário: ");
    leituraString(dados.user, 20);
    printf("\t\t\t   Senha: ");
    leituraSenha(dados.password, 20);

    printf("\n\n\t\t\t**************************************************");
    printf("\n\t\t\t*         Cadastro realizado com sucesso!\t *\n");
    printf("\t\t\t**************************************************\n");
    escreveArquivo();
    substPause();
    system("cls");
}

//Função que pede ao usuario para Logar.
int telaLogin(int aux){
    Login login;

    while(1){
        printf("\n\n\t\t\t==============================\n");
        printf("\t\t\t||\t   BEM VINDO        ||\n");
        printf("\t\t\t==============================");
        printf("\n");
        printf("\n\t\t\t   Usuário: ");
        leituraString(login.user, 20);
        printf("\t\t\t   Senha: ");
        leituraSenha(login.password, 20);

        if(strcmp(login.user, dados.user) == 0 && strcmp(login.password, dados.password) == 0){
            printf("\n\t\t\t\t     .-""-.\n");
            printf("\t\t\t\t  / /    \\ \\\n");
            printf("\t\t\t\t  | |    | |\n");
            printf("\t\t\t\t         | |\n");
            printf("\t\t\t\t     .-""-.| \\\n");
            printf("\t\t\t\t ///`.::::.`\\\n");
            printf("\t\t\t\t||| ::/  \\:: ;\n");
            printf("\t\t\t\t||; ::\\__/:: ;\n");
            printf("\t\t\t\t \\\\\\ '::::' /\n");
            printf("\t\t\t\t  `=':-..-'`");
            substPause();
            system("cls");
            return 1;
        }
        else{
            printf("\n\n\t\t**************************************************");
            printf("\n\t\t*\t     Usuário ou Senha errados.\t\t *\n");
            printf("\t\t**************************************************\n");
            substPause();
            if(aux){
                return 0;
            }
            system("cls");
        }
    }
}

void editarLogin(){
    printf("Confirme seu usuário e senha atual antes de prosseguir.\n\n");

    if(telaLogin(1) == 1){
        printf("Digite um novo usuário e uma nova senha.\n");
        printf("Usuário: ");
        leituraString(dados.user, 20);
        printf("Senha: ");
        leituraSenha(dados.password, 20);

        printf("\n\nLogin alterado com sucesso!");
    }
    else{

        return;
    }


}

void limparDadosArquivos(){
    printf("Confirme seu usuário e senha atual.");

    if(telaLogin(1) == 1){
        int aux;
        printf("Você realmente deseja apagar todos os dados do programa?\n");
        aux = (int)remove("terminal.bin");
        if(aux != 0){
            errorArquivo("terminal.bin");
            return;
        }
        else{
            printf("\n\t\tTodos os dados foram apagados.");
            substPause();
            exit(0);
        }
    }
    else{
        return;
    }
}

//Submenus: Utiliza-se as ARROW_KEYS(setas do teclado) para selecionar uma opção e ENTER para confirmá-la.

//Submenu referente a opção Motorista.
void menuMotorista(){

    int i;
    int key = 0;
    int tecla = 0;
    int atualiza = 0;
    char vetor[5] = {'>',' ',' ',' ',' '};


    do{
        printf("\n\n               Escolha uma das opções a seguir e aperte Enter para confirmar.\n\n\n");

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

        printf("\t\t\t\t***************************\n");
        printf("\t\t\t\t||%c Listar Motoristas    ||\n", vetor[0]);
        printf("\t\t\t\t||%c Adicionar Motoristas ||\n", vetor[1]);
        printf("\t\t\t\t||%c Alterar Motoristas   ||\n", vetor[2]);
        printf("\t\t\t\t||%c Remover Motoristas   ||\n", vetor[3]);
        printf("\t\t\t\t||%c Voltar               ||\n", vetor[4]);
        printf("\t\t\t\t***************************\n");

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
                printf("Digite as informacões do funcionário a ser inserido: \n");
                adicionarMotorista(infoMotorista());
                escreveArquivo();
                break;

            case 3:
                system("cls");
                alterarMotorista();
                escreveArquivo();
                break;

            case 4:
                system("cls");
                removerMotorista();
                escreveArquivo();
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

        printf("\n\n               Escolha uma das opções a seguir e aperte Enter para confirmar.\n\n\n");
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

        printf("\t\t\t\t***************************\n");
        printf("\t\t\t\t||%c Listar Cobradores    ||\n", vetor[0]);
        printf("\t\t\t\t||%c Adicionar Cobradores ||\n", vetor[1]);
        printf("\t\t\t\t||%c Alterar Cobradores   ||\n", vetor[2]);
        printf("\t\t\t\t||%c Remover Cobradores   ||\n", vetor[3]);
        printf("\t\t\t\t||%c Voltar               ||\n", vetor[4]);
        printf("\t\t\t\t***************************\n");

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
                printf("Digite as informacões do funcionário a ser inserido: \n");
                adicionarCobrador(infoCobrador());
                escreveArquivo();
                break;

            case 3:
                system("cls");
                alterarCobrador();
                escreveArquivo();
                break;

            case 4:
                system("cls");
                removerCobrador();
                escreveArquivo();
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

        printf("\n\n                Escolha uma das opções a seguir e aperte Enter para confirmar.\n\n\n");
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


        printf("\t\t\t||%c Listar Linhas                                 ||\n", vetor[0]);
        printf("\t\t\t||%c Adicionar Nova Linha                          ||\n", vetor[1]);
        printf("\t\t\t||%c Adicionar Novo(s) Ônibus (Linha já existente) ||\n", vetor[2]);
        printf("\t\t\t||%c Alterar Linha                                 ||\n", vetor[3]);
        printf("\t\t\t||%c Remover Linha do Terminal                     ||\n", vetor[4]);
        printf("\t\t\t||%c Remover Ônibus de uma Linha                   ||\n", vetor[5]);
        printf("\t\t\t||%c Voltar                                        ||\n", vetor[6]);


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
                escreveArquivo();
                break;

            case 3:
                system("cls");
                implementaOnibus();
                escreveArquivo();
                break;

            case 4:
                system("cls");
                alterarOnibus();
                escreveArquivo();
                break;

            case 5:
                system("cls");
                removerOnibus();
                escreveArquivo();
                break;

            case 6:
                system("cls");
                decrementaOnibus();
                escreveArquivo();
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

//Submenu referente a Configurações. Mudança de user/password e limpar dados.
void menuConfig(){
    int i;
    int key = 0;
    int tecla = 0;
    int atualiza = 0;
    char vetor[3] = {'>',' ',' '};


    do{

        printf("\n\n              Escolha uma das opções a seguir e aperte Enter para confirmar.\n\n\n");
        for(i=atualiza; i<3; i++){
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

        printf("\t\t\t||%c Alterar Usuário/Senha ||\n", vetor[0]);
        printf("\t\t\t||%c Apagar todos os Dados ||\n", vetor[1]);
        printf("\t\t\t||%c Voltar                ||\n", vetor[2]);

        key = getch();

        if(key == KEY_ENTER){
            for(i=0; i<3; i++){
                if(vetor[i]=='>'){
                    tecla=i+1;
                }
            }
        }

        switch(tecla){
            case 1:
                system("cls");
                editarLogin();
                break;

            case 2:
                system("cls");
                limparDadosArquivos();

            case 3:
                break;
        }
        if(tecla!=3){
            tecla=0;
        }
        system("cls");

    }while(tecla!=3);
}

//Falta implementar as arrow keys aqui.
void mainMenu(){

    int sair=0;

    do{
        printf("\n\n\n\t\t\t=======================MENU PRINCIPAL========================\n");
        printf("\n\t\t\t\t\t");
        printf("Digite a opção que deseja alterar.\n\n");
        printf("\t\t\t\t1 - MOTORISTAS\n");
        printf("\t\t\t\t2 - COBRADORES\n");
        printf("\t\t\t\t3 - ONIBUS\n");
        printf("\t\t\t\t4 - CONFIGURAÇÕES\n");
        printf("\t\t\t\t5 - SAIR\n\n");
        printf("\t\t\t==============================================================\n");

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
                escreveArquivo();
                break;

            default:
                printf("Opcão não existente//inválida!\n");
        }
    }while(!sair);
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    lerArquivo();

    if(telaLogin(0) == 1){
        mainMenu();
    }
    return 0;
}
