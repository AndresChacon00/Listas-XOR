#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node *npx;
}Node;

typedef struct Lista {
    Node *ini, *fin;
}Lista;

void inicializar(Lista *listp);
Node *XOR(Node *a, Node *b);
Node *new_node(int value);
int esVacia(Lista listp);
int insertarPrincipio(Lista *listp, int value);
int insertarFinal(Lista *listp, int value);
int insertarOrden(Lista *listp, int e);
int buscar(Lista listp, int e);
int sacarInicio(Lista *listp, int *e);
int sacarFinal(Lista *listp, int *e);
int sacarPrimeraOcurrencia(Lista *listp, int e);
void listarInicioAFinal (Lista listp);
void listarFinalAInicio (Lista listp);
int cantidadElementos(Lista listp);
