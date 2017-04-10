#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

int x, y, antigoX, antigoY; // PRECISAMOS DO ANTIGO X E Y PARA APAGAR NOSSO RASTRO ANTERIOR
int colunaVertical, colunaHorizontal; // Variaveis que guardam o tamanho total do console


// Com esta função é possível pegar o tamanho total das tela. Os valores da Coluna estão nas variaveis globais acima.
void tamanhoTotalDaTela(){

CONSOLE_SCREEN_BUFFER_INFO bufferConsole;

GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferConsole); // Passamos a variavel bufferConsole para esta função
colunaVertical = bufferConsole.srWindow.Right - bufferConsole.srWindow.Left + 1; // Pega tamanho total de linhas na vertical
colunaHorizontal = bufferConsole.srWindow.Bottom - bufferConsole.srWindow.Top + 1; // Pega tamanho total de linhas horizontal
}


// Com esta função nós conseguimos nos mover pelo console utilizando X e Y
void movePOS(int x, int y) {

    COORD coords; // Classe COORD (Windows.h)
    coords.X = x; //Coordenadas X (Horizontal)
    coords.Y = y; //Coordenads Y (Vertical)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coords);
    printf("%c", 254); //Printa um quadrado na determinada posição do console.

}



int menuInicial () {

    /*MENU DEVE CONTER AS SEGUINTER INFORMAÇÕES
     * - IMAGEM DE APRESENTAÇÃO EM ASCII
     * - NOMES DOS DESENVOLVEDORES
     * - VERSÃO DO JOGO
     * - MENU DE OPÇÕES [ INICIAR JOGO, MOSTRAR RECORDE, SAIR DO JOGO ]
    */

    //Está função deverá retornar um int ou um char

    return 1;
}

void mapa() {
    tamanhoTotalDaTela();

    for(int i = 0; i<500; i++) {

        for(int k = 0; k<500; k++) {

            movePOS(rand() % colunaVertical,rand() % colunaHorizontal);
        }
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

    /*EXEMPLO DE COORDENADAS
     * O SEGUINTE CÓDIGO ABAIXO COLETA O TAMANHO DO CONSOLE ATRAVÉS
     * DA FUNÇÃO tamanhoTotalTabela(); E LOGO APÓS COM A FUNÇÃO
     * movePOS(y,x) NÓS NOS MOVEMOS PARA O MEIO DA TELA
     * UTILIZANDO AS VARIAVEIS GLOBAIS COM O TAMANHO DO CONSOLE
     * GERADO PELA FUNÇÃO tamanhoTotalTabela() ANTERIORMENTE.
     */

    mapa();

    system("pause");
}


