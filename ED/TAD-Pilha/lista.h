typedef struct Lista * lista;

lista Inicializar(lista a);

int Vazia(lista a);

lista InserirPilha(lista a, int x);

lista InserirFila(lista a, int x);

lista Remover(lista a);

int Cheia(lista a);

int conta(lista a);

void Imprime(lista a);

void Destruir(lista a);
