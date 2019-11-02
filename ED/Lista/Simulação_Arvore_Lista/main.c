#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
/*-
 -
 --Ruan de Almeida
 --Trabalho para simular árvore avl com TAD
 -
 -*/

typedef struct Lista
{
    int info;
	struct Lista* prox;
} lista ;

lista * lst_inserirFim(lista *l, int v);
lista * lst_excluirNo(lista* l, int v);
int lst_altera(lista *l, int v, int n);
int lst_existe(lista *l, int v);
int lst_conta(lista *l, int v);
int soma(lista *l);
void lst_libera(lista* l);
int lst_vazia(lista* l);




int main()
{
    int num=0, opcao, novo, cont;
    lista* l = NULL;

   while(opcao != 7)
    {
        printf("Trabalho de Lista encadeada recursiva \n\n");
        printf("1-Inserir um elemento na Lista\n");
        printf("2-Remover um elemento da lista\n");
        printf("3-Alterar um elemento da lista\n");
        printf("4-Verificar se um elemento existe na lista\n");
        printf("5-Contar o número de elementos superiores a um valor\n");
        printf("6-Somar todos os elementos da lista\n");
        printf("7-Sair\n");
        scanf("%d \n", &opcao);

		switch(opcao)
        {
        case 1:
            scanf("%d ", &num);
            l = lst_inserirFim(l, num);
            break;

        case 2:
            scanf("%d ", &num);
            l = lst_excluirNo(l, num);
            break;

        case 3:
            scanf("%d %d ", &num, &novo);
			if(lst_altera(l, num, novo))
				printf("Alterado");
            else
                printf("Não existe na lista");

            break;

        case 4:
            scanf("%d ", &num);
            if(lst_existe(l, num)){
                printf("Existe o elemento na lista");
            }
            else{
                printf("Não existe o elemento na lista");
            }
            break;

        case 5:
            scanf("%d ", &num);
            if(lst_existe(l, num))
            {
                cont = lst_conta(l, num);
                printf("Existe %d elementos na lista \n", cont);
            }
            else
                printf("Não existe esse elemento na lista");
            break;

       case 6:
          int soma(l);
          printf("Somado os valores");
          break;

        case 7:
            lst_libera(l);
            printf("Lista Destruida");
            continue;
        }
    }
}



int lst_vazia(lista* l)
{
    if(l == NULL);
}
lista * lst_excluirNo(lista* l, int v)
{
    if(!lst_vazia(l))

    if(l->info == v)
    {
        lista* t = l;
        l = l->prox;
        free(t);
    }
    else
        l->prox = lst_excluirNo(l->prox, v);


    return l;
}
int lst_existe(lista* l, int v)
{
    if(!lst_vazia(l))

    if(l->info == v)
		return 1;
    else
        l->prox = lst_existe(l->prox, v);


}
lista * lst_inserirFim(lista* l, int v)
{

    if(lst_vazia(l))
    {
        l = (lista*)malloc(sizeof(lista));
        l->info = v;
        l->prox = NULL;
        return l;
    }
    else
    {
        l->prox = lst_inserirFim(l->prox, v);
        return l;
    }
}
int lst_conta(lista* l, int x)
{
    if(!lst_vazia(l))
        return 0;

    else
    {
        if(l->info > x)
        {
            return 1+ lst_conta(l->prox, x);
        }

        else
        {
            return lst_conta(l->prox, x);
        }
    }
}
int lst_altera(lista* l, int v, int n)
{
    if(!lst_vazia(l))

    if(l->info == v)
    {
        l->info = n;
    }
    else
        l->prox = lst_altera(l->prox, v);

}
void lst_libera(lista* l)
{
    if(!lst_vazia(l))
    {
        lst_libera(l->prox);
        free(l);
    }
}
int soma(lista* l)
{
    if(lst_vazia(l))
        return 0;
    else
    {
        return l->info + somar(l->prox);
    }
}
