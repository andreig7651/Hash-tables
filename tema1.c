/* Gavriliu Andrei - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tl2.h"
#include "thash.h"

int codHash(char *key)//functie pentru calcularea codului hash
{
	int s = 0;
    for(; *key != '\0'; key++)//calculam suma codurilor ascii ale cuvantului
        s = s + *key;
    return s%M;
}

void afisareElement(void *e)//functia pentru afisarea in fisier a elementului
{
	TElement *element = (TElement *)e;
	FILE *out=fopen(outfilename, "at");
	fprintf(out,"%s ", element->value);
	fclose(out);
}

void distrElement(void *e)//functie pentru distrugerea unui element
{
	TElement *element = (TElement *)e;
	if (element != NULL) {
		if (element->key != NULL)
			free(element->key);
		if (element->value != NULL)
			free(element->value);
		free(element);
	}
}

void eliberareMemorie(TH *h, char *line, FILE *f)//functie pentru eliberarea
{
	DistrTH(h, distrElement);//eliberare tabela hash
	if (line != NULL)
		free(line);
	if (f != NULL)
		fclose(f);
}

int main(int argc, char **argv)
{
	FILE *f = NULL;
	TElement *element;
	if(argv[1]!=NULL)//citire argumentelor din linia de comanda
		M=atoi(argv[1]);
	else
		return 0;
	
	if(argv[2]!=NULL)//citire argumentelor din linia de comanda
		strcpy (infilename,argv[2]);
	else
		return 0;
	
	if(argv[3]!=NULL)//citire argumentelor din linia de comanda
		strcpy (outfilename,argv[3]);
	else
		return 0;
    
	char *line = NULL;
	size_t len = 80; //dimensiunea maxima a unei linii in fisierul de intrare
    TH *h = NULL;
    h = (TH *)IniTH(M, codHash);//initializare tabela hash
		if (h == NULL)
			return 0;
	line = (char *)malloc(len * sizeof(char));
		if (line == NULL) {
			printf("eroare alocare buffer citire din fisierul de intrare\n");
			eliberareMemorie(h, line, f);
			return 0;
		}

    f = fopen(infilename, "rt");//deschidere fisier pentru citire
		if (f == NULL) {
			printf("eroare deschidere fisier de intrare\n");
			eliberareMemorie(h, line, f);
			return 0;
		}

	
	while (fgets(line, len, f) != NULL) {
        char *operatia1 = strtok(line, "\0"), *operatia = strtok(line, " ");//primul cuvant de pe fiecare linie din fisier
			if (operatia1[strlen(operatia1) - 1] == '\n')//escapare caracter final
				operatia1[strlen(operatia1) - 1] = '\0';
			if (operatia1[strlen(operatia1) - 1] == '\r')
				operatia1[strlen(operatia1) - 1] = '\0';
		
			if (strcmp(operatia, "put") == 0) {
				char *key = strtok(NULL, " ");//salvam cheia in pointerul key
				char *value = strtok(NULL, " ");//salvam valoarea in pointerul key
					if (value[strlen(value) - 1] == '\n')//escapare caracter final
						value[strlen(value) - 1] = '\0';
					if (value[strlen(value) - 1] == '\r')
						value[strlen(value) - 1] = '\0';
					if (key[strlen(value) - 1] == ' ')
						value[strlen(value) - 1] = '\0';
			
				element = (TElement *)malloc(sizeof(TElement));//alocam informatia din celula(elementul)
					if (element == NULL) {
						printf("%s:%s %s - %s\n", operatia, key, value, "eroare alocare element");
						continue;//instructiune pentru a trece la bucla urmatoare
					}
				element->key = strdup(key);
				element->value = strdup(value);
					if (element->key == NULL || element->value == NULL) {
						distrElement(element);
						printf("%s:%s %s - %s\n", operatia, key, value, "eroare alocare element");
						continue;
					}
				int rez = putTH(h, element, cmpElement);//stocam rezultatul adaugarii in tabela hash,0 pentru esec si 1 pentru succes 
					if (rez == 0) {
						//elementul nu a fost inserat pentru ca exista deja sau pentru ca a esuat operatia de alocare
						distrElement(element);
					}
			}
        	
			if (strcmp(operatia, "get") == 0) {
            	char *key = strtok(NULL, " ");//salvam cheia in pointerul key
					if (key[strlen(key) - 1] == '\n')//escapam caracterul final
						key[strlen(key) - 1] = '\0';
					if (key[strlen(key) - 1] == '\r')
						key[strlen(key) - 1] = '\0';
			
				char *value = getTH(h, key);//stocam valoarea de la cheia data sau NULL daca nu exista
				FILE *out=fopen(outfilename,"at");
					if (value == NULL) {
						fprintf(out,"NULL\n");
					} else {
						fprintf(out,"%s\n", value);
					}
				fclose(out);
        	}

        	if (strcmp(operatia, "remove") == 0) {
            	char *key = strtok(NULL, " ");//salvam cheia in key
					if (key[strlen(key) - 1] == '\n')//escapam caracterul final
						key[strlen(key) - 1] = '\0';
					if (key[strlen(key) - 1] == '\r')
						key[strlen(key) - 1] = '\0';

				removeTH(h, key, distrElement);//eliminam elementul din tabela
			}

        	if (strcmp(operatia, "find") == 0) {
            	char *key = strtok(NULL, " ");//salvam cheia in key
            		if (key[strlen(key) - 1] == '\n')//escapam caracterul final
			    		key[strlen(key) - 1] = '\0';
            		if (key[strlen(key) - 1] == '\r')
			    		key[strlen(key) - 1] = '\0';

				int found = findTH(h, key);//apelam functia found ce intoarce ca rezultat 0 in caz de esec si 1 in caz de succes
				FILE *out=fopen(outfilename,"at");
					if (found == 1)
						fprintf(out,"True\n");
					else
						fprintf(out,"False\n");
				fclose(out);
        	}
        	
			if (strcmp(operatia1 ,"print") == 0) {
				printTH(h, afisareElement);//afisare tabela hash
			}
        
			if (strcmp(operatia, "print_bucket") == 0) {
            	char *numar = strtok(NULL, " ");//salvam numarul bucket-ului dorit in numar
            		if (numar[strlen(numar) - 1] == '\n')//escapam caracterul final
			    		numar[strlen(numar) - 1] = '\0';
            		if (numar[strlen(numar) - 1] == '\r')
			    		numar[strlen(numar) - 1] = '\0';
				int n = atoi(numar);//convertim in intreg
					if (n < M)//afisam bucket-ul doar daca acesta se gaseste in dimensiunile listei
						print_bucket(h->v[n], afisareElement);//afisam bucket-ul(lista)
        	}
    }

	eliberareMemorie(h, line, f);//eliberam meomria
	
	return 0;
}

