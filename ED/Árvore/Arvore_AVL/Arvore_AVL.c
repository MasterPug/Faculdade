#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
/*-
 -
 --Ruan de Almeida
 --Trabalho de Estrutura de dados
 -
 -*/

typedef struct Avl
{
    int info;
    struct Avl *ant;
    struct Avl * FB;
    struct Avl *prox;
} Avl;

int menu()
{
    int esc;

    printf("\nMenu de opcoes:\n");
    printf("(1) Ler a Avl de um arquivo.\n");
    printf("(2) Imprimir a Avl.\n");
    printf("(3) Verificar se um elemento existe na Avl.\n");
    printf("(4) Calcular altura da Avl.\n");
    printf("(5) Contar o numero de ocorrencias de um elemento.\n");
    printf("(6) Contar o numero de elementos entre x e y. \n");
    printf("(7) Imprimir as folhas da Avl.\n");
    printf("(8) Contar nos internos.\n");
    printf("(9) Verificar se a Avl e cheia.\n");
    printf("(10) Verificar se a Avl e ordenada.\n");
    printf("(11) Imprimir em parenteses. \n");
    printf("(12) Inserir nó.\n");
    printf("(13) Remover nó. \n");
    printf("(14) Sair.\n\n");

    scanf("%d", &esc);
    fflush(stdin);

    return esc;

}

int conta(Avl *a, int x, int y)
{

    if(a == NULL)
        return 0;
    else
    {
        if(a->info > x && a->info < y)
        {
            return 1 + conta(a->ant, x, y) + conta(a->prox, x, y);
        }
        else
        {
            if(a->info <= x){
               return conta(a->prox, x, y);
                }
            if(a->info >= y){
                return conta(a->ant, x, y);
            }
        }
    }
}

Avl *Remover (Avl *a, int x, int *hMudou)
{
    if (a != NULL)
    {
        if (a->info == x)
        {
            if (a->ant == NULL && a->prox == NULL)
            {
                free (a);
                *hMudou = 1;
                return NULL;
            }
            else if (a->ant == NULL || a->prox == NULL)
            {
                Avl *aux;
                if (a->ant == NULL)
                    aux = a->prox;
                else
                    aux = a->ant;

                *hMudou = 1;
                return aux;
            }
            else
            {
                Avl *maiorant = a->ant;
                while (maiorant->prox != NULL)
                maiorant = maiorant->prox;
                a->info = maiorant->info;
                a->ant = Remover(a->ant,a->info,hMudou);

                if (hMudou == 1)
                {
                    switch(a->FB)
                    {
                    case -1:
                        a->FB = 0;
                        hMudou = 1;
                        break;

                    case 0:
                        a->FB = 1;
                        hMudou = 0;
                        break;

                    case 1:
                        int aux = a->prox->FB;
                        a = Rotacaoant(r);

                        if (aux == 0)
                            hMudou = 0;
                        else
                            hMudou = 1;
                        break;

                    }
                }
            }
        }
        else if (x < a->info)
        {
            a->ant = Remover(a->ant, x, hMudou);

            if (hMudou == 1)
            {
                switch(a->FB)
                {
                case -1:
                    a->FB = 0;
                    hMudou = 1;
                    break;
                case 0:
                    a->FB = 1;
                    hMudou = 0;
                    break;
                case +1:
                {
                    int aux = a->prox->FB;
                    a = Rotacaoant(r);

                    if (aux == 0)
                        hMudou = 0;
                    else    hMudou = 1;
                    break;
                }
                }
            }
        }
        else
        {
            a->prox = Remover(a->prox, x, hMudou);

            if (hMudou == 1)
            {
                switch(a->FB)
                {
                case +1:
                    a->FB = 0;
                    hMudou = 1;
                    break;
                case 0:
                    a->FB = -1;
                    hMudou = 0;
                    break;
                case -1:
                {
                    int aux = a->ant->FB;
                    a = Rotacaoprox(r);

                    if (aux == 0)
                        hMudou = 0;
                    else     hMudou = 1;
                    break;
                }
                }
            }
        }
        return a;
    }
}

Avl *Inserir(Avl *a, int x, int *hMudou)
{
    if (a == NULL)
    {
        a = (Avl*) malloc (sizeof(Avl));
        a->info = x;
        a->ant = NULL;
        a->prox = NULL;
        a->FB = 0;
        *hMudou = 1;
    }
    else
    {
        if (x <= a->info)
        {
            a->ant = Inserir (a->ant,x,hMudou);
            if (*hMudou == 1)
            {
                switch (a->FB)
                {
                case -1:
                    a = Rotacaoprox(a);
                    *hMudou = 0;
                    break;
                case 0:
                    a->FB = -1;
                    *hMudou = 1;
                    break;
                case +1:
                    a->FB = 0;
                    *hMudou = 0;
                    break;
                }
            }
        }
        else
        {
            a->prox = Inserir (a->prox,x,hMudou);
            if (*hMudou == 1)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *hMudou = 0;
                    break;
                case 0:
                    a->FB = +1;
                    *hMudou = 1;
                    break;
                case +1:
                    a = Rotacaoant (r);
                    *hMudou = 0;
                    break;
                }
            }
        }
    }
    return a;
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
            a->ant = atribuir(dados, a->ant);
            a->prox = atribuir(dados, a->prox);
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

    dados = fopen(arq, "r");
    if(dados != NULL)
        a = atribuir(dados, a);
    fclose(dados);

    return a;
}

