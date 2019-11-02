#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
/*-
 -
 --Ruan de Almeida
 --Trabalho de Hash
 -
 -*/

typedef struct Lista{
    int destino;
    float custo;
    struct Lista *prox;
} lista;

int lista_vazia(lista * a){
    if(a == NULL);
}

lista Inicializacao(lista ** a, int n){
    int i;
    for(i=0; i<=n; i++)
    {
        a[i]=NULL;
    }
}

void ImprimirLista(lista * a){
    lista * p = a;
    while(p!=NULL)
    {
        printf("%d, %.2f |", p->destino, p->custo);
        p=p->prox;
    }
}

void Imprimir(lista ** a, int n){
    int i;
    for (i=0; i<=n; i++)
    {
        printf("\n %d:", i);
        ImprimirLista(a[i]);
    }
}

lista * inserirLista(lista * a, int d, float c){
    lista * no = (lista*)malloc(sizeof(lista));
    no->destino=d;
    no->custo=c;
    no->prox=a;
    return no;
}

void Inserir(lista ** a, int origem, int destino, float custo){
    a[origem] = inserirLista(a[origem], destino, custo);
}

lista * removerLista(lista * a, int d, float c){
    if(lista_vazia(a))
    {
        if(a->destino == d && a->custo == c)
        {
            lista * t = a;
            a=a->prox;
            free(t);
            return a;
        }
        else
            a->prox = removerLista(a->prox,d,c);
    }
    else
        return a;
}

void Remover(lista ** a, int origem, int destino, float custo){
    a[origem] = removerLista(a[origem], destino, custo);

}

int GrauEntrada(lista * a, int v){
    if(!lista_vazia(a))
        return 0;

    else
    {
        if(a->destino == v)
        {
            int cont;
            cont = GrauEntrada(a->prox, v);
            return cont +1;
        }
        else
        {
            GrauEntrada(a->prox, v);
        }
    }
}

int GrauSaida(lista * a){
    if(!lista_vazia(a))
        return 0;

    else
    {
        int Ae;
        Ae = GrauSaida(a -> prox);

        return Ae+1;
    }

}

int Esparso(lista ** a, int n){
    int num=0, i;
    float t;
    t = n *(n-1);
    t  = (t*0.30);

    for(i=1; i<=n; i++)
    {
        num = num + GrauSaida(a[i]);
    }

    if(num <= t)
        return 1;
    else
        return 0;
}

int	CalcGrau(lista ** a, int v, int n){
    int i,e=0,s;
    for(i=0; i<n; i++)
    {
        e = e + GrauEntrada(a[i], v);
    }

    s = GrauSaida(a[v]);

    return (e+s);

}

int ExisteVetor(int * vet, int n, int x){
    int i;
    for(i=0;i<n;i++){
        if(vet[i]==x)
            return 1;
    }
    return 0;
}

int ExisteCaminho(lista ** a, int origem, int destino, int *rota, int pos){
    if(origem == destino)
    {
        return 1;
    }
    else{
        if(!ExisteVetor(rota,pos,origem)){
            lista *l = a[origem];
            rota[pos]= origem;
            while(l!=NULL){
                int ret = ExisteCaminho(a,l->destino,destino,rota,pos+1);

                if(ret == 1)
                    return 1;

                l = l->prox;
            }
        }
        return 0;
    }
}

int existeVetor(int *vet, int n, int x){
    for(int i=0; i<n;i++)
        if(vet[i]==x)
            return 1;
    return 0;
}

void imprimeCaminhos(lista **g, int origem, int destino, int *rota, int pos){
    if(origem==destino){
        rota[pos]=origem;
        for(int i=0; i<=pos; i++)
            printf("%d    ",rota[i]);
        printf("\n");
    }else{
        if(existeVetor(rota, pos, origem)==0){
            lista *l=g[origem];
            rota[pos]=origem;
            while(l!=NULL){
                imprimeCaminhos(g, l->destino, destino,rota, pos+1);
                l=l->prox;
            }
        }
    }
}


