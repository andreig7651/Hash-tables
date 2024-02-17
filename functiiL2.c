/* Gavriliu Andrei - 313CB */
/*--- functiiLG.c -- operatii de baza pentru lista dublu inlantuita generica circulara---*/
#include "tl2.h"

int cmpElement(void *e1, void *e2)//functie pentru compararea a doua elemente
{
	TElement *element1 = (TElement *)e1;
	TElement *element2 = (TElement *)e2;
	//avem trei cazuri la comparare 
	if (strcmp(element1->key, element2->key) < 0)
		return -1;
	if (strcmp(element1->key, element2->key) > 0)
		return 1;
	return 0;
}

void OrdoneazaL2(TL2 aL)//functie pentru ordonarea listei
{
	TL2 prim,el,el1,prim1;
	void *aux;
		if (aL == NULL) {
			return;
		}
	prim = aL;//salvam inceputul listei
		for (el = prim; el != NULL; el = el->urm) {//iteram prin lista
			prim1=el;//salvam punctul de unde incepe iteratia
			//concomitent iteram prin lista de la pozitia urmatoare pozitiei initiale
			for (el1 = prim1->urm; el1 != NULL; el1 = el1->urm){
				if(cmpElement(el->info,el1->info)==-1)//comparam cele doua informatii 
					{aux=el->info;//efectuam interschimbarea
					el->info=el1->info;
					el1->info=aux;}
				if (el1->urm == prim1)//conditie de iesire din al doilea for
					break;
			
			}
			
			if (el->urm == prim)//conditie de iesire din primul for
				break;
		}
}

int InsL2(TL2 *aL, void* ae)
{
	TL2 prim, ultim, c = malloc(sizeof(TCelula2));
		if (c == NULL)
			return 0;
		if ((*aL) != NULL) {
			//adaugare element intr-o lista existenta si actualizare legaturi
			prim = (*aL);
			ultim = prim->pre;
			c->info = ae;
			ultim->urm = c;
			c->pre = ultim;
			c->urm = prim;
			prim->pre = c;
		} else {
			//adauga primul element intr-o lista vida
			c->info = ae;
			c->urm = c;
			c->pre = c;
			*aL = c;
		}
	OrdoneazaL2(*aL);//ordonam lista dupa fiecare inserare
    return 1;
}


void print_bucket(TL2 aL, TF afiEl)
{
	TL2 prim, el;
	if (aL == NULL) {//afisam "VIDA" in cazul unei liste vide
		FILE *out3=fopen(outfilename,"at");
        fprintf(out3,"VIDA\n");
		fclose(out3);
        return;
    }
	prim = aL;//salvam inceputul listei
	for (el = prim; el != NULL; el = el->urm) {//iteram prin lista si afisam fiecare element
		afiEl(el->info);
		if (el->urm == prim)//conditie pentru a iesi din for
			break;
	}
	FILE *out7=fopen(outfilename,"at");
        fprintf(out7,"\n");
		fclose(out7);
}
