#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define ocupado 1
#define livre 0

typedef struct adress{
    struct adress *esquerda, *direita;
    int espacos;
    int lugar;  //indice do local inicial  /  o menor é 0
}adress;
char* ler(FILE *arq, char **comando, int tam);

int main()
{
    FILE *arq;
    char **comando, nome[20];
    printf("Nome do arquivo: ");
    scanf("%s", &nome);
    strcat(nome, ".txt");
    arq=fopen(nome, "r");
    int tam=tamanho(arq);
    rewind(arq);
    comando=ler(arq, comando, tam);
    fclose(arq);



    return 0;
}

char* ler(FILE *arq, char **comando, int tam){
    int i;
    comando=(char**)malloc(tam*sizeof(char*));
    for(i=0; i<tam; i++){
        comando[i]=(char*)malloc(15*sizeof(char));
        fscanf(arq, " %s", comando[i]);
    }
    return *comando;
}

int tamanho(FILE *arq){
    char c;
    int cont=1;
    while ((c = fgetc(arq)) != EOF)
    {
        if (c == '\n')
        cont++;
    }
    return cont;
}

adress *Inserir(adress *r, int x, int *hMudou){
     //Momento de inserir
    if (r == NULL){
        r = (adress*) malloc (sizeof(adress));
        r->espacos = x;
        r->esquerda = NULL;
        r->direita = NULL;
    }else{
        if (x <= r->espacos)
        {
        r->esquerda = Inserir (r->esquerda,x,hMudou);
        }
        else{
        r->direita = Inserir (r->direita,x,hMudou);
        }
        }
    return r;
}

void preenche(int *vetor, int inicio, int quantidade, int valor){
    int i;
    for(i=0; i<quantidade; i++, inicio++)
        vetor[inicio]=valor;
}
