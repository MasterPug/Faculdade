#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "avl.h"
int hMudou = 0;


struct arvore{
int info, Fb;
struct arvore *esq,*dir;
};

AVL inicializar(AVL a)
{
    a = NULL;
    return a;
}

AVL atribuir(FILE *dados, AVL a)
{
    int num;
    char c;

    fscanf(dados, "%c", &c);
    fscanf(dados, "%d", &num);

        if(num == -1)
        {
            a=NULL;
        }
        else
        {
            a=(AVL *) malloc(sizeof(AVL));
            a->info = num;
            a->esq = atribuir(dados, a->esq);
            a->dir = atribuir(dados, a->dir);
        }

    fscanf(dados, "%c", &c);
    return a;

}

AVL Ler(AVL a)
{
    FILE *dados;
    char arq[31]="";

    printf("\nDigite o nome do arquivo:\n");
    scanf("%s", arq);

    strcat(arq, ".txt");

    dados = fopen(arq, "rt");
    if(dados != NULL)
        a = atribuir(dados, a);
    fclose(dados);
    calculaFb(a);
    return a;
}

int menu()
{
    int op;

    printf("\nMenu de opcoes:\n");
    printf("(1) Ler a arvore de um arquivo.\n");
    printf("(2) Inserir um novo no.\n");
    printf("(3) Remover da arvore.\n");
    printf("(4) Imprimir em largura.\n");
    printf("(5) Verificar se o no existe na arvore.\n");
    printf("(6) Sair.\n\n");

    scanf("%d", &op);
    fflush(stdin);

    return op;


}

 RotacaoEsqSimples(AVL a)
{
	//Os nos d e c serao aqueles com Fb modificados.
	//AVL *a = r;
	//AVL *b = a->dir;
	AVL d = a;
	AVL c = d->dir;


	d->dir = c->esq;
	c->esq = d;

	if (c->Fb == 1)
	{
		d->Fb = 0;
		c->Fb = 0;
	}
	else
	{
		d->Fb = 1;
		c->Fb = -1;
	}

	a = c;
	return a;
}

AVL RotacaoEsqDupla(AVL a)
{
	//Os nos a, b, c serão aqueles com Fbs modificados
	//AVL *a = r;
	//AVL *c = a->dir;
	//AVL *b = c->esq; //O no b sera a nova raiz

	AVL d = a;
	AVL e = d->dir;
	AVL c = e->esq;

	e->esq = c->dir;
	d->dir = c->esq;
	c->esq = d;
	c->dir = e;

	//Setando os valores dos Fbs de acordo
	//com Fb da nova raiz.
	switch (c->Fb)
	{
	case -1:
		d->Fb = 0;
		e->Fb = 1;
		break;
	case 0:
		d->Fb = 0;
		e->Fb = 0;
		break;
	case +1:
		d->Fb = -1;
		e->Fb = 0;
		break;
	}
	c->Fb = 0;

	a = c;
	return a;
}

AVL RotacaoEsq(AVL a)
{
	if (a->dir->Fb == -1)
		a = RotacaoEsqDupla(a);
	else
		a = RotacaoEsqSimples(a);

	return a;
}

AVL RotacaoDirSimples(AVL a)
{
	//Os nos a e b serao aqueles com Fb modificados.
	AVL d = a->esq;
	AVL c = a;

	c->esq = d->dir;
	d->dir = c;

	if (d->Fb == -1)
	{
		d->Fb = 0;
		c->Fb = 0;
	}
	else
	{
		d->Fb = 1;
		c->Fb = -1;
	}

	a = d;
	return a;
}

AVL RotacaoDirDupla(AVL a)
{
	//Os nos a, b, c serao aqueles com Fbs modificados
	//AVL *c = r;
	//AVL *a = c->esq;
	//AVL *b = a->dir;

	AVL e = a;
	AVL d = e->esq;
	AVL c = d->dir;

	e->esq = c->dir;
	d->dir = c->esq;
	c->esq = d;
	c->dir = e;

	//Setando os valores dos Fbs de acordo
	//com Fb da nova raiz.
	switch (c->Fb)
	{
	case -1:
		d->Fb = 0;
		e->Fb = 1;
		break;
	case 0:
		d->Fb = 0;
		e->Fb = 0;
		break;
	case +1:
		d->Fb = -1;
		e->Fb = 0;
		break;
	}
	c->Fb = 0;

	a = c;
	return a;
}

AVL RotacaoDir(AVL a)
{
	if(a->esq->Fb == 1)
		a = RotacaoDirDupla(a);
	else
		a = RotacaoDirSimples(a);

	return a;
}

