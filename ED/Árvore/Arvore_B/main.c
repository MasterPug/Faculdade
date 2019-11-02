#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
/*-
 -
 --Ruan de Almeida
 --Trabalho de Estrutura de dados
 -
 -*/

typedef struct arvore
{
    int info;
    struct arvore *ant;
    struct arvore *prox;
} Arvore;

int menu()
{
    int esc;

    printf("\nMenu de opcoes:\n");
    printf("(1) Ler a arvore de um arquivo.\n");
    printf("(2) Imprimir a arvore.\n");
    printf("(3) Verificar se um elemento existe na arvore.\n");
    printf("(4) Calcular altura da arvore.\n");
    printf("(5) Contar o numero de ocorrencias de um elemento.\n");
    printf("(6) Imprimir as folhas da arvore.\n");
    printf("(7) Contar nos internos.\n");
    printf("(8) Verificar se a arvore e cheia.\n");
    printf("(9) Verificar se a arvore e ordenada.\n");
    printf("(11) Sair.\n");
	printf("(10) Arvore e completa?\n\n");
    scanf("%d", &esc);
    fflush(stdin);

    return esc;

}

Arvore *atribuir(FILE *dados, Arvore *a)
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
            a=(Arvore *) malloc(sizeof(Arvore));
            a->info = num;
            a->ant = atribuir(dados, a->ant);
            a->prox = atribuir(dados, a->prox);
        }

    fscanf(dados, "%c", &c);
    return a;

}

int completa(Arvore *a){


    int Ae, Ad;
    if(a == NULL)
        return 0;

    else
    {
        if(a->ant!= NULL && a->prox!=NULL){
        Ae = cheia(a->ant);
        Ad = cheia(a->prox);
        }
            if(Ae == Ad || Ae-1 == Ad || Ae==Ad-1 )
                return 1;
            else
                return 0;
    }

}

Arvore *abrirArquivo(Arvore *a)
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

void imprimirPre(Arvore *a)
{
    if(a != NULL)
    {
        printf("%d ", a->info);
        imprimirPre(a->ant);
        imprimirPre(a->prox);
    }
}

void imprimirPos(Arvore *a)
{
    if(a != NULL)
    {
        imprimirPos(a->ant);
        imprimirPos(a->prox);
        printf("%d ", a->info);
    }
}

void imprimirOrd(Arvore *a)
{

    if(a != NULL)
    {
        imprimirOrd(a->ant);
        printf("%d ", a->info);
        imprimirOrd(a->prox);
    }
}

void nivel(Arvore* a,int n)
{
    if(a != NULL)
    {
        if(n == 0)
        {
            printf("%d ",a->info);
        }
        else
        {
            nivel(a->ant,n-1);
            nivel(a->prox,n-1);
        }
    }
}

void largura(Arvore *a)
{
    int p;
    p = altura(a);
    int i;
    for(i=0; i<p; i++)
    {
        nivel(a, i);
        printf("\n");
    }

}

void menu2(Arvore *a)
{
    char esc;

    printf("[a] Imprimir em pre-ordem.\n");
    printf("[b] Imprimir em pos-ordem.\n");
    printf("[c] Imprimir em ordem.\n");
    printf("[d] Imprimir por largura.\n");

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

int verificar(Arvore *a, int n)
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

int altura(Arvore * a)
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

int contarOcorrencias(Arvore *a, int n)
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

void imprimirFolhas(Arvore *a)
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

int contarNI(Arvore *a, int cont)
{
    if(a==NULL)
        return 0;

    else
    {
        if(cont==0)
            return contarNI(a->prox, cont+1)+contarNI(a->ant, cont+1);

        else
        {
            if(a->ant == NULL && a->prox == NULL)
                return contarNI(a->prox, cont+1)+contarNI(a->ant, cont+1);

            else
                return 1+contarNI(a->prox, cont+1)+contarNI(a->ant, cont+1);
        }

    }
}

int cheia(Arvore *a)
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

int ordenada(Arvore* a)
{
    if(a->ant == NULL && a->prox==NULL)
    {
        return 1;
    }
    else
    {
        if(a->ant != NULL && a->prox == NULL)
        {
            if(a->ant->info <= a->info)
            {
                return ordenada(a->ant);
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(a->ant == NULL && a->prox != NULL)
            {
                if(a->prox->info > a->info)
                {
                    return ordenada(a->prox);
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if(a->ant->info <= a->info && a->prox->info > a->info)
                {
                    return ordenada(a->ant)&& ordenada(a->prox);
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}

void destruir(Arvore *a)
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
    Arvore *a = NULL;
    int opcao, n, v, c, cont=0, ha, ch, t;
    while(opcao != 12)
    {
        Sleep(7000);
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
                    printf("O numero existe na arvore.");
                else
                    printf("O numero nao aparece na arvore");
                break;

            case 4:
                ha=altura(a);
                printf("A altura da arvore e %d", ha);
                break;

            case 5:
                printf("\nDigite o numero que deseja verificar ocorrencias:\n");
                scanf("%d", &n);
                c=contarOcorrencias(a, n);
                printf("O numero %d aparece %d vez(es).", n, c);
                break;

            case 6:
                printf("\n");
                imprimirFolhas(a);
                break;

            case 7:
                c=contarNI(a, cont);
                printf("A arvore tem %d nos internos.", c);
                break;

            case 8:
                ch=cheia(a);
                if(ch == 1)
                    printf("\nA arvore e cheia.\n");
                else
                    printf("\nA arvore nao e cheia.\n");
                break;

            case 9:
            	cont = ordenada(a);
            	if(cont == 1){
            		printf("e ordenada");
					}else
            		printf("nao e ordenada");
                break;

            case 11:
                destruir(a);
                opcao = 12;
                break;

            case 10:
            	t = completa(a);
            	if(t==1)
            	printf ("arvore completa");
            	else
                printf("nao e completa");
            	break;

        }
    }

    return 0;
}
