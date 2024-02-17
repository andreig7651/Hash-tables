/* Gavriliu Andrei - 313CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tl2.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (* TFElem)(void *);     /* functie prelucrare element */
typedef int (* TFCmp)(void *, void *); /* functie de comparare doua elemente */
typedef void (* TF)(void *);     /* functie afisare/eliberare un element */
typedef int (* TFHash)(char *);

typedef struct
{
    size_t M;
    TFHash fh;
    TL2 *v;
} TH;//declarare structura tabela hash

/* functii tabela hash */
TH *IniTH(size_t M, TFHash fh);//initiere tabela hash
void DistrTH(TH *ah, TF fe);//distrugere tabela hash
int cmpElement(void *e1, void *e2);//comparare elemente lista
int putTH(TH *ah, void *ae, TFCmp f);//adaugare element in tabela hash
char *getTH(TH *ah, char *s);//intoarce valoarea unei chei date
void removeTH(TH *ah, char *s,TF freeEl);//stergere element din tabela hash
int findTH(TH *ah, char *s);//cautare dupa cheie in tabela hash
void printTH(TH *ah, TF afiEl);//afisare tabela hash


#endif