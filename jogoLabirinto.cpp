// Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>


//setlocale(LC_ALL, "Portuguese"); No idea why is not working.

// DEFINIÇÕES
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// VARIAVEIS GLOBAIS

int x, y, antigoX, antigoY; // PRECISAMOS DO ANTIGO X E Y PARA APAGAR NOSSO RASTRO ANTERIOR
int colunaVertical, colunaHorizontal; // Geralmente 120x30
int nivel = 110;
int posXY[120][2]; // Guarda o total de objetos na tela (Paredes)


// DECLARAÇÕES DE FUNÇÕES

void geraMapa(); // Gera mapa aleatorio
void moveChar(); // Move-se Pelo mapa
void tamanhoTotalDaTela(); // Captura o tamanho total da tela. (Geralmente 120x30)
void movePOS(int x, int y, int tipo); // Utiliza X e Y para se navegar
void menuInicial(); //Menu Inicial
int menuFinal(); // Menu Final



void tamanhoTotalDaTela(){

CONSOLE_SCREEN_BUFFER_INFO bufferConsole;

GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferConsole); // Passamos a variavel bufferConsole para esta função
colunaHorizontal = bufferConsole.srWindow.Right - bufferConsole.srWindow.Left + 1; // Pega tamanho total de linhas na vertical
colunaVertical = bufferConsole.srWindow.Bottom - bufferConsole.srWindow.Top + 1; // Pega tamanho total de linhas horizontal
}


// Com esta função nós conseguimos nos mover pelo console utilizando X e Y
void movePOS(int x, int y, int tipo) {


    COORD coords; // Classe COORD (Windows.h)
    coords.X = x; //Coordenadas X (Horizontal)
    coords.Y = y; //Coordenads Y (Vertical)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coords);

    // 1 - Adicionar
    // 0 - Apagar

    if(tipo == 0) {
        printf("%c", ' '); //Remove espaço em branco
    }
    else if(tipo == 1) {
        printf("%c", 248); // Move o carrinho
    }
    else
        printf("%c", 219); //  Paredes

}


void menuInicial () {

    int opcaoSelecionada = 0;
    printf("\n\n\n\t\t\t\t\t _           _     _      _       _        \n"
                   "\t\t\t\t\t| |         | |   (_)    (_)     | |       \n"
                   "\t\t\t\t\t| |     __ _| |__  _ _ __ _ _ __ | |_ ___  \n"
                   "\t\t\t\t\t| |    / _` | '_ \| | '__| | '_ \| __/ _ \ \n"
                   "\t\t\t\t\t| |___| (_| | |_) | | |  | | | | | || (_) |\n"
                   "\t\t\t\t\t|______\__,_|_.__/|_|_|  |_|_| |_|\__\___/ \n\n\n");


    printf("\t\t\t\t\t MENU DE OPCOES\n");
    printf("\t\t\t\t\t1 - Iniciar jogo\n");
    printf("\t\t\t\t\t2 - Exibir recoords\n");
    printf("\t\t\t\t\t3 - Sair\n");

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
            system("exit");
            break;

        }
        default:{
            system("cls");
            menuInicial();
            break;
        }
    }

}

bool existeNoMapa(int testeX, int testeY) {

    for (int i = 0; i < 120; ++i) {

        if(testeX == posXY[i][0])
            for (int j = 0; j < 120; ++j) {
                if(testeY == posXY[i][1]){
                    system("cls");
                    menuFinal();
                    break;
                }
            }
    }
   
}


void moveChar() {

    int numMovimento = 0;

    existeNoMapa(x,y);

    while (true) {


        switch (numMovimento = getch()) {

            case KEY_UP:
                movePOS(x, y - 1, 1); //Move um para cima

                antigoX = x;
                antigoY = y;
                existeNoMapa(antigoX,antigoY);
                movePOS(antigoX, antigoY, 0); // Limpa localização anterior
                y -= 1;

                break;
            case KEY_DOWN:
                movePOS(x, y + 1, 1); // Move um para baixo

                antigoX = x;
                antigoY = y;
                existeNoMapa(antigoX,antigoY);
                movePOS(antigoX, antigoY, 0); // Limpa localização anterior
                y += 1;

                break;
            case KEY_LEFT:
                movePOS(x - 1, y, 1); // Move um para esquerda

                antigoX = x;
                antigoY = y;
                existeNoMapa(antigoX,antigoY);
                movePOS(antigoX, antigoY, 0); // Limpa localização anterior
                x -= 1;

                break;
            case KEY_RIGHT:
                movePOS(x + 1, y, 1); // Move um para direita

                antigoX = x;
                antigoY = y;
                existeNoMapa(antigoX,antigoY);
                movePOS(antigoX, antigoY, 0); // Limpa localização anterior
                x += 1;

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

        movePOS(posXY[k][0],posXY[k][1],3);
    }

}

int menuFinal() {

    int opcaoSelecionada;

    printf("  ______        ______  _______     _____  _    _ _______ ______  \n"
                   " / _____)  /\\  |  ___ \\(_______)   / ___ \\| |  | (_______|_____ \\ \n"
                   "| /  ___  /  \\ | | _ | |_____     | |   | | |  | |_____   _____) )\n"
                   "| | (___)/ /\\ \\| || || |  ___)    | |   | |\\ \\/ /|  ___) (_____ ( \n"
                   "| \\____/| |__| | || || | |_____   | |___| | \\  / | |_____      | |\n"
                   " \\_____/|______|_||_||_|_______)   \\_____/   \\/  |_______)     |_|\n"
                   "                                                                  ");

    printf("MENU DE OPÇÕES");
    printf("1 - Jogar novamente\n");
    printf("2 - Recordes\n");
    printf("3 - Sair\n");

    scanf("%d", &opcaoSelecionada);

    switch (opcaoSelecionada){
        case 1:
            // Chama função inicia o jogo
            break;
        case 2:
            // Chama função de recodes
            break;
        case 3:
            // Chama função de sair
            break;
        default:
            printf("\nVocê digitou incorretamente");
    }

}

void Recorde() {


}

int main() {

    tamanhoTotalDaTela();
    menuInicial();

    system("pause");
}


