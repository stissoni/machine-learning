#include <stdio.h>
#include <stdio_ext.h>

const int JUGADOR = -1;
const int COMPUTADORA = 1;
const int CASILLERO_VACIO = 0;
const int EMPATE = 0;
const int TAMANIO_TABLERO = 9;
const char CRUZ = 'X';
const char CERO = 'O';
const char CARACTER_VACIO = ' ';
const int INFINITO = 999;

void imprimir_tablero(int tablero[TAMANIO_TABLERO], int jugador_inicial);
void jugar_partida(int tablero[TAMANIO_TABLERO]);

int main() {
    char continuar_partida = 'n';
    do{ 
        int tablero[9] = {0,0,0,0,0,0,0,0,0};
        printf("\nJuguemos TIC-TAC-TOE!\n\n");
        imprimir_tablero(tablero, 1);  
        jugar_partida(tablero);
        printf("Jugar nuevamente? (S/n): ");
        __fpurge(stdin);
        scanf("%c", &continuar_partida);
    } while (continuar_partida == 'S');

    return 0;
}