void arquivoClone(Avl *a)
{
    int b=1, c=1;
    if(a != NULL)
    {
        printf("(");
        printf("%d", a->info);
        b=arquivoClone(a->ant);
        c=arquivoClone(a->prox);

        if(c==0)printf("(-1)");
        if(b==0)printf("(-1)");
        printf(")");
    }else return 0;
}

Avl *Rotacaoant (Avl *r)
{
    if (r->prox->FB == -1)
        r = RotacaoantDupla(r);
    else
        r = RotacaoantSimples(r);
    return r;
}

Avl *RotacaoantSimples (Avl *r)
{
    Avl *a = r;
    Avl *b=a->prox;

    a->prox = b->ant;
    b->ant = a;
    if (b->FB == 1)
    {
        a->FB = 0;
        b->FB = 0;
    }
    else
    {
        a->FB = 1;
        b->FB = -1;
    }
    r=b;
    return r;
}

Avl *RotacaoantDupla(Avl *r)
{
    Avl *a = r;
    Avl *c = a->prox;
    Avl *b = c->ant;

    c->ant = b->prox;
    a->prox = b->ant;
    b->ant = a;
    b->prox = c;

    switch(b->FB)
    {
    case -1:
        a->FB = 0;
        c->FB = 1;
        break;
    case 0:
        a->FB = 0;
        c->FB = 0;
        break;
    case +1:
        a->FB = -1;
        c->FB = 0;
        break;
    }
    b->FB = 0;
    r = b;
    return r;
}

Avl *Rotacaoprox (Avl *r)
{
    if (r->ant->FB == 1)
        r = RotacaoproxDupla(r);
    else
        r = RotacaoproxSimples(r);
    return r;
}

Avl *RotacaoproxSimples (Avl *r)
{
    Avl *a = r->ant;
    Avl *b = r;

    b->ant = a->prox;
    a->prox = b;
    if (a->FB == -1)
    {
        a->FB = 0;
        b->FB = 0;
    }
    else
    {
        a->FB = 1;
        b->FB = -1;
    }
    r = a;
    return r;
}

Avl *RotacaoproxDupla(Avl *r)
{
    Avl *c = r;
    Avl *a = c->ant;
    Avl *b = a->prox;

    c->ant = b->prox;
    a->prox = b->ant;
    b->ant = a;
    b->prox = c;

    switch(b->FB)
    {
    case -1:
        a->FB = 0;
        c->FB = 1;
        break;
    case 0:
        a->FB = 0;
        c->FB = 0;
        break;
    case +1:
        a->FB = -1;
        c->FB = 0;
        break;
    }
    b->FB = 0;

    r = b;
    return r;
}

void imprimirPre(Avl *a)
{
    if(a != NULL)
    {
        printf("%d ", a->info);
        imprimirPre(a->ant);
        imprimirPre(a->prox);
    }
}

void imprimirPos(Avl *a)
{
    if(a != NULL)
    {
        imprimirPos(a->ant);
        imprimirPos(a->prox);
        printf("%d ", a->info);
    }
}

void imprimirOrd(Avl *a)
{

    if(a != NULL)
    {
        imprimirOrd(a->ant);
        printf("%d ", a->info);
        imprimirOrd(a->prox);
    }
}

void nivel(Avl* arv,int n)
{
    if(arv != NULL)
    {
        if(n == 0)
        {
            printf("%d ",arv->info);
        }
        else
        {
            nivel(arv->ant,n-1);
            nivel(arv->prox,n-1);
        }
    }
}

void largura(Avl *arv)
{
    int p;
    p = altura(arv);
    int i;
    for(i=0; i<p; i++)
    {
        nivel(arv, i);
        printf("\n");
    }

}

void menu2(Avl *a)
{
    char esc;

    printf("[a] Imprimir em pre-ordem.\n");
    printf("[b] Imprimir em pos-ordem.\n");
    printf("[c] Imprimir em ordem.\n");
    printf("[d] Imprimir por largura.\n");
    printf("[e] Imprimir a notação");

    scanf("%c", &esc);

    switch(esc)
    {
        case 'a':
            imprimirPre(a);
            break;

        case 'b':
            imprimirPos(a);
            break;

        case 'c':
            imprimirOrd(a);
            break;

        case 'd':
            largura(a);
            break;

    }


}

