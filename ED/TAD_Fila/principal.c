#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "fila.h"
/*-
 -
 --Ruan de Almeida
 --Trabalho de Estrutura de dados
 -
 -*/

int main(){
    fila a;
    int x, control = 0;
    a = Inicializar(a);
    while(control != 5){
        Sleep(3500);
        system("cls");
        int opcao = menu();
        switch(opcao){
        case 1:
            printf("Numero a inserir:\n");
            scanf("%d", &x);
            a = Inserir(a, x);
            break;
        case 2:
            a = Remover(a);
            break;
        case 3:
            Imprime(a);
            break;
        case 4:
            Destruir(a);
            control = 5;
            break;
        }
    }
}
