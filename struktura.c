#include "bazadanych.h"

int czyIstniejeDzial(char *nazwa)
{
	struct Dzial *it = poczatek;
	while(it != NULL){
		if(!strcmp(nazwa, it->nazwa))
			return 1;
		it = it->nastepny;
	}
	return 0;
}

void zerujDzial(struct Dzial *x)
{
	int i = 0;

	for(i = 0; i < MAXDZIAL; i++)
		x->nazwa[i] = 0;
	x->nastepny = NULL;
	x->pierwsza = NULL;
}

void zerujGazete(struct Gazeta *x)
{
	int i = 0;

	for(i = 0; i < MAXNAZWA; i++)
		x->nazwa[i] = 0;
	for(i = 0; i < MAXNUMER; i++)
		x->numer[i] = 0;
	for(i = 0; i < MAXCZESTOSC; i++)
		x->czestosc[i] = 0;
	x->nastepna = NULL;
}

void usun(struct Dzial *y)
{
	struct Gazeta *a = NULL, *b = NULL;

	a = y->pierwsza;

	while(a != NULL)
	{
		b = a->nastepna;
		a->nastepna = NULL;
		ID[atoi(a->numer)] = 0;
		zerujGazete(a);
		free(a);
		a = b;
	}

	free(y);
}

void usunDzial(struct Dzial *c, struct Dzial *pocz)
{
	struct Dzial *d = pocz;

	while(d->nastepny != c && d != NULL)
		d = d->nastepny;

	d->nastepny = c->nastepny;
	usun(c);
}

struct Dzial *znajdzDzial(char *nazwa)
{
	struct Dzial *pom = poczatek;

	while(pom != NULL){
		if(strcmp(nazwa, pom->nazwa) == 0)
			return pom;
		pom = pom->nastepny;
	}

	return NULL;
}

struct Gazeta *znajdzGazete(char *numer)
{
	struct Dzial *y = poczatek;
	struct Gazeta *x = NULL;

	while(y != NULL)
	{
		x = y->pierwsza;
		while(x != NULL){
			if(!strcmp(x->numer, numer))
				return x;
			x = x->nastepna;
			}
		y = y->nastepny;
	}

	return NULL;
}

void utworzDzial(char *nazwa)
{
	struct Dzial *pom = poczatek;

	if(nazwa[0] >= 'a' && nazwa[0] <= 'z')
		nazwa[0] += 'A' - 'a';

	if(poczatek == NULL)
	{
		poczatek = malloc(sizeof(struct Dzial));
		if(poczatek == NULL){
			printf("Nie udalo sie utworzyc nowego dzialu.\n");
			return;
		}

		zerujDzial(poczatek);
		strcpy(poczatek->nazwa, nazwa);
		return;
	}

	while(pom->nastepny != NULL)
		pom = pom->nastepny;

	pom->nastepny = malloc(sizeof(struct Dzial));
	if(pom->nastepny == NULL){
		printf("Nie udalo sie utworzyc nowego dzialu.\n");
		return;
	}

	zerujDzial(pom->nastepny);
	strcpy(pom->nastepny->nazwa, nazwa);
	return;
}

void utworzGazete(struct Dzial *pocz, char *dzial, char *nazwa, char *numer, char *czestosc)
{
	struct Dzial *y = pocz;
	struct Gazeta *x = NULL;

	if(dzial[0] >= 'a' && dzial[0] <= 'z')
		dzial[0] += 'A' - 'a';
	if(nazwa[0] >= 'a' && nazwa[0] <= 'z')
		nazwa[0] += 'A' - 'a';

	if(pocz == NULL){
		printf("Nie mozna dodac gazety. Prosze najpierw utworzyc przynajmniej jeden dzial.\n");
		return;
	}

	while(y != NULL && strcmp(y->nazwa, dzial))
		y = y->nastepny;

	if(y == NULL){
		printf("Nie udalo sie dodac nowej gazety.\n");
		return;
	}

	x = y->pierwsza;

	if(y->pierwsza == NULL){
		y->pierwsza = malloc(sizeof(struct Gazeta));
		if(y->pierwsza == NULL){
			printf("Nie udalo sie dodac nowej gazety.\n");
			return;
		}

		zerujGazete(y->pierwsza);
		strcpy(y->pierwsza->nazwa, nazwa);
		strcpy(y->pierwsza->numer, numer);
		strcpy(y->pierwsza->czestosc, czestosc);
		return;
	}

	while(x->nastepna != NULL)
		x = x->nastepna;

	x->nastepna = malloc(sizeof(struct Gazeta));
	if(x->nastepna == NULL){
		printf("Nie udalo sie dodac nowej gazety.\n");
		return;
	}

	zerujGazete(x->nastepna);
	strcpy(x->nastepna->nazwa, nazwa);
	strcpy(x->nastepna->numer, numer);
	strcpy(x->nastepna->czestosc, czestosc);
	ID[atoi(numer)] = 1;

	return;
}

void posprzataj()
{
	struct Dzial *y = poczatek, *pom = NULL;

	while(y != NULL){
		pom = y->nastepny;
		usun(y);
		y = pom;
	}
}

void sortuj()
{
	struct Dzial *a = poczatek, *b = poczatek;
	struct Gazeta *x = NULL, *y = NULL;

	while(a != NULL){
		b = poczatek;
		while(b->nastepny != NULL){
			if(strcmp(b->nazwa, b->nastepny->nazwa) > 0)
				zamienDzialy(b, b->nastepny);
			b = b->nastepny;
		}
		a = a->nastepny;
	}

	a = poczatek;

	while(a != NULL){
		x = a->pierwsza;
		while(x != NULL){
			y = a->pierwsza;
			while(y->nastepna != NULL){
				if(strcmp(y->nazwa, y->nastepna->nazwa) > 0)
					zamienGazety(y, y->nastepna);
				y = y->nastepna;
			}
			x = x->nastepna;
		}
		a = a->nastepny;
	}
}

void zamienGazety(struct Gazeta *a, struct Gazeta *b)
{
	struct Gazeta pom = *a;
	strcpy(a->nazwa, b->nazwa);
	strcpy(a->numer, b->numer);
	strcpy(a->czestosc, b->czestosc);
	strcpy(b->nazwa, pom.nazwa);
	strcpy(b->numer, pom.numer);
	strcpy(b->czestosc, pom.czestosc);
}

void zamienDzialy(struct Dzial *a, struct Dzial *b)
{
	struct Dzial pom = *a;
	strcpy(a->nazwa, b->nazwa);
	a->pierwsza = b->pierwsza;
	strcpy(b->nazwa, pom.nazwa);
	b->pierwsza = pom.pierwsza;
}
