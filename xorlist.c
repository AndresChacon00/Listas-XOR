#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

typedef struct node {
    int val;
    struct node *npx;
}Node;

typedef struct Lista {
    Node *ini, *fin;
}Lista;

Node *XOR(Node *a, Node *b){
    return (Node*) ((intptr_t) (a) ^ (intptr_t) (b));
}

Node *new_node(int value){
    Node *newp;
    if ((newp = (Node*)malloc(sizeof(Node))) == NULL){
        fprintf(stderr,"new_node: Error reservando la memoria");
        exit(1);
    }
    newp->val = value;
    newp->npx = NULL;

    return newp;
}

int esVacia(Lista listp){
    return listp.ini==NULL;
}

int insertarPrincipio(Lista *listp, int value){
    Node *p = new_node(value);
    Node *curr = (*listp).ini;
    p->npx =XOR(curr, NULL);


    if(!esVacia(*listp)){
        Node *next = XOR(curr->npx, NULL);
        curr->npx = XOR(p, next);
    }else{
        (*listp).fin = p;
    }

    if(((*listp).ini = p)!=NULL)
        return 1;
    return 0;
}


int insertarFinal(Lista *listp, int value){
    Node *p = new_node(value);
    Node *final = (*listp).fin;
    if(!esVacia(*listp)){
        p->npx = XOR(final, NULL);

        final->npx = XOR(XOR(final->npx,NULL),p);
    }else
        (*listp).ini = p;
    if(((*listp).fin = p)!=NULL)
	return 1;
    return 0;
}
int sacarInicio(Lista *listp, int *e){
    if(!esVacia(*listp)){
        Node *tmp = XOR(NULL,(*listp).ini->npx);
        if (tmp != NULL)
            (tmp)->npx = XOR(NULL, XOR( (*listp).ini,(tmp)->npx) );
        else
            (*listp).fin = NULL;
        *e = (*listp).ini->val;
        free((*listp).ini);
        (*listp).ini = tmp;

        return 1;
    }
    *e = 0;
    return 0;
}


int sacarFinal(Lista *listp, int *e){
    if(!esVacia(*listp)){
        Node *final = (*listp).fin;

        Node *tmp = XOR(NULL,(final)->npx);
        if (tmp != NULL)
            (tmp)->npx = XOR(NULL, XOR( final,(tmp)->npx) );
        else
            (*listp).ini = tmp;
        *e = (final)->val;
        free(final);
        final = tmp;
        (*listp).fin = final;
        return 1;
    }
    *e = 0;
    return 0;
}

void listarInicioAFinal (Lista listp){
    Node *curr = listp.ini;
    Node *prev = NULL;
    Node *next;
    printf("-->");
    while( curr!=NULL){
        printf("%i-->", curr->val);
        next = XOR(prev, curr->npx);

        prev = curr;
        curr = next;
    }
    printf("NULL\n");
}
void listarFinalAInicio (Lista listp){
    Node *curr = listp.fin;
    Node *prev = NULL;
    Node *next;
    printf("-->");
    while(curr!=NULL){
        printf("%i-->",curr->val);
        next = XOR(prev, curr->npx);

        prev = curr;
        curr = next;
    }
    printf("NULL\n");
}

void inicializar(Lista *listp){
    Node *prev = NULL;
    Node *curr = listp->ini;
    while(curr != NULL){
        Node *tmp = XOR(prev, curr->npx);
        prev = curr;
        free(curr);
        curr = tmp;
    }
    listp->ini = listp->fin = NULL;
}


int cantidadElementos(Lista listp){
    Node *prev = NULL, *next, *curr = listp.ini;
    int contador = 0;
    while(curr!=NULL){
        ++contador;
        next = XOR(prev,curr->npx);
        prev = curr;
        curr = next;
    }
    return contador;
}
int buscar(Lista listp, int e){
    Node *prev = NULL,*next, *curr=listp.ini;
    int posicion = 0;
    while(curr!=NULL){
        if(curr->val == e)
            return posicion;
        ++posicion;
        next = XOR(prev,curr->npx);
        prev = curr;
        curr = next;
    }
    return -1;
}


int insertarOrden(Lista *listp, int e){
    Node *p = new_node(e);
    p->npx = NULL;

    if(esVacia(*listp)){
        (*listp).ini = (*listp).fin = p;
        return 1;
    }

    Node *prev = NULL;
    Node *curr = (*listp).ini;
    Node *next = NULL;
    while(curr!=NULL && curr->val < e){
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }

    if (prev == NULL){
        insertarPrincipio(&(*listp), e);
        return 1;
    }

    if (curr == NULL){
        insertarFinal(&(*listp), e);
        return 1;
    }
/*
    Node *aux1 = prev;
    prev->npx = XOR( XOR(curr, prev->npx), p);
    curr->npx = XOR (p, XOR(aux1, curr->npx));
    p->npx = XOR(prev, curr);
    return 1;
*/
    p->npx = XOR( prev,curr);
    prev->npx = XOR(XOR(prev->npx,curr),p);
    curr->npx = XOR(XOR(curr->npx,prev),p);
    return 1;
}


int sacarPrimeraOcurrencia(Lista *listp, int e){
    Node *prev = NULL,*next, *curr = (*listp).ini;

    while(curr!=NULL){

        next = XOR(prev,curr->npx);

        if(curr->val == e){
            if (prev != NULL)
                prev->npx = XOR( XOR(prev->npx, curr) ,  next);
            if (next != NULL)
                next->npx = XOR( prev , XOR(curr, next->npx));
            if(prev == NULL)
                (*listp).ini = next;
            if(next == NULL)
                (*listp).fin = prev;
            return 1;
        }
        prev = curr;
        curr = next;

    }
    return 0;
}
