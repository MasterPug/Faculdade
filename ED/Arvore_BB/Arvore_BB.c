/*
Trabalho de Árvore Binária de Busca.
Beatriz Rangel
Ruan Almeida
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct avl
{
    int info;
    int Fb;
    struct avl *esq;
    struct avl *dir;
} Avl;

int menu()
{
    int op;

    printf("\nMenu de opcoes:\n");
    printf("(1) Ler a arvore de um arquivo.\n");
    printf("(2) Inserir um novo no.\n");
    printf("(3) Remover da arvore.\n");
    printf("(4) Imprimir em largura.\n");
    printf("(5) Imprimir em notacao de parenteses\n");
    printf("(6) Imprimir valores menores que x e maiores que y.\n");
    printf("(7) Contar os elementos entre x e y.\n");
    printf("(8) Imprimir as folhas de valor maior ou igual a x.\n");
    printf("(9) Verificar se o no existe na arvore.\n");
    printf("(10) Sair.\n\n");

    scanf("%d", &op);
    fflush(stdin);

    return op;

}

Avl *atribuir(FILE *dados, Avl *a)
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
            a=(Avl *) malloc(sizeof(Avl));
            a->info = num;
            a->esq = atribuir(dados, a->esq);
            a->dir = atribuir(dados, a->dir);
        }

    fscanf(dados, "%c", &c);
    return a;

}

Avl *abrirArquivo(Avl *a)
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

    return a;
}

Avl *RotacaoEsqSimples(Avl *a)
{
	//Os nos d e c serao aqueles com Fb modificados.
	//AVL *a = r;
	//AVL *b = a->dir;
	Avl *d = a;
	Avl *c = d->dir;
	

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

Avl *RotacaoEsqDupla(Avl *a)
{
	//Os nos a, b, c serÃ£o aqueles com Fbs modificados
	//AVL *a = r;
	//AVL *c = a->dir;
	//AVL *b = c->esq; //O no b sera a nova raiz
	
	Avl *d = a;
	Avl *e = d->dir;
	Avl *c = e->esq;

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

Avl *RotacaoEsq(Avl *a)
{
	if (a->dir->Fb == -1)
		a = RotacaoEsqDupla(a);
	else
		a = RotacaoEsqSimples(a);

	return a;
}

Avl *RotacaoDirSimples(Avl *a)
{
	//Os nos a e b serao aqueles com Fb modificados.
	Avl *d = a->esq;
	Avl *c = a;

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

Avl *RotacaoDirDupla(Avl *a)
{
	//Os nos a, b, c serao aqueles com Fbs modificados
	//AVL *c = r;
	//AVL *a = c->esq;
	//AVL *b = a->dir;
	
	Avl *e = a;
	Avl *d = e->esq;
	Avl *c = d->dir;

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

Avl *RotacaoDir(Avl *a)
{
	if(a->esq->Fb == 1)
		a = RotacaoDirDupla(a);
	else
		a = RotacaoDirSimples(a);

	return a;
}

Avl *Inserir(Avl *a, int x, int *hMudou)
{
	if(a == NULL) //Momento de inserir
	{
		a = (Avl*)malloc(sizeof(Avl));
		a->info = x;
		a->esq = NULL;
		a->dir = NULL;
		a->Fb = 0;
		*hMudou = 1;
	}
	else
	{
		if (x <= a->info)
		{
			a->esq = Inserir(a->esq,x,hMudou);
			if (*hMudou == 1)
			{
				switch (a->Fb)
				{
				case -1:
					a = RotacaoDir(a);
					*hMudou = 0;
					break;
				case 0:
					a->Fb = -1;
					*hMudou = 1;
					break;
				case +1:
					a->Fb = 0;
					*hMudou = 0;
					break;
				}
			}
		}
		else
		{
			a->dir = Inserir(a->dir,x,hMudou);
			if (*hMudou == 1)
			{
				switch (a->Fb)
				{
				case -1:
					a->Fb = 0;
					*hMudou = 0;
					break;
				case 0:
					a->Fb = +1;
					*hMudou = 1;
					break;
				case +1:
					a = RotacaoEsq(a);
					*hMudou = 0;
					break;
				}
			}
		}
	}

	return a;
}

Avl *Remover(Avl *a, int x, int *hMudou)
{
	if(a != NULL)
	{
		if(a->info == x)
		{
			//Verificar se Ã© folha
			if(a->esq == NULL && a->dir == NULL)
			{
				free(a);
				*hMudou = 1;
				return NULL;
			}
			//Verificar se um dos filhos Ã© nulo
			else if (a->esq == NULL || a->dir == NULL)
			{
				Avl *aux;
				if(a->esq == NULL)
					aux = a->dir;
				else
					aux = a->esq;

				*hMudou = 1;
				free(a);
				return aux;
			}
			//Nenhum filho nulo
			else
			{
				Avl *maiorEsq = a->esq;
				while (maiorEsq->dir != NULL)
					maiorEsq = maiorEsq->dir;

				a->info = maiorEsq->info;
				a->esq = Remover(a->esq,a->info,hMudou);

				if (*hMudou == 1)
				{
					switch(a->Fb)
					{
					case -1:
						a->Fb = 0;
						*hMudou = 1;
						break;
					case 0:
						a->Fb = 1;
						*hMudou = 0;
						break;
					
					case +1:{
					
					
						int aux = a->dir->Fb;
						a = RotacaoEsq(a);
						if (aux == 0)
							*hMudou = 0;
						else
							*hMudou = 1;
						break;
						}
					}
				}
			}
		}
		else if (x < a->info)
		{
			a->esq = Remover(a->esq, x, hMudou);

			if (*hMudou == 1)
			{
				switch(a->Fb)
				{
					case -1:
						a->Fb = 0;
						*hMudou = 1;
						break;
					case 0:
						a->Fb = 1;
						*hMudou = 0;
						break;
					case +1:
					{
						int aux = a->dir->Fb;
						a = RotacaoEsq(a);

						if (aux == 0)
							*hMudou = 0;
						else
							*hMudou = 1;
						break;
					}
				}
			}
		}
		else
		{
			a->dir = Remover(a->dir, x, hMudou);

			if (*hMudou == 1)
			{
				switch(a->Fb)
				{
					case +1:
						a->Fb = 0;
						*hMudou = 1;
						break;
					case 0:
						a->Fb = -1;
						*hMudou = 0;
						break;
					case -1:
					{
						int aux = a->esq->Fb;
						a = RotacaoDir(a);

						if (aux == 0)
							*hMudou = 0;
						else
							*hMudou = 1;
						break;
					}
				}
			}
		}
	}
	return a;
}

int altura(Avl * a)
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

void calculaFb(Avl *a)
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

void imprimirLargura(Avl *a, int nivel)
{

    if(a != NULL && nivel == 0)
        printf("%d ", a->info);

    else
    {
        if(a != NULL)
        {
            imprimirLargura(a->esq, nivel-1);
            imprimirLargura(a->dir, nivel-1);
        }
    }
}

void imprimirLargura2(Avl *a)
{
    int i, tam=altura(a);

    for(i=0; i<tam; i++)
    {
        printf("\n");
        imprimirLargura(a, i);
    }
    if(a == NULL)
    	printf("NULL");
}

int parenteses(Avl *a)
{
    int b=1, c=1;
    if(a != NULL)
    {
        printf("(");
        printf("%d", a->info);

        b=parenteses(a->esq);
        c=parenteses(a->dir);

        if(c==0)
            printf("(-1)");

        if(b==0)
            printf("(-1)");

        printf(")");
    }

    else
        return 0;
}

void imprimirFora(Avl *a, int x, int y)
{
    if(a != NULL)
    {
        if(a->info < x || a->info > y)
            printf("%d ", a->info);

            imprimirFora(a->esq, x, y);
            imprimirFora(a->dir, x, y);
    }
}

int conta(Avl *a, int x, int y)
{

    if(a == NULL)
        return 0;

    else
    {
        if(a->info > x && a->info < y)
            return 1 + conta(a->esq, x, y) + conta(a->dir, x, y);

        else
        {
            if(a->info <= x)
               return conta(a->dir, x, y);

            if(a->info >= y)
                return conta(a->esq, x, y);
        }
    }
}

void imprimirFolhas(Avl *a, int x)
{
    if(a != NULL)
    {
        if(x > a->info)
            imprimirFolhas(a->dir, x);

        else
        {
            if(a->esq == NULL && a->dir == NULL)
                printf("%d ", a->info);

            else
            {
                imprimirFolhas(a->esq, x);
                imprimirFolhas(a->dir, x);
            }
        }
    }
}

int verificar(Avl *a, int x)
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
                return verificar(a->dir, x);

            else
                return verificar(a->esq, x);
        }
    }
}

void destruir(Avl *a)
{
    if(a != NULL)
    {
        destruir(a->esq);
        destruir(a->dir);
        free(a);
    }

    if(a == NULL)
        free(a);
}

int main(void)
{
    Avl *a = NULL;
    int opcao, x, y, v, cont;

    while(opcao != 11)
    {
        Sleep(3500);
        system("cls");
        opcao = menu();

        switch(opcao)
        {
            case 1:
                a=abrirArquivo(a);
                calculaFb(a);
                break;

            case 2:{
			
			
            	int mudou = 0;
                printf("Digite o numero a ser inserido:\n");
                scanf("%d", &x);
                a = Inserir(a, x, &mudou);
                break;
				}

            case 3:{
			
            	int mudou = 0;
                printf("Digite o numero a ser removido:\n");
                scanf("%d", &x);
                a = Remover(a, x, &mudou);
                break;
					}

            case 4:
                imprimirLargura2(a);
                break;

            case 5:
                parenteses(a);
                break;

            case 6:
                printf("Digite os valores de x e y, respectivamente:\n");
                scanf("%d %d", &x, &y);
                imprimirFora(a, x, y);
                break;

            case 7:
                printf("Digite os valores de x e y, respectivamente:\n");
                scanf("%d %d", &x, &y);
                cont=conta(a, x, y);
                printf("Existem %d valores entre x e y na arvore", cont);
                break;

            case 8:
                printf("Digite o valor de x:\n");
                scanf("%d", &x);
                printf("Os valores maiores que x sao: ");
                imprimirFolhas(a, x);
                break;

            case 9:
                printf("\nDigite o numero que deseja verificar:\n");
                scanf("%d", &x);
                v=verificar(a, x);
                if(v == 1)
                    printf("O numero existe na arvore.");
                else
                    printf("O numero nao aparece na arvore");
                break;

            case 10:
                destruir(a);
                opcao = 11;
                break;

        }
    }

    return 0;
}