void MenorCaminho(lista **a, int destino, int *vet, int pos, float menorCusto, int *tamanho, int *auxvet)
{
    int i;
    float custo=0;
    if(vet[pos+1]==destino)
    {
        if(pos<tamanho)
        {
            tamanho = pos;
            for(i=0; i<pos; i++)
            {
                auxvet[i]=vet[i];
            }
            for(i=0; i<pos-1; i++)
            {
                lista *t= a[vet[i]];
                while(t->destino!=vet[i+2])
                {
                    t=t->prox;
                }
                custo=custo + t->custo;
            }
            menorCusto = custo;
        }
    }
    else
    {
        lista *p = a[vet[pos+1]];
        while(p!=NULL)
        {
//criar uma função que verifica se o valor existe no vetor para não entrar emloop
            if(ExisteVetor(vet,pos,p->destino)==0)
            {
                vet[pos]= p->destino;

                MenorCaminho(a,destino,vet,pos+1,menorCusto,tamanho,auxvet);
            }
            p=p->prox;
        }
    }
}

void DestruirLista(lista * a){
    if(lista_vazia(a))
    {
        while(a == NULL)
        {
            lista *aux = a;
            a = a->prox;
            free(aux);
        }
    }
}

void Destruir(lista ** a, int n){
    int i;
    for(i=0; i<n; i++)
    {
        DestruirLista(a[i]);
    }
    free(a);
}

int menu(){
    int op;

    printf("\nMenu de opcoes:\n");
    printf("(1) Inserir aresta.\n");
    printf("(2) Remover uma aresta.\n");
    printf("(3) Imprimir.\n");
    printf("(4) Grau do vertice.\n");
    printf("(5) Verificar se e esparso.\n");
    printf("(6) imprimir todos os caminhos entre uma origem e o destino.\n");
    printf("(7) imprimir o maior caminho.\n");
    printf("(8) imprimir caminho de menor custo.\n");
    printf("(9) Sair.\n\n");
    scanf("%d", &op);
    fflush(stdin);

    return op;
}

int main(int argc, char * argv[]){
    lista ** a;
    int n, opcao, origem, destino, v, rota, pos=0;
    int *vet, *aux;
    float custo, menorcusto;
    printf("numeros de vertices:");
    scanf("%d", &n);
    a = (lista**)malloc((n+1)*sizeof(lista*));
    Inicializacao(a, n);
    while(opcao!=10)
    {
        system("cls");
        opcao = menu();
        switch(opcao)
        {

        case 1:
            printf("origem?");
            scanf("%d", &origem);
            printf("destino?");
            scanf("%d", &destino);
            printf("custo?");
            scanf("%f", &custo);
            Inserir(a,origem,destino,custo);
            system("pause");
            break;

        case 2:
            printf("origem?");
            scanf("%d", &origem);
            printf("destino?");
            scanf("%d", &destino);
            printf("custo?");
            scanf("%d", &custo);
            Remover(a,origem,destino,custo);
            system("pause");
            break;

        case 3:
            Imprimir(a,n);
            printf("\n");
            system("pause");
            break;

        case 4:
            printf("Digite o numero do vertice: ");
            scanf("%d", &v);
            int grau = CalcGrau(a,v,n);
            printf("O grau do vertice %d e:%d", v, grau);
            system("pause");
            break;

        case 5:
            if(Esparso(a,n))
                printf("Ele e Esparso\n");
            else
                printf("Nao e Esparso\n");
            system("pause");
            break;

        case 6:
            printf("origem?");
            scanf("%d", &origem);
            printf("Destino?");
            scanf("%d", &destino);
            imprimeCaminhos(a,origem,destino,&rota,pos);
            system("pause");
            break;

        case 8:
            printf("origem?");
            scanf("%d", &origem);
            printf("Destino?");
            scanf("%d", &destino);
            vet[0]=origem;
            MenorCaminho(a,destino,vet,pos,menorcusto,n,aux);
            break;

        case 9:
            Destruir(a,n);
            opcao = 10;
            break;
        }
    }
}
