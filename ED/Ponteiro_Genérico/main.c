#include <stdio.h>
#include <stdlib.h>
#include "FilaVoid.h"
#include <string.h>
/*-
 -
 --Ruan de Almeida
 --Trabalho de Hash
 -
 -*/
typedef struct pessoa
{
    char nome[41];
    int  idade;
    int  cpf;
}Pessoa;
int main()
{
    int op,id;
    Pessoa *a;
    FilaV b = IncializaV();

        do{
                printf("\n*************************\n");
                printf("1 - Inserir uma pessoa.\n");
                printf("2 - Remover pessoa pelo ID\n");
                printf("3 - Verificar se ha pessoas na fila.\n");
                printf("4 - Verificar se a fila ta vazia. \n");
                printf("5 - Sair\nop -> ");

                scanf("%d",&op);

                switch(op){

                        case 1 :
                                a=(Pessoa*)malloc(sizeof(Pessoa));
                                printf("\nInforme o nome: ");
                                setbuf(stdin,NULL);
                                scanf(" %[^\n]",a->nome);
                                printf("\nIdade: ");
                                setbuf(stdin,NULL);
                                scanf("%d",&a->idade);
                                printf("\nCPF : ");
                                setbuf(stdin,NULL);
                                scanf("%d",&a->cpf);
                                printf("Digite um id: ");
                                scanf("%d",&id);
                                PushV(b,a,id); // estamos falando para o compilador que ´tipo é pessooa
                        break;

                        case 2 :
                            op=VaziaV(b);
                            if(op!=1){
                            op=PopV(b);
                            printf("A pessoa com o ID %d foi removida\n ",op);
                            }else{
                                printf("\n********* Não pessoas na fila *************\n");
                            }
                        break;

                        case 3:// ?
                            op = CheiaV(b);
                            if(op==1)
                                printf("Fila esta cheia de pessoas"); // tem que ser int, nao? retornar sim ou nao
                            else
                                printf("Nao ha pessoas na fila");
                        break;

                        case 4:
                            op = VaziaV(b);
                            if(op!=1)
                                printf("Tem pessoas na fila");
                            else
                                printf("Nao tem pessoas na fila ");
                        break;

                        case 5:
                                DestruirV (b);
                                exit(1);
                        break;
                        default : printf("\n\n");
                        system("cls");
                }
        }while(op!=5);
    return 0;
}
