/* Gavriliu Andrei - 313CB */
/*-- tl2h --- LISTA DUBLU INLANTUITA GENERICA CIRCULARA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

int M;//dimensiunea maxima a tabelei hash
char infilename[50];//fisier de intrare
char outfilename[50];//fisier de iesire

typedef struct celula2
{
    void* info;
    struct celula2 *urm;
    struct celula2 *pre;
    
} TCelula2, *TL2;//declarare element de tip lista

typedef struct
{
    char *key;
    char *value;
    
} TElement;//declarare informatie din lista

typedef int (* TFElem)(void *);     /* functie prelucrare element */
typedef int (* TFCmp)(void *, void *); /* functie de comparare doua elemente */
typedef void (* TF)(void *);     /* functie afisare/eliberare un element */

/* functii lista generica */
int InsL2(TL2 *al, void *ae);  /*inserare la sfarsitul listei reusita sau nu (1/0)*/
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void print_bucket(TL2 al, TF afiEl);


#endif