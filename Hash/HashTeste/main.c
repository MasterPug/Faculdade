#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define x 2

#define M 5

typedef struct aluno{
	char mat[10];
	char nome[150];
}Aluno;

typedef struct lista{
	Aluno info;
	struct lista *prox;
}Lista;

int inc(int pos, int soma, int n){
	return (pos+soma)%n;
}

int soma(char *s){
	int soma=0;
	int i;

	for(i=0;s[i]!='\0';i++){
		soma=soma+s[i];
	}
	return soma;
}

int hash(int valor){
	return valor%M;
}

int hash2(int valor, int n){
	return ((7*valor)%n) + 1;
}

void Inicializar(Lista **vet){
	int i;
	for(i=0;i<M;i++){
		vet[i]=NULL;
	}
}

Lista * Inserir(Lista **vet, char *mat, char *nome){

	int s = soma(mat);
	int pos = hash(s);
	Lista *no = (Lista*)malloc(sizeof(Lista));
	strcpy(no->info.mat, mat);
	strcpy(no->info.nome, nome);
	no->prox=vet[pos];
	vet[pos] = no;
	return *vet;
}

Lista* compara(Lista *l, char *mat){
while(strcmp(l->info->mat,mat)==0){
		printf("%s", mat);
		printf("%s",l.info->mat);
		l=l->prox;
	}
	if(strcmp(l->info->mat,mat)){
		aux = l;

}

void Busca(Lista **vet, Lista *aux, char *mat, char *nome){
	int s=soma(mat);
	int pos = hash(s);
	 l = vet[pos];


	}
}

int menu(){
	int opc;
	printf("(1) Inserir\n");
	printf("(2) Buscar\n");
	printf("(3) Sair\n");
	scanf("%d", &opc);
	fflush(stdin);
	return opc;
}

main(){
	int n=0,opcao;
	Lista *vet[M], *aux;
	Inicializar(vet);
	char mat[11], nome[150];
	while(opcao != 5){
		opcao = menu();
		system("cls");
		switch(opcao){
			case 1:
				printf("Matricula:");
				scanf("%d", &mat);
				printf("Nome:");
				scanf("%s", &nome);
				*vet = Inserir(vet,mat,nome);
				printf("\n");
				system("pause");
				break;
			case 2:
				printf("Matricula:");
				scanf("%s", &mat);
				printf("Nome:");
				scanf("%s", &nome);
				Busca(vet,aux,mat,nome);
				printf("%s,%s", aux->info.nome, aux->info.mat);
				printf("Encontrado");
				printf("\n");
				system("pause");
		}
	}
}


