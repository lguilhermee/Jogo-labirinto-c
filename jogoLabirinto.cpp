#include <stdlib.h>
#include <stdio.h>
#include <windows.h>


int x,y, oldX, oldY; // Variaveis que serão utilizadas depois.

// Imprime na tela em determinado X localização
void movePOS(int x, int y) {

    COORD coords; // Classe COORD (Windows.h)
    coords.X = x; //Coordenadas X (Horizontal)
    coords.Y = y; //Coordenads Y (Vertical)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coords);
}


//Função principal
int main() {

    movePOS(40,160);
    printf("x");

    system("pause");
}


