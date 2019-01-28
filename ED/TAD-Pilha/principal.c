#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "pilha.h"

int main(){
    lista a;
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
            a = InserirP(a, x);
            break;
        case 2:
            a = RemoverP(a);
            break;
        case 3:
            ImprimeP(a);
            break;
        case 4:
            DestruirP(a);
            control = 5;
            break;
        }
    }
}
