#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "pilha.h"
/*-
 -
 --Ruan de Almeida
 --Trabalho de Estrutura de dados
 -
 -*/

lista InicializarP(lista a){
  a = Inicializar(a);
}

lista InserirP(lista a, int x){
  a = InserirPilha(a, x);
}

lista RemoverP(lista a){
  a = Remover(a);
}

void ImprimeP(lista a){
  Imprime(a);
}

lista DestruirP(lista a){
  Destruir(a);
}

int menu()
{
    int op;

    printf("\nMenu de opcoes:\n");
    printf("(1) Inserir um novo numero na pilha.\n");
    printf("(2) Remover da pilha.\n");
    printf("(3) Imprimir.\n");
    printf("(4) Sair.\n\n");

    scanf("%d", &op);
    fflush(stdin);

    return op;
}
