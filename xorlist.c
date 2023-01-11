#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

typedef struct node { //Nodos de la estructura
    int val;
    struct node *npx;
}Node;

typedef struct Lista {//Estructura de la lista XOR, tiene un puntero al inicio y al final de la lista
    Node *ini, *fin;
}Lista;

Node *XOR(Node *a, Node *b){ //Funcion XOR
    return (Node*) ((intptr_t) (a) ^ (intptr_t) (b));
}

Node *new_node(int value){//Crea un nuevo nodo
    Node *newp;
    if ((newp = (Node*)malloc(sizeof(Node))) == NULL){
        fprintf(stderr,"new_node: Error reservando la memoria");
        exit(1);
    }
    newp->val = value;
    newp->npx = NULL;

    return newp;
}

int esVacia(Lista listp){ //Revisa si la lista esta vacia
    return listp.ini==NULL;
}

int insertarPrincipio(Lista *listp, int value){//inserta un elemento al inicio
    Node *p = new_node(value);
    Node *curr = (*listp).ini;
    p->npx =XOR(curr, NULL);


    if(!esVacia(*listp)){ //actualiza la direccion del primer elemento actual de la lista
        Node *next = XOR(curr->npx, NULL);
        curr->npx = XOR(p, next);
    }else{
        (*listp).fin = p;//Si la lista esta vacia solo agrega ese nodo
    }

    if(((*listp).ini = p)!=NULL)//Coloca al nuevo elemento como el inicio de la lista
        return 1;
    return 0;
}


int insertarFinal(Lista *listp, int value){//agrega un elemento al final
    Node *p = new_node(value);
    Node *final = (*listp).fin;
    if(!esVacia(*listp)){          //revisa si la lista esta vacia
        p->npx = XOR(final, NULL);

        final->npx = XOR(XOR(final->npx,NULL),p);//actualiza la direccion del ultimo elemento
    }else
        (*listp).ini = p;    //si lalista esta vacia solo agrega el nuevo nodo
    if(((*listp).fin = p)!=NULL)//Coloca el nuevo elemento como el final de la lista
	return 1;
    return 0;
}
int sacarInicio(Lista *listp, int *e){//Saca el primer elemento de la lista
    if(!esVacia(*listp)){            // Revisa si la lista esta vacia
        Node *tmp = XOR(NULL,(*listp).ini->npx);
        if (tmp != NULL)
            (tmp)->npx = XOR(NULL, XOR( (*listp).ini,(tmp)->npx) ); //Cambia la direccion del siguiente elemento (Si es que existe)
        else
            (*listp).fin = NULL;
        *e = (*listp).ini->val;
        free((*listp).ini);	//Libera la memoria del nodo
        (*listp).ini = tmp;    //Coloca el siguiente elemento como el inicio de la lista

        return 1;
    }
    *e = 0;
    return 0; //Devuelve cero si no se elimino ningun nodo
}


int sacarFinal(Lista *listp, int *e){ //Saca el ultimo elemento de la lista
    if(!esVacia(*listp)){		//Revisa si la lista esta vacia
        Node *final = (*listp).fin;

        Node *tmp = XOR(NULL,(final)->npx);
        if (tmp != NULL)
            (tmp)->npx = XOR(NULL, XOR( final,(tmp)->npx) ); //Cambia la direccion del elemento anterior si es que existe
        else
            (*listp).ini = tmp;
        *e = (final)->val;
        free(final);			//libera la memoria
        final = tmp;
        (*listp).fin = final;
        return 1;
    }
    *e = 0;
    return 0;   ///Devuelve cero si no se elimino ningun elemento
}

void listarInicioAFinal (Lista listp){//muestra en pantalla los elementos de inicio a fin
    Node *curr = listp.ini;
    Node *prev = NULL;
    Node *next;
    printf("-->");
    while( curr!=NULL){
        printf("%i-->", curr->val);//recorre la lista y va imprimiendo los valores
        next = XOR(prev, curr->npx);

        prev = curr;
        curr = next;
    }
    printf("NULL\n");
}
void listarFinalAInicio (Lista listp){//muestra en pantalla los elementos de fin a inicio
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

void inicializar(Lista *listp){//Inicializa la lista
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


int cantidadElementos(Lista listp){//Cuenta los elementos de la lista
    Node *prev = NULL, *next, *curr = listp.ini;
    int contador = 0;
    while(curr!=NULL){ //Recorre la lista con un contador
        ++contador;
        next = XOR(prev,curr->npx);
        prev = curr;
        curr = next;
    }
    return contador;
}
int buscar(Lista listp, int e){//Busca la primera aparicion de un elemento
    Node *prev = NULL,*next, *curr=listp.ini;
    int posicion = 0;
    while(curr!=NULL){//Recorre la lista hasta encontrarlo
        if(curr->val == e)//si lo encuentra devuelve su posicion
            return posicion;
        ++posicion;
        next = XOR(prev,curr->npx);
        prev = curr;
        curr = next;
    }
    return -1; //Sino devuelve -1
}


int insertarOrden(Lista *listp, int e){//inserta un elemento ordenado
    Node *p = new_node(e);
    p->npx = NULL;

    if(esVacia(*listp)){
        (*listp).ini = (*listp).fin = p;
        return 1;
    }

    Node *prev = NULL;
    Node *curr = (*listp).ini;
    Node *next = NULL;
    while(curr!=NULL && curr->val < e){ //Recorre la lista y guarda la ultima posicion en la que se debe insertar el nuevo elemento
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }

    if (prev == NULL){		//Si el elemento se tiene que insertar al inicio
        insertarPrincipio(&(*listp), e);
        return 1;
    }

    if (curr == NULL){		//Si el elemento se tiene que insertar al final
        insertarFinal(&(*listp), e);
        return 1;
    }
/*
    Node *aux1 = prev;
    prev->npx = XOR( XOR(curr, prev->npx), p);
    curr->npx = XOR (p, XOR(aux1, curr->npx));
    p->npx = XOR(prev, curr);
    return 1;
*/				//Si el elemento se tiene que insertar en una posicion intermedia
    p->npx = XOR( prev,curr);
    prev->npx = XOR(XOR(prev->npx,curr),p);
    curr->npx = XOR(XOR(curr->npx,prev),p);
    return 1;
}


int sacarPrimeraOcurrencia(Lista *listp, int e){//Saca la primera ocurrencia de un elemento
    Node *prev = NULL,*next, *curr = (*listp).ini;

    while(curr!=NULL){

        next = XOR(prev,curr->npx);

        if(curr->val == e){		//Recorre la lista hasta encontrar el elemento
            if (prev != NULL)
                prev->npx = XOR( XOR(prev->npx, curr) ,  next); //Se actualizan las direcciones de los nodos vecinos
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
    return 0; //Si no se encuentra devuelve cero
}
