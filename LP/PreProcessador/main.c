/*ta tudo desarrumado nesse inicio pq eu estava testando como as coisas podem ficar sem dar erro
*/
#include <stdio.h>#include <stdlib.h>
int linhas=1;
int main()  {int d,k;
    scanf("%d",
          &d);
    printf("Hello world!\n");
    return 0;
}
/* vamos receber o arquivo inicial e tirar os comentarios fazendo um outro arquivo, o  "saida"
    aproveitamos e pegamos o nome das bibliotecas

    No meu computador eu achei as bibliotecas em:
    C:\MinGW\include

    */
char *ler(FILE *entrada, FILE *saida){      //não esta finalizada
    int i,j;
    char *palavra=(char*)malloc(100*sizeof(char*)), *bibli=(char*)malloc(15*sizeof(char));
    for(i=0; i<linhas; i++){
        fscanf(entrada, " %s", palavra);
        for(j=0; j<99; j++){    //precisa consertar o if para o caso em que usa o "/*", pois desse jeito só vai pular 1 linha e as demais
                                //linhas do comentario vão continuar no arquivo
            if(!((palavra[j]=='/' && palavra[j+1]=='*') || (palavra[j]=='/' && palavra[j+1]=='/')))
            fprintf(saida,"%s", palavra);       //botei sem \n para ja tirar de uma vez
        }
    }
    /*colocarr função que eu não lembro o nome dentro de um if, assim veremos se tem um "#include" e se precisa adicionar uma biblioteca*/
    free(palavra);
    return bibli;
}

void tamanho(FILE *arq){
    char c;
    linhas=1;   //variavel global
    while ((c = fgetc(arq)) != EOF)
    {
        if (c == '\n')
        linhas++;
    }
}
