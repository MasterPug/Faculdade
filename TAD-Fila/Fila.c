#include <stdlib.h>
#include <stdio.h>
#include "fila.h"


struct Fila{
    int info;
    struct Fila *prox;
};

int Vazia(fila a)
{
    if(a == NULL);
}

fila Inicializar(fila a)
{
    a = NULL;
    return a;
}

void Destruir(fila a)
{
    if(!Vazia(a)){
        while(a == NULL){
            fila aux = a;
            a = a->prox;
            free(aux);
            printf("Lista destruida\n");
        }
    }
}

fila Inserir(fila a, int x)
{
    int h=0;
    if(Cheia(a)){
        return a;
    }
    else
    {
        if(!Vazia(a))
        {
            a = (fila*)malloc(sizeof(fila));
            a->info = x;
            a->prox = NULL;
        }
        else
        {
            a->prox = Inserir(a->prox, x);
        }
    }
}

int Cheia(fila a)
{
    int h;
    h = conta(a);
    if(h == 5)
    {
        printf(" A fila esta cheia");
        return 1;
    }
    else
        return 0;
}

int conta(fila a)
{
        int he=0;
        if(!Vazia(a))
            return 0;

        else
        {
            he = 1+ conta(a->prox);
        }
    return he;
}

fila Remover(fila a)
{

    if(Vazia(a)){
        fila aux;
        aux = a;
        a = a->prox;
        printf("Voce acabou de excluir o numero: %d", aux->info);
        free(aux);
    }
    return a;
}

void Imprime(fila a)
{
    if(!Vazia(a)){
    }
    else{
        printf("%d ", a->info);
        Imprime(a->prox);
    }
}

int menu()
{
    int op;

    printf("\nMenu de opcoes:\n");
    printf("(1) Inserir um novo numero na fila.\n");
    printf("(2) Remover da fila.\n");
    printf("(3) Imprimir.\n");
    printf("(4) Sair.\n\n");

    scanf("%d", &op);
    fflush(stdin);

    return op;


}
