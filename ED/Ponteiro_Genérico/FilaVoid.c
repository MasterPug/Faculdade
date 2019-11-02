#include "FilaVoid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Fila, primeiro a entrar primeiro a sair

//por ser do tipo void, devemos fazaer apontar para um ponteiro q tem alguma coisa
typedef struct listaV
{
    int id; // vai ser muito usado para apnntae
    void* info;   // vai ser qualquer coisa
    struct listaV* prox;
} ListaV;
struct filaV
{
    ListaV* ini;
    ListaV* fim;
};
FilaV IncializaV()
{
    FilaV p=(FilaV)malloc(sizeof(struct filaV)) ;
    p->ini=NULL;
    p->fim=NULL;
    return p;
}
void PushV(FilaV p,void* x,int id)
{ //inserir no inicio
    ListaV* no=(ListaV*)malloc(sizeof(ListaV));
    no->id = id;
    no->info=x;
    no->prox=NULL;
    if(p->fim!=NULL)// lista nao vazia
    {
        p->fim->prox= no;

    }else
    {
      p->ini=no;
    }
    p->fim=no;
}
int PopV (FilaV p)
{ // remover no fim
    int r;    // aqui deve ser inteiro, nao? é removido pelo cpf
    ListaV* a;
    a=p->ini;
    r=a->id;
    p->ini=a->prox;
    if(p->ini==NULL)
     {
       p->fim=NULL;
     }
    free(a);
    return r;
}
void DestruirV(FilaV p)
{
    ListaV *no =p->ini;
    while(no!=NULL)
    {
         ListaV *t=no->prox;
         free(no);
         no=t;
    }
    free(p);
}
int VaziaV (FilaV p)
{
    if(p == NULL || p->ini == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int CheiaV(FilaV p){
    return 0;
}
