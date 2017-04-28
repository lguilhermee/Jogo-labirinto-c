// Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <time.h>


// DEFINIÇÕES
#define TECLA_CIMA 72
#define TECLA_BAIXO 80
#define TECLA_ESQUERDA 75
#define TECLA_DIREITA 77

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
void menuFinal(); // Menu Final



void tamanhoTotalDaTela(){

CONSOLE_SCREEN_BUFFER_INFO bufferConsole;

GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferConsole); // Passamos a variavel bufferConsole para esta função
colunaHorizontal = bufferConsole.srWindow.Right - bufferConsole.srWindow.Left + 1; // Pega tamanho total de linhas na vertical
colunaVertical = bufferConsole.srWindow.Bottom - bufferConsole.srWindow.Top + 1; // Pega tamanho total de linhas horizontal
}


void mudaCor(int nomeCor){

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (nomeCor){
        case 1:
            SetConsoleTextAttribute(console, FOREGROUND_GREEN);
            break;
        case 2:
            SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            break;
        case 3:
            SetConsoleTextAttribute(console, FOREGROUND_RED);
            break;
        case 4:
            SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
        default:
            break;
    }

}


// Com esta função nós conseguimos nos mover pelo console utilizando X e Y

void movePOS(int x, int y, int tipo) {

    COORD coords; // Classe COORD (Windows.h)
    coords.X = x; //Coordenadas X (Horizontal)
    coords.Y = y; //Coordenads Y (Vertical)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coords);

    // 0 - Remove espaços em branco
    // 1 - Move o carrinho
    // 2 - Paredes

    if(tipo == 0) {
        printf("%c", ' '); //Remove espaço em branco
    }
    else if(tipo == 1) {
        mudaCor(1);
        printf("%c", 254); // Move o carrinho
        mudaCor(4);
    }
        else if(tipo == 2) {
        mudaCor(3);
        printf("%c", 169); // Objetivo no mapa
        mudaCor(4);
    }
    else
        printf("%c", 219); //  Paredes

}

void IniciaNovoJogo() {
    x = 0;
    y = 0;
    antigoX = 0;
    antigoY = 0;

    system("cls");
    geraMapa();
    moveChar();
    movePOS(0,0,0); //Voltando para posição inicial
    system("pause");
}


void menuInicial () {

    int opcaoSelecionada = 0;
    mudaCor(1);
    printf("\n\n\n\t\t\t\t\t _           _     _      _       _        \n"
                   "\t\t\t\t\t| |         | |   (_)    (_)     | |       \n"
                   "\t\t\t\t\t| |     __ _| |__  _ _ __ _ _ __ | |_ ___  \n"
                   "\t\t\t\t\t| |    / _` | '_ \| | '__| | '_ \| __/ _ \ \n"
                   "\t\t\t\t\t| |___| (_| | |_) | | |  | | | | | || (_) |\n"
                   "\t\t\t\t\t|______\__,_|_.__/|_|_|  |_|_| |_|\__\___/ \n\n\n\n\n");


    mudaCor(4);
    printf("\t\t\t\t\t\t MENU DE OPCOES\n\n");
    printf("\t\t\t\t\t\t1 - Iniciar jogo\n");
    printf("\t\t\t\t\t\t2 - Exibir recoords\n");
    printf("\t\t\t\t\t\t3 - Sair\n");
    movePOS(119,29,0);
    printf("DESENVOLVEDORES: Davi. L, Emerson, Gabriel. C, Jorge. L, Juan. P, Lucas. C, Lucas. G, Lucas. R, Mariana. F, Vinicius. G");

    switch(opcaoSelecionada  = getch()){
        case 49: {
            IniciaNovoJogo();
            break;
        }
        case 50: {
            break;
        }
        case 51: {
            exit(0);
            break;

        }
        default:{
            system("cls");
            menuInicial();
            break;
        }
    }

}

int existeNoMapa(int testeX, int testeY) {

    if(testeX == posXY[50][0] && testeY == posXY [50][1]) {
        system("cls");
        printf("VOCE GANHOU MODA FOCKERRRRRRR");
        return 1;
    }


    for (int i = 0; i < 120; ++i) {

        if(testeX == posXY[i][0])
            for (int j = 0; j < 120; ++j) {
                if(testeY == posXY[i][1]){
                    system("cls");
                    menuFinal();
                    return 0;
                }
            }
    }

    return 2;
   
}


void moveChar() {

    int numMovimento = 0;



    while (existeNoMapa(x,y) == 2) {

        switch (numMovimento = getch()) {

            case TECLA_CIMA:
                movePOS(x, y - 1, 1); //Move um para cima

                antigoX = x;
                antigoY = y;
                existeNoMapa(antigoX,antigoY);
                movePOS(antigoX, antigoY, 0); // Limpa localização anterior
                y -= 1;

                break;
            case TECLA_BAIXO:
                movePOS(x, y + 1, 1); // Move um para baixo

                antigoX = x;
                antigoY = y;
                existeNoMapa(antigoX,antigoY);
                movePOS(antigoX, antigoY, 0); // Limpa localização anterior
                y += 1;

                break;
            case TECLA_ESQUERDA:
                movePOS(x - 1, y, 1); // Move um para esquerda

                antigoX = x;
                antigoY = y;
                existeNoMapa(antigoX,antigoY);
                movePOS(antigoX, antigoY, 0); // Limpa localização anterior
                x -= 1;

                break;
            case TECLA_DIREITA:
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
                posXY[i][j] = rand() %  20;
            }
        }
    }


    for (int k = 0; k < 120; ++k) {

        if(k==50)
            movePOS(posXY[k][0],posXY[k][1],2);
        else
            movePOS(posXY[k][0],posXY[k][1],3);

    }

}

void menuFinal() {

    int opcaoSelecionada;

    movePOS(0,3,0);
    mudaCor(3);
    printf("\t\t\t  ______        ______  _______     _____  _    _ _______ ______  \n"
                   "\t\t\t / _____)  /\\  |  ___ \\(_______)   / ___ \\| |  | (_______|_____ \\ \n"
                   "\t\t\t| /  ___  /  \\ | | _ | |_____     | |   | | |  | |_____   _____) )\n"
                   "\t\t\t| | (___)/ /\\ \\| || || |  ___)    | |   | |\\ \\/ /|  ___) (_____ ( \n"
                   "\t\t\t| \\____/| |__| | || || | |_____   | |___| | \\  / | |_____      | |\n"
                   "\t\t\t \\_____/|______|_||_||_|_______)   \\_____/   \\/  |_______)     |_|\n\n\n");


    mudaCor(4);
    printf("\t\t\t\t\t   MENU DE OPCOES\n\n");
    printf("\t\t\t\t\t1 - Jogar novamente\n");
    printf("\t\t\t\t\t2 - Recordes\n");
    printf("\t\t\t\t\t3 - Sair\n");


    switch (opcaoSelecionada = getch()){
        case 49:
            IniciaNovoJogo();
            break;
        case 50:
            // Chama função de recodes
            break;
        case 51:
            exit(0);
            break;
        default:
            break;
    }

}

void Recorde() {


}

int main() {

    srand(time(NULL));
    //tamanhoTotalDaTela();
    menuInicial();

    system("pause");
}


