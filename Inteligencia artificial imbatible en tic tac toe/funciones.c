#include <stdio.h>
#include <stdbool.h>
#include "constantes.h"

char imprimir_jugada(int i, int jugador_inicial) {
    if (jugador_inicial == COMPUTADORA){
        if (i == COMPUTADORA)  
            return CRUZ;
        if (i == JUGADOR)
            return CERO;
        else
            return CARACTER_VACIO;
    }
    if (jugador_inicial == JUGADOR){
        if (i == JUGADOR)
            return CRUZ;
        if (i == COMPUTADORA)  
            return CERO;
        else
            return CARACTER_VACIO;
    }
}

void imprimir_tablero(int tablero[9], int jugador_inicial) {
        printf(" %c | %c | %c\n",imprimir_jugada(tablero[0], jugador_inicial),imprimir_jugada(tablero[1], jugador_inicial),imprimir_jugada(tablero[2], jugador_inicial));
        printf("---+---+---\n");
        printf(" %c | %c | %c\n",imprimir_jugada(tablero[3], jugador_inicial),imprimir_jugada(tablero[4], jugador_inicial),imprimir_jugada(tablero[5], jugador_inicial));
        printf("---+---+---\n");
        printf(" %c | %c | %c\n",imprimir_jugada(tablero[6], jugador_inicial),imprimir_jugada(tablero[7], jugador_inicial),imprimir_jugada(tablero[8], jugador_inicial));
}

int verificar_ganador(int tablero[TAMANIO_TABLERO]) {
    int combinaciones_ganadoras[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if (tablero[combinaciones_ganadoras[i][0]] != 0 && tablero[combinaciones_ganadoras[i][0]] == tablero[combinaciones_ganadoras[i][1]] && tablero[combinaciones_ganadoras[i][0]] == tablero[combinaciones_ganadoras[i][2]]){
            return tablero[combinaciones_ganadoras[i][2]];
        }
    }
    return EMPATE;
}

int minimax(int tablero[TAMANIO_TABLERO], int jugador) {
    bool encontro_movimiento = false;
    int score = -INFINITO;
    int i;

    int winner = verificar_ganador(tablero);
    if(winner != EMPATE) 
        return winner * jugador;

    for (i = 0; i < 9; i++) {
        if(tablero[i] == CASILLERO_VACIO) {
            tablero[i] = jugador;
            int minimax_score = -minimax(tablero, -jugador);
            if(minimax_score > score) {
                score = minimax_score;
                encontro_movimiento = true;
            }
            tablero[i] = CASILLERO_VACIO;
        }
    }
    if (encontro_movimiento == false){
        return 0;
    }
    else{
        return score;
    }
}

void movimiento_computadora(int tablero[TAMANIO_TABLERO]) {
    int movimiento;
    int mejor_score = -INFINITO;
    int i;
    for(i = 0; i < TAMANIO_TABLERO; ++i) {
        if (tablero[i] == CASILLERO_VACIO){
            tablero[i] = COMPUTADORA;
            int score = -minimax(tablero, JUGADOR);
            if (score > mejor_score){
                mejor_score = score;
                movimiento = i;
            }
            tablero[i] = CASILLERO_VACIO;
        }
    }
    tablero[movimiento] = COMPUTADORA;
}

void movimiento_jugador(int tablero[TAMANIO_TABLERO]) {
    int movimiento = 0;
    do {
        printf("\nIngrese su jugada (1-9): ");
        scanf("%i", &movimiento);
    } while (((movimiento - 1) >= TAMANIO_TABLERO || (movimiento - 1) < 0) || (tablero[(movimiento -1)] != CASILLERO_VACIO));
    
    tablero[(movimiento - 1)] = JUGADOR;
}

void jugar_partida(int tablero[TAMANIO_TABLERO]){
    int turno_global;
    int turno_jugador;
    int jugador_inicial;
    printf("\nQuieres ir pimero o segundo?: ");
    scanf("%i", &turno_jugador);
    while (turno_jugador != 1 && turno_jugador != 2){
        printf("\nQuieres ir pimero o segundo?: ");
        scanf("%i", &turno_jugador);
    }

    if (turno_jugador == 2){
        printf("\nLA COMPUTADORA EMPIEZA.\n\n");
        jugador_inicial = COMPUTADORA;
    }
    else {
        printf("\nEMPIEZAS!\n\n");
        jugador_inicial = JUGADOR;
    }
    
    for(turno_global = 0; turno_global < 9 && verificar_ganador(tablero) == EMPATE; turno_global++) {
        if (turno_jugador % 2 == 0){
            movimiento_computadora(tablero);
            turno_jugador++;
        }
        else {
            imprimir_tablero(tablero, jugador_inicial);
            movimiento_jugador(tablero);
            turno_jugador++;
            printf("\n");
        }
    }
    if (verificar_ganador(tablero) == COMPUTADORA){
        imprimir_tablero(tablero, jugador_inicial);
        printf("\nHas perdido!\n\n");
    }
    if (verificar_ganador(tablero) == CASILLERO_VACIO){
        imprimir_tablero(tablero, jugador_inicial);
        printf("\nHan empatado\n\n");
    }
}
