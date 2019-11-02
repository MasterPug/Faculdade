#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
/*-
 -
 --Ruan de Almeida
 --Trabalho de Estrutura de dados
 -
 -*/

struct Lista
{
  int info;
  struct Lista *prox;
};

lista Inicializar(lista a)
{
    a = NULL;
    return a;
}

int Vazia(lista a)
{
    if(a == NULL);
}

lista InserirPilha(lista a, int x)
{
    int h=0;
    if(Cheia(a))
        return a;

    else
    {
      lista aux = a;
      a = (lista*)malloc(sizeof(lista));
      a->info = x;
        a->prox = aux;
    }
}

lista InserirFila(lista a, int x)
{
    int h=0;
    if(Cheia(a)){
        return a;
    }
    else
    {
        if(!Vazia(a))
        {
            a = (lista*)malloc(sizeof(lista));
            a->info = x;
            a->prox = NULL;
        }
        else
        {
            a->prox = InserirFila(a->prox, x);
        }
    }
}

lista Remover(lista a)
{

    if(Vazia(a)){
        lista aux;
        aux = a;
        a = a->prox;
        printf("Voce acabou de excluir o numero: %d", aux->info);
        free(aux);
    }
    return a;
}

int Cheia(lista a)
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

int conta(lista a)
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

void Imprime(lista a)
{
    if(!Vazia(a)){
    }
    else{
        printf("%d ", a->info);
        Imprime(a->prox);
    }
}

void Destruir(lista a)
{
    if(!Vazia(a)){
        while(a == NULL){
            lista aux = a;
            a = a->prox;
            free(aux);
        }
    }
}
