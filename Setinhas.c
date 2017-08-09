#include <stdio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

void menuMotorista(){

    int i;
    int key = 0;
    int tecla = 0;
    int rebobina = 0;
    char vetor[5] = {'>',' ',' ',' ',' '};



    do{
        system("cls");
        printf("Escolha uma das opcoes a seguir e aperte Enter para confirmar.\n");
        for(i=rebobina; i<5; i++){
            if(key == KEY_DOWN){
                if(vetor[i+1] == ' '){
                    vetor[i]=' ';
                    vetor[i+1]='>';
                    rebobina++;
                    break;
                }
            }
            if(key == KEY_UP){
                if(vetor[i-1] == ' ' && rebobina > 0){
                    vetor[i] = ' ';
                    vetor[i-1] = '>';
                    rebobina--;
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
                    break;
                }
            }
        }

        switch(tecla)
        {
            case 1:
                system("cls");
                printf("Listar");
                break;

            case 2:
                printf("Adicionar");
                break;

            case 3:
                printf("Alterar");
                break;

            case 4:
                printf("Remover");
                break;

            case 5:
                printf("Voltar");
                break;
        }
        tecla=0;
    }while(1);
}


int main()
{
    menuMotorista();
    return 0;
}


