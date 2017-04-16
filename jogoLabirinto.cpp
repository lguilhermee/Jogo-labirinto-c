#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

int x, y, antigoX, antigoY; // PRECISAMOS DO ANTIGO X E Y PARA APAGAR NOSSO RASTRO ANTERIOR
int colunaVertical, colunaHorizontal; // Variaveis que guardam o tamanho total do console
int nivel = 110;
int posXY[120][2];

// Funções declaradas lá embaixo.
void geraMapa();
void moveChar();


// Com esta função é possível pegar o tamanho total das tela. Os valores da Coluna estão nas variaveis globais acima.
void tamanhoTotalDaTela(){

CONSOLE_SCREEN_BUFFER_INFO bufferConsole;

GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferConsole); // Passamos a variavel bufferConsole para esta função
colunaHorizontal = bufferConsole.srWindow.Right - bufferConsole.srWindow.Left + 1; // Pega tamanho total de linhas na vertical
colunaVertical = bufferConsole.srWindow.Bottom - bufferConsole.srWindow.Top + 1; // Pega tamanho total de linhas horizontal
}


// Com esta função nós conseguimos nos mover pelo console utilizando X e Y
void movePOS(int x, int y, int eraseOrPrint) {


    COORD coords; // Classe COORD (Windows.h)
    coords.X = x; //Coordenadas X (Horizontal)
    coords.Y = y; //Coordenads Y (Vertical)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coords);

    // 1 - Adicionar
    // 0 - Apagar

    if(eraseOrPrint == 0) {
        printf("%c", ' ');
    }
    else if(eraseOrPrint == 1) {
        printf("%c", 219); //Printa um quadrado na determinada posição do console.
    }

}


void menuInicial () {


    int opcaoSelecionada = 0;
    printf(" _           _     _      _       _        \n"
                   "| |         | |   (_)    (_)     | |       \n"
                   "| |     __ _| |__  _ _ __ _ _ __ | |_ ___  \n"
                   "| |    / _` | '_ \| | '__| | '_ \| __/ _ \ \n"
                   "| |___| (_| | |_) | | |  | | | | | || (_) |\n"
                   "|______\__,_|_.__/|_|_|  |_|_| |_|\__\___/ \n");


    printf("1 - Iniciar jogo\n");
    printf("2 - Exibir recoords\n");
    printf("3 - Sair\n");

    printf("\nDigite uma opção: ");
    scanf("%d", &opcaoSelecionada);

    switch(opcaoSelecionada){
        case 1: {
            x = 0;
            y = 0;
            antigoX = 0;
            antigoY = 0;


            system("cls");
            geraMapa();
            moveChar();
            movePOS(0,0,0); //Voltando para posição inicial
            system("pause");
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;

        }
        default:{
            break;
        }
    }

}


void moveChar() {

    int numMovimento = getch();

    while (numMovimento != '22472') {

        fseek(stdin,0,SEEK_END);

    switch(numMovimento){

        case 22472:
            movePOS(x,y-1,1); //Move um para cima

            antigoX = x;
            antigoY = y;
            movePOS(antigoX,antigoY,0); // Limpa localização anterior
            y -= 1;

            break;
        case 22480:
            movePOS(x,y+1,1); // Move um para baixo

            antigoX = x;
            antigoY = y;
            movePOS(antigoX,antigoY,0); // Limpa localização anterior
            y+=1;

            break;
        case 22475:
            movePOS(x-1,y,1); // Move um para esquerda

            antigoX = x;
            antigoY = y;
            movePOS(antigoX,antigoY,0); // Limpa localização anterior
            x-=1;

            break;
        case 22477:
            movePOS(x+1,y,1); // Move um para direita

            antigoX = x;
            antigoY = y;
            movePOS(antigoX,antigoY,0); // Limpa localização anterior
            x+=1;

            break;
        default:
            break;
    }
    }
}


void geraMapa() {

    for (int i = 0; i < 120; ++i) {

        for (int j = 0; j < 2; ++j) {

            if(j==0) {
                posXY[i][j] = rand() % 120;
            }
            else if(j==1) {
                posXY[i][j] = rand() % 30;
            }
        }
    }


    for (int k = 0; k < 120; ++k) {

        movePOS(posXY[k][0],posXY[k][1],1);
    }

}

char menuFinal() {

    /*MENU FINAL DEVE CONTER AS SEGUINTES INFORMAÇÕES
     * - IMAGEM DE GAME OVER EM ASCII
     * - JOGADOR NOVAMENTE
     * - VOLTAR AO MENU PRINCIPAL
     * - SAIR DO JOGO
     * */

    // O MENU DEVE RETORNAR UM CHAR OU UM INTEIRO

    return 'a';
}

int main() {

    tamanhoTotalDaTela();
    menuInicial();

    system("pause");
}


