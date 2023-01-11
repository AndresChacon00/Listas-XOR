#Archivo de manejo de listas xor
xorlist.o: xorlist.h xorlist.c
	gcc -Wall -g -c xorlist.c -o xorlist.o

#Programa principal
proy2: proy2.c xorlist.o
	gcc -Wall -g -o proy2 proy2.c xorlist.o

