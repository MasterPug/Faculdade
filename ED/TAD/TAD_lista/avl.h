/*-
 -
 --Ruan de Almeida
 --Trabalho de Estrutura de dados
 -
 -*/

typedef struct arvore *AVL;

AVL inicializar(AVL a);

void Destruir(AVL a);

AVL Ler(AVL a);

AVL Inserir(AVL a, int x);

AVL Remover(AVL a, int x);

int Existe(AVL a, int x);

void ImprimeLargura(AVL a);