int verificar(Avl *a, int n)
{
    if(a == NULL)
        return 0;

    if(a->info == n)
        return 1;

    else
    {
        int va, vp;
        va = verificar(a->ant, n);
        vp = verificar(a->prox, n);

        if(va == 1 || vp == 1)
            return 1;

        else
            return 0;
    }
}

int altura(Avl * a)
{
    if(a == NULL)
        return 0;

    else{
        int Ae, Ad;
        Ae = altura(a -> ant);
        Ad = altura(a -> prox);

        if(Ae > Ad)
        {
            return Ae+1;
        }
        else
        {
            return Ad+1;
        }

    }

}

int contarOcorrencias(Avl *a, int n)
{
    if(a == NULL)
        return 0;

    else
    {
        if(a->info == n)
            return 1+contarOcorrencias(a->ant, n)+contarOcorrencias(a->prox, n);

        else
            return contarOcorrencias(a->ant, n)+contarOcorrencias(a->prox, n);
    }
}

void imprimirFolhas(Avl *a)
{
    if(a != NULL)
    {
        if(a->ant == NULL && a->prox == NULL)
        {
            printf("%d ", a->info);
            imprimirFolhas(a->ant);
            imprimirFolhas(a->prox);
        }

         else
        {
            imprimirFolhas(a->ant);
            imprimirFolhas(a->prox);
        }
    }
}

int contarNI(Avl *a, int cont)
{
    if(a==NULL)
        return 0;

    else
    {
            if(a->ant == NULL && a->prox == NULL)
                return contarNI(a->prox, cont+1)+contarNI(a->ant, cont+1);
            else
                return 1+contarNI(a->prox, cont+1)+contarNI(a->ant, cont+1);
        }

    }

int cheia(Avl *a)
{
    int Ae, Ad;
    if(a == NULL)
        return 0;

    else
    {
        Ae = cheia(a->ant);
        Ad = cheia(a->prox);
            if(Ae == Ad)
                return 1;
            else
                return 0;
    }

}

int ordenada(Avl* arv)
{
    if(arv->ant == NULL && arv->prox==NULL)
    {
        return 1;
    }
    else
    {
        if(arv->ant != NULL && arv->prox == NULL)
        {
            if(arv->ant->info <= arv->info)
            {
                return ordenada(arv->ant);
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(arv->ant == NULL && arv->prox != NULL)
            {
                if(arv->prox->info > arv->info)
                {
                    return ordenada(arv->prox);
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if(arv->ant->info <= arv->info && arv->prox->info > arv->info)
                {
                    return ordenada(arv->ant)&& ordenada(arv->prox);
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}

void destruir(Avl *a)
{
    if(a != NULL)
    {
        destruir(a->ant);
        destruir(a->prox);
        free(a);
    }

    if(a == NULL)
        free(a);
}

int main(void)
{
    Avl *a = NULL;
    int opcao, n, v, c, cont=0, ha, ch, x, y;
    int av=0, hMudou;

    while(opcao != 12)
    {
        Sleep(10000);
        system("cls");
        opcao = menu();

        switch(opcao)
        {
            case 1:
                a=abrirArquivo(a);
                break;

            case 2:
                menu2(a);
                break;

            case 3:
                printf("\nDigite o numero que deseja verificar:\n");
                scanf("%d", &n);
                v=verificar(a, n);
                if(v == 1)
                    printf("O numero existe na Avl.");
                else
                    printf("O numero nao aparece na Avl");
                break;

            case 4:
                ha=altura(a);
                printf("A altura da Avl e %d", ha);
                break;

            case 5:
                printf("\nDigite o numero que deseja verificar ocorrencias:\n");
                scanf("%d", &n);
                c=contarOcorrencias(a, n);
                printf("O numero %d aparece %d vez(es).", n, c);
                break;

            case 6:
                scanf("%d \n", &x);
                scanf("%d", &y);
                av = conta(a, x, y);
                printf(" %d ", av);
                break;

            case 7:
                printf("\n");
                imprimirFolhas(a);
                break;

            case 8:
                c=contarNI(a, cont);
                printf("A Avl tem %d nos internos.", c);
                break;

            case 9:
                ch=cheia(a);
                if(ch == 1)
                    printf("\nA Avl e cheia.\n");
                else
                    printf("\nA Avl nao e cheia.\n");
                break;

            case 10:
            	cont = ordenada(a);
            	if(cont == 1){
            		printf("e ordenada");
					}else
            		printf("nao e ordenada");
                break;

            case 11:
                arquivoClone(a);
                break;


            case 12:
                scanf("%d ", &x);
                Inserir(a, x, hMudou);
                break;

            case 13:
                scanf("%d ", &y);
                Remover(a, y, hMudou);
                break;

            case 14:
                destruir(a);
                opcao = 12;
                break;

        }
    }

    return 0;
}
