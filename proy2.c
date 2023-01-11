#include<stdio.h>
#include "xorlist.h"
int main(){
    Lista list = {NULL, NULL};
    inicializar(&list);
    int opcion=0;
    printf("*****  Listas XOR   ******");
    while(opcion >= 0 && opcion <= 11){
        printf("\nSeleccione la accion a realizar \n");
        printf("1: Inicializar lista \n");
        printf("2: Insertar al principio\n");
        printf("3: Insertar al final \n");
        printf("4: Insertar ordenado\n");
        printf("5: Buscar elemento\n");
        printf("6: Sacar principio\n");
        printf("7: Sacar final\n");
        printf("8: Sacar primera ocurrencia\n");
        printf("9: Listar inicio a final\n");
        printf("10: Listar final a inicio\n");
        printf("11: Cantidad de elementos\n");
        printf("12: Salir\n");

        scanf("%i",&opcion);

        while(opcion<1 || opcion > 12 ){
            printf("Opcion no valida, ingrese nuevamente\n");
            scanf("%i",&opcion);
        }

        if(opcion == 1){
            inicializar(&list);
        }
        if(opcion == 2){
            printf("Ingrese el elemento para insertar al  frente:\n");
            int e;
            scanf("%i",&e);
            insertarPrincipio(&list,e);
        }
        if(opcion == 3){
            printf("Ingrese el elemento para insertar al  final:\n");
            int e;
            scanf("%i",&e);
            insertarFinal(&list,e);
        }
        if(opcion == 4){
            printf("Ingrese el elemento para insertar ordenado:\n");
            int e;
            scanf("%i",&e);
            insertarOrden(&list,e);
        }
        if(opcion == 5){
            printf("Ingrese el elemento a buscar:\n");
            int e;
            scanf("%i",&e);
            int pos = buscar(list,e);
            if(pos!=-1){
                printf("El elemento se encuentra en la posicion %i\n",pos);
            }
            else
                printf("No se encontro el elemento\n");
        }
        if(opcion == 6){
            int e;
            if(sacarInicio(&list,&e))
                printf("Se elimino el elemento %i\n",e);
            else
                printf("No se elimino ningun elemento\n");
        }
        if(opcion == 7){
            int e;
            if(sacarFinal(&list,&e))
                printf("Se elimino el elemento %i\n",e);
            else
                printf("No se elimino ningun elemento\n");
        }
        if(opcion == 8){
            int e;
            printf("Ingrese el elemento a eliminar: \n");
            scanf("%i",&e);
            if(sacarPrimeraOcurrencia(&list,e))
                printf("Se elimino el elemento %i\n",e);
            else
                printf("No se elimino ningun elemento\n");
        }
        if(opcion == 9){
            listarInicioAFinal(list);
        }
        if(opcion == 10){
            listarFinalAInicio(list);
        }
        if(opcion == 11){
            printf("La lista tiene %i elementos\n",cantidadElementos(list));
        }
    }
    listarInicioAFinal(list);
    printf("\n Gracias por usar el editor de listas XOR \n");
    return 0;
}
