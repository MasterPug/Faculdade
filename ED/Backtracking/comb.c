#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

void soma(int *vet, int *contTotal,int n){

	  int i, cont0=0, cont1=0;
        for(i=0; i<n; i++)//varre o vetor em busca de 0 e 1
        {
            if(vet[i]==0){
                cont0++;// contador dos 0's
            }
            else{
                cont1++;//contador do 1's
            }
        }
        if(cont0 > cont1){
            *contTotal = 1 + *contTotal;// no final, conta o numero de combinações total com prevalencia de 0.
        }
}

void comb01(int *vet, int pos, int n, int *contTotal)
{
    if (pos==n)
    {
    	soma(vet, contTotal, n);
    }
    else
    {
        vet[pos]=0;// ta desse jeito, mas pode pegar um vetor auxiliar la da main, com os numeros 0 e 1.
        comb01(vet, pos+1, n, contTotal);// fica mais bonito, eu acho
        vet[pos]=1;
        comb01(vet, pos+1, n, contTotal);
    }
}

//int igual(char *vet, int n)
//{
//    // usei dois for, por comodidade, pode colocar while tbm
//	int cont=0, j, i;
//	for(i=0;i<n;i++){//ele não estava imprimindo o "U" se tivesse "i<=n" dentro dos for
//        for(j=0;j<n;j++){//#nãosei não me pergunte pq kkkkk
//            if(i != j){
//                if(vet[i]==vet[j]){// ele vai entrar e adicionar nesse cont se encontrar letras iguais
//                    cont++;
//                }
//            }
//        }
//	}
//	return cont;
//}

int igual(char *vet, int n){
	int i, conth=0, contj=0, contk=0, cont00;
	for(i=0;i<=n;i++){
		if(vet[i] == 'h'){
			conth=1;
		}
		if(vet[i] == 'j'){
			contj=1;
		}
		if(vet[i] == 'k'){
			contk=1;
		}
	}
	cont00 = conth+contj+contk;
	if(cont00 == 3){

		return 0;
	}
	else{
		return 1;
	}

}

void comb02(char *vet, char *aux, int pos, int n)// aeiou
{
    int i, k=0;
    if(pos == n)
    {
        k = igual(vet, n);// ele chama a função para ver se há igualdade
        if(k==1){
            for (i=0; i<n; i++)
            {
            printf("%c",vet[i]);
            }
        printf("\n");
        }
    }
    else
    {
        for(i=0; i<5; i++)
        {
            vet[pos] = aux[i];
            comb02(vet,aux,pos+1,n);
        }
    }
}

int calcula(int *vet, int x, int n){
    int i=0, aux=0;
    while(i!=(n+1)){//n+1 para ele contar quem esta na possição n tbm
       aux = aux + vet[i];
       i++;
    }
    if(aux == x)
        return 1;
    else
        return 0;
}

void combCalcula0_9(int *vet, int pos, int n, int x)
{
    int i=0, k=0, j=0;
    if(pos == n)
    {
        if(calcula(vet,x,n)){
        for (i=0; i<n; i++)
        {
           printf("%d ",vet[i]);
        }
        printf("\n");
        }
    }

    else
    {
        for(j=0; j<=9; j++)
        {
            vet[pos] = j;
            combCalcula0_9(vet,pos+1,n,x);
        }
    }

}

 void imprime(int* qtd)
{
    printf("100 centavos: %d\t",qtd[5]);
    printf("50 centavos: %d\t",qtd[4]);
    printf("25 centavos: %d\t",qtd[3]);
    printf("10 centavos: %d\t",qtd[2]);
    printf("05 centavos: %d\t",qtd[1]);
    printf("01 centavos: %d\n",qtd[0]);
}

void CombMoedas(int *qtd, int* moedas, int pos,int n)
{
        int i,y,soma;

        if(pos==6)
        {
            soma =qtd[5]*100+qtd[4]*50+qtd[3]*25+qtd[2]*10+qtd[1]*5+qtd[0]*1;
            if(soma==n)
            {
              imprime(qtd);
            }
        }
        else
        {
          y=n/moedas[pos];

          for(i=0;i<=y;i++)
          {
            qtd[pos]=i;
            CombMoedas(qtd,moedas, pos+1, n);
          }
        }
}

int menu()
{
    int op;

    printf("\nMenu de opcoes:\n");
    printf("(1) Numero de combinacoes entre 0's e 1's.\n");
    printf("(2) combinacao sem repeticao.\n");
    printf("(3) combinacoes de 0 a 9, com valor definido.\n");
    printf("(4) combinacao de moedas de valor definido.\n");
    printf("(5) Sair.\n\n");

    scanf("%d", &op);
    fflush(stdin);
    return op;
}

int main(){
int vet[]={0,0,0,0,0,0}, vetMoedas[6]={1,5,10,25,50,100};
int pos=0, contTotal=0, n, valorRes, opcao;
char vet1[6],vetc[]={'a','h','j','k','o','\0'};

    while(opcao!=5){// eee no backtracking não precisa usar o destruir, pq não tem oq destruir
        system("cls");// os vetores são estaticos, então eles vão sair quando terminar o programa
        opcao = menu();// e de resto me pergunta
        switch(opcao){// tudo funcionando 06/11/2018

        case 1:
            printf("numero de combinacoes:");
            fflush(stdin);
            scanf("%d", &n);
      		comb01(&vet,pos,n,&contTotal);
            printf("Numero de combinacoes com maior quantidade de 0's: %d \n\n", contTotal);
            contTotal = 0;
            system("pause");
            break;

        case 2:
            printf("Numero de combinacoes desejada:");
            scanf("%d", &n);
            comb02(&vet1,&vetc,pos,n);
            system("pause");
            break;

        case 3:
            printf("valor resultado: \n");
            scanf("%d", &valorRes);
            printf("Numero de combinacoes: \n");
            scanf("%d", &n);
            combCalcula0_9(&vet,pos,n,valorRes);
            system("pause");
            break;

        case 4:
            printf("digite o valor total da soma: ");
            fflush(stdin);
            scanf("%d", &valorRes);
            CombMoedas(&vet,&vetMoedas,pos,valorRes);
            system("pause");
            break;
        }
    }


}