AVL Inserir(AVL a, int x)
{
	if(a == NULL) //Momento de inserir
	{
		a = (AVL)malloc(sizeof(AVL));
		a->info = x;
		a->esq = NULL;
		a->dir = NULL;
		a->Fb = 0;
		hMudou = 1;
	}
	else
	{
		if (x <= a->info)
		{
			a->esq = Inserir(a->esq,x);
			if (hMudou == 1)
			{
				switch (a->Fb)
				{
				case -1:
					a = RotacaoDir(a);
					hMudou = 0;
					break;
				case 0:
					a->Fb = -1;
					hMudou = 1;
					break;
				case +1:
					a->Fb = 0;
					hMudou = 0;
					break;
				}
			}
		}
		else
		{
			a->dir = Inserir(a->dir,x);
			if (hMudou == 1)
			{
				switch (a->Fb)
				{
				case -1:
					a->Fb = 0;
					hMudou = 0;
					break;
				case 0:
					a->Fb = +1;
					hMudou = 1;
					break;
				case +1:
					a = RotacaoEsq(a);
					hMudou = 0;
					break;
				}
			}
		}
	}

	return a;
}

void calculaFb(AVL a)
{
    int he, hd;
    if(a != NULL)
    {
        he = altura(a->esq);
        hd = altura(a->dir);

        a->Fb = hd - he;

        calculaFb(a->esq);
        calculaFb(a->dir);
    }
}

int altura(AVL a)
{
    if(a == NULL)
        return 0;

    else{
        int Ae, Ad;
        Ae = altura(a -> esq);
        Ad = altura(a -> dir);

        if(Ae > Ad)
            return Ae+1;

        else
            return Ad+1;
    }

}

void imprimirLargura2(AVL a, int nivel)
{

    if(a != NULL && nivel == 0)
        printf("%d ", a->info);

    else
    {
        if(a != NULL)
        {
            imprimirLargura2(a->esq, nivel-1);
            imprimirLargura2(a->dir, nivel-1);
        }
    }
}

void ImprimeLargura(AVL a)
{
    int i, tam=altura(a);

    for(i=0; i<tam; i++)
    {
        printf("\n");
        imprimirLargura2(a, i);
    }
    if(a == NULL)
    	printf("NULL");
}

int Existe(AVL a, int x)
{
    if(a == NULL)
        return 0;

    else
    {
        if(x == a->info)
            return 1;

        else
        {
            if(x > a->info)
                return Existe(a->dir, x);

            else
                return Existe(a->esq, x);
        }
    }
}

void Destruir(AVL a)
{
    if(a != NULL)
    {
        a->esq = Destruir(a->esq);
        a->dir = Destruir(a->dir);
    }
        free(a);
        return NULL;
}

AVL Remover(AVL a, int x)
{
	if(a != NULL)
	{
		if(a->info == x)
		{
			//Verificar se é folha
			if(a->esq == NULL && a->dir == NULL)
			{
				free(a);
				hMudou = 1;
				return NULL;
			}
			//Verificar se um dos filhos é nulo
			else if (a->esq == NULL || a->dir == NULL)
			{
				AVL aux;
				if(a->esq == NULL)
					aux = a->dir;
				else
					aux = a->esq;

				hMudou = 1;
				free(a);
				return aux;
			}
			//Nenhum filho nulo
			else
			{
				AVL maiorEsq = a->esq;
				while (maiorEsq->dir != NULL)
					maiorEsq = maiorEsq->dir;

				a->info = maiorEsq->info;
				a->esq = Remover(a->esq,a->info);

				if (hMudou == 1)
				{
					switch(a->Fb)
					{
					case -1:
						a->Fb = 0;
						hMudou = 1;
						break;
					case 0:
						a->Fb = 1;
						hMudou = 0;
						break;

					case +1:{


						int aux = a->dir->Fb;
						a = RotacaoEsq(a);
						if (aux == 0)
							hMudou = 0;
						else
							hMudou = 1;
						break;
						}
					}
				}
			}
		}
		else if (x < a->info)
		{
			a->esq = Remover(a->esq, x);

			if (hMudou == 1)
			{
				switch(a->Fb)
				{
					case -1:
						a->Fb = 0;
						hMudou = 1;
						break;
					case 0:
						a->Fb = 1;
						hMudou = 0;
						break;
					case +1:
					{
						int aux = a->dir->Fb;
						a = RotacaoEsq(a);

						if (aux == 0)
							hMudou = 0;
						else
							hMudou = 1;
						break;
					}
				}
			}
		}
		else
		{
			a->dir = Remover(a->dir, x);

			if (hMudou == 1)
			{
				switch(a->Fb)
				{
					case +1:
						a->Fb = 0;
						hMudou = 1;
						break;
					case 0:
						a->Fb = -1;
						hMudou = 0;
						break;
					case -1:
					{
						int aux = a->esq->Fb;
						a = RotacaoDir(a);

						if (aux == 0)
							hMudou = 0;
						else
							hMudou = 1;
						break;
					}
				}
			}
		}
	}
	return a;
}

