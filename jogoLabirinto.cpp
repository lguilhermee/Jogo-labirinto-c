// Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>


// DEFINIÇÕES
#define TECLA_CIMA 72 // Character para mover para cima.
#define TECLA_BAIXO 80 //Character para mover para baixo.
#define TECLA_ESQUERDA 75 //Character para mover para esquerda
#define TECLA_DIREITA 77 // Character para mover para direita

// VARIAVEIS GLOBAIS

int x,y, antigoX, antigoY; // PRECISAMOS DO ANTIGO X E Y PARA APAGAR NOSSO RASTRO ANTERIOR
int colunaVertical, colunaHorizontal; // Geralmente 120x30
int nivel = 0; // Nível inicial que é incrementado.
int **posXY = (int**) malloc(120*sizeof(int));
int objetivoRandom; // Aqui nós geramos valores aleatórios para o objetivo na tela.
int pontuacao = 0; // Pontuação do jogador
char nomeJogador[50];
FILE *f;

// DECLARAÇÕES DE FUNÇÕES

void geraMapa(); // Gera mapa aleatorio
void moveChar(); // Move-se Pelo mapa
void tamanhoTotalDaTela(); // Captura o tamanho total da tela. (Geralmente 120x30)
void movePOS(int x, int y, int tipo); // Utiliza X e Y para se navegar
void menuInicial(); //Menu Inicial
void menuFinal(); // Menu Final
void Recorde();
void LerRecordes();
void DesenharLogo();


void tamanhoTotalDaTela(){

CONSOLE_SCREEN_BUFFER_INFO bufferConsole;

GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferConsole); // Passamos a variavel bufferConsole para esta função
colunaHorizontal = bufferConsole.srWindow.Right - bufferConsole.srWindow.Left + 1; // Pega tamanho total de linhas na vertical
colunaVertical = bufferConsole.srWindow.Bottom - bufferConsole.srWindow.Top + 1; // Pega tamanho total de linhas horizontal
}


void mudaCor(int nomeCor){

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Criamos uma variavel para manusear o console
    switch (nomeCor){
        case 1:
            SetConsoleTextAttribute(console, FOREGROUND_GREEN); // Verde
            break;
        case 2:
            SetConsoleTextAttribute(console, FOREGROUND_BLUE); // Azul
            break;
        case 3:
            SetConsoleTextAttribute(console, FOREGROUND_RED); // Vermelho
            break;
        case 4:
            SetConsoleTextAttribute(console, FOREGROUND_INTENSITY); // Padrão
        default:
            break;
    }

}


void movePOS(int x, int y, int tipo) {

    COORD coords; // Classe COORD (Windows.h)
    coords.X = x; //Coordenadas X (Horizontal)
    coords.Y = y; //Coordenads Y (Vertical)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coords);

    // 0 - Remove espaços em branco
    // 1 - Move o carrinho
    // 2 - Objetivo no mapa
    // 3 ou outro valor - Paredes

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

    // Iniciamos os valores X e Y iniciais
    x = 0;
    y = 1;
    antigoX = 0;
    antigoY = 0;

    system("cls"); // Limpa tela
    geraMapa();  //Gera o Mapa
    moveChar(); //Se move pelo mapa
    movePOS(x,y,1); //Voltando para posição inicial
}


void menuInicial () {

    int opcaoSelecionada = 0;
    DesenharLogo();
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
            LerRecordes();
            exit(0);
        }
        case 51: {
            exit(0);
        }
        default:{
            system("cls");
            menuInicial();
            break;
        }
    }

}

int existeNoMapa(int testeX, int testeY) {

    // Verifca se colidimos com o objetivo no mapa
    if(testeX == posXY[objetivoRandom][0] && testeY == posXY[objetivoRandom][1]) {
        pontuacao++;
        nivel+=50;
        IniciaNovoJogo();
        return 1;
    }

    // Verificamos se colidimos com uma parede.
    for (int i = 0; i < (nivel+120); ++i) {

        if(testeX == posXY[i][0])
            for (int j = 0; j < (nivel+120); ++j) {
                if(testeY == posXY[i][1]){
                    system("cls");
                    nivel = 0;
                    if(pontuacao > 0)
                    Recorde();
                    menuFinal();
                    return 0;
                }
            }
    }

    return 2;
   
}


