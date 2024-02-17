/* Gavriliu Andrei - 313CB */
//functii aferente tabelei hash
#include "thash.h"
#include "tl2.h"

TH *IniTH(size_t M, TFHash fh)//functie pentru initiere tabela hash
{
    TH *h = (TH *)calloc(1, sizeof(TH));
		if (!h) {
			printf("eroare alocare hash\n");
			return NULL;
		}
	h->v = (TL2 *) calloc(M, sizeof(TL2));
		if(!h->v) {
			printf("eroare alocare vector de pointeri TL2 in hash\n");
			free(h);
			return NULL;
		}
    h->M = M;
    h->fh = fh;
    return h;
}

void DistrTH(TH *ah, TF freeEl)//distrugere tabela hash
{
	TL2 prim, el, urm;
	TElement *element;
	int i;
		if (ah == NULL)
			return;
		if (ah->v == NULL) {
			free(ah);
			return;
		}
	
		for (i = 0; i < ah->M; i++) {//parcurgem fiecare lista a tabelei hash 
			prim = ah->v[i];//stocam primul element din lista
			if (prim != NULL) {
				for (el = prim; el != NULL; el = el->urm) {//parcurgem fiecare element din lista si il eliberam
					urm = el->urm;
					element = (TElement *)(el->info);//eliberam informatia din fiecare celula
					freeEl(element);
					free(el);
					if (urm == prim) {//cand ajungem in capatul listei facem break
						ah->v[i] = NULL;
						break;
					}
				}
			}
		}
	free(ah->v);
	free(ah);
}

int putTH(TH *a, void *ae, TFCmp f)//adaugare element in tabela hash
{
	TElement *element = (TElement *)ae;
	int cod = a->fh(element->key), rez;//calculam codul elementului
	TL2 prim, el;
	prim = a->v[cod];//salvam inceputul listei
    for (el = prim; el != NULL; el = el->urm) {//verificam ca elementul sa nu fie deja inserat
		if (f(el->info, ae) == 0)
			return 0;//intoarcem 0 in caz ca elementul exista
        if (el->urm == prim)//iesim din for cand ajungem la inceputul listei
            break;
    }

    rez = InsL2(a->v + cod, ae);//intoacem rezultatul inserarii

    return rez;//intoarcem rezultatul inserarii 
}

char *getTH(TH* ah, char *s)//functie ce intoarce valoarea unei chei date
{
	TL2 prim, el;
	int cod = ah->fh(s);//calculam codul elementului
	prim = ah->v[cod];//salvam inceputul listei
	if (prim == NULL) {
		return NULL;
	}
	for (el = prim; el != NULL; el = el->urm) {//parcurgem lista si cautam cheia data pentru a-i intoarce valoarea
		TElement *element = (TElement *)(el->info);
		if (strcmp(element->key, s) == 0) {
			return element->value;//daca am gasit cheia,intoarcem valoarea
		}
		if (el->urm == prim)//iesim din for
			break;
	}

	return NULL;//intoarcem NULL in caz de esec
}

void removeTH(TH *ah, char *key, TF freeEl)//functie ce elimina un element din tabela hash
{
	TL2 prim, el, urm, pre;
	TElement *element;
	int cod = ah->fh(key);//calculam codul hash al elementului
    prim = ah->v[cod];//salvam inceputul listei
		if (prim == NULL)
			return;
		for (el = prim; el != NULL; el = el->urm) {//iteram prin lista pana gasim elementul
			element = (TElement *)(el->info);
				if (strcmp(element->key, key) == 0) {//refacem legaturile
					urm = el->urm;
					pre = el->pre;
					pre->urm = urm;
					urm->pre = pre;
					if (el == prim) {//cazul in care vrem sa stergem primul element din lista
						if (el->urm == prim)//daca lista are un singur element atunci dispare
							ah->v[cod] = NULL;
						else
							ah->v[cod] = urm;//daca lista are mai mult de un element, capatul listei devine al doilea element
					}
					freeEl(element);
					free(el);
					return;
				}
			if (el->urm == prim)//iesim din for
				break;
		}
}

int findTH(TH* ah, char *s)//cautarea uni element in tabela
{
	TL2 prim, el;
	int cod = ah->fh(s);
	prim = ah->v[cod];//calculam codul elementului
		if (prim == NULL) {
			return 0;
		}
		for (el = prim; el != NULL; el = el->urm) {//iteram prin lista corespunzatoare si cautam elementul
			TElement *element = (TElement *)(el->info);
			if (strcmp(element->key, s) == 0) {
				return 1;//intoarcem 1 in caz de succes
			}
			if (el->urm == prim)//conditie pentru a iesi din for
				break;
		}

	return 0;//intoarcem 0 in caz de esec
}

void printTH(TH *ah, TF afiEl)//functie de afisare a tabelei
{
    TL2 prim, el;
    int i;
		for (i = 0; i < ah->M; i++) {//parcurgem tabela hash
			prim = ah->v[i];//salvam inceputul
			if (prim != NULL) {
				FILE *out=fopen(outfilename,"at");
				fprintf(out,"%d: ", i);
				fclose(out);
				for (el = prim; el != NULL; el = el->urm) {//parcurgem fiecare lista din tabela si o afisam
					afiEl(el->info);//functie de afisare a fiecarui element
					if (el->urm == prim)
						break;
				}
					FILE *out2=fopen(outfilename,"at");
					fprintf(out2,"\n");
					fclose(out2);
				
			}
		}
}
