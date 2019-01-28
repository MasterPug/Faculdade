#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "avl.h"

int main(void)
{
    AVL a = inicializar(a);
    int opcao, x, y, v, cont;

    while(opcao != 7)
    {
        Sleep(3500);
        system("cls");
        opcao = menu();

        switch(opcao)
        {
            case 1:
                a=Ler(a);
                break;

            case 2:{


            	int mudou = 0;
                printf("Digite o numero a ser inserido:\n");
                scanf("%d", &x);
                a = Inserir(a, x);
                break;
				}

            case 3:{

            	int mudou = 0;
                printf("Digite o numero a ser removido:\n");
                scanf("%d", &x);
                a = Remover(a, x);
                break;
					}

            case 4:
                ImprimeLargura(a);
                break;

            case 5:
                printf("\nDigite o numero que deseja verificar:\n");
                scanf("%d", &x);
                v=Existe(a, x);
                if(v == 1)
                    printf("O numero existe na arvore.");
                else
                    printf("O numero nao aparece na arvore");
                break;

            case 6:
                Destruir(a);
                opcao = 7;
                break;

        }
    }

    return 0;
}