// Movimentos nossa posição no mapa
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

    if(nivel != 0)
    posXY = (int**) realloc(posXY,(nivel+120)*sizeof(int)); // Gera mapa proximo nível


    //Gera parede completa encima
    for (int l = 0; l < 120; ++l) {

        movePOS(l,26,3);
    }

    //Gera parede completa embaixo
    for (int l = 0; l < 120; ++l) {

        movePOS(l,0,3);
    }

    movePOS(50,27,0); // Se move abaixo do lugar do jogo
    printf("Pontuacao: %d", pontuacao); // Escreve a pontuação na tela

    objetivoRandom = rand() % (nivel+120); //Gera objetivo em um lugar aleatório no mapa

    for (int i = 0; i < (nivel+120); ++i) {
        posXY[i] = (int*) malloc(1*sizeof(int)); // Criando uma nova matriz

        for (int j = 0; j < 2; ++j) {

            if(j==0) {
                posXY[i][j] = rand() % 120;
            }
            else if(j==1) {
                posXY[i][j] = rand() %  25;
            }
        }
    }

    //Desenha o mapa / Objetivo na tela
    for (int k = 0; k < (nivel+120); ++k) {

        if(k == objetivoRandom)
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
            pontuacao = 0; // Zera a pontuação
            IniciaNovoJogo(); // Inicia um novo jogo
            break;
        case 50:
            printf("Versão Alpha. Ainda não está disponível\n\n");
            break;
        case 51:
            exit(0);
        default:
            break;
    }

}

void LerRecordes() {

    system("cls");
    DesenharLogo();

    mudaCor(1);
    movePOS(45,15,0);
    printf("#_________ RECORDES _________#\n");
    printf("NOME\tPONTUACAO\n");
    mudaCor(4);

    f = fopen("recordes.txt","r");
    if(f== NULL) {
        printf("ERRO arquivo");
        Sleep(5000);
        exit(0);
    }else {
        char c =0;

        while(c != EOF){
            if(c == ':'){
                printf("\n");
            }
            else
                printf("%c", c);
                c = fgetc(f);
        }

        fclose(f);
        printf("\n\n\n\n\n");
        system("Pause");
        system("cls");
        menuInicial();
    }
    
}

void Recorde() {

    f = fopen("recordes.txt","a+");
    if(f == NULL){
        printf("Error arquivo");
    Sleep(3000);
    exit(0);
    }
    else {
        char c = pontuacao+'0';

        fputs(nomeJogador,f);

        fputs(",",f);

        fputc(c,f);

        fputs(":",f);

        fclose(f);
    }
}

void DesenharLogo() {

    mudaCor(1);
    printf("\n\n\n\t\t\t\t\t _           _     _      _       _        \n"
                   "\t\t\t\t\t| |         | |   (_)    (_)     | |       \n"
                   "\t\t\t\t\t| |     __ _| |__  _ _ __ _ _ __ | |_ ___  \n"
                   "\t\t\t\t\t| |    / _` | '_ \| | '__| | '_ \| __/ _ \ \n"
                   "\t\t\t\t\t| |___| (_| | |_) | | |  | | | | | || (_) |\n"
                   "\t\t\t\t\t|______\__,_|_.__/|_|_|  |_|_| |_|\__\___/ \n\n\n\n\n");

    mudaCor(4);
}

void requisitaNomeJogador() {

    DesenharLogo();
    printf("Seu nome: ");
    gets(nomeJogador);
    fflush(stdin);
    system("cls");
}

int main() {

    requisitaNomeJogador();
    srand(time(NULL)); // Faz com que todos os valores Aleatórios possuam um valor unico.
    menuInicial(); // Inicia o Labirinto.
}


